#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

class Character {
protected:
    std::string name;
public:
    Character();
    Character(const std::string& n);
    Character(const Character& other);
    virtual ~Character();

    std::string getName() const;
    void setName(const std::string& n);

    virtual void print() const = 0;
    virtual void edit() = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual void load(std::istream& is) = 0;
    virtual std::string getType() const = 0;
};

#endif
