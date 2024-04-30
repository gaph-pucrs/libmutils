/**
 * libmutils
 * @file ringbuffer.c
 *
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date April 2024
 *
 * @brief Ringbuffer data structure
 */

#include <mutils/ringbuffer.h>

#include <string.h>
#include <stdlib.h>
#include <errno.h>

int ringbuffer_init(ringbuffer_t *buffer, const size_t size)
{
	buffer->_data = malloc(size);
	if (buffer->_data == NULL)
		return errno;

	buffer->_head  = 0;
	buffer->_tail  = 0;
	buffer->_full  = false;
	buffer->_empty = true;
	buffer->_size  = size;

	return 0;
}

size_t ringbuffer_write(ringbuffer_t *buffer, const void *source, const size_t size)
{
	/* If the buffer is full don't even try to write data */
	if (buffer->_full)
		return 0;

	/* Cap the transfer size to the buffer size if needed */
	size_t write_size = size;
	if (write_size > buffer->_size)
		write_size = buffer->_size;

	/**
	 * The copy occurs from tail to top, and from bottom to head.
	 * If the head is ahead of the tail, the top is the head and no transfer is 
	 * made at the bottom.
	 * Otherwise, the top is the buffer size and the bottom is the head.
	*/
	size_t top = buffer->_size;
	size_t bot_size = 0;
	if (buffer->_head > buffer->_tail)
		top = buffer->_head;
	else
		bot_size = buffer->_head;

	/* Compute the size from tail to top cap to buffer size if needed    */
	size_t top_size = top - buffer->_tail;
	if (top_size > write_size)
		top_size = write_size;

	/* Compute the size from bottom to head cap to buffer size if needed */
	size_t rem_size = (write_size - top_size);
	if (bot_size > rem_size)
		bot_size = rem_size;

	/* Transfer top and bottom */
	memcpy(buffer->_data + buffer->_tail, source, top_size);
	memcpy(buffer->_data, source + top_size, bot_size);

	/* Compute the number of bytes transferred and move the tail */
	size_t xferred = (top_size + bot_size);
	buffer->_tail += xferred;
	buffer->_tail %= buffer->_size;

	/* After a write, the buffer is full if head and tail are at the same place */
	/* But after a write, the buffer is never emtpy 							*/
	buffer->_full  = (buffer->_tail == buffer->_head);
	buffer->_empty = false;
	
	return xferred;
}

size_t ringbuffer_read(ringbuffer_t *buffer, void *dest, const size_t size)
{
	/* If the buffer is full don't even try to read data */
	if (buffer->_empty)
		return 0;

	/* Cap the transfer size to the buffer size if needed */
	size_t read_size = size;
	if (read_size > buffer->_size)
		read_size = buffer->_size;

	/**
	 * The copy occurs from head to top, and from bottom to tail.
	 * If the tail is ahead of the head, the top is the tail and no transfer is 
	 * made at the bottom.
	 * Otherwise, the top is the buffer size and the bottom is the tail.
	*/
	size_t top = buffer->_size;
	size_t bot_size = 0;
	if (buffer->_tail > buffer->_head)
		top = buffer->_tail;
	else
		bot_size = buffer->_tail;

	/* Compute the size from head to top and cap to buffer size if needed    */
	size_t top_size = top - buffer->_head;
	if (top_size > read_size)
		top_size = read_size;

	/* Compute the size from bottom to tail and cap to buffer size if needed */
	size_t rem_size = (read_size - top_size);
	if (bot_size > rem_size)
		bot_size = rem_size;

	/* Transfer top and bottom */
	memcpy(dest, buffer->_data + buffer->_head, top_size);
	memcpy(dest + top_size, buffer->_data, bot_size);

	/* Compute the number of bytes transferred and move the head */
	size_t xferred = (top_size + bot_size);
	buffer->_head += xferred;
	buffer->_head %= buffer->_size;

	/* After a read, the buffer is empty if head and tail are at the same place */
	/* But after a read, the buffer is never full	 							*/
	buffer->_full  = false;
	buffer->_empty = (buffer->_tail == buffer->_head);
	
	return xferred;
}

bool ringbuffer_empty(ringbuffer_t *buffer)
{
	return buffer->_empty;
}

bool ringbuffer_full(ringbuffer_t *buffer)
{
	return buffer->_full;
}

void ringbuffer_destroy(ringbuffer_t *buffer)
{
	free(buffer->_data);
	buffer->_data = NULL;
	buffer->_size = 0;
	buffer->_head = 0;
	buffer->_tail = 0;
	buffer->_full = true;
	buffer->_empty = true;
}
