#pragma once
#include <vector>
#include <utility> 

template <class TKey, class TValue>
class UnorderedTable {
private:
    std::vector<std::pair<TKey, TValue>> data;

public:
    struct Iterator {
        Iterator(std::pair<TKey, TValue>* pointer) : ptr(pointer) {}


        std::pair<TKey, TValue>& operator*() const { return *ptr; }
        std::pair<TKey, TValue>* operator->() { return ptr; }

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }


        TKey key() { return ptr->first; }
        TValue& value() { return ptr->second; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

    private:
        std::pair<TKey, TValue>* ptr;
    };

    Iterator begin() 
    {
        if (!data.size()) return Iterator(nullptr);
        return Iterator(&data[0]);
    }
    Iterator end() 
    {
        if (!data.size()) return Iterator(nullptr);
        return Iterator(data.data() + data.size());
    }

    Iterator insert(const TKey& key, const TValue& value) 
    {   
        auto elem = std::make_pair(key, value);

        auto it_found = find(key);
        if (it_found != end()) throw 0;
        data.emplace_back(elem);

        return Iterator(&data[data.size()-1]);;
    }

    Iterator erase(const TKey& key) {
        if (data.empty()) return end();
        int erase_index = -1;
        size_t vector_size = data.size();
        for (size_t i = 0; i < vector_size; ++i)
        {
            if (data[i].first == key) 
            {
                erase_index = i;
                if (i < vector_size - 1) 
                    std::swap(data[i], data[vector_size - 1]);
                data.pop_back();

                if (i < data.size()) 
                    return Iterator(&data[erase_index]);
     
                else return end();
            }
        }
        return end();
    }

    Iterator find(const TKey& key) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first == key) {
                return Iterator(&data[i]);
            }
        }
        return end();
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    TValue& operator[](const TKey& key) {
        auto it = find(key);

        if (it == end()) throw 0;

        return it.value();
    }

};