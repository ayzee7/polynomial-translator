#pragma once
#include <vector>
#include <list>
#include <utility>


template <class TKey, class TValue, class THash = std::hash<TKey>>
class HashTableChaining {
private:

    std::vector<std::list<std::pair<TKey, TValue>>> buckets;
    THash hasher;
    size_t count;

    size_t hash_function(const TKey& key) const 
    {
        if (buckets.empty()) return 0;
        return hasher(key) % buckets.size();
    }

public:
    struct Iterator {
        Iterator(std::vector<std::list<std::pair<TKey, TValue>>>* b, size_t bucket_idx, typename std::list<std::pair<TKey, TValue>>::iterator chain_it)
            : p_buckets(b), current_bucket_idx(bucket_idx), current_chain_it(chain_it) {}

        Iterator(std::vector<std::list<std::pair<TKey, TValue>>>* b, size_t end_marker_idx): p_buckets(b), current_bucket_idx(end_marker_idx), current_chain_it() {}

        std::pair<TKey, TValue>& operator*() const { return *current_chain_it; }
        std::pair<TKey, TValue>* operator->() { return  &(*current_chain_it); }

        Iterator& operator++()
        {
            if (!p_buckets) return *this;
            if (current_bucket_idx < p_buckets->size()) 
            {
                ++current_chain_it;
                if (current_chain_it == (*p_buckets)[current_bucket_idx].end()) 
                {
                    ++current_bucket_idx;
                    while (current_bucket_idx < p_buckets->size() && (*p_buckets)[current_bucket_idx].empty()) ++current_bucket_idx;

                    if (current_bucket_idx < p_buckets->size()) current_chain_it = (*p_buckets)[current_bucket_idx].begin();
                }
            }
            return *this;
        }

        Iterator operator++(int) 
        {
            Iterator tmp = *this;
            ++(*this); 
            return tmp;
        }

        TKey key() const 
        {
            if (!p_buckets || current_bucket_idx >= p_buckets->size()) throw 0;
            return current_chain_it->first;
        }
        TValue& value() const 
        { 
            if (!p_buckets || current_bucket_idx >= p_buckets->size()) throw 0;
            return current_chain_it->second;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {

            if (a.p_buckets != b.p_buckets) return false;
            if (a.p_buckets == nullptr) return true;

            bool a_is_end = (a.current_bucket_idx >= a.p_buckets->size());
            bool b_is_end = (b.current_bucket_idx >= b.p_buckets->size());

            if (a_is_end && b_is_end) return true;
            if (a_is_end || b_is_end) return false;
            
            return a.current_bucket_idx == b.current_bucket_idx
                && a.current_chain_it == b.current_chain_it;
        };
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return !(a == b);
        };

    private:
        std::vector<std::list<std::pair<TKey, TValue>>>* p_buckets;
        size_t current_bucket_idx;
        typename std::list<std::pair<TKey, TValue>>::iterator current_chain_it;

        friend class HashTableChaining<TKey, TValue, THash>;
    };

    explicit HashTableChaining(size_t initial_buckets = 16) : count(0) {
        buckets.resize(std::max(size_t(1), initial_buckets));
    }
    Iterator begin()
    {
        size_t start_bucket_idx = 0;
        while (start_bucket_idx < buckets.size() && buckets[start_bucket_idx].empty()) ++start_bucket_idx;

        if (start_bucket_idx == buckets.size()) return end();

        return Iterator(&buckets, start_bucket_idx, buckets[start_bucket_idx].begin());
    }

    Iterator end() { return Iterator(&buckets, buckets.size()); } 


    Iterator insert(const TKey& key, const TValue& value) 
    {
        size_t index = hash_function(key);
        std::list<std::pair<TKey, TValue>>& chain = buckets[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                throw std::exception("Cannot overwrite existing key, must delete it first.");
            }
        }

        chain.emplace_back(key, value);
        count++;

        typename std::list<std::pair<TKey, TValue>>::iterator last_element_it = chain.end();
        --last_element_it;
        return Iterator(&buckets, index, last_element_it);
    }

    Iterator erase(const TKey& key) {
        size_t index = hash_function(key);
        std::list<std::pair<TKey, TValue>>& chain = buckets[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                auto next_list_it = chain.erase(it);
                count--;
                if (next_list_it != chain.end()) return Iterator(&buckets, index, next_list_it);
                else 
                {
                    size_t next_bucket_idx = index + 1;
                    while (next_bucket_idx < buckets.size() && buckets[next_bucket_idx].empty()) ++next_bucket_idx;

                    if (next_bucket_idx < buckets.size()) return Iterator(&buckets, next_bucket_idx, buckets[next_bucket_idx].begin());
                    else return end();
                }
            }
        }
        return end();
    }

    Iterator find(const TKey& key) 
    {
        size_t index = hash_function(key);
        std::list<std::pair<TKey, TValue>>& chain = buckets[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) return Iterator(&buckets, index, it);
        }
        return end();
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    TValue& operator[](const TKey& key) {
        Iterator it = find(key);

        if (it != end()) return it->second;
        else throw std::exception("Index overflow.");
    }
};