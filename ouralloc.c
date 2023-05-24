#include "ourshel.h"

/**
 * _memf - fills memory with a constant byte
 * @v: the pointer to the memory area
 * @u: the byte to fill *v with
 * @m: the amount of bytes to be filled
 * Return: (v) a pointer to the memory area v
 */
char *_memf(char *v, char u, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		v[j] = u;
	return (v);
}

/**
 * frye - frees a string of strings
 * @uv: string of strings
 */
void frye(char **uv)
{
	char **z = uv;

	if (!uv)
		return;
	while (*uv)
		free(*uv++);
	free(z);
}

/**
 * _realm - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @pre_size: byte size of previous block
 * @post_size: byte size of new block
 *
 * Return: pointer to the pre'block name.
 */
void *_realm(void *pointer, unsigned int pre_size, unsigned int post_size)
{
	char *q;

	if (!pointer)
		return (malloc(post_size));
	if (!post_size)
		return (free(pointer), NULL);
	if (post_size == pre_size)
		return (pointer);

	q = malloc(post_size);
	if (!q)
		return (NULL);

	pre_size = pre_size < post_size ? pre_size : post_size;
	while (pre_size--)
		q[pre_size] = ((char *)pointer)[pre_size];
	free(pointer);
	return (q);
}
