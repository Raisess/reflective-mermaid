#include "LinkedList.h"
#include "../Syntax/Lexer.h"
#include "../Syntax/Parser.h"

template class Common::LinkedList<std::string>;
template class Common::LinkedList<Syntax::Token>;
template class Common::LinkedList<Syntax::Statement>;
template class Common::LinkedList<Syntax::PropertyStatement>;
template class Common::LinkedList<Syntax::AttributeStatement>;

template<typename T>
void Common::LinkedList<T>::create_node(T data) {
  if (this->head == NULL) {
    this->head = new Node<T>(data);
  } else {
    Node<T>* tmp = this->head;

    while (tmp->next != NULL) {
      tmp = tmp->next;
    }

    tmp->next = new Node<T>(data);
  }
}

template<typename T>
void Common::LinkedList<T>::for_each(std::function<void(T)> callback) {
  Node<T>* tmp = this->head;

  while (tmp != NULL) {
    callback(tmp->data);
    tmp = tmp->next;
  }
}
