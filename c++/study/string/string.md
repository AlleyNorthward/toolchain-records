&emsp;&emsp;@author 巷北  
&emsp;&emsp;@time 2026-01-28 18:31:52  

- [string](#string)
    - [基础string](#基础string)
    - [进阶string](#进阶string)

## string
&emsp;&emsp;这似乎是一切的开始, 所以我们就直接从这里开始讲解吧.<br>

### 基础string
~~~cpp
int main() {
  std::string s = "123456";
  std::cout << s;
}
~~~

- 这是一个再基础不过的`string` 类型对象了. 这里, 我们给它赋初值为`"123456"`. 当然, 我们也可以改变初值.
~~~cpp
int main() {
  std::string s = "123456";
  s = "1234";
  std::cout << s;
}
~~~
- 毫无疑问, 这都是合法的. 如果我们添加了`const`, 那么就必须赋初值, 且值不能变.
~~~cpp
int main() {
  const std::string s;
  std::cout << s;
}
~~~
- 如下所示, 虽然没给`s` 赋值, 但实际上调用了它的默认构造函数, 是一个空字符串. 关于其底层, 实际上是这样的.
~~~cpp
namespace std {
    typedef basic_string<char> string;
}
~~~
- 对于`basic_string` 类, 这里不作讨论, 知道即可.

### 进阶string
- 对于`"123456"`而言, 我们可以理解为`string`, 但实际上也可能是`const char[7]`类型的.
~~~cpp
int main(){
    std::string s = "123456";
    const char ss[7] = {'1', '2', '3', '4', '5', '6', '\0'};
    std::cout << (s == ss);
}
~~~
- 最终结果输出为`1`. 底层可能是调用了`string` 的`==`重载函数. 但换个位置仍然输出为`1`, 此时可能调用的是全局的重载`==`函数. 类型是不一的, 但是效果可以保持一致.
- 需要注意, `ss` 中, 单个字符使用的是`''`, 用`""` 不行.
- 对于一个`"123456"`对象而言, 它是`const char[7]`类型, 但会被隐式转换为`string`类型. 具体表现可以看如下代码.
~~~cpp
void print(const std::string &s) {
  std::cout << s << std::endl;
}

int main() {
  std::string s = "123456";
  const char ss[7] = {'1', '2', '3', '4', '5', '6', '\0'};
  print(s);
  print(ss);
  print("123456");
}
~~~
- 输出结果都是`123456`, 那么内部到底发生了什么呢?
    - 对于`ss`, 其最终退化为`const char*` 类型, 而`string` 中有个构造函数是接收该类型参数的, 于是产生个临时`string`类型变量, 最终将`const char*`隐式地转换为`string`类型.
    - `"123456"`, 也是同一个道理, 本质上也是`const char*`, 走的还是上面的路线.


















