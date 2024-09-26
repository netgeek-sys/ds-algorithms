//
// Created by Zakaria Mehamdia on 24/09/2024.
//

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <stdexcept>
#include <cstddef>

#include "DNode.h"

namespace DS {
    /**
     * @brief Template class representing a doubly linked list.
     *
     * This class provides basic functionalities to manipulate a doubly linked list
     * with nodes that contain a value of type T. It supports operations such as insertion,
     * removal, search, and displaying the contents of the list.
     *
     * @tparam T Type of the values stored in the list.
     */
    template<typename T>
    class DLinkedList {
        DNode<T> *head; ///< Pointer to the first node in the list.
        DNode<T> *tail; ///< Pointer to the last node in the list.
        std::size_t size; ///< Number of nodes currently in the list.

    public:
        /**
         * @brief Constructor that initializes an empty list.
         */
        explicit DLinkedList() : head(nullptr), tail(nullptr), size(0) {}

        /**
         * @brief Destructor that clears the list.
         */
        ~DLinkedList() {
            clear(); ///< Ensures all allocated nodes are freed.
        }

        /**
         * @brief Checks if the list is empty.
         * @return true if the list is empty, false otherwise.
         */
        bool is_empty() const noexcept {
            return size == 0;
        }

        /**
         * @brief Retrieves the value of the first node in the list.
         * @throws std::runtime_error if the list is empty.
         * @return The value stored in the first node.
         */
        T get_front() const {
            if (is_empty()) {
                throw std::runtime_error("Cannot get the front of an empty list.");
            }
            return head->value;
        }

        /**
         * @brief Retrieves the value of the last node in the list.
         * @throws std::runtime_error if the list is empty.
         * @return The value stored in the last node.
         */
        T get_back() const {
            if (is_empty()) {
                throw std::runtime_error("Cannot get the back of an empty list.");
            }
            return tail->value;
        }

        /**
         * @brief Retrieves the number of nodes in the list.
         * @return The size of the list.
         */
        std::size_t get_size() const {
            return size;
        }

        /**
         * @brief Inserts a new node with the given value at the front of the list.
         * @param value The value to insert.
         */
        void insert_front(const T &value) {
            auto *new_node = new DNode<T>(value);

            if (is_empty()) {
                head = tail = new_node;
            } else {
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            }

            ++size;
        }

        /**
         * @brief Inserts a new node with the given value at the back of the list.
         * @param value The value to insert.
         */
        void insert_back(const T &value) {
            auto *new_node = new DNode<T>(value);

            if (is_empty()) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }

            ++size;
        }

        /**
         * @brief Inserts a new node after the target node with the given value.
         * @param target A pointer to the target node after which the new node will be inserted.
         * @param value The value to insert in the new node.
         * @throws std::runtime_error if the target node is null.
         */
        void insert_after(DNode<T> *const target, const T &value) {
            if (target == nullptr) {
                throw std::runtime_error("Target node cannot be null when inserting a new node.");
            }

            auto new_node = new DNode<T>(value);
            auto after_target = target->next; ///< Preserve the node after the target.

            // Insert the new node between the target and the next node.
            target->next = new_node;
            new_node->prev = target;

            if (target == tail) {
                tail = new_node;
            } else {
                new_node->next = after_target;
                after_target->prev = new_node;
            }

            ++size;
        }

        /**
         * @brief Removes the first node in the list.
         * @throws std::runtime_error if the list is empty.
         */
        void remove_front() {
            if (is_empty()) {
                throw std::runtime_error("Cannot remove from an empty list.");
            }

            const DNode<T> *old_head = head;

            if (size == 1) {
                head = tail = nullptr; ///< Only one node in the list.
            } else {
                head = old_head->next;
                head->prev = nullptr;
            }

            delete old_head;
            --size;
        }

        /**
         * @brief Removes the last node from the list.
         *
         * Deallocates the memory of the removed node. If the list becomes empty, both head and tail are set to nullptr.
         *
         * @throws std::runtime_error if the list is empty.
         */
        void remove_last() {
            if (is_empty()) {
                throw std::runtime_error("Cannot remove from an empty list.");
            }

            const DNode<T> *old_tail = tail;

            if (size == 1) {
                head = tail = nullptr; ///< Only one node in the list.
            } else {
                tail = old_tail->prev;
                tail->next = nullptr;
            }

            delete old_tail;
            --size;
        }

        /**
         * @brief Removes the first node with the given value.
         * @param value The value of the node to remove.
         * @return true if the node was found and removed, false otherwise.
         * @throws std::runtime_error if the list is empty.
         */
        bool remove(const T &value) {
            if (is_empty()) {
                throw std::runtime_error("Cannot remove from an empty list.");
            }

            DNode<T> *curr_node = head;

            // Special case: removing the head node
            if (curr_node->value == value) {
                if (head == tail) {
                    delete curr_node;
                    head = tail = nullptr;
                } else {
                    head = curr_node->next;
                    head->prev = nullptr;
                    delete curr_node;
                }
                --size;
                return true;
            }

            // General case: traversing the list
            while (curr_node != nullptr) {
                if (curr_node->value == value) {
                    if (curr_node == tail) {
                        tail = curr_node->prev;
                        tail->next = nullptr;
                    } else {
                        curr_node->prev->next = curr_node->next;
                        curr_node->next->prev = curr_node->prev;
                    }

                    delete curr_node;
                    --size;
                    return true;
                }

                curr_node = curr_node->next;
            }

            return false; ///< Node with the given value was not found.
        }

        /**
         * @brief Finds the first node with the given value.
         * @param value The value to search for.
         * @return A pointer to the node if found, nullptr otherwise.
         */
        DNode<T> *find(const T &value) const {
            auto iter = head;

            while (iter != nullptr) {
                if (iter->value == value) {
                    return iter;
                }

                iter = iter->next;
            }

            return nullptr; ///< Node with the given value not found.
        }

        /**
         * @brief Clears the list, deleting all nodes.
         */
        void clear() {
            while (!is_empty()) {
                remove_front(); ///< Remove the front node until the list is empty.
            }
        }

        /**
         * @brief Displays the contents of the list in a readable format.
         * @remark Only works with a list based of one of the integral types (int, char, double...etc)
         */
        void show() const {
            std::cout << "{";

            auto iter = head;

            while (iter != nullptr) {
                std::cout << iter->value;

                if (iter->next != nullptr) {
                    std::cout << " <-> ";
                }

                iter = iter->next;
            }

            std::cout << "}\n";
        }
    };
} // DS

#endif //DLINKEDLIST_H
