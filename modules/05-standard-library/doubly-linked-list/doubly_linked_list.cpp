
// Good explanation here: https://www.youtube.com/watch?v=jgmQjit6wSc
//
// ReSharper disable CppJoinDeclarationAndAssignment

#include <cstdio>

#include "doubly_linked_list.h"

Node::~Node() {
  printf("deleting node with data %d\n", m_data);
  // If the data were allocated on the heap, you'd delete it here.
  // Don't call delete on the previous and next pointers, though, since 
  // that will be handled by the linked list.
}

DoublyLinkedList::~DoublyLinkedList() {
  Node* next;
  while (m_head != nullptr) {
    next = m_head->m_next;
    delete m_head;
    m_head = next;
  }
}

void DoublyLinkedList::add_at(const int data, int target_position) {

  // If this is the first item in the list...
  if (m_head == nullptr) {
    m_head = new Node(data, nullptr, nullptr);
    return;
  }

  // Otherwise, seek to the requested position or the end of the list, 
  // while keeping track of the previous and current nodes.
  int position = 0;
  Node* previous = nullptr;
  Node* current = m_head;
  while (position != target_position && current != nullptr) {
    ++position;
    previous = current;
    current = current->m_next;
  }

  // If the insertion point is the head of the list...
  if (position == 0) {
    m_head = new Node(data, nullptr, current);
    current->m_previous = m_head;
    return;
  }

  // If the insertion point is the end of the list...
  if (current == nullptr) {
    previous->m_next = new Node(data, previous, nullptr);
    return;
  }

  // If the insertion point is in the middle of the list...
  previous->m_next = new Node(data, previous, current);
  current->m_previous = previous->m_next;
}

void DoublyLinkedList::add_at_beginning(const int data) { add_at(data, 0); }

void DoublyLinkedList::add_at_end(const int data) { add_at(data, -1); }

void DoublyLinkedList::remove(const int data) {

  // Seek until we find the data item or hit the end of the list.
  const Node* p_node = m_head;
  while (p_node->m_data != data && p_node != nullptr) { p_node = p_node->m_next; }

  // If we reach the end of the list without finding the item, do nothing.
  if (p_node == nullptr) { return; }

  // If there's only one item in the list...
  if (p_node->m_previous == nullptr && p_node->m_next == nullptr) {
    m_head = nullptr;
    delete p_node;
    return;
  }

  // If the item is at the beginning of a list with more than one item...
  if (p_node->m_previous == nullptr && p_node->m_next != nullptr) {
    m_head = p_node->m_next;
    m_head->m_previous = nullptr;
    delete p_node;
    return;
  }

  // If the item is at the end of the list...
  if (p_node->m_next == nullptr) {
    p_node->m_previous->m_next = nullptr;
    delete p_node;
    return;
  }

  // Otherwise, we have the item is in the middle of the list...
  p_node->m_previous->m_next = p_node->m_next;
  p_node->m_next->m_previous = p_node->m_previous;
  delete p_node;
}

void DoublyLinkedList::print() const {
  const Node* p_node = m_head;
  while (p_node != nullptr) {
    printf("data: %d\n", p_node->m_data);
    p_node = p_node->m_next;
  }
}

void DoublyLinkedList::print_in_reverse() const {
  const Node* p_node = m_head;
  while (p_node->m_next != nullptr) { p_node = p_node->m_next; } // seek to the end
  while (p_node != nullptr) {
    printf("data: %d\n", p_node->m_data);
    p_node = p_node->m_previous;
  }
}
