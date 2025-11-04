#include "Monster.h"
#include <iostream>

Monster::Monster() : Character(), description("") {
    std::cout << "Monster: конструктор по умолчанию\n";
}
Monster::Monster(const std::string& n, const std::string& d)
    : Character(n), description(d) {
    std::cout << "Monster: параметризованный конструктор\n";
}
Monster::Monster(const Monster& other) : Character(other), description(other.description) {
    std::cout << "Monster: конструктор копирования\n";
}
Monster::~Monster() { std::cout << "Monster: деструктор\n"; }

void Monster::print() const {
    std::cout << "Монстр: " << name << ", описание: " << description << '\n';
}
void Monster::edit() {
    std::cout << "Редактирование Монстра (" << name << ")\nВведите новое имя: ";
    std::getline(std::cin, name);
    std::cout << "Введите новое описание: ";
    std::getline(std::cin, description);
}
void Monster::save(std::ostream& os) const {
    os << "MONSTER\n" << name << '\n' << description << '\n';
}
void Monster::load(std::istream& is) {
    std::getline(is, name);
    std::getline(is, description);
}
