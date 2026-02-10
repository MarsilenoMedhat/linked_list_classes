# Linked List Library

A comprehensive **C++ template library** providing various linked list structures. This library is designed with a focus on ease of use and includes an "Optimized Search" feature in specific implementations to improve performance based on temporal locality.

---

## Features

* **Template Support**: Works with any data type, such as `int`, `std::string`, or custom objects.
* **Current Pointer Tracking**: Every list maintains a `_Current` pointer, allowing you to track a specific "active" node.
* **Temporal Locality Optimization**: Search operations in `singlyList` and `doublyList` start from the `_Current` node, potentially reducing search time for recently accessed data.
* **Safety**: Uses `std::optional` for "get" methods to safely handle empty list scenarios without crashing.
* **Memory Management**: Full destructor support to prevent memory leaks by cleaning up all nodes on object destruction.

---

## Included Classes

### 1. `singlyList`
A standard unidirectional linked list.
* **Key Operations**: `insertAtTheBeginning`, `insertAtTheEnd`, `insertAfter`, `deleteNode`, and `setAsCurrent`.
* **Best For**: Simple stacks or queues where memory overhead must be kept to a minimum.

### 2. `doublyList`
A bidirectional linked list where each node points to both the next and previous nodes.
* **Key Operations**: `printListFromHeadToTail`, `printListFromTailToHead`, `insertAtBeginning`, and `insertAtEnd`.
* **Best For**: Scenarios requiring frequent reverse traversal or deletions where you only have a pointer to the node itself.

### 3. `CircularSinglyList`
A unidirectional list where the last node points back to the first node.
* **Key Operations**: `insertAtTheBeginningOrEnd`, `deleteFirstOrLastNode`, and `deleteNode`.
* **Best For**: Round-robin scheduling or applications that need to cycle through items indefinitely.

### 4. `CircularDoublyList`
A bidirectional list where the head and tail are linked together.
* **Key Operations**: `printListFromHeadToTail`, `printListFromTailToHead`, and `insertAtBeginningOrEnd`.
* **Best For**: Advanced buffer management or navigation systems, such as cycling through items in both directions.