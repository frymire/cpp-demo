#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::unique_ptr;

namespace {

  struct Deleter {
    void operator()(const int* t) const {
      cout << "Deleting Node data.\n";
      delete t;
    }
  };

  class Node {
    unique_ptr<int, Deleter> m_data;

  public:
    Node* m_next = nullptr;
    Node(const int data, Node* next) : m_data(new int(data)), m_next(next) {}
    ~Node() { cout << "Deleting Node, data = " << *m_data << ".\n"; }
    [[nodiscard]] Node* get_next() const { return m_next; }
    void print() const { cout << *m_data << endl; }
  };

  class MyList {
    Node* m_head = nullptr;

  public:
    MyList() { cout << "MyList constructor" << endl; };

    ~MyList() {
      cout << "Destroying MyList\n";
      while (m_head != nullptr) {
        Node* next = m_head->get_next();
        delete m_head;
        m_head = next;
      }
    }

    void add(const int data) { m_head = new Node(data, m_head); }

    void print() const {
      const Node* node = m_head;
      while (node != nullptr) {
        node->print();
        node = node->get_next();
      }
    }
  };

}  // namespace

int main() {
  MyList list{};
  list.add(1);
  list.add(2);
  list.add(3);
  list.print();
  return 0;
}
