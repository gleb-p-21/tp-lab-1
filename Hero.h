#ifndef HERO_H
#define HERO_H

#include "Character.h"

class Hero : public Character {
private:
    std::string weapon;
    std::string* skills;
    int num_skills;
public:
    Hero();
    Hero(const std::string& n, const std::string& w, std::string* sk, int num);
    Hero(const Hero& other);
    ~Hero() override;

    void print() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
    std::string getType() const override { return "HERO"; }
};

#endif
