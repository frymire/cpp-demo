// Demo a stack data structure using smart pointers instead of raw pointers.

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::unique_ptr;

namespace {

  template<typename T>
  struct Node {
    T m_data;
    unique_ptr<Node> m_next;
    Node(const T data, unique_ptr<Node> next) : m_data(data), m_next(std::move(next)) {}
    ~Node() { cout << "Deleting Node, data = " << m_data << ".\n"; }
    [[nodiscard]] Node* get_next() const { return m_next.get(); }
    void print() const { cout << m_data << endl; }
  };

  template<typename T>
  class Stack {
    unique_ptr<Node<T>> m_head;

  public:
    Stack() { cout << "Constructing Stack" << endl; };

    ~Stack() {
      cout << "Destroying Stack\n";
      // With each move, the Stack instance takes ownership of the next node from the current node. With this
      // assignment, the current node loses its reference and unique_ptr deletes it.
      while (m_head) { m_head = std::move(m_head->m_next); }
    }

    void add(const T data) {
      // We transfer ownership of the stack's current head node to the new node as we make it, and then the stack
      // takes ownership of the new node.
      m_head = std::make_unique<Node<T>>(data, std::move(m_head));
    }

    void print() const {
      // It is appropriate and idiomatic to use a raw pointer for a non-owning iterator.
      const Node<T>* node = m_head.get();
      while (node) {
        node->print();
        node = node->get_next();
      }
    }
  };

}  // namespace

int main() {
  Stack<float> stack{};
  stack.add(1.1);
  stack.add(2.1);
  stack.add(3.1);
  stack.print();
  return 0;
}
