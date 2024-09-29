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
        int _size;
        T *_array;

        bool index_in_bounds(const int index) const {
            return index >= 0 && index < _size;
        }

        bool setter_index_in_bounds(const int index) const {
            return index >= 0 && index <= _size; // Does not result in a sparse array
        }

        void set_capacity(const int capacity = 1) {
            if (!is_valid_capacity(capacity)) throw std::runtime_error("Invalid capacity");
            _capacity = capacity;
        }

        void set_size(const int size) {
            if (!is_valid_size(size)) throw std::runtime_error("Invalid size");
            _size = size;
        }

        bool is_valid_capacity(const int capacity) {
            return capacity >= 1;
        }

        bool is_valid_size(const int size) {
            return size >= 0;
        }

        void grow() {
            if (full()) {
                const int new_capacity = _capacity == 0 ? 1 : _capacity * 2;
                resize(new_capacity);
            }
        }

        void shrink() {
            if (_size < _capacity / 4) {
                resize(_capacity / 2);
            }
        }

        bool full() const {
            return _size == _capacity;
        }

    public:
        explicit Array(const int capacity = 1) {
            set_capacity(capacity);
            set_size(0);
            _array = new T[capacity];
        }

        ~Array() {
            clear();
        }

        void clear() {
            delete[] _array;
            _array = nullptr;
            set_size(0);
        }

        bool empty() const {
            return _size == 0;
        }

        // Overloading the [] operator for getter
        T operator[](const int index) const {
            if (!index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }
            return _array[index];
        }

        // Overloading the [] operator for setter
        T &operator[](const int index) {
            if (!setter_index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }

            if (full()) throw std::runtime_error("Array is full");

            if (index == _size) ++_size;
            return _array[index];
        }

        int capacity() const {
            return _capacity;
        }

        int size() const {
            return _size;
        }

        void resize(const int new_capacity) {
            if (!is_valid_capacity(new_capacity)) throw std::runtime_error("Invalid capacity argument");
            if (new_capacity == _capacity) return;

            T *new_array = new T[new_capacity];
            const int copy_limit = std::min(new_capacity, _size);

            for (int i = 0; i < copy_limit; ++i) {
                new_array[i] = _array[i];
            }

            clear();
            _array = new_array;
            _capacity = new_capacity;
            _size = copy_limit;
        }

        void reverse() {
            if (empty()) return;

            const int mid = (_size - 1) / 2;

            for (int i = 0; i <= mid; ++i) {
                std::swap(_array[i], _array[_size - 1 - i]);
            }
        }

        void push(const T &value) {
            if (full()) {
                grow();
            }
            _array[_size++] = value;
        }

        void pop() {
            if (empty()) throw std::runtime_error("Array is empty");
            _array[_size - 1].~T();
            --size;
            shrink();
        }

        T at(const int index) const {
            if (!index_in_bounds(index)) throw std::out_of_range("Index out of bounds");
            return _array[index];
        }

        void remove_at(const int index, const int length = 1) {
            if (!index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }

            if (length < 0) {
                throw std::runtime_error("Invalid length");
            }

            if (length == 0) {
                return;
            }

            const int end_delete_idx = index + (length - 1);

            if (end_delete_idx >= _size) {
                throw std::out_of_range("Length is out of bounds");
            }

            T *copy_arr = new T[_capacity];
            int new_size = _size - length;

            for (int i = 0; i < index; ++i) {
                copy_arr[i] = _array[i];
            }

            for (int i = end_delete_idx + 1; i < _size; ++i) {
                copy_arr[i - length] = _array[i];
            }

            clear();
            _array = copy_arr;
            _size = new_size;
            shrink();
        }

        void insert_at(const int index, const T &value) {
            if (!index_in_bounds(index)) {
                throw std::out_of_range("Index out of bounds");
            }

            const int new_capacity = full() ? ++_capacity : _capacity;
            const int new_size = _size + 1;
            T *copy_arr = new T[new_capacity];

            for (int i = 0; i < index; ++i) {
                copy_arr[i] = _array[i];
            }

            copy_arr[index] = value;

            for (int i = index + 1; i <= _size; ++i) {
                copy_arr[i] = _array[i - 1];
            }

            clear();
            _array = copy_arr;
            _capacity = new_capacity;
            _size = new_size;
            grow();
        }



        void pop_back() {
            remove_at(_size - 1, 1);
        }

        void pop_front() {
            remove_at(0, 1);
        }

        int find(const T &value) {
            for (int i = 0; i < _size; ++i) {
                if (_array[i] == value) {
                    return i;
                }
            }
            return -1;
        }

        void remove(const T &value) {
            if (const int found_at = find(value); found_at != -1) {
                remove_at(found_at);
            }
        }

        void show() {
            std::cout << "{";
            for (int i = 0; i < _size; ++i) {
                std::cout << _array[i];
                if (i < _size - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "}\n";
        }
    };
} // DS

#endif //LIST_H
