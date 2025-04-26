#pragma once
#include "bs_tree.h"
#include <stdexcept>
#include <vector>   
#include <algorithm> 
#include <iostream> 

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue>
{
public:
    using Tree = BSTree<TKey, TValue>;
    using Node = typename Tree::Node<TKey, TValue>;
    using Color = typename Tree::Color;
    using Iterator = typename Tree::Iterator;

protected:

    using Tree::root_node;
    using Tree::rotate_left;
    using Tree::rotate_right;
    using Tree::grandparent;
    using Tree::sibling;
    using Tree::uncle;

    Color node_color(const Node* n) const
    {
        return (n == nullptr) ? Color::BLACK : n->color;
    }

    void set_color(Node* n, Color c)
    {
        if (n != nullptr) {
            n->color = c;
        }
    }


    void rotate_left(Node* P) {
        if (!P || !P->right) return; // Невозможно вращать без правого ребенка

        Node* R = P->right; // Правый ребенок становится новым корнем поддерева
        Node* Parent = P->parent;

        // 1. Переместить левого ребенка R (RL) стать правым ребенком P
        P->right = R->left;
        if (R->left != nullptr) {
            R->left->parent = P;
        }

        // 2. Установить родителя R
        R->parent = Parent;
        if (Parent == nullptr) {
            root_node = R; // R становится новым корнем всего дерева
        }
        else if (P == Parent->left) {
            Parent->left = R; // R становится левым ребенком бывшего родителя P
        }
        else {
            Parent->right = R; // R становится правым ребенком бывшего родителя P
        }

        // 3. Установить P как левого ребенка R
        R->left = P;
        P->parent = R;
    }

    void rotate_right(Node* P) {
        if (!P || !P->left) return; // Невозможно вращать без левого ребенка

        Node* L = P->left; // Левый ребенок становится новым корнем поддерева
        Node* Parent = P->parent;

        // 1. Переместить правого ребенка L (LR) стать левым ребенком P
        P->left = L->right;
        if (L->right != nullptr) {
            L->right->parent = P;
        }

        // 2. Установить родителя L
        L->parent = Parent;
        if (Parent == nullptr) {
            root_node = L; // L становится новым корнем всего дерева
        }
        else if (P == Parent->right) {
            Parent->right = L; // L становится правым ребенком бывшего родителя P
        }
        else {
            Parent->left = L; // L становится левым ребенком бывшего родителя P
        }

        // 3. Установить P как правого ребенка L
        L->right = P;
        P->parent = L;
    }


    void insert_balance(Node* curr)
    {
        if (curr->parent == nullptr) {
            set_color(curr, Color::BLACK);
            return;
        }

        if (node_color(curr->parent) == Color::BLACK) {
            return;
        }

        Node* p = curr->parent;
        Node* g = grandparent(curr);
        Node* u = uncle(curr);

        if (node_color(u) == Color::RED) {
            set_color(p, Color::BLACK);
            set_color(u, Color::BLACK);
            set_color(g, Color::RED);
            insert_balance(g);
            return;
        }

        //if (g == nullptr) {
        //    std::cerr << "RB Warning: Grandparent is null in insert_balance case 4 for node " << curr->key << std::endl;
        //    set_color(p, Color::BLACK); 
        //    return;
        //}

        if (p == g->left) {
            if (curr == p->right) {
                rotate_left(p);
                curr = p;
                p = curr->parent;
            }
            rotate_right(g);
            set_color(p, Color::BLACK);
            set_color(g, Color::RED);
        }
        else
        {
            if (curr == p->left) {
                rotate_right(p);
                curr = p;
                p = curr->parent;
            }
            rotate_left(g);
            set_color(p, Color::BLACK);
            set_color(g, Color::RED);
        }
    }

    void transplant(Node* u, Node* v)
    {
        if (u->parent == nullptr)
        {
            this->root_node = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        if (v != nullptr)
        {
            v->parent = u->parent;
        }
    }

    Node* minimum(Node* node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    void delete_balance(Node* x, Node* parent)
    {
        while ((x != root_node) && (node_color(x) == Color::BLACK))
        {

            if (x == parent->left)
            {
                Node* w = parent->right;
                if (node_color(w) == Color::RED)
                {
                    set_color(w, Color::BLACK);
                    set_color(parent, Color::RED);
                    rotate_left(parent);
                    w = parent->right;
                }

                if (node_color(w->left) == Color::BLACK && node_color(w->right) == Color::BLACK)
                {
                    set_color(w, Color::RED);
                    x = parent;
                    parent = x->parent;
                }
                else
                {
                    if (node_color(w->right) == Color::BLACK)
                    {
                        set_color(w->left, Color::BLACK);
                        set_color(w, Color::RED);
                        rotate_right(w);
                        w = parent->right;
                    }
                    set_color(w, node_color(parent));
                    set_color(parent, Color::BLACK);
                    set_color(w->right, Color::BLACK);
                    rotate_left(parent);
                    x = root_node;
                }
            }
            else
            {
                Node* w = parent->left;
                if (node_color(w) == Color::RED)
                {
                    set_color(w, Color::BLACK);
                    set_color(parent, Color::RED);
                    rotate_right(parent);
                    w = parent->left;
                }

                if (node_color(w->right) == Color::BLACK && node_color(w->left) == Color::BLACK)
                {
                    set_color(w, Color::RED);
                    x = parent;
                    parent = x->parent;
                }
                else
                {
                    if (node_color(w->left) == Color::BLACK)
                    {
                        set_color(w->right, Color::BLACK);
                        set_color(w, Color::RED);
                        rotate_left(w);
                        w = parent->left;
                    }
                    set_color(w, node_color(parent));
                    set_color(parent, Color::BLACK);
                    set_color(w->left, Color::BLACK);
                    rotate_right(parent);
                    x = root_node;
                }
            }
        }
        if (x) set_color(x, Color::BLACK);
    }

    bool check_bst_property_recursive(const Node* node, const TKey* min_key, const TKey* max_key) const {
        if (!node) return true;

        if ((min_key && node->key <= *min_key) || (max_key && node->key >= *max_key)) {
            std::cerr << "BST Violation: Node " << node->key << " is out of bounds." << std::endl;
            return false;
        }

        return check_bst_property_recursive(node->left, min_key, &(node->key)) &&
            check_bst_property_recursive(node->right, &(node->key), max_key);
    }

    bool check_red_black_property_recursive(const Node* node) const
    {
        if (!node) return true;

        if (node_color(node) == Color::RED)
        {
            if (node_color(node->left) == Color::RED || node_color(node->right) == Color::RED)
            {
                std::cerr << "RB Violation: Red node " << node->key << " has a red child." << std::endl;
                return false;
            }
        }
        return check_red_black_property_recursive(node->left) &&
            check_red_black_property_recursive(node->right);
    }

    int check_black_height_recursive(const Node* node) const
    {
        if (!node)
        {
            return 1;
        }

        int left_bh = check_black_height_recursive(node->left);
        if (left_bh == -1) return -1;

        int right_bh = check_black_height_recursive(node->right);
        if (right_bh == -1) return -1;

        if (left_bh != right_bh) {
            std::cerr << "RB Violation: Black height mismatch at node " << node->key
                << " (Left BH: " << left_bh << ", Right BH: " << right_bh << ")" << std::endl;
            return -1;
        }
        return left_bh + (node_color(node) == Color::BLACK ? 1 : 0);
    }


public:
    Iterator begin() const
    {
        if (root_node == nullptr)
            return Iterator(nullptr);

        Node* current = root_node;
        while (current->left != nullptr)
            current = current->left;

        return Iterator(current);
    }

    Iterator insert(const TKey& key, const TValue& value) override
    {
        Node* parent = nullptr;
        Node* current = this->root_node;
        while (current != nullptr)
        {
            parent = current;
            if (key == current->key) {
                throw std::exception("Cannot overwrite existing key, must delete it first.");
            }
            else if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
        }

        Node* newNode = new Node(key, value);
        newNode->parent = parent;

        if (parent == nullptr)
            this->root_node = newNode;
        else if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;

        insert_balance(newNode);

        if (this->root_node)
            this->root_node->color = Color::BLACK;
        return Iterator(newNode);
    }

    Iterator erase(const TKey& key) override
    {
        Node* z = find(key, root_node);
        if (z == nullptr) return this->end();

        Node* y = z;
        Node* x = nullptr;
        Node* x_parent = nullptr;
        Color y_original_color = node_color(y);

        if (z->left == nullptr)
        {
            x = z->right;
            x_parent = z->parent;
            transplant(z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            x_parent = z->parent;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = node_color(y);
            x = y->right;

            if (y->parent == z)
            {
                if (x) x->parent = y;
                x_parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right) y->right->parent = y;
                x_parent = y->parent;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left) y->left->parent = y;
            y->color = z->color;
        }

        Iterator it = Iterator(x ? x : x_parent);
        delete z;

        if (y_original_color == Color::BLACK)
        {
            if (x != nullptr)
                delete_balance(x, x->parent);
            else
                delete_balance(x, x_parent);
        }
        return it;
    }


    bool verify_properties(bool check_bst = true) const
    {
        if (root_node == nullptr)
            return true;

        if (node_color(root_node) != Color::BLACK)
        {
            std::cerr << "RB Violation: Root node is not black." << std::endl;
            return false;
        }

        if (check_bst && !check_bst_property_recursive(root_node, nullptr, nullptr))
            return false;

        if (!check_red_black_property_recursive(root_node))
            return false;

        if (check_black_height_recursive(root_node) == -1)
            return false;

        return true;
    }
};