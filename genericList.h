#ifndef GENERIC_LINKED_LIST_H_
#define GENERIC_LINKED_LIST_H_

#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
 private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head;
  Node* tail;
  int size;

 public:
  LinkedList() : head(nullptr), tail(nullptr), size(0) {}

  void insert(T data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    if (tail == nullptr) {
      tail = new_node;
    }
    size++;
  }

  void append(T data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = nullptr;
    if (tail != nullptr) {
      tail->next = new_node;
    }
    tail = new_node;
    if (head == nullptr) {
      head = new_node;
    }
    size++;
  }

  void remove(T data) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr) {
      if (current->data == data) {
        if (previous != nullptr) {
          previous->next = current->next;
        } else {
          head = current->next;
        }
        if (current == tail) {
          tail = previous;
        }
        delete current;
        size--;
        return;
      }
      previous = current;
      current = current->next;
    }
  }

  T* find(T data) {
    Node* current = head;
    while (current != nullptr) {
      if (current->data == data) {
        return &(current->data);
      }
      current = current->next;
    }
    return NULL;
  }

	T findParent(T data){
		if(intfindParent(data)==NULL)
			return data;
		return *intfindParent(data);


	}
  
  T* intfindParent(T data) {
    Node* current = head;
    while (current != nullptr) {
      if (current->data == data) {
		if(current->next!=NULL)
        return &current->next->data;
      }
      current = current->next;
    }
    return NULL;
  }

  void clear() {
    Node* current = head;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  int get_size() { return size; }
};

#endif