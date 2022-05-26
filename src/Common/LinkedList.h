#pragma once

#include <functional>
#include <iostream>

namespace Common {

template<typename T>
class Node {
  public:
    T data;
    Node* next;

    Node(T data) {
      this->data = data;
    }
};

template<typename T>
class LinkedList {
  public:
    Node<T>* head;

    void create_node(T data);
    void for_each(std::function<void(T)> callback);

  private:
    Node<T>* node;
};

}
