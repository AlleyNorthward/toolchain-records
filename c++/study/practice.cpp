inline int add(int a, int b) noexcept{
  return a + b;
}
virtual std::string name() const override
int main(){
  const int x = 10;
  static double* p = nullptr;
  int a[5]{1, 2, 4};

  int (*fp)(int, int) = add;
  constexpr const int* (*ff[5])(double) noexcept;

  // 当然, 为了缓解, 现代C++提供了一系列缓解方案.
  // using
  using FP = int(*)(int, int);
  //auto
  auto fpp = add;
  //decltype 没怎么用过, 但确实不错, 可以获取对象类型
  decltype(add)* fppp;
  fppp = add;
  // trailing return Ai的, 没用过
  auto f(int x) -> int;
}
