#include "binary_trees.h"

/**
 * binary_tree_height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height.
 *
 * Return: If tree is NULL, your function must return 0, else return height.
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
	if (tree)
	{
		size_t left_size = 0, right_size = 0;

		right_size = tree->right ? 1 + binary_tree_height(tree->right) : 0;
		left_size = tree->left ? 1 + binary_tree_height(tree->left) : 0;
		return ((left_size > right_size) ? left_size : right_size);
	}
	return (0);
}
