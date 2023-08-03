#include "binary_trees.h"

/**
 * array_to_heap - builds a Max Binary Heap tree from an array
 * @array: input array
 * @size: size of array
 * Return: pointer to the root node of the created Binary Heap,
 * or NULL on failure
 */
heap_t *array_to_heap(int *array, size_t size)
{
	size_t c = 0;
	bst_t *root_node = NULL;

	if (!array)
		return (NULL);
	while (c < size)
	{
		heap_insert(&root_node, array[c]);
		c++;
	}
	return (root_node);
}
