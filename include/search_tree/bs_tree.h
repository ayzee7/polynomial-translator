#pragma once
#include <algorithm>

template <class TKey, class TValue>
class BSTree {

protected:

	template<class TKey, class TValue>
	struct Node {

		TKey key;
		TValue value;
		Node* left, * right, * parent;

		Node(const TKey& key, const TValue& value): key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}

	};

	Node<TKey, TValue>* root_node = nullptr;

	Node<TKey, TValue>* grandparent(Node<TKey, TValue>* curr) {
		if (curr->parent)
			return curr->parent->parent;
		else return nullptr;
	}

	Node<TKey, TValue>* sibling(Node<TKey, TValue>* curr) {
		if (!curr->parent)
			return nullptr;
		else if (curr == curr->parent->left)
			return curr->parent->right;
		else return curr->parent->left;
	}

	Node<TKey, TValue>* uncle(Node<TKey, TValue>* curr) {
		if (curr->parent)
			return sibling(curr->parent);
		else return nullptr;
	}

	Node<TKey, TValue>* find(const TKey& key, Node<TKey, TValue>* curr) {
		if (!curr) return nullptr;
		else if (key == curr->key) return curr;
		else if (key > curr->key) return find(key, curr->right);
		return find(key, curr->left);
	}

	Node<TKey, TValue>* insert(const TKey& key, const TValue& value, Node<TKey, TValue>* curr) {
		if (!curr) return new Node<TKey, TValue>(key, value);
		else if (key == curr->key) throw "Cannot overwrite existing key, must delete it first.";
		else if (key < curr->key) {
			curr->left = insert(key, value, curr->left);
			curr->left->parent = curr;
		}
		else if (key > curr->key) {
			curr->right = insert(key, value, curr->right);
			curr->right->parent = curr;
		}
		return curr;
	}

	Node<TKey, TValue>* erase(const TKey& key, Node<TKey, TValue>* curr) {
		if (!curr) {
			return nullptr;
		}
		else if (key < curr->key) {
			curr->left = erase(key, curr->left);
		}
		else if (key > curr->key) {
			curr->right = erase(key, curr->right);
		}
		else if (!curr->left && !curr->right) {
			delete curr;
			return nullptr;
		}
		else if (!curr->right) {
			Node<TKey, TValue>* tmp = curr->left;
			tmp->parent = curr->parent;
			delete curr;
			return tmp;
		}
		else {
			Node<TKey, TValue>* m = find_min(curr->right);
			curr->key = m->key;
			curr->value = m->value;
			curr->right = erase(m->key, curr->right);
		}
		return curr;
	}

	Node<TKey, TValue>* find_min(Node<TKey, TValue>* curr) {
		Node<TKey, TValue>* min = curr;
		while (min->left) {
			min = min->left;
		}
		return min;
	}

	void print(Node<TKey, TValue>* curr) {
		if (!curr) return;
		print(curr->left);
		std::cout << curr->key << " ";
		print(curr->right);
	}

	void print_keys(Node<TKey, TValue>* curr, std::vector<TKey>& keys) {
		if (!curr) return;
		print_keys(curr->left, keys);
		keys.push_back(curr->key);
		print_keys(curr->right, keys);
	}

	void rotate_left(Node<TKey, TValue>* curr) {
		curr->parent->right = curr->left;
		if (curr->left)
			curr->left->parent = curr->parent;
		curr->left = curr->parent;
		Node<TKey, TValue>* gp = grandparent(curr);
		curr->parent->parent = curr;
		if (gp) {
			if (gp->left == curr->parent) {
				gp->left = curr;
			}
			else gp->right = curr;
			curr->parent = gp;
		}
		else {
			root_node = curr;
			curr->parent = nullptr;
		}
	}

	void rotate_right(Node<TKey, TValue>* curr) {
		curr->parent->left = curr->right;
		if (curr->right)
			curr->right->parent = curr->parent;
		curr->right = curr->parent;
		Node<TKey, TValue>* gp = grandparent(curr);
		curr->parent->parent = curr;
		if (gp) {
			if (gp->left == curr->parent) {
				gp->left = curr;
			}
			else gp->right = curr;
			curr->parent = gp;
		}
		else {
			root_node = curr;
			curr->parent = nullptr;
		}
	}

	void is_balanced(Node<TKey, TValue>* curr, std::vector<int>& lens, int k) {
		if (!curr) {
			lens.push_back(k);
		}
		else {
			k++;
			is_balanced(curr->left, lens, k);
			is_balanced(curr->right, lens, k);
		}
	}

public:

	struct Iterator {
		Iterator(Node<TKey, TValue>* pointer) : ptr(pointer) {}

		Node<TKey, TValue>& operator*() const { return *ptr; }
		Node<TKey, TValue>* operator->() { return ptr; }

		Iterator& operator++() {
			if (ptr->right) {
				ptr = ptr->right;
				while (ptr->left) {
					ptr = ptr->left;
				}
			}
			else {
				if (ptr->parent) {
					while (ptr != ptr->parent->left) {
						ptr = ptr->parent;
						if (!ptr->parent) break;
					}
				}
				if (ptr->parent)
					ptr = ptr->parent;
				else ptr = nullptr;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator left() {
			return ptr->left;
		}

		Iterator right() {
			return ptr->right;
		}

		Iterator parent() {
			return ptr->parent;
		}

		TKey key() {
			return ptr->key;
		}

		TValue value() {
			return ptr->value;
		}

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	private:
		Node<TKey, TValue>* ptr;
	};

	Iterator begin() { 
		if (!root_node) return Iterator(nullptr);
		return Iterator(find(print_keys()[0])); 
	}
	Iterator root() { return Iterator(root_node); }
	Iterator null() { return Iterator(nullptr); }

	void print() {
		print(root_node);
	}

	std::vector<TKey> print_keys() {
		std::vector<TKey> keys;
		print_keys(root_node, keys);
		return keys;
	}

	Iterator find(const TKey& key) {
		return Iterator(find(key, root_node));
	}

	virtual Iterator insert(const TKey& key, const TValue& value) {
		root_node = insert(key, value, root_node);
		return find(key);
	}

	virtual Iterator erase(const TKey& key) {
		root_node = erase(key, root_node);
		return root();
	}

	bool is_balanced() {
		if (!root_node) {
			return true;
		}
		int k = 0;
		std::vector<int> lens;
		is_balanced(root_node->left, lens, k);
		is_balanced(root_node->right, lens, k);
		std::sort(lens.begin(), lens.end());
		if (std::abs(lens[0] - lens[lens.size() - 1]) > 1) {
			return false;
		}
		else return true;
	}

};