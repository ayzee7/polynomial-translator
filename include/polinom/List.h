#ifndef LIST_H
#define LIST_H

#include <iostream>

/*template <class T>
class List;

template <class T>
class Node {
protected:
	Node* next;
	
public:
	T value;
	Node(T value, Node* next) : value(value), next(next) {}

	friend class List<T>;
};*/

template <class T>
class List {

	template <class T>
	struct Node {
		Node* next;
		T val;
		Node(T value, Node* next) : val(value), next(next) {}
	};

	Node<T>* first = nullptr;
	size_t sz = 0;

public:
	List(size_t n = 0) {
		if (n > INT_MAX) {
			throw "Invalid list size";
		}
		while (n--) {
			Node<T>* tmp = new Node<T>(T(), first);
			first = tmp;
			sz++;
		}
	}

	~List() {
		sz = 0;
		Node<T>* curr;
		while (first != nullptr) {
			curr = first->next;
			delete first;
			first = curr;
		}
	}

	List(const List& other): sz(other.sz) {
		if (other.first != nullptr) {
			Node<T>* curr1 = other.first;
			Node<T>* curr2 = new Node<T>(curr1->val, nullptr);
			first = curr2;
			while (curr1 != nullptr) {
				Node<T>* next1 = curr1->next;
				if (next1 == nullptr) {
					break;
				}
				curr2->next = new Node<T>(next1->val, nullptr);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
	}

	List& operator=(const List& other) {
		if (&other != this) {
			sz = other.sz;
			if (other.first != nullptr) {
				Node<T>* curr1 = other.first;
				Node<T>* curr2 = new Node<T>(curr1->val, nullptr);
				first = curr2;
				while (curr1 != nullptr) {
					Node<T>* next1 = curr1->next;
					if (next1 == nullptr) {
						break;
					}
					curr2->next = new Node<T>(next1->val, nullptr);
					curr2 = curr2->next;
					curr1 = curr1->next;
				}
			}
		}
		return *this;
	}

	struct Iterator {
		Iterator(Node<T>* pointer) : ptr(pointer) {}

		Node<T>& operator*() const { return *ptr; }
		Node<T>* operator->() { return ptr; }

		Iterator& operator++() { 
			ptr = ptr->next;
			return *this; 
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator next() {
			return ptr->next;
		}

		T value() { return ptr->val; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	private:
		Node<T>* ptr;
	};

	Iterator begin() const { return Iterator(first); }
	Iterator end() const { return Iterator(nullptr); }

	void print() {
		if (sz == 1 && !first->val.get_coef()) {
			std::cout << "0";
		}
		else {
			size_t zero_counter = 0;
			for (Iterator i = this->begin(); i != this->end(); ++i) {
				if (i.value().get_coef()) {
					std::cout << i.value();
					if (i.next() != this->end()) {
						if (i.next().value().get_coef() > 0) {
							std::cout << "+";
						}
						else if (i.next().value().get_coef() < 0) {
							std::cout << "-";
						}
					}
				}
				else {
					zero_counter++;
				}
			}
			if (zero_counter == sz) {
				std::cout << "0";
			}
		}
		std::cout << std::endl;
	}


	size_t size() const {
		return sz;
	}

	List(List&& other) noexcept {
		sz = other.sz;
		first = other.first;
		other.first = nullptr;
	}

	Iterator operator[](size_t ind) {
		Iterator it = this->begin();
		for (size_t i = 0; i < ind; ++i, ++it);
		return it;
	}

	Iterator insert_after(T data, Iterator prev) {
		if (prev == nullptr) {
			throw "Invalid node pointer";
		}
		Node<T>* tmp = new Node<T>(data, nullptr);
		tmp->next = prev->next;
		prev->next = tmp;
		sz++;
		return Iterator(tmp);
	}

	Iterator insert_front(T data) {
		sz++;
		first = new Node<T>(data, first);
		return Iterator(first);
	}

	Iterator erase_after(Iterator prev) {
		if (prev == nullptr) {
			throw "Invalid node pointer";
		}
		Node<T>* tmp = prev->next;
		Node<T>* tmp_copy(tmp);
		if (tmp) {
			sz--;
			prev->next = prev->next->next;
			delete tmp;
		}
		return Iterator(tmp_copy);
	}

	Iterator erase_front() {
		sz--;
		Node<T>* front_copy = first;
		first = first->next;
		return Iterator(front_copy);
	}

	Iterator find(T val) {
		for (Iterator it = this->begin(); it != this->end(); ++it) {
			if (it.value() == val) {
				return it;
			}
		}
		return this->end();
	}

	void clear() {
		first = nullptr;
		sz = 0;
	}

	bool empty() {
		return first ? false : true;
	}
};

#endif