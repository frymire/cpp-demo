// https://www.youtube.com/watch?v=M0GLQEfplxs

// ReSharper disable CppTooWideScope

#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

#include <print>
using std::print;

namespace {

  struct Object {
    int data;
    explicit Object(const int data) : data(data) { print("Object created.\n"); }
    ~Object() { print("Object destroyed.\n"); }
  };

  struct StrongManager {
    shared_ptr<Object> p_object;  // this reference would prevent the object from dying
  };

  struct [[maybe_unused]] BadWeakManager {

    // We don't want this reference to keep the target from dying. We try using a raw pointer, setting it perhaps
    // by calling get() on a shared or unique pointer.
    Object* p_object;

    [[maybe_unused]] void print() const {
      // Checking for a null pointer isn't meaningful here, because we don't know if the target object was destroyed
      // since object was set.
      if (p_object) {
        std::print("{}\n", p_object->data);  // might point to deleted data
      }
    }
  };

  struct WeakManager {

    weak_ptr<Object> p_object;

    void print() const {
      // Check if the object still exists. lock() returns a shared pointer valid in this scope to
      // protect against, for example, another thread deleting the object before the next access.
      if (shared_ptr<Object> p_object_shared = p_object.lock()) {
        std::print("{}\n", p_object_shared->data);  // access here is now safe
      } else {
        std::print("Object no longer exists.\n");
      }
    }

    // Can do this if you're just curious whether the object still exists, but you don't need a lock to access it.
    const char* object_exists() const { return p_object.expired() ? "false" : "true"; }

  };

}  // namespace

int main() {

  WeakManager weak_manager;

  {
    const shared_ptr<Object> p_object = make_shared<Object>(42);
    print("Object use count: {}\n", p_object.use_count()); // 1

    StrongManager strong_manager;
    strong_manager.p_object = p_object;
    print("Object use count: {}\n", p_object.use_count()); // 2

    weak_manager.p_object = p_object;
    print("Object still exists: {}\n", weak_manager.object_exists());
    print("Object use count: {}\n", p_object.use_count()); // still 2
    weak_manager.print();
  }

  print("Object still exists: {}\n", weak_manager.object_exists());
  print("Object use count: {}\n", weak_manager.p_object.use_count()); // 0
  // The weak manager holds a weak reference to the now-deleted object, but invoking this doesn't cause an error.
  weak_manager.print();

  return 0;
}
