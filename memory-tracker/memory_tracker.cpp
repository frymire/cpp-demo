
#include <iostream>
using std::cout;
using std::endl;

// Demonstrate a hack to monitor heap memory usage. See here: https://www.youtube.com/watch?v=sLlGEUO_EGE&list=WL&index=100

struct AllocationMetrics {
  uint32_t total_bytes_allocated = 0;
  uint32_t total_bytes_freed = 0;
  uint32_t GetCurrentUsage() { return total_bytes_allocated - total_bytes_freed; }
};

static AllocationMetrics s_AllocationMetrics;

// Override the new operator so that we can do other stuff at the same time.
void* operator new(size_t size) {
  s_AllocationMetrics.total_bytes_allocated += size;
  return malloc(size);
}

void operator delete(void* memory, size_t size) {
  s_AllocationMetrics.total_bytes_freed += size;
  free(memory);
}

struct Object {
  int x, y, z;
};

static void PrintMemoryUsage() {
  cout << "Memory usage: " << s_AllocationMetrics.GetCurrentUsage() << " bytes\n";
}

int main() {

  // Start with 0 bytes allocated.
  PrintMemoryUsage();

  // Check after allocating some Object instances on the heap.
  Object* myObject = new Object;
  PrintMemoryUsage();

  // Check again after creating an Object instance (4 bytes x 3 = 12 bytes)... 
  { 
    std::unique_ptr<Object> obj = std::make_unique<Object>(); 
    PrintMemoryUsage(); 
  }

  // ...and check again after the Object is automatically destroyed when the previous scope ends.
  PrintMemoryUsage();

  // Finally, hopefully we're back to zero after deleting our first Object instance.
  delete myObject;
  PrintMemoryUsage();
}
