#include <iostream>
class complex {
public:
  complex(double r = 0, double i = 0) : re(r), im(i) {}

  double real() const { return re; }
  double imag() const { return im; }

private:
  double re, im;
};

int main() {
  complex c1(2, 3);
  const complex c2(3, 4);

  std::cout << c1.real() << " " << c1.imag() << std::endl;
  std::cout << c2.real() << " " << c2.imag() << std::endl;
}

