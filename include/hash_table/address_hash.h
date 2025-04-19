#pragma once
#include <vector>

template <class TKey, class TValue>
class AddressHashTable {

	enum class Status {
		EMPTY,
		OCCUPIED,
		ERASED
	};

	template <class TKey, class TValue>
	struct Entry {
		TKey key;
		TValue value;
		Status status;

		Entry() : status(Status::EMPTY) {}
		Entry(TKey key, TValue value) : key(key), value(value), status(Status::EMPTY) {}
	};

	size_t m;
	size_t n = 0;
	std::vector<Entry<TKey, TValue>> data;

	size_t hash1(TKey key) {
		size_t hash = 5381;
		for (auto& c : key) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash % m;
	}

	size_t hash1(TKey key, size_t table_size) {
		size_t hash = 5381;
		for (auto& c : key) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash % table_size;
	}

	size_t hash2(TKey key) {
		size_t hash = 0;
		for (auto& c : key) {
			hash = hash * 31 + c;
		}
		size_t result = 11 - (hash % 11);
		return result == 0 ? 1 : result;
	}

	size_t probe(TKey key, size_t att) {
		return (hash1(key) + att * hash2(key)) % m;
	}

	size_t probe(TKey key, size_t att, size_t table_size) {
		return (hash1(key, table_size) + att * hash2(key)) % table_size;
	}

	void repack() {
		std::vector<Entry<TKey, TValue>> data_new(m * 2);
		for (size_t i = 0; i < m; ++i) {
			if (data[i].status != Status::EMPTY) {
				for (size_t j = 0; j < m; ++j) {
					size_t index = probe(data[i].key, j, m * 2);
					if (data_new[index].status != Status::OCCUPIED) {
						if (data[i].status == Status::OCCUPIED) {
							data_new[index] = Entry<TKey, TValue>(data[i].key, data[i].value);
						}
						data_new[index].status = data[i].status;
						break;
					}
				}
			}
		}
		data = std::move(data_new);
		m *= 2;
	}

public: 

	AddressHashTable(size_t m = 128) {
		this->m = m;
		for (size_t i = 0; i < m; i++) {
			Entry<TKey, TValue> entry;
			data.push_back(entry);
		}
	}

	struct Iterator {
		Iterator(Entry<TKey, TValue>* pointer, Entry<TKey, TValue>* pointer_last) : ptr(pointer), ptr_last(pointer_last) {}

		Entry<TKey, TValue>& operator*() const { return *ptr; }
		Entry<TKey, TValue>* operator->() { return ptr; }

		Iterator& operator++() {
			do {
				ptr++;
				if (ptr > ptr_last) {
					break;
				}
			} while (ptr->status != Status::OCCUPIED);
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		TKey key() { return ptr->key; }
		TValue& value() { return ptr->value; }
		Status status() { return ptr->status; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	private:
		Entry<TKey, TValue>* ptr;
		Entry<TKey, TValue>* ptr_last;
	};

	Iterator begin() {
		for (size_t i = 0; i < m; i++) {
			if (data[i].status == Status::OCCUPIED) {
				return Iterator(&data[i], &data[data.size() - 1]);
			}
		}
		return end();
	}
	Iterator end() {
		if (!n) return Iterator(nullptr, &data[data.size() - 1]);
		return ++Iterator(&*(data.end() - 1), &data[data.size() - 1]);
	}

	Iterator insert(const TKey& key, const TValue& value) {
		for (size_t i = 0; i < m; i++) {
			size_t index = probe(key, i);
			if (data[index].key == key) {
				throw "Cannot overwrite existing key, must delete it first.";
			}
			if (data[index].status != Status::OCCUPIED) {
				data[index] = Entry<TKey, TValue>(key, value);
				data[index].status = Status::OCCUPIED;
				n++;
				if ((float)n / (float)m > 0.8) {
					repack();
				}
				return Iterator(&data[index], &data[data.size() - 1]);
			}
		}
		return end();
	}
	
	Iterator erase(const TKey& key) {
		for (size_t i = 0; i < m; i++) {
			size_t index = probe(key, i);
			if (data[index].status == Status::EMPTY) {
				return end();
			}
			if (data[index].key == key) {
				Entry<TKey, TValue> entry;
				entry.status = Status::ERASED;
				data[index] = entry;
				return Iterator(&data[index], &data[data.size() - 1]);
				n--;
			}
		}
		return end();
	}

	Iterator find(const TKey& key) {
		for (size_t i = 0; i < m; i++) {
			size_t index = probe(key, i);
			if (data[index].status == Status::EMPTY) {
				return end();
			}
			if (data[index].key == key) {
				return Iterator(&data[index], &data[data.size() - 1]);
			}
		}
		return end();
	}

	size_t size() {
		return n;
	}

	TValue& operator[](const TKey& key) {
		auto it = find(key);
		if (it == end()) throw "Index overflow.";
		return it.value();
	}

	Iterator& operator[](size_t index) {
		return Iterator(&data[index], &data[data.size() - 1]);
	}

	bool empty() {
		return n ? false : true;
	}
};