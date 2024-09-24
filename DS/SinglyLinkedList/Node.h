//
// Created by Zakaria Mehamdia on 24/09/2024.
//

#ifndef NODE_H
#define NODE_H

namespace DS {
    // Forward declaration of SinglyLinkedList
    template<typename T>
    class SinglyLinkedList;

    /**
     * @class Node
     * @brief A node in the singly linked list.
     *
     * This class represents a node that stores a value and a pointer to the next node in the list.
     *
     * @tparam T The type of value stored in the node.
     */
    template<typename T>
    class Node {
        T value; ///< The value stored in the node.
        Node *next; ///< Pointer to the next node in the list.

    public:
        /**
         * @brief Constructs a new node with the given value.
         *
         * Initializes the node with the provided value and sets the next pointer to nullptr.
         *
         * @param value The value to store in the node.
         */
        explicit Node(const T &value) : value(value), next(nullptr) {}

        /**
         * @brief Destructor for the Node.
         */
        ~Node() = default;

        T get_value() const {
            return value;
        }

        friend class SinglyLinkedList<T>; // Granting SinglyLinkedList access to Node's private members.
    };
} // DS

#endif //NODE_H
