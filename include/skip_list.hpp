#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>

namespace stl {

/**
 * @brief A skip list implementation with STL-style iterator support.
 *
 * @tparam T Type of elements stored in the skip list.
 */
template <typename T>
class SkipList {
private:
    /**
     * @brief Internal node structure for the skip list.
     */
    struct Node {
        T value;                          ///< Value stored in the node
        std::vector<Node*> forward;      ///< Forward pointers to nodes on each level

        /**
         * @brief Constructs a node with a value and level.
         * @param val The value of the node.
         * @param level The number of forward pointers.
         */
        Node(const T& val, size_t level) : value(val), forward(level, nullptr) {}
    };

    Node* head;                          ///< Pointer to head node
    size_t max_level;                    ///< Maximum level for nodes
    float probability;                   ///< Probability for level generation
    size_t current_level;                ///< Current highest level in use
    size_t node_count;                   ///< Number of nodes in the skip list

    std::default_random_engine engine;   ///< Random number generator engine
    std::uniform_real_distribution<float> distribution; ///< Uniform distribution

    /**
     * @brief Generates a random level based on the probability.
     * @return A level between 1 and max_level.
     */
    size_t random_level() {
        size_t lvl = 1;
        while (distribution(engine) < probability && lvl < max_level)
            ++lvl;
        return lvl;
    }

public:
    /**
     * @brief Constructs a SkipList with specified parameters.
     * @param max_level Maximum level of the skip list.
     * @param probability Probability factor for random level generation.
     */
    SkipList(size_t max_level = 16, float probability = 0.5)
        : max_level(max_level),
          probability(probability),
          current_level(1),
          node_count(0),
          engine(std::random_device{}()),
          distribution(0.0, 1.0)
    {
        head = new Node(T{}, max_level);
    }

    /**
     * @brief Destructor to clean up all nodes.
     */
    ~SkipList() {
        Node* node = head;
        while (node) {
            Node* next = node->forward[0];
            delete node;
            node = next;
        }
    }

    /**
     * @brief Inserts a value into the skip list if it doesn't already exist.
     * @param value The value to insert.
     */
    void insert(const T& value) {
        std::vector<Node*> update(max_level, nullptr);
        Node* current = head;

        for (int i = current_level - 1; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current && current->value == value) return;

        size_t new_level = random_level();
        if (new_level > current_level) {
            for (size_t i = current_level; i < new_level; ++i) {
                update[i] = head;
            }
            current_level = new_level;
        }

        Node* new_node = new Node(value, new_level);
        for (size_t i = 0; i < new_level; ++i) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }

        ++node_count;
    }

    /**
     * @brief Removes a value from the skip list.
     * @param value The value to remove.
     */
    void erase(const T& value) {
        std::vector<Node*> update(max_level, nullptr);
        Node* current = head;

        for (int i = current_level - 1; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (!current || current->value != value) return;

        for (size_t i = 0; i < current_level; ++i) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        delete current;

        while (current_level > 1 && head->forward[current_level - 1] == nullptr) {
            --current_level;
        }

        --node_count;
    }

    /**
     * @brief Checks whether the skip list contains a value.
     * @param value The value to check.
     * @return True if value is found, false otherwise.
     */
    bool contains(const T& value) const {
        return std::find(begin(), end(), value) != end();
    }

    /**
     * @brief Returns the number of elements in the skip list.
     * @return Size of the skip list.
     */
    size_t size() const { return node_count; }

    /**
     * @brief Iterator class for traversing the skip list.
     */
    class Iterator {
    private:
        Node* node; ///< Current node the iterator points to

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Constructs an iterator pointing to a node.
         * @param node Pointer to the node.
         */
        Iterator(Node* node) : node(node) {}

        T& operator*() const { return node->value; }

        Iterator& operator++() {
            node = node->forward[0];
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return node == other.node; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
    };

    /**
     * @brief Returns an iterator to the beginning of the skip list.
     */
    Iterator begin() const { return Iterator(head->forward[0]); }

    /**
     * @brief Returns an iterator to the end (nullptr) of the skip list.
     */
    Iterator end() const { return Iterator(nullptr); }
};

} // namespace stl