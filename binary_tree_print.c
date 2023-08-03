#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

/* Original code from http://stackoverflow.com/a/13755911/5184480 */

/**
 * print_t - Stores recursively each level in an array of strings
 *
 * @tree: Pointer to the node to print
 * @offset: Offset to print
 * @depth: Depth of the node
 * @s: Buffer
 *
 * Return: length of printed tree after process
 */
static int print_t(const binary_tree_t *tree, int offset, int depth, char **s)
{
	char b[6];
	int width, left, right, is_left, p;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offset, depth + 1, s);
	right = print_t(tree->right, offset + left + width, depth + 1, s);
	for (p = 0; p < width; p++)
		s[depth][offset + left + p] = b[p];
	if (depth && is_left)
	{
		for (p = 0; p < width + right; p++)
			s[depth - 1][offset + left + width / 2 + p] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (p = 0; p < left + width; p++)
			s[depth - 1][offset - width / 2 + p] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * _height - Measures the height of a binary tree
 *
 * @tree: Pointer to the node to measures the height
 *
 * Return: The height of the tree starting at @node
 */
static size_t _height(const binary_tree_t *tree)
{
	size_t height_right;
	size_t height_left;

	height_left = tree->left ? 1 + _height(tree->left) : 0;
	height_right = tree->right ? 1 + _height(tree->right) : 0;
	return (height_left > height_right ? height_left : height_right);
}

/**
 * binary_tree_print - Prints a binary tree
 *
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, c, p;

	if (!tree)
		return;
	height = _height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (c = 0; c < height + 1; c++)
	{
		s[c] = malloc(sizeof(**s) * 255);
		if (!s[c])
			return;
		memset(s[c], 32, 255);
	}
	print_t(tree, 0, 0, s);
	for (c = 0; c < height + 1; c++)
	{
		for (p = 254; p > 1; --p)
		{
			if (s[c][p] != ' ')
				break;
			s[c][p] = '\0';
		}
		printf("%s\n", s[c]);
		free(s[c]);
	}
	free(s);
}
