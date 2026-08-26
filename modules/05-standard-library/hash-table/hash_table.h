
#pragma once

#include <cstdio>
#include <cstdlib>
// ReSharper disable once CppUnusedIncludeDirective
#include <cstring>

class Entry {
public:
  char* m_key;
  char* m_value;
  Entry* m_next;
  Entry(const char* key, const char* value);
  ~Entry();
  static unsigned int Hash(const char* m_key, int table_size);
};

class HashTable {
public:
  const int k_table_size;
  Entry** m_entries;
  explicit HashTable(int table_size);
  ~HashTable();
  void set(const char* key, const char* value) const;
  char* get(const char* key) const;
  void remove(const char* key) const;
  void print() const;
};
