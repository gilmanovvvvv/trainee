//SinglyLinkedList.h:
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
    void insert(const T& value, int index);
    void remove(int index);
    int search(const T& value);
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
void SinglyLinkedList<T>::insert(const T& value, int index) {
    if (index < 0) {
        std::cerr << "Invalid index" << std::endl;
        return;
    }

    Node* newNode = new Node(value);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    int currIndex = 0;
    while (temp && currIndex < index - 1) {
        temp = temp->next;
        currIndex++;
    }

    if (!temp) {
        std::cerr << "Invalid index." << std::endl;
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

template <class T>
void SinglyLinkedList<T>::remove(int index) {
    if (index < 0) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    if (index == 0) {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            std::cerr << "List is already empty." << std::endl;
        }
        return;
    }

    Node* curr = head;
    Node* prev = nullptr;
    int currIndex = 0;

    while (curr && currIndex < index) {
        prev = curr;
        curr = curr->next;
        currIndex++;
    }

    if (!curr) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
}

template <class T>
int SinglyLinkedList<T>::search(const T& value) {
    Node* curr = head;
    int index = 0;
    while (curr) {
        if (curr->data == value) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1; //Если элемент не найден
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
