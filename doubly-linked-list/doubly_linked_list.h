
#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int data; // could be a struct to hold more data
  struct node_t* previous;
  struct node_t* next;
} node_t;

void add_at(int data, int position);
void add_at_beginning(int data);
void add_at_end(int data);
void remove(int data);
void print();
void print_in_reverse();
