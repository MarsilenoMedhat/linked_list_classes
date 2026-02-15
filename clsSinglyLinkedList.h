#include <iostream>
#include <optional>

template <typename T>
class singlyList {

private:

    struct _Node {
        T _Value;
        _Node* _Next;
    };

    _Node* _Head;
    _Node* _Tail;
    _Node* _Current;
    int _Count = 0;

    // finds node by the val and return the node once we find it, and return nullptr if it doesn't exist.
    _Node* _FindNode(T searchVal) {
        
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

    // insert at the beginning of the list.
    bool _InsertAtTheBeginning(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;

        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
        }
        else {
            newNode->_Next = _Head;
            _Head = newNode;
        }
        _Count++;
        return true;
    }

    // insert at the end of the list.
    bool _InsertAtTheEnd(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = nullptr;
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
        }
        else {
            _Tail->_Next = newNode;
            _Tail = newNode;
        }
        _Count++;
        return true;
    }

    // insert after a specific node by check the previous node by value.
    bool _InsertAfter(T preVal, T newVal) {

        // check if the list id empty or not.
        if (_Head == nullptr) {
            return false;
        }

        _Node* tempNode = _FindNode(preVal);

        // check if the previous not is exists or not
        if (tempNode == nullptr) {
            return false;
        }

        // check if the previous node is the last one or not.
        if (tempNode == _Tail) {
            return _InsertAtTheEnd(newVal);
        }
        
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = tempNode->_Next;
        tempNode->_Next = newNode;
        _Count++;
        return true;
    }

    // delete the first node.
    bool _DeleteFirstNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has one node or not.
        if (_Head->_Next == nullptr) {
            delete _Head;
            _Head = nullptr;
            _Current = nullptr;
            _Tail = nullptr;
            _Count--;
            return true;
        }

        // check if the current is at the node we want to delete or not.
        if (_Current == _Head) {
            _Current = _Current->_Next;
        }

        _Node* tempNode = _Head;
        _Head = _Head->_Next;
        delete tempNode;
        _Count--;
        return true;
    }

    // delete the last node.
    bool _DeleteLastNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has one node or not.
        if (_Head->_Next == nullptr) {
            delete _Head;
            _Head = nullptr;
            _Current = nullptr;
            _Tail = nullptr;
            _Count--;
            return true;
        }
        
        // check if the current is at the node we want to delete or not.
        if (_Current == _Tail) {
            _Current = _Head;
        }

        _Node* tempCurrent = _Head;
        while (tempCurrent->_Next != _Tail) {
            tempCurrent = tempCurrent->_Next;
        }
        delete tempCurrent->_Next;
        tempCurrent->_Next = nullptr;
        _Tail = tempCurrent;
        _Count--;
        return true;
    }

    // delete a specific node.
    bool _DeleteNode(T deleteVal) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the node we want to delete is the first one or not.
        if (_Head->_Value == deleteVal) {
            return _DeleteFirstNode();
        }
        
        // check if the node we want to delete is the last one or not.
        if (_Tail->_Value == deleteVal) {
            return _DeleteLastNode();
        }
        
        //  check if the node is existed or not.
        _Node* temp_DeleteNode = _FindNode(deleteVal);
        if (temp_DeleteNode == nullptr) {
            return false;
        }

        _Node* PreNode = nullptr;
        _Node* tempNode = _Head;
        while (tempNode != temp_DeleteNode) {
            PreNode = tempNode;
            tempNode = tempNode->_Next;
        }

        // check if the current is at the node we want to delete or not.
        if (_Current == temp_DeleteNode) {
            _Current = _Head;
        }

        PreNode->_Next = temp_DeleteNode->_Next;
        delete temp_DeleteNode;
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
    
    singlyList(T value) {
        _Node* newNode = new _Node;
        newNode->_Value = value;
        newNode->_Next = nullptr;

        _Current = newNode;
        _Head = newNode;
        _Tail = newNode;
        _Count++;
    }
    
    singlyList() {
        _Current = nullptr;
        _Head = nullptr;
        _Tail = nullptr;
    }
    
    // return current value if it's not empty.
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
    int getSize () const {
        return _Count;
    }
    
    // check the existance of node by the value.
    bool find(T searchVal) {
        return _FindNode(searchVal) != nullptr;
    }
    
    // check the existance of node by the value and set it as current.
    bool setAsCurrent(T  Val) {
        _Node* currentNode = _FindNode(Val);
        if (currentNode != nullptr) {
            _Current = currentNode;
            return true;
        }
        return false;
    }

    bool insertAtTheBeginning(T newVal) {
        return _InsertAtTheBeginning(newVal);
    }

    bool insertAtTheEnd(T newVal) {
        return _InsertAtTheEnd(newVal);
    }

    bool insertAfter(T preVal, T newVal) {
        return _InsertAfter(preVal, newVal);
    }

    bool deleteFirstNode() {
        return _DeleteFirstNode();
    }

    bool deleteLastNode() {
        return_DeleteLastNode();
    }

    bool deleteNode(T deleteVal) {
        return _DeleteNode(deleteVal);
    }

    void deleteFullList() {
        return _DeleteFullList();
    }

    ~singlyList() {
        _DeleteFullList();
    }
};