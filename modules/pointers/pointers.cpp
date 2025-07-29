
#include <iostream>
using std::cout;
using std::endl;

#include <memory> // smart pointers
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class Entity {
public:
  Entity() { cout << "Created an Entity!" << endl; }
  ~Entity() { cout << "Destroyed an Entity!" << endl; }
};

int main() {

  // unique_ptr: a scoped pointer that gets a delete call at the end of the scope in which it is created
  //   -- can't be copied, because when one instance dies, delete will be called and other pointers would be orphaned
  {
    cout << "Demo unique_ptr...\n"; 
    unique_ptr<Entity> entity1(new Entity()); // works
    unique_ptr<Entity> entity2 = make_unique<Entity>(); // preferred to avoid dangling pointers with exceptions

    // Note that you can't call "new Entity()", because the unique_ptr constructor is explicit.
    //unique_ptr<Entity> entity = new Entity(); // compile error

    // You also can't assign a unique_ptr, because the copy constuctor has been deleted.
    //Entity* myPtrEntity = entity1; // compile error
  }

  // shared_ptr: uses reference counting to decide whether to call delete when a pointer goes out of scope
  {
    cout << "\n\nDemo shared_ptr...\n";
    shared_ptr<Entity> ptr_future_entity;
    //shared_ptr<Entity> shared_entity(new Entity()); // avoid, causes extra copying
    {
      shared_ptr<Entity> shared_entity1 = make_shared<Entity>(); // creates the Entity
      shared_ptr<Entity> shared_entity2 = shared_entity1; // reference the existing Entity
      ptr_future_entity = shared_entity2; // reference the existing Entity again
      cout << "Shared Entity not deleted yet in inner scope...\n";
    }
    cout << "Shared Entity still not deleted in outer scope...\n";
  }
  cout << "Shared Entity finally deleted.\n";
}
