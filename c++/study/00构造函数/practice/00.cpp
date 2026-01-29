#include <iostream>
class A {
  int val;
public:
  A(int val_ = 3) : val(val_) {}
  int getVal() const { return val; }
};
class complex {
public:
  complex(double r = 0, double i = 0) : re(r), im(i){}
  int getA() const { return a.getVal(); }
private:
  double re, im;
  A a;
};
int main() {
  complex c1;
  std::cout << c1.getA();
}
