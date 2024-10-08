# README Documentation for Singly Linked List Implementation

This implementation of a singly linked list is designed to provide a basic understanding of data structures and
object-oriented programming (OOP) concepts. The code is written in C++ and utilizes the Doxygen comment format for
documentation.

### Key Features

* **Template Class**: Both the `Node` and the `SinglyLinkedList` classes are implemented as template classes, allowing
  them to work with various data types. This provides flexibility and reusability.
* **Friend Keyword**: The `Node` class uses the `friend` keyword to allow the `SinglyLinkedList` class to access its
  private
  members, promoting encapsulation and data hiding.
* **Added Tail Field**: A `tail` field is included to enable O(1) access to the last node in the list, improving
  performance for certain operations.
* **Namespace**: The linked list is encapsulated within the `DS` (Data Structures) namespace, promoting organization and
  avoiding naming conflicts.
* **Size Property and `get_size()` Method**: The `size` property and `get_size()` method allow users to easily retrieve
  the number of nodes in the list.
* **Clear Method**: The `clear()` method is provided to remove all nodes from the list, ensuring memory is properly
  deallocated.
* **Show Method**: The `show()` method is included to quickly display the contents of the linked list to the console.
  However, please note that this method only works with basic integral types (
  e.g., `int`, `double`, `unsigned int`, `char`, etc.) and will generate a compilation error if used with custom types.
* **Doxygen Comment Format**: The code is documented using the Doxygen comment format, which is beneficial for learning
  and using the class within an IDE. Doxygen comments provide a clear and concise way to understand the purpose and
  behavior of each method.
  ![image](https://github.com/user-attachments/assets/a6f38e24-0a25-40df-84b0-6711105b22df)
  ![image](https://github.com/user-attachments/assets/54b7ed96-2d1b-4865-bca9-c6d899466d58)



### Using the Linked List

To use the linked list, simply include both the `Node.h` and `SinglyLinkedList.h` header files in your project and
create an instance of the `SinglyLinkedList` class. You can then utilize the various methods provided to manipulate the
list.

### Example Usage

```cpp
#include "SinglyLinkedList.h"

int main() {
    DS::SinglyLinkedList<int> list;

    // Insert nodes at the back of the list
    list.insert_back(10);
    list.insert_back(20);
    list.insert_back(30);

    // Display the contents of the list
    list.show(); // Output: {10 => 20 => 30}

    // Remove a node from the list
    list.remove(20);

    // Display the updated contents of the list
    list.show(); // Output: {10 => 30}

    // Insert a node at the front of the list
    list.insert_front(5);

    // Display the updated contents of the list
    list.show(); // Output: {5 => 10 => 30}

    // Get the size of the list
    int size = list.get_size();
    std::cout << "List size: " << size << std::endl; // Output: List size: 3

    // Clear the list
    list.clear();

    // Check if the list is empty
    if (list.is_empty()) {
        std::cout << "The list is empty." << std::endl;
    } else {
        std::cout << "The list is not empty." << std::endl;
    }

    return 0;
}
