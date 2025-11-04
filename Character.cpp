#include "Character.h"
#include <iostream>

Character::Character() : name("") {
    std::cout << "Character: конструктор по умолчанию\n";
}
Character::Character(const std::string& n) : name(n) {
    std::cout << "Character: параметризованный конструктор\n";
}
Character::Character(const Character& other) : name(other.name) {
    std::cout << "Character: конструктор копирования\n";
}
Character::~Character() {
    std::cout << "Character: деструктор\n";
}

std::string Character::getName() const { return name; }
void Character::setName(const std::string& n) { name = n; }
