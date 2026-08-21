
#include "doubly_linked_list.h"

Node::~Node() {
  printf("deleting node with data %d\n", m_data);
  // If the data were allocated on the heap, you'd delete it here.
  // Don't call delete on the previous and next pointers, though, since 
  // that will be handled by the linked list.
}

// Good explanation here: https://www.youtube.com/watch?v=jgmQjit6wSc
DoublyLinkedList::~DoublyLinkedList() { 
  Node* next;
  while (m_head != NULL) {
    next = m_head->m_next;
    delete m_head;
    m_head = next;
  }
}

void DoublyLinkedList::AddAt(int data, int target_position) {

  // If this is the first item in the list...
  if (m_head == NULL) {
    m_head = new Node(data, NULL, NULL);
    return;
  }

  // Otherwise, seek to the requested position or the end of the list, 
  // while keeping track of the previous and current nodes.
  int position = 0;
  Node* previous = NULL;
  Node* current = m_head;
  while (position != target_position && current != NULL) {
    ++position;
    previous = current;
    current = current->m_next;
  }

  // If the insertion point is the head of the list...
  if (position == 0) {
    m_head = new Node(data, NULL, current);
    current->m_previous = m_head;
    return;
  }

  // If the insertion point is the end of the list...
  if (current == NULL) {
    previous->m_next = new Node(data, previous, NULL);
    return;
  }

  // If the insertion point is in the middle of the list...
  previous->m_next = new Node(data, previous, current);
  current->m_previous = previous->m_next;
}

void DoublyLinkedList::AddAtBeginning(int data) { AddAt(data, 0); }

void DoublyLinkedList::AddAtEnd(int data) { AddAt(data, -1); }

void DoublyLinkedList::Remove(int data) {

  // Seek until we find the data item or hit the end of the list.
  Node* current = m_head;
  while (current->m_data != data && current != NULL) { current = current->m_next; }

  // If we reach the end of the list without finding the item, do nothing.
  if (current == NULL) { return; }

  // If there's only one item in the list...
  if (current->m_previous == NULL && current->m_next == NULL) {
    m_head = NULL;
    delete current;
    return;
  }

  // If the item is at the beginning of a list with more than one item...
  if (current->m_previous == NULL && current->m_next != NULL) {
    m_head = current->m_next;
    m_head->m_previous = NULL;
    delete current;
    return;
  }

  // If the item is at the end of the list...
  if (current->m_next == NULL) {
    current->m_previous->m_next = NULL;
    delete current;
    return;
  }

  // Otherwise, we have the item is in the middle of the list...
  current->m_previous->m_next = current->m_next;
  current->m_next->m_previous = current->m_previous;
  delete current;
  return;
}

void DoublyLinkedList::Print() {
  Node* current = m_head;
  while (current != NULL) {
    printf("data: %d\n", current->m_data);
    current = current->m_next;
  }
}

void DoublyLinkedList::PrintInReverse() {
  Node* current = m_head;
  while (current->m_next != NULL) { current = current->m_next; } // seek to the end
  while (current != NULL) {
    printf("data: %d\n", current->m_data);
    current = current->m_previous;
  }
}
