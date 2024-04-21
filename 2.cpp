SinglyLinkedList.h:
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

template <class T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void insert(const T& value);
    void remove(const T& value);
    bool search(const T& value);
    void display();
};

#include "SinglyLinkedList.cpp"

#endif

//SinglyLinkedList.cpp:

#include "SinglyLinkedList.h"
#include <iostream>

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr) {}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <class T>
void SinglyLinkedList<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

template <class T>
void SinglyLinkedList<T>::remove(const T& value) {
    Node* curr = head;
    Node* prev = nullptr;

    while (curr) {
        if (curr->data == value) {
            if (prev) {
                prev->next = curr->next;
            } else {
                head = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

template <class T>
bool SinglyLinkedList<T>::search(const T& value) {
    Node* curr = head;
    while (curr) {
        if (curr->data == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <class T>
void SinglyLinkedList<T>::display() {
    Node* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template class SinglyLinkedList<int>;
