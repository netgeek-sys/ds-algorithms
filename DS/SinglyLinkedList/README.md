# README Documentation for Singly Linked List Implementation

This implementation of a singly linked list is designed to provide a basic understanding of data structures and
object-oriented programming (OOP) concepts. The code is written in C++ and utilizes the Doxygen comment format for
documentation.

### Key Features

* **Template Class**: The linked list is implemented as a template class, allowing it to work with various data types.
  This provides flexibility and reusability.
* **Friend Keyword**: The linked list class uses the `friend` keyword to allow other classes to access its private
  members, promoting encapsulation and data hiding.

### Using the Linked List

* **Added Tail Field**: A `tail` field is included to enable O(1) access to the last node in the list, improving
  performance for certain operations.
* **Namespace**: The linked list is encapsulated within the `DS` (Data Structures) namespace, promoting organization and
  avoiding naming conflicts.
* **Size Property and `get_size()` Method**: The `size` property and `get_size()` method allow users to easily retrieve
  the number of nodes in the list.
* **Doxygen Comment Format**: The code is documented using the Doxygen comment format, which is beneficial for learning
  and using the class within an IDE. Doxygen comments provide a clear and concise way to understand the purpose and
  behavior of each method.
* **Clear Method**: The `clear()` method is provided to remove all nodes from the list, ensuring memory is properly
  deallocated.
* **Show Method**: The `show()` method is included to quickly display the contents of the linked list to the console.
  However, please note that this method only works with basic integral types (
  e.g., `int`, `double`, `unsigned int`, `char`, etc.) and will generate a compilation error if used with custom types.

### Using the Linked List

To use the linked list, simply include the `SinglyLinkedList.h` header file in your project and create an instance of
the `SinglyLinkedList` class. You can then utilize the various methods provided to manipulate the list.

### Example Usage

```cpp
#include "SinglyLinkedList.h"

int main() {
    DS::SinglyLinkedList<int> list;

    list.insert_back(10);
    list.insert_back(20);
    list.insert_back(30);

    list.show(); // Output: {10 => 20 => 30}

    list.remove(20);

    list.show(); // Output: {10 => 30}

    return 0;
}