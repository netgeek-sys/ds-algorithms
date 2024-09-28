//
// Created by Zakaria on 28/09/2024.
//

#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace DS {
    template<typename T>
    class Array {
        int _capacity;
        T *_array;

        bool index_in_bounds(const int index) const {
            return index < 0 || index >= _capacity;
        }

        void set_capacity(const int capacity) {
            if (!is_valid_capacity(capacity)) throw std::runtime_error("Invalid capacity argument");
            _capacity = capacity;
        }

        bool is_valid_capacity(const int capacity) {
            return capacity >= 1;
        }

    public:
        explicit Array(const int capacity = 0) {
            set_capacity(capacity);
            _array = new T[capacity];
        }

        ~Array() {
            clear();
        }

        void clear() {
            delete[] _array;
            _array = nullptr;
            _capacity = 0;
        }

        // Overloading the [] operator for getter
        T operator[](const int index) const {
            if (index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }
            return _array[index];
        }

        // Overloading the [] operator for setter
        T &operator[](const int index) {
            if (index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }
            return _array[index];
        }

        int capacity() const {
            return _capacity;
        }

        void resize(const int new_capacity) {
            if (!is_valid_capacity(new_capacity)) throw std::runtime_error("Invalid capacity argument");
            if (new_capacity == _capacity) return;

            T *new_array = new T[new_capacity];
            int copy_limit = std::min(new_capacity, _capacity); // std::min is defined in the <algorithm> header

            for (int i = 0; i < copy_limit; ++i) {
                new_array[i] = _array[i];
            }

            clear();
            _array = new_array;
            _capacity = new_capacity;
        }

        void show() {
            std::cout << "{";
            for (std::size_t i = 0; i < _capacity; ++i) {
                std::cout << _array[i];
                if (i < _capacity - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "}\n";
        }
    };
} // DS

#endif //LIST_H
