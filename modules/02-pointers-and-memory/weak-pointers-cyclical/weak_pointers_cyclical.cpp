// https://www.youtube.com/watch?v=M0GLQEfplxs (12:45)

#include <print>
using std::print;

#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

namespace {

  struct B;  // forward declaration so B can appear in the definition of A

  struct A {
    shared_ptr<B> p_B;
    A() { print("A created.\n");}
    ~A() { print("A destroyed.\n");}
  };

  struct B {
    shared_ptr<A> p_A;
    B() { print("B created.\n");}
    ~B() { print("B destroyed.\n");}
  };

  struct B2;

  struct A2 {
    shared_ptr<B2> p_B;
    A2() { print("A created.\n");}
    ~A2() { print("A destroyed.\n");}
  };

  struct B2 {
    weak_ptr<A2> p_A;
    B2() { print("B created.\n");}
    ~B2() { print("B destroyed.\n");}
  };

} // namespace

int main() {

  // At the end of this scope, neither object gets destroyed, due to the cyclical reference A <-> B
  {
    const shared_ptr<A> a = make_shared<A>();
    const shared_ptr<B> b = make_shared<B>();
    a->p_B = b;
    b->p_A = a;
  }

  // But here, it works, because the weak pointer in B2 doesn't prevent the A2 instance from dying.
  print("\n");
  {
    const shared_ptr<A2> a = make_shared<A2>();
    const shared_ptr<B2> b = make_shared<B2>();
    a->p_B = b;
    b->p_A = a;
  }

}
