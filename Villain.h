#ifndef VILLAIN_H
#define VILLAIN_H

#include "Character.h"

class Villain : public Character {
private:
    std::string weapon, crime, habitat;
    std::string* skills;
    int num_skills;
public:
    Villain();
    Villain(const std::string& n, const std::string& w, const std::string& c,
            const std::string& h, std::string* sk, int num);
    Villain(const Villain& other);
    ~Villain() override;

    void print() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
    std::string getType() const override { return "VILLAIN"; }
};

#endif
