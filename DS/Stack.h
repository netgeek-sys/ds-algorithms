#ifndef STACK_H
#define STACK_H

#include <stdexcept>

#include "DoublyLinkedList/DLinkedList.h"

namespace DS {
    /**
     * @brief A stack data structure implemented using a doubly linked list.
     *
     * This class provides a basic stack data structure with methods for pushing,
     * popping, checking the size, and accessing the top and bottom elements.
     *
     * @tparam T The type of elements stored in the stack.
     */
    template<typename T>
    class Stack {
        /**
         * @brief The underlying doubly linked list that stores the stack elements.
         */
        DLinkedList<T> stack;

    public:
        /**
         * @brief Constructs an empty stack.
         */
        explicit Stack() = default;

        /**
         * @brief Destroys the stack and releases any allocated memory.
         */
        ~Stack() = default;

        /**
         * @brief Checks if the stack is empty.
         *
         * @return True if the stack is empty, false otherwise.
         */
        bool empty() const {
            return stack.empty();
        }

        /**
         * @brief Adds an element to the top of the stack.
         *
         * @param value The element to add to the stack.
         * @return The added element.
         */
        T push(const T value) {
            return stack.push_back(value)->get_value();
        }

        /**
         * @brief Removes the top element from the stack.
         *
         * @return The removed element.
         * @throws std::runtime_error If the stack is empty.
         */
        T pop() {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return stack.remove_last();
        }

        /**
         * @brief Returns the number of elements in the stack.
         *
         * @return The size of the stack.
         */
        int size() const {
            return stack.get_size();
        }

        /**
         * @brief Returns the top element of the stack without removing it.
         *
         * @return The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T top() const {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }

            return stack.get_back();
        }

        /**
         * @brief Returns the bottom element of the stack.
         *
         * @return The bottom element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T bottom() const {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }

            return stack.get_front();
        }

        void clear() {
            stack.clear();
        }

        /**
         * @brief Prints the elements of the stack to the console.
         */
        void show() const {
            stack.show();
        }
    };
}


#endif //STACK_H
