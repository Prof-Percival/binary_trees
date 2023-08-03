#include "binary_trees.h"

#define INIT_NODE {0, NULL, NULL, NULL}

#define CONVERT "0123456789ABCDEF"

#define SETUP_NODE_BLOC { \
	tmp = *root; \
	size = binary_tree_size(*root); \
	binary = &buffer[49]; \
	*binary = 0; \
	}

#define FREE_NODE_BLOC { \
		res = tmp->n; \
		free(tmp); \
		*root = NULL; \
	}

#define SWAP_HEAD_BLOC { \
		head = *root; \
		head = swap_head(head, tmp); \
		res = head->n; \
		free(head); \
		*root = tmp; \
		tmp = perc_down(tmp); \
		*root = tmp; \
	}

#define CONVERT_LOOP { \
		*--binary = CONVERT[size % 2]; \
		size /= 2; \
	}

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
 * swap_head - helper func to swap head and node
 * @head: pointer to head
 * @node: pointer to node
 * Return: pointer to severed head of tree
 */
heap_t *swap_head(heap_t *head, heap_t *node)
{
	if (node->parent->left == node)
	{
		node->parent->left = NULL;
	} else
		node->parent->right = NULL;
	node->parent = NULL;
	node->left = head->left;
	node->right = head->right;
	if (head->left)
		head->left->parent = node;
	if (head->right)
		head->right->parent = node;
	return (head);
}

/**
 * perc_down - percolate head into correct position
 * @node: pointer to head
 * Return: pointer to head of tree
 */
heap_t *perc_down(heap_t *node)
{
	int max;
	heap_t *next_node = node;

	if (!node)
		return (NULL);
	max = node->n;
	if (node->left)
		max = MAX(node->left->n, max);
	if (node->right)
		max = MAX(node->right->n, max);
	if (node->left && max == node->left->n)
		next_node = node->left;
	else if (node->right && max == node->right->n)
		next_node = node->right;
	if (next_node != node)
	{
		swap(node, next_node);
		perc_down(node);
	}
	return (next_node);
}

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to root of tree
 * Return: value stored in the root node
 */
int heap_extract(heap_t **root)
{
	size_t size, p;
	char *binary, c, buffer[50];
	int res;
	heap_t *temp, *head;

	if (!root || !*root)
		return (0);
	SETUP_NODE_BLOC;
	if (size == 1)
	{
		FREE_NODE_BLOC;
		return (res);
	}
	do {
		CONVERT_LOOP;
	} while (size);

	for (p = 1; p < strlen(binary); p++)
	{
		c = binary[p];
		if (p == strlen(binary) - 1)
		{
			if (c == '1')
			{
				temp = temp->right;
				break;
			}
			else if (c == '0')
			{
				temp = temp->left;
				break;
			}
		}
		if (c == '1')
			temp = temp->right;
		else if (c == '0')
			temp = temp->left;
	}
	SWAP_HEAD_BLOC;
	return (res);
}
