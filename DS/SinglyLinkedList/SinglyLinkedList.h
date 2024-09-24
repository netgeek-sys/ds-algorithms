//
// Created by Zakaria Mehamdia on 24/09/2024.
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <cstddef>
#include <stdexcept>

#include "Node.h"

namespace DS {
    /**
     * @class SinglyLinkedList
     * @brief A singly linked list implementation.
     *
     * This class provides basic functionality to manage a singly linked list,
     * including insertion, deletion, and retrieval of front and back elements.
     *
     * @tparam T The type of elements stored in the linked list.
     */
    template<typename T>
    class SinglyLinkedList {
        Node<T> *head; ///< Pointer to the first node in the list.
        Node<T> *tail; //< Pointer to the last node in the list.
        std::size_t size; //< Number of nodes in the list.

    public:
        /**
         * @brief Constructs an empty singly linked list.
         *
         * Initializes the list with no nodes and size set to 0.
         */
        explicit SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

        /**
         * @brief Destructor that deallocates all nodes in the list.
         *
         * Frees the memory for each node in the list to prevent memory leaks.
         */
        ~SinglyLinkedList() {
            clear();
        }

        /**
         * @brief Checks if the list is empty.
         *
         * @return true if the list is empty, false otherwise.
         */
        bool is_empty() const noexcept {
            return head == nullptr;
        }

        /**
         * @brief Retrieves the value stored in the first node.
         *
         * @return The value stored at the front of the list.
         * @throws std::runtime_error if the list is empty.
         */
        T get_front() const {
            if (is_empty()) {
                throw std::runtime_error("Empty singly linked list");
            }

            return head->value;
        }

        /**
         * @brief Retrieves the value stored in the last node.
         *
         * @return The value stored at the back of the list.
         * @throws std::runtime_error if the list is empty.
         */
        T get_back() const {
            if (is_empty()) {
                throw std::runtime_error("Empty singly linked list");
            }

            return tail->value;
        }

        /**
         * @brief Gets the number of nodes in the list.
         *
         * @return The number of nodes in the list.
         */
        std::size_t get_size() const {
            return size;
        }

        /**
         * @brief Inserts a new node with the specified value at the front of the list.
         *
         * The new node becomes the new head. If the list was empty, the new node also becomes the tail.
         *
         * @param value The value to store in the new node.
         */
        void insert_front(const T &value) {
            auto *new_node = new Node<T>(value);

            // Set the next pointer of the new node to the current head
            new_node->next = head;

            // Update the head to point to the new node
            head = new_node;

            ++size;

            // If the list was empty, update the tail to point to the new node as well
            if (get_size() == 1) {
                tail = head;
            }
        }

        /**
         * @brief Inserts a new node with the specified value at the back of the list.
         *
         * The new node becomes the new tail. If the list was empty, the new node also becomes the head.
         *
         * @param value The value to store in the new node.
         */
        void insert_back(const T &value) {
            auto *new_node = new Node<T>(value);

            if (is_empty()) {
                // If the list is empty, set the new node as both the head and tail
                head = tail = new_node;
            } else {
                // If the list is not empty, insert the new node after the current tail
                tail->next = new_node;
                tail = new_node;
            }

            ++size;
        }

        /**
         * Inserts a new node with the given value after the target node in the linked list.
         *
         * @param target The node after which to insert the new node.
         * @param value The value to be stored in the new node.
         * @throws std::runtime_error If the target node is null.
         */
        void insert_after(Node<T> *target, const T &value) {
            if (target == nullptr) {
                throw std::runtime_error("Target node cannot be null when inserting a new node.");
            }

            auto new_node = new Node<T>(value);
            auto after_target = target->next; // Store the original next node
            target->next = new_node; // Set the new node as the next node of the target

            if (after_target != nullptr) {
                // If the target node is not the last node, set the new node's next node to the original next node
                new_node->next = after_target;
            }

            ++size;
        }

        /**
         * @brief Removes the first node from the list.
         *
         * Deallocates the memory of the removed node. If the list becomes empty, both head and tail are set to nullptr.
         *
         * @throws std::runtime_error if the list is empty.
         */
        void remove_front() {
            if (is_empty()) {
                throw std::runtime_error("Empty singly linked list");
            }

            const Node<T> *old_head = head;
            head = old_head->next;
            delete old_head;
            --size;

            if (is_empty()) {
                tail = nullptr; // Important: Reset tail when the list is empty
            }
        }

        /**
         * Removes the node with the specified value from the linked list.
         *
         * @param value The value to be removed from the list.
         * @return true if the node is found and removed, false otherwise.
         *
         * If the node is found, it is removed from the list and its memory is manually managed by deleting the node.
         * If the node is not found, false is returned.
         *
         * Throws a std::runtime_error if the list is empty, with a message indicating that the operation cannot be performed on an empty list.
         */
        bool remove(const T &value) {
            if (is_empty()) {
                throw std::runtime_error("Cannot remove a target node with a null reference.");
            }

            Node<T> *curr_node = head;
            Node<T> *prev_node = head;

            // Check if the head node is the one to be removed
            if (curr_node->value == value) {
                head = curr_node->next;
                delete curr_node;
                --size;
                return true;
            }

            // Iterate through the list to find the node to be removed
            while (curr_node != nullptr) {
                if (curr_node->value == value) {
                    prev_node->next = curr_node->next;
                    delete curr_node;
                    --size;
                    return true;
                }

                prev_node = curr_node;
                curr_node = curr_node->next;
            }

            return false;
        }

        /**
         * Finds a node in the linked list with a matching value.
         *
         * This method iterates through the linked list, comparing each node's value with the given `value`.
         * If a match is found, the method returns a pointer to that node.
         * If no match is found, the method returns `nullptr`.
         *
         * @param value The value to search for in the linked list.
         * @return A pointer to the node with the matching value, or `nullptr` if not found.
         */
        Node<T> *find(const T &value) const {
            auto iter = head;

            while (iter != nullptr) {
                if (iter->value == value) {
                    return iter;
                }

                iter = iter->next;
            }

            return nullptr;
        }

        /**
         * Clears the linked list by removing all nodes.
         */
        void clear() {
            while (!is_empty()) {
                // Remove the front node until the list is empty
                remove_front();
            }
        }

        /**
         * Prints the linked list to the console.
         *
         * The output format is "{value1 => value2 => ... => valueN}".
         *
         * @note This method only works with a linked list based off a basic integral type (e.g. int, double, unsigned int, char...etc).
         *       It will generate a compilation error if used with custom types.
         */
        void show() const {
            std::cout << "{";

            auto iter = head;

            while (iter != nullptr) {
                std::cout << iter->value;

                if (iter->next != nullptr) {
                    std::cout << " => ";
                }

                iter = iter->next;
            }

            std::cout << "}\n";
        }
    };
} // DS

#endif //SINGLYLINKEDLIST_H
