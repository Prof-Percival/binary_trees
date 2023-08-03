#include "binary_trees.h"
#include<stdlib.h>
#include<string.h>
#define INIT_NODE {0, NULL, NULL, NULL}

/**
 * swap - swaps two nodes in binary tree
 * @a: first node
 * @b: second node
 * Return: pointer to root
 */
bst_t *swap(bst_t *a, bst_t *b)
{
	bst_t node_copy = INIT_NODE;

	node_copy.n = a->n;
	node_copy.parent = a->parent;
	node_copy.left = a->left;
	node_copy.right = a->right;
	a->parent = b;
	a->left = b->left;
	a->right = b->right;
	if (b->left)
		b->left->parent = a;
	if (b->right)
		b->right->parent = a;

	b->parent = node_copy.parent;
	if (node_copy.parent)
	{
		if (a == node_copy.parent->left)
			node_copy.parent->left = b;
		else
			node_copy.parent->right = b;
	}
	if (b == node_copy.left)
	{
		b->left = a;
		b->right = node_copy.right;
		if (node_copy.right)
			node_copy.right->parent = b;
	}
	else if (b == node_copy.right)
	{
		b->right = a;
		b->left = node_copy.left;
		if (node_copy.left)
			node_copy.left->parent = b;
	}
	while (b->parent)
		b = b->parent;
	return (b);
}

/**
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 * @lowercase: flag if hexa values need to be lowercase
 * Return: result string
 */
char *convert(unsigned long int num, int base, int lowercase)
{
	static char *rep;
	static char buffer[50];
	char *pointer;

	rep = (lowercase)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = 0;
	do {
		*--pointer = rep[num % base];
		num /= base;
	} while (num);

	return (pointer);
}

/**
 * binary_tree_size - measures the size of a binary tree
 * @tree: input binary tree
 * Return: number of descendant child nodes
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * insert - helper func to insert node to correct location
 * @root: double pointer to root of max heap
 * @node: node to insert
 */
void insert(heap_t **root, heap_t *node)
{
	heap_t *tmp;
	int size;
	unsigned int i;
	char *binary;
	char c;

	tmp = *root;
	size = binary_tree_size(tmp) + 1;
	binary = convert(size, 2, 1);
	for (i = 1; i < strlen(binary); i++)
	{
		c = binary[i];
		if (i == strlen(binary) - 1)
		{
			if (c == '1')
			{
				node->parent = tmp;
				tmp->right = node;
				break;
			}
			else if (c == '0')
			{
				node->parent = tmp;
				tmp->left = node;
				break;
			}
		}
		if (c == '1')
			tmp = tmp->right;
		else if (c == '0')
			tmp = tmp->left;
	}
}


/**
 * heap_insert - inserts a value in Max Binary Heap
 * @root: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *ht = NULL, *ret;

	if (!root)
		return (NULL);
	ht = calloc(1, sizeof(heap_t));
	ht->n = value;
	if (!*root)
	{
		*root = ht;
		return (ht);
	}
	insert(root, ht);
	while (ht->parent && ht->n > ht->parent->n)
	{
		ret = swap(ht->parent, ht);
		if (ret)
			*root = ret;
	}
	return (ht);
}
