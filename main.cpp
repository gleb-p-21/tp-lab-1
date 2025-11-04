#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
#include "CustomExceptions.h"
#include <iostream>
#include <string>

void addHero(Keeper& k) {
    std::string name, weapon; int n;
    std::cout << "Имя героя: "; std::getline(std::cin, name);
    std::cout << "Оружие: "; std::getline(std::cin, weapon);
    std::cout << "Количество навыков: "; std::cin >> n; std::cin.ignore();
    std::string* sk = new std::string[n];
    for (int i = 0; i < n; ++i) {
        std::cout << "Навык " << i + 1 << ": "; std::getline(std::cin, sk[i]);
    }
    k.add(new Hero(name, weapon, sk, n));
    delete[] sk;
}

void addVillain(Keeper& k) {
    std::string name, weapon, crime, habitat; int n;
    std::cout << "Имя злодея: "; std::getline(std::cin, name);
    std::cout << "Оружие: "; std::getline(std::cin, weapon);
    std::cout << "Злодеяние: "; std::getline(std::cin, crime);
    std::cout << "Место обитания: "; std::getline(std::cin, habitat);
    std::cout << "Количество навыков: "; std::cin >> n; std::cin.ignore();
    std::string* sk = new std::string[n];
    for (int i = 0; i < n; ++i) {
        std::cout << "Навык " << i + 1 << ": "; std::getline(std::cin, sk[i]);
    }
    k.add(new Villain(name, weapon, crime, habitat, sk, n));
    delete[] sk;
}

void addMonster(Keeper& k) {
    std::string name, desc;
    std::cout << "Имя монстра: "; std::getline(std::cin, name);
    std::cout << "Описание: "; std::getline(std::cin, desc);
    k.add(new Monster(name, desc));
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");
    Keeper keeper;
    int ch;
    do {
        try {
            std::cout << "\n1. Добавить Героя\n2. Добавить Злодея\n3. Добавить Монстра\n"
                         "4. Показать всех\n5. Редактировать\n6. Удалить\n"
                         "7. Сохранить\n8. Загрузить\n9. Выход\nВыбор: ";
            std::cin >> ch; std::cin.ignore();
            if (ch == 1) addHero(keeper);
            else if (ch == 2) addVillain(keeper);
            else if (ch == 3) addMonster(keeper);
            else if (ch == 4) keeper.display();
            else if (ch == 5) { 
                int i; 
                std::cout << "Индекс: "; 
                std::cin >> i; 
                std::cin.ignore(); 
                keeper.edit(i); 
            }
            else if (ch == 6) { 
                int i; 
                std::cout << "Индекс: "; 
                std::cin >> i; 
                std::cin.ignore(); 
                keeper.remove(i); 
            }
            else if (ch == 7) { 
                std::string fn; 
                std::cout << "Файл: "; 
                std::getline(std::cin, fn); 
                keeper.saveToFile(fn); 
            }
            else if (ch == 8) { 
                std::string fn; 
                std::cout << "Файл: "; 
                std::getline(std::cin, fn); 
                keeper.loadFromFile(fn); 
            }
        } catch (const KeeperException& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Неизвестная ошибка: " << e.what() << std::endl;
        }
    } while (ch != 9);
    return 0;
}