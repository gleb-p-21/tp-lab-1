#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"
#include <fstream>
#include <iostream>
#include <limits>

Keeper::Keeper() : arr(new Character*[10]), size(0), capacity(10) {
    std::cout << "Keeper: создан\n";
    for (int i = 0; i < capacity; ++i) arr[i] = nullptr;
}

// Конструктор копирования
Keeper::Keeper(const Keeper& other) : arr(new Character*[other.capacity]), size(other.size), capacity(other.capacity) {
    std::cout << "Keeper: конструктор копирования\n";
    for (int i = 0; i < capacity; ++i) {
        if (i < size) {
            // Создаем копии объектов (для этого нужен метод clone в наследниках)
            if (dynamic_cast<Hero*>(other.arr[i])) {
                arr[i] = new Hero(*dynamic_cast<Hero*>(other.arr[i]));
            } else if (dynamic_cast<Villain*>(other.arr[i])) {
                arr[i] = new Villain(*dynamic_cast<Villain*>(other.arr[i]));
            } else if (dynamic_cast<Monster*>(other.arr[i])) {
                arr[i] = new Monster(*dynamic_cast<Monster*>(other.arr[i]));
            }
        } else {
            arr[i] = nullptr;
        }
    }
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) delete arr[i];
    delete[] arr;
    std::cout << "Keeper: уничтожен\n";
}

// Оператор присваивания
Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        // Очищаем текущие данные
        for (int i = 0; i < size; ++i) delete arr[i];
        delete[] arr;

        // Копируем данные
        size = other.size;
        capacity = other.capacity;
        arr = new Character*[capacity];
        
        for (int i = 0; i < capacity; ++i) {
            if (i < size) {
                if (dynamic_cast<Hero*>(other.arr[i])) {
                    arr[i] = new Hero(*dynamic_cast<Hero*>(other.arr[i]));
                } else if (dynamic_cast<Villain*>(other.arr[i])) {
                    arr[i] = new Villain(*dynamic_cast<Villain*>(other.arr[i]));
                } else if (dynamic_cast<Monster*>(other.arr[i])) {
                    arr[i] = new Monster(*dynamic_cast<Monster*>(other.arr[i]));
                }
            } else {
                arr[i] = nullptr;
            }
        }
    }
    std::cout << "Keeper: оператор присваивания\n";
    return *this;
}

// Оператор индексации
Character* Keeper::operator[](int index) {
    if (index < 0 || index >= size) {
        throw KeeperException("Индекс выходит за границы массива");
    }
    return arr[index];
}

void Keeper::resize() {
    capacity *= 2;
    Character** tmp = new Character*[capacity];
    for (int i = 0; i < size; ++i) tmp[i] = arr[i];
    for (int i = size; i < capacity; ++i) tmp[i] = nullptr;
    delete[] arr;
    arr = tmp;
}

void Keeper::add(Character* c) {
    if (size == capacity) resize();
    arr[size++] = c;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw KeeperException("Неверный индекс при удалении");
    }
    delete arr[index];
    for (int i = index; i < size - 1; ++i) arr[i] = arr[i + 1];
    arr[--size] = nullptr;
}

void Keeper::display() const {
    if (size == 0) { std::cout << "Пусто\n"; return; }
    for (int i = 0; i < size; ++i) {
        std::cout << i << ". ";
        arr[i]->print();
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw KeeperException("Неверный индекс при редактировании");
    }
    arr[index]->edit();
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) { 
        throw KeeperException("Ошибка открытия файла для записи"); 
    }
    out << size << '\n';
    for (int i = 0; i < size; ++i) arr[i]->save(out);
    std::cout << "Сохранено " << size << " объектов\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) { 
        throw KeeperException("Ошибка открытия файла для чтения"); 
    }
    
    // Очищаем старые данные
    for (int i = 0; i < size; ++i) delete arr[i];
    size = 0;
    
    int newSize;
    in >> newSize;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    for (int i = 0; i < newSize; ++i) {
        std::string type;
        std::getline(in, type);
        Character* obj = nullptr;
        if (type == "HERO") obj = new Hero();
        else if (type == "VILLAIN") obj = new Villain();
        else if (type == "MONSTER") obj = new Monster();
        else continue;
        
        obj->load(in);
        add(obj);
    }
    std::cout << "Загружено " << size << " объектов\n";
}