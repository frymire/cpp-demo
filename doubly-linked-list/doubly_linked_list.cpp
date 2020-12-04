
#include "doubly_linked_list.h"

node_t* head = NULL;

void add_at(int data, int target_position) {

  node_t* node = (node_t*) malloc(sizeof(node_t));
  node->data = data;
  node->previous = NULL;
  node->next = NULL;

  // Handle the case when this is the first item in the list.
  if (head == NULL) {
    head = node;
    return;
  }

  // Walk through list until the requested position or the end is reached.
  // Keep track of the previous and current nodes along the way.
  int position = 0;
  node_t* previous = NULL;
  node_t* current = head;
  while (position != target_position && current != NULL) {
    ++position;
    previous = current;
    current = current->next;
  }

  // If the insertion point is the head of the list...
  if (position == 0) {
    head = node;
    node->next = current;
    current->previous = node;
    return;
  }

  // Otherwise, if the insertion point is the end of the list...
  if (current == NULL) {
    previous->next = node;
    node->previous = previous;
    return;
  }

  // Otherwise, the insertion point is in the middle of the list...
  previous->next = node;
  current->previous = node; 
  node->previous = previous;
  node->next = current;  
}

void add_at_beginning(int data) { add_at(data, 0); }

void add_at_end(int data) { add_at(data, -1); }

void remove(int data) {

  node_t* current = head;

  while (current != NULL && current->data != data) { current = current->next; }

  // If we didn't find the item, do nothing.
  if (current == NULL) { return; }

  // handle first item
  if (current->previous == NULL) {
    if (current->next == NULL) {
      // only item?
      head = NULL;
    } else {
      // more items?
      head = current->next;
      head->previous = NULL;
    }

    free(current);
    return;
  }

  // handle last item
  if (current->next == NULL) {
    current->previous->next = NULL;
    free(current);
    return;
  }

  // handle middle item
  if (current->previous != NULL && current->next != NULL) {
    current->previous->next = current->next;
    current->next->previous = current->previous;
    free(current);
    return;
  }
}

void print() {
  node_t* current = head;
  while (current != NULL) {
    printf("data: %d\n", current->data);
    current = current->next;
  }
}

void print_in_reverse() {
  node_t* current = head;
  while (current->next != NULL) { current = current->next; } // seek to the end
  while (current != NULL) {
    printf("data: %d\n", current->data);
    current = current->previous;
  }
}
