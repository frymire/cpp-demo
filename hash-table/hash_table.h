
#pragma once

// Suppress security errors using strcpy instead of strcpy_s
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Entry {
public:
  char* m_key;
  char* m_value;
  Entry* m_next;
  Entry(const char* key, const char* value);
  ~Entry();
  static unsigned int hash(const char* m_key, const int table_size);
};

class HashTable {
public:
  const int kTableSize;
  Entry** m_entries;
  HashTable(int table_size);
  ~HashTable();
  void set(const char* key, const char* value);
  char* get(const char* key);
  void remove(const char* key);
  void print();
};
