#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <stdexcept>
#include <string>

namespace ds {
    template<typename T>
    class Queue {
        std::unique_ptr<T[]> queue;
        int capacity;
        int front;
        int rear;
        int size;

    public:
        explicit Queue(int capacity) : queue(new T[capacity]), capacity(capacity), front(0), rear(-1), size(0) {}

        ~Queue() override = default;

        int get_size() const {
            return rear + 1;
        }

        int get_capacity() const {
            return capacity;
        }

        bool is_empty() const {
            return size == 0;
        }

        bool is_full() const {
            return size == capacity;
        }

        void enqueue(const T element) {
            if (is_full()) {
                throw std::out_of_range("Queue overflow exception");
            }

            rear = (rear + 1) % capacity;
            queue[rear] = element;
            ++size;
        }

        T dequeue() {
            if (is_empty()) {
                throw std::out_of_range("Queue underflow exception");
            }

            T popped = queue[front];
            front = (front + 1) % capacity;
            --size;

            return popped;
        }

        std::string to_str() const {
            std::string str = "{";

            if (!is_empty()) {
                for (int i{front}; i <= rear; ++i) {
                    str += std::to_string(queue[i]);

                    if (i < rear) {
                        str += ", ";
                    }
                }
            }

            return str + "}";
        }
    };
} // ds

#endif //QUEUE_H
