#pragma once

#include <vector>
#include <iterator>
#include <set>
#include <list>

namespace ariel
{
}

class MagicalContainer
{
    std::vector<int> originalElements; // stores original insertion order
    std::list<int> crossElements;      // stores elements in cross order
    std::multiset<int> sortedElements; // stores elements in ascending order
    std::vector<int> primeElements;    // stores prime numbers only

    void updateCrossElements();
    bool isPrime(int number) const;

public:
    MagicalContainer() = default;
    ~MagicalContainer() = default;

    void addElement(int element);
    void removeElement(int element);
    int size() const;

    bool operator==(const MagicalContainer &other) const;
    bool operator!=(const MagicalContainer &other) const;

    // give access to private members to the following classes
    friend class BaseIterator;
    friend class AscendingIterator;
    friend class SideCrossIterator;
    friend class PrimeIterator;
};


class BaseIterator
{
protected:
    MagicalContainer &mc;
    std::vector<int>::iterator it;
    int pos;

public:
    BaseIterator(MagicalContainer &mc);
    BaseIterator(const BaseIterator &other);
    virtual ~BaseIterator() = default;

    BaseIterator &operator=(const BaseIterator &other);
    bool operator==(const BaseIterator &other) const;
    bool operator!=(const BaseIterator &other) const;
    bool operator>(const BaseIterator &other) const;
    bool operator<(const BaseIterator &other) const;
    virtual int operator*() const;
    virtual BaseIterator &operator++();

    virtual BaseIterator& begin();
    virtual BaseIterator& end();
};

class AscendingIterator : public BaseIterator
{
private:
    std::multiset<int>::iterator it;

public:
    AscendingIterator(MagicalContainer &mc);
    AscendingIterator(const AscendingIterator &other);

    int operator*() const override;
    AscendingIterator &operator++() override;

    AscendingIterator& begin() override;
    AscendingIterator& end() override;
};

class SideCrossIterator : public BaseIterator
{
private:
    std::list<int>::iterator it;

public:
    SideCrossIterator(MagicalContainer &mc);
    SideCrossIterator(const SideCrossIterator &other);

    int operator*() const override;
    SideCrossIterator &operator++() override;

    SideCrossIterator& begin() override;
    SideCrossIterator& end() override;
};

class PrimeIterator : public BaseIterator
{
private:
    std::vector<int>::iterator it;

public:
    PrimeIterator(MagicalContainer &mc);
    PrimeIterator(const PrimeIterator &other);

    int operator*() const override;
    PrimeIterator &operator++() override;

    PrimeIterator& begin() override;
    PrimeIterator& end() override;
};
