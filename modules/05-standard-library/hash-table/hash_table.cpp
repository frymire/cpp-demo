
#include "hash_table.h"


Entry::Entry(const char* key, const char* value) {
  m_key = static_cast<char*>(malloc(strlen(key) + 1));
  m_value = static_cast<char*>(malloc(strlen(value) + 1));
  m_next = nullptr;
  strcpy(m_key, key);
  strcpy(m_value, value);
}

Entry::~Entry() {
  printf("Destructing Entry: %s = %s\n", m_key, m_value);
  free(m_key);
  free(m_value);
}

// Treat the key as a sequence of 8-bit integers, apply an iterative function 
// using each one, and return the value modulo k_table_size.
unsigned int Entry::Hash(const char* key, const int table_size) {
  const size_t key_length = strlen(key);
  unsigned long int hash_value = 0;
  for (int i = 0; i < key_length; ++i) { hash_value = 37*hash_value + key[i]; }
  return hash_value % table_size;
}


HashTable::HashTable(int table_size): k_table_size(table_size) {
  m_entries = static_cast<Entry**>(malloc(sizeof(Entry*) * k_table_size));
  for (int i = 0; i < k_table_size; ++i) { m_entries[i] = nullptr; }
}

HashTable::~HashTable() {

  for (int i = 0; i < k_table_size; ++i) {

   // Delete each entry in slot i.
   const Entry* head = m_entries[i];
   while (head != nullptr) {
      const Entry* next = head->m_next;
      delete head;
      head = next;
    }
  }

  // Delete the entries array itself.
  delete m_entries;
}

void HashTable::set(const char *key, const char *value) const {

  // Check for any existing entries in the slot associated with the key's hash value.
  const unsigned int slot = Entry::Hash(key, k_table_size);
  Entry* entry = m_entries[slot];

  // If there is no existing entry, simply add the new one.
  if (entry == nullptr) {
    m_entries[slot] = new Entry(key, value);
    return;
  }

  // Otherwise, walk through each entry in the slot until either a matching key is found
  // the end is reached.
  Entry* previous = nullptr;
  while (entry != nullptr) {

    // If we find a matching key, replace the value.
    if (strcmp(entry->m_key, key) == 0) {
      free(entry->m_value);
      entry->m_value = static_cast<char*>(malloc(strlen(value) + 1));
      strcpy(entry->m_value, value);
      return;
    }

    // Walk to next entry.
    previous = entry;
    entry = previous->m_next;
  }

  // If you reach the end without a match, append a new entry.
  previous->m_next = new Entry(key, value);
}

char* HashTable::get(const char* key) const {

  // Get the head entry, if any, in the slot associated with the key's hash.
  const Entry* entry = m_entries[Entry::Hash(key, k_table_size)];

  // If the slot is empty, return nullptr.
  if (entry == nullptr) { return nullptr; }

  // Otherwise walk the slot's entries, returning the value if a key match is found.
  while (entry != nullptr) {
    if (strcmp(entry->m_key, key) == 0) { return entry->m_value; }
    entry = entry->m_next;
  }

  // If you reach the end of the slot without a match, return nullptr.
  return nullptr;
}

void HashTable::remove(const char* key) const {

  // Get the head entry, if any, in the slot associated with the key's hash.
  const unsigned int slot = Entry::Hash(key, k_table_size);
  Entry* entry = m_entries[slot];

  // If the slot is empty, there is nothing to remove.
  if (entry == nullptr) { return; }

  // Otherwise, walk entries until we find a matching key or hit the end.
  Entry* previous = nullptr;
  int i = 0;
  while (entry != nullptr) {

    // If the key is a match, fix up the neighboring data structures and delete the entry...
    if (strcmp(entry->m_key, key) == 0) {

      // Only 1 entry...
      if (i == 0 && entry->m_next == nullptr) { m_entries[slot] = nullptr; }

      // First entry, with a next entry...
      if (i == 0 && entry->m_next != nullptr) { m_entries[slot] = entry->m_next; }

      // Last entry...
      if (i != 0 && entry->m_next == nullptr) { previous->m_next = nullptr; }

      // Middle entry...
      if (i != 0 && entry->m_next != nullptr) { previous->m_next = entry->m_next; }

      delete entry;
      return;
    }

    // Walk to the next entry.
    previous = entry;
    entry = previous->m_next;
    ++i;
  }
}

void HashTable::print() const {

  for (int i = 0; i < k_table_size; ++i) {

    // Get the head entry in slot i.
    const Entry* entry = m_entries[i];

    // If the slot is empty, move on to the next slot.
    if (entry == nullptr) { continue; }

    // Otherwise, loop over the entries in the slot, printing out each key-value pair.
    printf("slot[%d]:\n", i);
    while (entry != nullptr) {
      printf("  %s = %s\n", entry->m_key, entry->m_value);
      entry = entry->m_next;
    }

    printf("\n");
  }
}
