#ifndef KEEPER_H
#define KEEPER_H
#include "Character.h"

class Keeper {
private:
    Character** arr;
    int size;
    int capacity;
    void resize();
public:
    Keeper();
    ~Keeper();

    void add(Character* c);
    void remove(int index);
    void display() const;
    void edit(int index);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
#endif
