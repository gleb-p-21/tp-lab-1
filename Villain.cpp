#include "Villain.h"
#include <iostream>
#include <limits>

Villain::Villain() : Character(), weapon(""), crime(""), habitat(""), skills(nullptr), num_skills(0) {
    std::cout << "Villain: конструктор по умолчанию\n";
}
Villain::Villain(const std::string& n, const std::string& w, const std::string& c,
                 const std::string& h, std::string* sk, int num)
    : Character(n), weapon(w), crime(c), habitat(h), num_skills(num) {
    std::cout << "Villain: параметризованный конструктор\n";
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) skills[i] = sk[i];
}
Villain::Villain(const Villain& other)
    : Character(other), weapon(other.weapon), crime(other.crime),
      habitat(other.habitat), num_skills(other.num_skills) {
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) skills[i] = other.skills[i];
}
Villain::~Villain() {
    delete[] skills;
    std::cout << "Villain: деструктор\n";
}

void Villain::print() const {
    std::cout << "Злодей: " << name << ", оружие: " << weapon
              << ", злодеяние: " << crime << ", место: " << habitat
              << ", навыки: ";
    for (int i = 0; i < num_skills; ++i)
        std::cout << skills[i] << (i < num_skills - 1 ? ", " : "");
    std::cout << '\n';
}
void Villain::edit() {
    std::cout << "Редактирование Злодея (" << name << ")\n";
    std::getline(std::cin, name);
    std::cout << "Введите оружие: ";
    std::getline(std::cin, weapon);
    std::cout << "Введите злодеяние: ";
    std::getline(std::cin, crime);
    std::cout << "Введите место обитания: ";
    std::getline(std::cin, habitat);
    std::cout << "Количество навыков: ";
    std::cin >> num_skills;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete[] skills;
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) {
        std::cout << "Навык " << i + 1 << ": ";
        std::getline(std::cin, skills[i]);
    }
}
void Villain::save(std::ostream& os) const {
    os << "VILLAIN\n" << name << '\n' << weapon << '\n'
       << crime << '\n' << habitat << '\n' << num_skills << '\n';
    for (int i = 0; i < num_skills; ++i) os << skills[i] << '\n';
}
void Villain::load(std::istream& is) {
    std::getline(is, name);
    std::getline(is, weapon);
    std::getline(is, crime);
    std::getline(is, habitat);
    is >> num_skills;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete[] skills;
    skills = new std::string[num_skills];
    for (int i = 0; i < num_skills; ++i) std::getline(is, skills[i]);
}
