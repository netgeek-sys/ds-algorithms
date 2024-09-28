//
// Created by Zakaria on 25/09/2024.
//

#ifndef DNODE_H
#define DNODE_H

#include "DLinkedList.h"

namespace DS {
    // Forward declaration of SinglyLinkedList
    template<typename T>
    class DLinkedList;

    template<typename T>
    class DNode {
        T value; ///< The value stored in the node.
        DNode *prev; ///< Pointer to the previous node in the list.
        DNode *next; ///< Pointer to the next node in the list.

    public:
        /**
         * @brief Constructs a new node with the given value.
         *
         * Initializes the node with the provided value and sets the prev, and next pointers to nullptr.
         *
         * @param value The value to store in the node.
         */
        explicit DNode(const T &value) : value(value), prev(nullptr), next(nullptr) {}

        /**
         * @brief Destructor for the Node.
         */
        ~DNode() = default;

        T get_value() {
            return value;
        }

        friend class DLinkedList<T>; // Granting DLinkedList access to DNode's private members.
    };
} // DS

#endif //DNODE_H
