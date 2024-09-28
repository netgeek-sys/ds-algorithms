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
        bool empty() const noexcept {
            return size == 0;
        }

        /**
         * @brief Retrieves the value of the first node in the list.
         * @throws std::runtime_error if the list is empty.
         * @return The value stored in the first node.
         */
        T get_front() const {
            if (empty()) {
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
            if (empty()) {
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

            if (empty()) {
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
        DNode<T> *push_back(const T &value) {
            auto *new_node = new DNode<T>(value);

            if (empty()) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }

            ++size;
            return new_node;
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

            // TODO: return DNode * instead
        }

        /**
         * @brief Inserts a new node with the given value after the node at the specified index.
         *
         * This method inserts a new node with the given value after the node at the specified index in the list.
         * If the index is out of range, the method does nothing.
         *
         * @param index The index of the node after which to insert the new node (0-indexed).
         * @param value The value to assign to the new node.
         */

        void insert_after_at(const std::size_t index, const T &value) {
            auto found_node = get_node_at(index);
            if (found_node == nullptr) return;
            insert_after(found_node, value);
            // TODO: return DNode * instead
        }

        /**
         * @brief Removes the first node in the list.
         * @throws std::runtime_error if the list is empty.
         */
        T pop_front() {
            if (empty()) {
                throw std::runtime_error("Cannot remove from an empty list.");
            }

            const DNode<T> *old_head = head;
            T value = old_head->value;

            if (size == 1) {
                head = tail = nullptr; ///< Only one node in the list.
            } else {
                head = old_head->next;
                head->prev = nullptr;
            }

            delete old_head;
            --size;
            return value;
        }

        /**
         * @brief Removes the last node from the list.
         *
         * Deallocates the memory of the removed node. If the list becomes empty, both head and tail are set to nullptr.
         *
         * @throws std::runtime_error if the list is empty.
         */
        T remove_last() {
            if (empty()) {
                throw std::runtime_error("Cannot remove from an empty list.");
            }

            const DNode<T> *old_tail = tail;

            if (size == 1) {
                head = tail = nullptr; ///< Only one node in the list.
            } else {
                tail = old_tail->prev;
                tail->next = nullptr;
            }
            auto value = old_tail->get_value();
            delete old_tail;
            --size;
            return value;
        }

        /**
         * @brief Removes the first node with the given value.
         * @param value The value of the node to remove.
         * @return true if the node was found and removed, false otherwise.
         * @throws std::runtime_error if the list is empty.
         */
        bool remove(const T &value) {
            if (empty()) {
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

        void swap_values(DNode<T> *n1, DNode<T> *n2) {
            auto temp = n1->value;
            n1->value = n2->value;
            n2->value = temp;
        }

        /**
         * @brief Returns a pointer to the node at the specified position in the list.
         *
         * @param index The position of the node to retrieve (0-indexed).
         * @return A pointer to the node at the specified position; otherwise, \code nullptr\endcode if not found
         * @throws std::out_of_range If the list is empty or the position is out of range.
         */
        DNode<T> *get_node_at(const std::size_t index) const {
            if (empty()) {
                throw std::out_of_range("The list is empty");
            }

            if (index < 0 || index >= size) {
                throw std::out_of_range("The provided position argument is out of range");
            }

            const std::size_t mid = (size - 1) / 2; /// Calculate the midpoint of the list
            DNode<T> *current_node = nullptr;

            // Iterate from the head or tail of the list, depending on the position
            if (index <= mid) {
                current_node = head;
                for (std::size_t node_index = 0; node_index <= mid; ++node_index) {
                    if (node_index == index) {
                        return current_node;
                    }
                    current_node = current_node->next;
                }
            } else {
                current_node = tail;
                for (std::size_t node_index = size - 1; node_index > mid; --node_index) {
                    if (node_index == index) {
                        return current_node;
                    }
                    current_node = current_node->prev;
                }
            }
            return nullptr;
        }

        /**
         * Reverses the linked list in-place.
         *
         * This method swaps the values of nodes from both ends of the list towards the center,
         * effectively reversing the list.
         *
         * @throws std::runtime_error if the list is empty
         */
        void reverse() {
            if (empty()) {
                throw std::runtime_error("Cannot reverse an empty list.");
            }

            if (size > 1) {
                auto start = head;
                auto end = tail;
                auto half_size = size / 2;

                // Perform halfSize number of swaps to reverse the list
                while (half_size-- > 0) {
                    swap_values(start, end);
                    start = start->next;
                    end = end->prev;
                }
            }
        }

        /**
         * @brief Updates the value of the node at the specified index in the list.
         *
         * This method updates the value of the node at the given index in the doubly linked list.
         * It throws an exception if the list is empty or if the index is out of range.
         *
         * @param index The index of the node to update (0-indexed).
         * @param new_value The new value to assign to the node at the specified index.
         * @return A pointer to the node at the specified index with the updated value; otherwise, \code nullptr\endcode if not found
         * @throws std::out_of_range If the list is empty or the index is out of range.
         */
        DNode<T> *update_at(const std::size_t index, const T &new_value) {
            auto found_node = get_node_at(index);
            if (found_node == nullptr) return nullptr;
            found_node->value = new_value;
            return found_node;
        }

        /**
         * @brief Clears the list, deleting all nodes.
         */
        void clear() {
            while (!empty()) {
                pop_front(); ///< Remove the front node until the list is empty.
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
                    std::cout << ", ";
                }

                iter = iter->next;
            }

            std::cout << "}\n";
        }
    };
} // DS

#endif //DLINKEDLIST_H
