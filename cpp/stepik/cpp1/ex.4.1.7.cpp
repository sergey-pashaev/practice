#include <string>  // std::string

struct Character {
    std::string const& name() const;
    unsigned health() const;
};

struct LongRange : public Character {
    std::string const& name() const;
    unsigned health() const;

    unsigned range() const;
};

struct SwordsMan : public Character {
    std::string const& name() const;
    unsigned health() const;

    unsigned strength() const;
};

struct Wizard : public LongRange {
    std::string const& name() const;
    unsigned health() const;

    unsigned range() const;

    unsigned mana() const;
};

struct Archer : public LongRange {
    std::string const& name() const;
    unsigned health() const;

    unsigned range() const;

    unsigned accuracy() const;
};

int main() {}
