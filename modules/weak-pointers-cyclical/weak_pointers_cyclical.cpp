// https://www.youtube.com/watch?v=M0GLQEfplxs (12:45)

#include <print>
#include <memory>

struct B;

struct A {
  std::shared_ptr<B> p_B;
  A() { std::print("A created.\n");}
  ~A() { std::print("A destroyed.\n");}
};

struct B {
  std::shared_ptr<A> p_A;
  B() { std::print("A created.\n");}
  ~B() { std::print("A destroyed.\n");}
};


struct B2;

struct A2 {
  std::shared_ptr<B2> p_B;
  A2() { std::print("A created.\n");}
  ~A2() { std::print("A destroyed.\n");}
};

struct B2 {
  std::weak_ptr<A2> p_A;
  B2() { std::print("A created.\n");}
  ~B2() { std::print("A destroyed.\n");}
};

int main() {

  // At the end of this scope, neither object gets destroyed, due to the cyclical reference A <-> B
  {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->p_B = b;
    b->p_A = a;
  }

  // But here, it works, because the weak pointer in B2 doesn't prevent the A2 instance from dying.
  std::print("\n");
  {
    std::shared_ptr<A2> a = std::make_shared<A2>();
    std::shared_ptr<B2> b = std::make_shared<B2>();
    a->p_B = b;
    b->p_A = a;
  }

}
