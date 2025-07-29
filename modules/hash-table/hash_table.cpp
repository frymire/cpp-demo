
#include "hash_table.h"

Entry::Entry(const char* key, const char* value) {
  m_key = (char*) malloc(strlen(key) + 1);
  m_value = (char*) malloc(strlen(value) + 1);
  m_next = NULL;
  strcpy(m_key, key);
  strcpy(m_value, value);
}

Entry::~Entry() {
  printf("Destructing Entry: %s = %s\n", m_key, m_value);
  free(m_key);
  free(m_value);
}

// Treat the key as a sequence of 8-bit integers, apply an iterative function 
// using each one, and return the value modulo kTableSize.
unsigned int Entry::Hash(const char* key, const int table_size) {
  int key_length = strlen(key);
  unsigned long int hash_value = 0;
  for (int i = 0; i < key_length; ++i) { hash_value = 37*hash_value + key[i]; }
  return hash_value % table_size;
}


HashTable::HashTable(int table_size): kTableSize(table_size) {
  m_entries = (Entry**) malloc(sizeof(Entry*)*kTableSize);
  for (int i = 0; i < kTableSize; ++i) { m_entries[i] = NULL; }
}

HashTable::~HashTable() {

  for (int i = 0; i < kTableSize; ++i) {

   // Delete each entry in slot i.
    Entry* head = m_entries[i];
    Entry* next;
    while (head != NULL) {
      next = head->m_next;
      delete head;
      head = next;
    }
  }

  // Delete the entries array itself.
  delete m_entries;
}

void HashTable::Set(const char *key, const char *value) {

  // Check for any existing entries in the slot associated with the key's hash value.
  unsigned int slot = Entry::Hash(key, kTableSize);
  Entry* entry = m_entries[slot];

  // If there is no existing entry, simply add the new one.
  if (entry == NULL) {
    m_entries[slot] = new Entry(key, value);
    return;
  }

  // Otherwise, walk through each entry in the slot until either a matching key is found
  // the end is reached.
  Entry* previous = NULL;
  while (entry != NULL) {

    // If we find a matching key, replace the value.
    if (strcmp(entry->m_key, key) == 0) {
      free(entry->m_value);
      entry->m_value = (char*) malloc(strlen(value) + 1);
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

char* HashTable::Get(const char* key) {

  // Get the head entry, if any, in the slot associated with the key's hash.
  Entry* entry = m_entries[Entry::Hash(key, kTableSize)];

  // If the slot is empty, return NULL.
  if (entry == NULL) { return NULL; }

  // Otherwise walk the slot's entries, returning the value if a key match is found.
  while (entry != NULL) {
    if (strcmp(entry->m_key, key) == 0) { return entry->m_value; }
    entry = entry->m_next;
  }

  // If you reach the end of the slot without a match, return NULL.
  return NULL;
}

void HashTable::Remove(const char* key) {

  // Get the head entry, if any, in the slot associated with the key's hash.
  unsigned int slot = Entry::Hash(key, kTableSize);
  Entry* entry = m_entries[slot];

  // If the slot is empty, there is nothing to remove.
  if (entry == NULL) { return; }

  // Otherwise, walk entries until we find a matching key or hit the end.
  Entry* previous = NULL;
  int i = 0;
  while (entry != NULL) {

    // If the key is a match, fix up the neighboring data structures and delete the entry...
    if (strcmp(entry->m_key, key) == 0) {

      // Only 1 entry...
      if (i == 0 && entry->m_next == NULL) { m_entries[slot] = NULL; }

      // First entry, with a next entry...
      if (i == 0 && entry->m_next != NULL) { m_entries[slot] = entry->m_next; }

      // Last entry...
      if (i != 0 && entry->m_next == NULL) { previous->m_next = NULL; }

      // Middle entry...
      if (i != 0 && entry->m_next != NULL) { previous->m_next = entry->m_next; }

      delete entry;
      return;
    }

    // Walk to the next entry.
    previous = entry;
    entry = previous->m_next;
    ++i;
  }
}

void HashTable::Print() {

  for (int i = 0; i < kTableSize; ++i) {

    // Get the head entry in slot i.
    Entry* entry = m_entries[i];

    // If the slot is empty, move on to the next slot.
    if (entry == NULL) { continue; }

    // Otherwise, loop over the entries in the slot, printing out each key-value pair.
    printf("slot[%d]:\n", i);
    while (entry != NULL) {
      printf("  %s = %s\n", entry->m_key, entry->m_value);
      entry = entry->m_next;
    }

    printf("\n");
  }
}
