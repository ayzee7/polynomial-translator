#pragma once
#include "bs_tree.h"
#include <algorithm>
#include <cmath>

template <class TKey, class TValue>
class AVLTree : public BSTree<TKey, TValue> {

	void balance(Node<TKey, TValue>* curr) {
		if (!curr) return;
		if (curr != root_node && curr->parent != root_node && !uncle(curr)) {
			if (curr == curr->parent->left) {
				if (curr->parent == grandparent(curr)->right) {
					rotate_right(curr);
					rotate_left(curr);
				}
				else {
					rotate_right(curr->parent);
				}
			}
			else {
				if (curr->parent == grandparent(curr)->left) {
					rotate_left(curr);
					rotate_right(curr);
				}
				else {
					rotate_left(curr->parent);
				}
			}
		}
		balance(curr->left);
		balance(curr->right);
	}

public:

	Iterator insert(const TKey& key, const TValue& value) override {
		root_node = BSTree<TKey, TValue>::insert(key, value, root_node);
		Node<TKey, TValue>* curr = find(key, root_node);
		balance(curr); 
		return Iterator(curr);
	}
	
	Iterator erase(const TKey& key) override {
		Node<TKey, TValue>* erased = find(key, root_node);
		Node<TKey, TValue>* sibl = sibling(erased);
		/*if (!erased->left && !erased->right && (sibl->left || sibl->right)) {
			root_node = BSTree<TKey, TValue>::erase(key, root_node);
			if (sibl->left)
				balance(sibl->left);
			else balance(sibl->right);
		}
		else {
			root_node = BSTree<TKey, TValue>::erase(key, root_node);
		}*/
		root_node = BSTree<TKey, TValue>::erase(key, root_node);
		balance(root_node);
		return root();
	}
};