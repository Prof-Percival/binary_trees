#include "binary_trees.h"

/**
 * _sorted_array_to_avl - helper func for sorted_array_to_avl
 * @array: input array
 * @start: starting index
 * @end: ending index
 * @parent: pointer to parent node
 * Return: newly created node
 */
avl_t *_sorted_array_to_avl(int *array, int start, int end, avl_t *parent)
{
	avl_t *new_node;
	int middle;

	if (start > end)
		return (NULL);
	middle = (start + end) / 2;
	new_node = calloc(1, sizeof(avl_t));
	if (!new_node)
		return (NULL);
	new_node->n = array[middle];
	new_node->parent = parent;
	new_node->left = _sorted_array_to_avl(array, start, middle - 1, new_node);
	new_node->right = _sorted_array_to_avl(array, middle + 1, end, new_node);
	return (new_node);
}


/**
 * sorted_array_to_avl - builds an AVL tree from an array
 * @array: input array
 * @size: size of array
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{

	if (!array)
		return (NULL);
	return (_sorted_array_to_avl(array, 0, size - 1, NULL));
}
