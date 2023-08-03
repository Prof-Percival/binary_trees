#include "binary_trees.h"
#include "limits.h"

size_t height(const binary_tree_t *tree);
int is_avl_helper(const binary_tree_t *tree, int lo, int hi);
int binary_tree_is_avl(const binary_tree_t *tree);

/**
 * height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height.
 *
 * Return: If tree is NULL, your function must return 0, else return height.
 */
size_t height(const binary_tree_t *tree)
{
	if (tree)
	{
		size_t left_size = 0, right_size = 0;

		left_size = tree->left ? 1 + height(tree->left) : 1;
		right_size = tree->right ? 1 + height(tree->right) : 1;
		return ((left_size > right_size) ? left_size : right_size);
	}
	return (0);
}

/**
 * is_avl_helper - Checks if a binary tree is a valid AVL tree.
 * @tree: A pointer to the root node of the tree to check.
 * @lo: The value of the smallest node visited thus far.
 * @hi: The value of the largest node visited this far.
 *
 * Return: If the tree is a valid AVL tree, 1, otherwise, 0.
 */
int is_avl_helper(const binary_tree_t *tree, int lo, int hi)
{
	size_t left_hand_gt, right_hand_gt, difference;

	if (tree != NULL)
	{
		if (tree->n < lo || tree->n > hi)
			return (0);
		left_hand_gt = height(tree->left);
		right_hand_gt = height(tree->right);
		difference = left_hand_gt > right_hand_gt ? left_hand_gt - right_hand_gt : right_hand_gt - left_hand_gt;
		if (difference > 1)
			return (0);
		return (is_avl_helper(tree->left, lo, tree->n - 1) &&
			is_avl_helper(tree->right, tree->n + 1, hi));
	}
	return (1);
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL tree.
 * @tree: A pointer to the root node of the tree to check.
 *
 * Return: 1 if tree is a valid AVL tree, and 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (is_avl_helper(tree, INT_MIN, INT_MAX));
}
