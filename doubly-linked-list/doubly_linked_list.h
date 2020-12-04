
#pragma once

#include <stdio.h>
#include <stdlib.h>

class Node {
public:
  int m_data;
  Node* m_previous;
  Node* m_next;
  Node(int data, Node* previous, Node* next) : m_data(data), m_previous(previous), m_next(next) {}
  ~Node();
};

class DoublyLinkedList {
  Node* m_head;
public:
  DoublyLinkedList() : m_head(NULL) {}
  ~DoublyLinkedList();
  void add_at(int data, int position);
  void add_at_beginning(int data);
  void add_at_end(int data);
  void remove(int data); // Removes the first instance of a specified value from the list.
  void print();
  void print_in_reverse();
};
