#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"

class Monster : public Character {
private:
    std::string description;
public:
    Monster();
    Monster(const std::string& n, const std::string& d);
    Monster(const Monster& other);
    ~Monster() override;

    void print() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
    std::string getType() const override { return "MONSTER"; }
};
#endif
