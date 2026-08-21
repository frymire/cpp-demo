// https://www.youtube.com/watch?v=M0GLQEfplxs

#include <memory>
#include <print>

struct Object {
  int data;
  Object(int data) : data(data) { std::print("Object created.\n");}
  ~Object() { std::print("Object destroyed.\n");}
};

struct StrongManager {
  std::shared_ptr<Object> object; // this reference would prevent the object from dying
};

struct BadWeakManager {

  // We don't want this reference to keep the target from dying. We try using a raw pointer, setting it perhaps
  // by calling get() on a shared or unique pointer.
  Object* p_object;

  void print() const {
    // Checking for a null pointer isn't meaningful here, because we don't know if the target object was destroyed
    // since object was set.
    if (p_object) {
      std::print("{}\n", p_object->data);  // might point to deleted data
    }
  }
};

struct WeakManager {

  std::weak_ptr<Object> object;

  void print() const {
    // Now we can check if the object still exists.
    if (std::shared_ptr<Object> object_ = object.lock()) {
      // lock() returns a shared pointer valid in this scope that to protect against, for example, another thread
      // deleting the object before the next access.
      std::print("{}\n", object_->data);  // access here is now safe
    } else {
      std::print("Object no longer exists.\n");
    }
  }

  // Can do this if you're just curious whether the object still exists, but you don't need a lock to access it.
  int object_exists() { return object.expired() ? 0 : 1; }

};

int main() {

  WeakManager weak_manager;

  {
    std::shared_ptr<Object> object = std::make_shared<Object>(42);
    std::print("Object use count: {}\n", object.use_count()); // 1

    StrongManager strong_manager;
    strong_manager.object = object;
    std::print("Object use count: {}\n", object.use_count()); // 2

    weak_manager.object = object;
    std::print("Object still exists: {}\n", weak_manager.object_exists());
    std::print("Object use count: {}\n", object.use_count()); // still 2
    weak_manager.print();
  }

  std::print("Object still exists: {}\n", weak_manager.object_exists());
  std::print("Object use count: {}\n", weak_manager.object.use_count()); // 0
  // The weak manager holds a weak reference to the now-deleted object, but invoking this doesn't cause an error.
  weak_manager.print();

  return 0;
}
