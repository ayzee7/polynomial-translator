#pragma once
#include "bs_tree.h"

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue>
{
protected:
	void insert_balance(Node<TKey, TValue>* curr)
	{
		if (!curr->parent)
		{
			curr->color = BLACK;
			return;
		}
		if (curr->parent->color == BLACK) return;
		if(uncle(curr)->color == RED)
		{
			curr->parent->color = BLACK;
			uncle(curr)->color = BLACK;
			grandparent(curr)->color = RED;
			insert_balance(grandparent(curr));
			return;
		}
		if (curr->parent == grandparent(curr)->left)
		{
			if (curr == curr->parent->left)
			{
				grandparent(curr)->color = RED;
				curr->parent->color = BLACK;
				rotate_right(grandparent(curr));
			}
			if (curr == curr->parent->right)
			{
				rotate_left(curr->parent);
				curr->color = BLACK;
				grandparent(curr)->color = RED;
				rotate_right(grandparent(curr));
			}
		}
		else
		{
			if (curr == curr->parent->right)
			{
				grandparent(curr)->color = RED;
				curr->parent->color = BLACK;
				rotate_left(grandparent(curr));
			}
			if (curr == curr->parent->left)
			{
				rotate_right(curr->parent);
				curr->color = BLACK;
				grandparent(curr)->color = RED;
				rotate_left(grandparent(curr));
			}
		}
		return;
	}
	void delete_balance(Node<TKey, TValue>* curr)
	{
		if (!curr->parent) return;
		if (sibling(curr)->color == RED)
		{
			curr->parent->color = RED;
			sibling(curr)->color = BLACK;
			if (curr == curr->parent->left) rotate_left(curr->parent);
			else rotate_right(curr->parent);
		}
		if (sibling(curr)->color == BLACK && curr->parent->color == BLACK && sibling(curr)->right->color == BLACK && sibling(curr)->left->color == BLACK)
		{
			sibling(curr)->color = RED;
			delete_balance(curr->parent);
			return;
		}
		if (sibling(curr)->color == BLACK && curr->parent->color == RED && sibling(curr)->right->color == BLACK && sibling(curr)->left->color == BLACK)
		{
			sibling(curr)->color = RED;
			curr->parent->color = BLACK;
			return;
		}
		if (curr == curr->parent->left)
		{
			if (sibling(curr)->left->color == RED && sibling(curr)->right->color == BLACK)
			{
				sibling(curr)->left->color = BLACK;
				sibling(curr)->color = RED;
				rotate_right(sibling(curr));
			}
			sibling(curr)->color = curr->parent->color;
			curr->parent->color = BLACK;
			sibling(curr)->right->color = BLACK;
			rotate_left(curr->parent);
			return;
		}
		else
		{
			if (sibling(curr)->left->color == BLACK && sibling(curr)->right->color == RED)
			{
				sibling(curr)->right->color = BLACK;
				sibling(curr)->color = RED;
				rotate_left(sibling(curr));
			}
			sibling(curr)->color = curr->parent->color;
			curr->parent->color = BLACK;
			sibling(curr)->left->color = BLACK;
			rotate_right(curr->parent);
			return;
		}
	}

	Iterator insert(const TKey& key, const TValue& value) override {
		root_node = BSTree<TKey, TValue>::insert(key, value, root_node);
		Node<TKey, TValue>* curr = find(key, root_node);
		insert_balance(curr);
		return Iterator(curr);
	}
	Iterator erase(const TKey& key) override {
		Node<TKey, TValue>* erased = find(key, root_node);
		Node<TKey, TValue>* sibl = sibling(erased);
		if (!erased->left && !erased->right && (sibl->left || sibl->right)) {
			root_node = BSTree<TKey, TValue>::erase(key, root_node);
			if (sibl->left)
				erase_balance(sibl->left);
			else erase_balance(sibl->right);
		}
		else {
			root_node = BSTree<TKey, TValue>::erase(key, root_node);
		}
		return root();
	}
};