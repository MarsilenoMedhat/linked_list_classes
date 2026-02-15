#include <iostream>
#include <optional>

template <typename T>
class clsDblLinkedList {

private:
    struct _Node {
        T _Value;
        _Node* _Previous;
        _Node* _Next;
    };

    _Node* _Head;
    _Node* _Tail;
    _Node* _Current;
    unsigned int _Count = 0;

    // finds node by the val and return the node once we find it, and return nullptr if it doesn't exist.
    _Node* _FindNode(T searchVal) const {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return nullptr;
        }
        
        _Node* tempNode = _Head;
        
        while (tempNode != nullptr) {
            if (tempNode->_Value == searchVal) {
                return tempNode;
            }
            tempNode = tempNode->_Next;
        }

        return nullptr;
    }    
    
    // insert new node at the beginning.
    bool _InsertAtBeginning(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Previous = nullptr;
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
        }
        else {
            newNode->_Next = _Head;
            _Head->_Previous = newNode;
            _Head = newNode;
        }
        _Count++;
        return true;
    }
    
    // insert new node at the end.
    bool _InsertAtEnd(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = nullptr;
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Previous = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
        }
        else {
            newNode->_Previous = _Tail;
            _Tail->_Next = newNode;
            _Tail = newNode;
        }
        _Count++;
        return true;
    }

    // insert after a spesific node by check the previous node by value.
    bool _InsertAfter(T previousVal, T newVal) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return  false;
        }
        
        // find the previous node in the list.
        _Node* previousNode = _FindNode(previousVal);
        
        // check if the previous node is exist or not
        if (previousNode == nullptr) {
            return false;
        }

        // check if the previos node is the last node in the list or not.
        if (previousNode->_Next == nullptr) {
            return _InsertAtEnd(newVal);
        } 
        else {
            _Node* newNode = new _Node;
            newNode->_Value = newVal;

            newNode->_Next = previousNode->_Next;
            newNode->_Previous = previousNode;
            previousNode->_Next->_Previous = newNode;
            previousNode->_Next = newNode;
            _Count++;
        }
        return true;
    }

    // delete the first node of the list.
    bool _DeleteFirstNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has 1 node or more.
        if (_Head == _Tail) {
            delete _Head;
            _Head = nullptr;
            _Tail = nullptr;
            _Current = nullptr;
        }
        else {
            if (_Current == _Head) {
                _Current = _Current->_Next;
            }
            _Head = _Head->_Next;
            delete _Head->_Previous;
            _Head->_Previous = nullptr;
        }
        _Count--;
        return true;
    }

    // delete the last node of the list.
    bool _DeleteLastNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has 1 node or more.
        if (_Head == _Tail) {
            delete _Head;
            _Head = nullptr;
            _Tail = nullptr;
            _Current = nullptr;
        }
        else {
            if (_Current == _Tail) {
                _Current = _Current->_Previous;
            }
            _Tail = _Tail->_Previous;
            delete _Tail->_Next;
            _Tail->_Next = nullptr;
        }
        _Count--;
        return true;
    }

    // delete a specific node.
    bool _DeleteNode(T Val) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }
        // check if the value we want to delete is in the first node or not.
        if (Val == _Head->_Value) {
            return _DeleteFirstNode();
        }
        // check if the value we want to delete is in the last node or not.
        if (Val == _Tail->_Value) {
            return _DeleteLastNode();
        }

        _Node* nodeToDelete = nullptr;

        // check if the value we want to delete is in the current node or not.
            if (Val == _Current->_Value) {
            nodeToDelete = _Current;

            // move the current node to another point to make to it will not point to a deleted node.
            if (_Current->_Next != nullptr) {
                _Current = _Current->_Next;
            }
            else {
                _Current = _Current->_Previous;
            }
        }
        else {
            // check the node in the list.
            nodeToDelete = _FindNode(Val);
        }

        // check if the node exists in the list or not.
        if (nodeToDelete == nullptr) {
            return false;
        }

        nodeToDelete->_Previous->_Next = nodeToDelete->_Next;
        nodeToDelete->_Next->_Previous = nodeToDelete->_Previous;
        delete nodeToDelete;
        _Count--;
        return true;
    }
    
    // delete the full list.
    void _DeleteFullList() {

        if (_Head == nullptr) {
            return;
        }

        _Node* tempNode = nullptr;
        while (_Head != nullptr) {
            tempNode = _Head;
            _Head = _Head->_Next;
            delete tempNode;
        }
        _Head = nullptr;
        _Current = nullptr;
        _Tail = nullptr;
        _Count = 0;
    }

public:

    clsDblLinkedList(T val) {
        _Node* Node = new _Node;
        Node->_Value = val;
        Node->_Next = nullptr;
        Node->_Previous = nullptr;

        _Current = Node;
        _Head = Node;
        _Tail = Node;
        _Count++;
    }

    clsDblLinkedList() {
        _Current = nullptr;
        _Head = nullptr;
        _Tail = nullptr;
    }

    std::optional<T> getCurrent() const {
        if (_Current == nullptr) {
            return std::nullopt;
        }
        return _Current->_Value;
    }
    
    // return head value if it's not empty.
    std::optional<T> getHead() const {
        if (_Head == nullptr) {
            return std::nullopt;
        }
        return _Head->_Value;
    }
    
    // return tail value if it's not empty.
    std::optional<T> getTail() const {
        if (_Tail == nullptr) {
            return std::nullopt;
        }
        return _Tail->_Value;
    }

    // return the number of nodes in the list.
    int getSize() const {
        return _Count;
    }

    // check if the val exists or not.
    bool find(T searchVal) const {
        return _FindNode(searchVal) != nullptr;
    }

    // check if the value exists or not and set is as the current.
    bool setAsCurrent(T Val) {
        _Node* tempcurrent = _FindNode(Val);
        if (tempcurrent != nullptr) {
            _Current = tempcurrent;
            return true;
        }
        return false;
    }

    bool insertAtBeginning(T newVal) {
        return _InsertAtBeginning(newVal);
    }

    bool insertAtEnd(T newVal) {
        return _InsertAtEnd(newVal);
    }

    bool insertAfter(T previousVal, T newVal) {
        return _InsertAfter(previousVal, newVal);
    }

    bool deleteFirstNode() {
        return _DeleteFirstNode();
    }

    bool deleteLastNode() {
        return _DeleteLastNode();
    }

    bool deleteNode(T Val) {
        return _DeleteNode(Val);
    }

    void deleteFullList() {
        return _DeleteFullList();
    }

    ~clsDblLinkedList() {
        _DeleteFullList();
    }
};