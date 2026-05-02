#include <iostream>
#include <string>

using namespace std;

class Pizza {
protected:
  string name;

public:
  virtual ~Pizza() {}

  virtual void prepare() { cout << "准备原料:" << name << endl; }

  virtual void bake() { cout << "烘焙 " << name << endl; }

  virtual void cut() { cout << "切割 " << name << endl; }

  virtual void box() { cout << "打包 " << name << endl; }

  string getName() { return name; }
};

class CheesePizzaNY : public Pizza {
public:
  CheesePizzaNY() { name = "NY Cheese Pizza"; }
};

class PepperoniPizzaNY : public Pizza {
public:
  PepperoniPizzaNY() { name = "NY Pepperoni Pizza"; }
};

class ClamPizzaNY : public Pizza {
public:
  ClamPizzaNY() { name = "NY Clam Pizza"; }
};

class VeggiePizzaNY : public Pizza {
public:
  VeggiePizzaNY() { name = "NY Veggie Pizza"; }
};

class CheesePizzaChicago : public Pizza {
public:
  CheesePizzaChicago() { name = "Chicago Cheese Pizza"; }
};

class PepperoniPizzaChicago : public Pizza {
public:
  PepperoniPizzaChicago() { name = "Chicago Pepperoni Pizza"; }
};

class ClamPizzaChicago : public Pizza {
public:
  ClamPizzaChicago() { name = "Chicago Clam Pizza"; }
};

class VeggiePizzaChicago : public Pizza {
public:
  VeggiePizzaChicago() { name = "Chicago Veggie Pizza"; }
};

class PizzaStore {
public:
  virtual ~PizzaStore() {}

  Pizza *orderPizza(string type) {
    Pizza *pizza = createPizza(type);

    if (pizza == NULL) {
      cout << "无法制作该类型Pizza" << endl;
      return NULL;
    }

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    cout << "完成:" << pizza->getName() << endl << endl;

    return pizza;
  }

protected:
  virtual Pizza *createPizza(string type) = 0;
};

class NYPizzaStore : public PizzaStore {
protected:
  Pizza *createPizza(string type) {
    if (type == "cheese")
      return new CheesePizzaNY();
    if (type == "pepperoni")
      return new PepperoniPizzaNY();
    if (type == "clam")
      return new ClamPizzaNY();
    if (type == "veggie")
      return new VeggiePizzaNY();
    return NULL;
  }
};

class ChicagoPizzaStore : public PizzaStore {
protected:
  Pizza *createPizza(string type) {
    if (type == "cheese")
      return new CheesePizzaChicago();
    if (type == "pepperoni")
      return new PepperoniPizzaChicago();
    if (type == "clam")
      return new ClamPizzaChicago();
    if (type == "veggie")
      return new VeggiePizzaChicago();
    return NULL;
  }
};

int main() {
  PizzaStore *nyStore = new NYPizzaStore();
  PizzaStore *chicagoStore = new ChicagoPizzaStore();

  cout << "=== NY Store ===" << endl;
  Pizza *p1 = nyStore->orderPizza("cheese");
  delete p1;

  Pizza *p2 = nyStore->orderPizza("clam");
  delete p2;

  cout << "=== Chicago Store ===" << endl;
  Pizza *p3 = chicagoStore->orderPizza("cheese");
  delete p3;

  Pizza *p4 = chicagoStore->orderPizza("veggie");
  delete p4;

  delete nyStore;
  delete chicagoStore;

  return 0;
}
