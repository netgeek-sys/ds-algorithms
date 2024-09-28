#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <cstddef>

#include "DoublyLinkedList/DLinkedList.h"

namespace DS {
    /**
     * @brief A queue data structure implemented using a doubly linked list.
     *
     * This class provides a basic queue data structure with methods for
     * enqueueing, dequeueing, peeking, and checking the size of the queue.
     *
     * @tparam T The type of elements stored in the queue.
     */
    template<typename T>
    class Queue {
        DS::DLinkedList<T> queue;

    public:
        /**
         * @brief Constructs an empty queue.
         */
        explicit Queue() = default;

        /**
         * @brief Destroys the queue and releases any allocated memory.
         */
        ~Queue() {
            queue.clear();
        }

        /**
         * @brief Returns the number of elements in the queue.
         *
         * @return The size of the queue.
         */
        std::size_t size() const {
            return queue.size();
        }

        /**
         * @brief Checks if the queue is empty.
         *
         * @return True if the queue is empty, false otherwise.
         */
        bool empty() const {
            return queue.empty();
        }

        /**
         * @brief Adds an element to the end of the queue.
         *
         * @param value The element to add to the queue.
         * @return The added element.
         */
        T enqueue(const T &value) {
            return queue.push_back(value)->get_value();
        }

        /**
         * @brief Removes the front element from the queue.
         *
         * @return The removed element.
         * @throws std::runtime_error If the queue is empty.
         */
        T dequeue() {
            if (empty()) {
                throw std::runtime_error("Queue is empty");
            }
            auto value = queue.pop_front();
            return value;
        }

        /**
        * @brief Returns the front element of the queue without removing it.
        *
        * @return The front element of the queue.
        */
        T peek() const {
            return queue.get_front();
        }

        /**
         * @brief Returns the back element of the queue.
         *
         * @return The back element of the queue.
         */
        T back() const {
            return queue.back();
        }

        /**
         * @brief Prints the elements of the queue to the console.
         */
        void show() const {
            queue.show();
        }
    };
} // ds

#endif //QUEUE_H
