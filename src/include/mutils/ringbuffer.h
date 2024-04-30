/**
 * libmutils
 * @file ringbuffer.h
 *
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date April 2024
 *
 * @brief Ringbuffer data structure
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Ringbuffer structure
*/
typedef struct _ringbuffer {
	void *_data;
	size_t _size;
	size_t _head;
	size_t _tail;
	bool _full;
	bool _empty;
} ringbuffer_t;

/**
 * @brief Initializes the ringbuffer
 * 
 * @param buffer Pointer to a ringbuffer structure
 * @param size   Size of the buffer (in bytes)
 * 
 * @return int errno on malloc error, 0 on success
*/
int ringbuffer_init(ringbuffer_t *buffer, const size_t size);

/**
 * @brief Writes into the ringbuffer
 * 
 * @param buffer Pointer to a ringbuffer structure
 * @param source Pointer to the data source
 * @param size   Size to write from source to buffer (in bytes)
 * 
 * @return size_t Number of bytes written
*/
size_t ringbuffer_write(ringbuffer_t *buffer, const void *source, const size_t size);

/**
 * @brief Reads from the ringbuffer
 * 
 * @param buffer Pointer to a ringbuffer structure
 * @param dest   Pointer to the data destination
 * @param size   Size to read from buffer to dest (in bytes)
 * 
 * @return size_t Number of bytes read
*/
size_t ringbuffer_read(ringbuffer_t *buffer, void *dest, const size_t size);

/**
 * @brief Verifies if the ringbuffer is empty
 * 
 * @param buffer Pointer to a ringbuffer structure
 * 
 * @return bool True if empty
*/
bool ringbuffer_empty(ringbuffer_t *buffer);

/**
 * @brief Verifies if the ringbuffer is full
 * 
 * @param buffer Pointer to a ringbuffer structure
 * 
 * @return bool True if full
*/
bool ringbuffer_full(ringbuffer_t *buffer);

/**
 * @brief Destroys the ringbuffer
 * 
 * @param buffer Pointer to a ringbuffer structure
*/
void ringbuffer_destroy(ringbuffer_t *buffer);
