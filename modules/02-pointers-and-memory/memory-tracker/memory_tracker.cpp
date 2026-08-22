
// Demonstrate a hack to monitor heap memory usage. 
// See here: https://www.youtube.com/watch?v=sLlGEUO_EGE&list=WL&index=100

#include <cstdint>
#include <memory>
#include <iostream>
using std::cout;
using std::endl;


namespace {

  struct AllocationMetrics {
    uint32_t total_bytes_allocated = 0;
    uint32_t total_bytes_freed = 0;
    uint32_t get_current_usage() const { return total_bytes_allocated - total_bytes_freed; }
  };

  AllocationMetrics s_allocation_metrics;

  struct Object {
    int x, y, z;
  };

  void print_memory_usage() {
    cout << "Memory usage: " << s_allocation_metrics.get_current_usage() << " bytes\n";
  }

}

// Override the new operator so that we can do other stuff at the same time.
void* operator new(const size_t size) {
  s_allocation_metrics.total_bytes_allocated += size;
  return malloc(size);
}

void operator delete(void* memory, const size_t size) {
  s_allocation_metrics.total_bytes_freed += size;
  free(memory);
}


int main() {

  // Start with 0 bytes allocated.
  print_memory_usage();

  // Check after allocating an Object instance on the heap.
  const Object* p_object_1 = new Object;
  print_memory_usage();

  // Check again after creating another Object instance (4 bytes x 3 = 12 bytes)...
  { 
    std::unique_ptr<Object> p_object_2 = std::make_unique<Object>();
    print_memory_usage();
  }

  // ...and check again after the most recent Object is automatically destroyed when the previous local scope ends.
  print_memory_usage();

  // Finally, hopefully we're back to zero after deleting our first Object instance.
  delete p_object_1;
  print_memory_usage();
}
