#include "Hero.h"
#include <iostream>
#include <limits>
#include <stdexcept>

Hero::Hero() : Character(), weapon(""), skills(nullptr), num_skills(0) {
    std::cout << "Hero: конструктор по умолчанию\n";
}
Hero::Hero(const std::string& n, const std::string& w, std::string* sk, int num)
    : Character(n), weapon(w), skills(nullptr), num_skills(0) {
    std::cout << "Hero: параметризованный конструктор\n";
    if (num < 0) throw std::invalid_argument("Отрицательное число навыков");
    num_skills = num;
    skills = new std::string[num];
    for (int i = 0; i < num; ++i) skills[i] = sk[i];
}
Hero::Hero(const Hero& other)
    : Character(other), weapon(other.weapon), skills(nullptr), num_skills(other.num_skills) {
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) skills[i] = other.skills[i];
}
Hero::~Hero() {
    delete[] skills;
    std::cout << "Hero: деструктор\n";
}

void Hero::print() const {
    std::cout << "Герой: " << name << ", оружие: " << weapon << ", навыки: ";
    for (int i = 0; i < num_skills; ++i)
        std::cout << skills[i] << (i < num_skills - 1 ? ", " : "");
    std::cout << '\n';
}
void Hero::edit() {
    std::cout << "Редактирование Героя (" << name << ")\nВведите новое имя: ";
    std::getline(std::cin, name);
    std::cout << "Введите новое оружие: ";
    std::getline(std::cin, weapon);
    std::cout << "Введите количество навыков: ";
    std::cin >> num_skills;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete[] skills;
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) {
        std::cout << "Навык " << i + 1 << ": ";
        std::getline(std::cin, skills[i]);
    }
}
void Hero::save(std::ostream& os) const {
    os << "HERO\n" << name << '\n' << weapon << '\n' << num_skills << '\n';
    for (int i = 0; i < num_skills; ++i) os << skills[i] << '\n';
}
void Hero::load(std::istream& is) {
    std::getline(is, name);
    std::getline(is, weapon);
    is >> num_skills;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete[] skills;
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) std::getline(is, skills[i]);
}
