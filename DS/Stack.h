#ifndef STACK_H
#define STACK_H

#include <memory>
#include <stdexcept>
#include <string>

#include "Object.h"


namespace ds {
    template<typename T>
    class Stack : public Object {
        std::unique_ptr<T[]> stack;
        int capacity;
        int top_index;

    public:
        explicit Stack(const int capacity): stack(new T[capacity]), capacity(capacity), top_index(-1) {
        }

        ~Stack() = default;

        bool is_full() const {
            return top_index == capacity - 1;
        }

        bool is_empty() const {
            return top_index < 0;
        }

        void push(const T element) {
            if (is_full()) {
                throw std::out_of_range("Stack overflow exception");
            }
            stack[++top_index] = element;
        }

        T pop() {
            if (is_empty()) {
                throw std::out_of_range("Stack underflow exception");
            }
            return stack[--top_index];
        }

        int get_size() const {
            return top_index + 1;
        }

        T get_top() const {
            return stack[top_index];
        }

        T get_bottom() const {
            if (is_empty()) {
                throw std::out_of_range("Stack underflow exception");
            }

            return stack[0];
        }

        int get_capacity() const {
            return capacity;
        }

        std::string to_str() const override {
            std::string str = "{";

            if (!is_empty()) {
                for (int i{0}; i <= top_index; ++i) {
                    str += stack[i];

                    if (i < top_index) {
                        str += ", ";
                    }
                }
            }

            return str + "}";
        }
    };
}


#endif //STACK_H
