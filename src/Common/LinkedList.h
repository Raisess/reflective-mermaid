#pragma once

#include <functional>
#include <iostream>

namespace Common {

template<typename T>
class Node {
  public:
    T data;
    Node* next = NULL;

    Node(T data) {
      this->data = data;
    }
};

template<typename T>
class LinkedList {
  public:
    Node<T>* head = NULL;

    void create_node(T data);
    void iterate(std::function<void(T)> callback);
};

}
