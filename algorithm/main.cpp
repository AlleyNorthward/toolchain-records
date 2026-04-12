struct Attrs {
  int hp;
  int mp;
  int attack;
  int defense;
};

class RoleStateMemento {
private:
  Attrs attrs;

public:
  RoleStateMemento(Attrs a_) : attrs(a_) {}
  RoleStateMemento() {}
  Attrs getAttrs() const { return attrs; }
};

class GameRole {
private:
  Attrs attrs;

public:
  GameRole(int hp, int mp, int attack, int defense)
      : attrs({hp, mp, attack, defense}) {}
  friend std::ostream &operator<<(std::ostream &os, const GameRole &g) {
    os << "HP=" << g.attrs.hp << ", MP=" << g.attrs.mp << ", ATK="
       << g.attrs.attack << ", DEF=" << g.attrs.defense;
    return os;
  }

  RoleStateMemento save() const { return RoleStateMemento(attrs); }
  void restore(const RoleStateMemento &m) { attrs = m.getAttrs(); }
  void fightBoss() {
    attrs.hp -= 50;
    attrs.mp -= 30;
    attrs.attack -= 10;
    attrs.defense -= 5;
  }
};

class SaveManager {
private:
  RoleStateMemento memento;

public:
  void setMemento(const RoleStateMemento &m) { memento = m; }
  RoleStateMemento getMemento() const { return memento; }
};

int main() {
  GameRole role(100, 80, 30, 20);
  SaveManager manager;
  std::cout << "进入战斗前: " << role << std::endl;

  manager.setMemento(role.save());
  role.fightBoss();
  std::cout << "战斗后: " << role << std::endl;

  role.restore(manager.getMemento());
  std::cout << "恢复后: " << role << std::endl;
}
