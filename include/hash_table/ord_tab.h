#include "ord_arr.h"

template <class TKey, class TValue>
class OrderedHashTable {

	std::vector<std::pair<size_t, TValue>> data;

public:

	struct Iterator {
		Iterator(std::pair<size_t, TValue>* pointer) : ptr(pointer) {}

		std::pair<size_t, TValue>& operator*() const { return *ptr; }
		std::pair<size_t, TValue>* operator->() { return ptr; }

		Iterator& operator++() {
			ptr++;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		size_t key() { return ptr->first; }
		TValue& value() { return ptr->second; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	private:
		std::pair<size_t, TValue>* ptr;
	};

	Iterator begin() {
		if (!data.size()) return Iterator(nullptr);
		return Iterator(&data[0]);
	}
	Iterator end() {
		if (!data.size()) return Iterator(nullptr);
		return ++Iterator(&*(data.end() - 1));
	}

	Iterator insert(const TKey& key, const TValue& value) {
		size_t hash_key = std::hash<TKey>{}(key);
		auto elem = std::make_pair(hash_key, value);
		int insert_index = 0;
		if (data.begin() == data.end() || elem.first > data[data.size() - 1].first) {
			data.push_back(elem);
			return Iterator(&data[data.size() - 1]);
		}
		else {
			for (int i = 0; i < data.size(); i++) {
				if (elem.first < data[i].first) {
					insert_index = i;
					data.push_back(elem);
					for (int j = data.size() - 1; j > i; j--) {
						std::swap(data[j], data[j - 1]);
					}
					break;
				}
				else if (elem.first == data[i].first) {
					throw "Cannot overwrite existing key, must delete it first.";
				}
			}
			return Iterator(&data[insert_index]);
		}
	}

	Iterator erase(const TKey& key) {
		size_t hash_key = std::hash<TKey>{}(key);
		int erase_index = -1;
		for (int i = 0; i < data.size(); i++) {
			if (hash_key == data[i].first) {
				erase_index = i;
				for (int j = i; j < data.size() - 1; j++) {
					std::swap(data[j], data[j + 1]);
				}
				data.pop_back();
				break;
			}
		}
		if (erase_index == -1 || erase_index == data.size()) {
			return end();
		}
		return Iterator(&data[erase_index]);
	}

	Iterator find(const TKey& key) {
		size_t hash_key = std::hash<TKey>{}(key);
		for (int i = 0; i < data.size(); i++) {
			if (data[i].first == hash_key) {
				return Iterator(&data[i]);
			}
		}
		return end();
	}

	size_t size() {
		return data.size();
	}

	TValue& operator[](const TKey& key) {
		auto it = find(key);
		if (it == end()) throw "Index overflow.";
		return it.value();
	}

	bool empty() {
		return data.size() ? false : true;
	}

};