#pragma once

#include <vector>
#include <iterator>
#include <set>
#include <list>

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
    MagicalContainer(const MagicalContainer &other) = default;
    MagicalContainer &operator=(const MagicalContainer &other) = default;
    MagicalContainer(MagicalContainer&& other) noexcept = default;
    MagicalContainer& operator=(MagicalContainer&& other) noexcept = default;



    void addElement(int element);
    void removeElement(int element);
    size_t size() const;

    bool operator==(const MagicalContainer &other) const;
    bool operator!=(const MagicalContainer &other) const;

    // give access to private members to the following classes
    friend class AscendingIterator;
    friend class SideCrossIterator;
    friend class PrimeIterator;
};

class AscendingIterator
{
private:
    MagicalContainer *magicalContainer;
    std::multiset<int>::iterator it;
    size_t pos;

public:
    AscendingIterator(MagicalContainer &magicalContainer);
    AscendingIterator(const AscendingIterator &other);
    ~AscendingIterator() = default;
     AscendingIterator(AscendingIterator&& other) noexcept = default;
    AscendingIterator& operator=(AscendingIterator&& other) noexcept = default;

    AscendingIterator &operator=(const AscendingIterator &other);
    bool operator==(const AscendingIterator &other) const;
    bool operator!=(const AscendingIterator &other) const;
    bool operator>(const AscendingIterator &other) const;
    bool operator<(const AscendingIterator &other) const;

    size_t getPosition() const{ return pos;};

    int operator*() const;
    AscendingIterator &operator++();

    AscendingIterator &begin();
    AscendingIterator &end();
};

class SideCrossIterator
{
private:
    MagicalContainer *magicalContainer;
    std::list<int>::iterator it;
    size_t pos;

public:
    SideCrossIterator(MagicalContainer &magicalContainer);
    SideCrossIterator(const SideCrossIterator &other);
    ~SideCrossIterator() = default;
    SideCrossIterator(SideCrossIterator&& other) noexcept = default;
    SideCrossIterator& operator=(SideCrossIterator&& other) noexcept = default;

    SideCrossIterator &operator=(const SideCrossIterator &other);
    bool operator==(const SideCrossIterator &other) const;
    bool operator!=(const SideCrossIterator &other) const;
    bool operator>(const SideCrossIterator &other) const;
    bool operator<(const SideCrossIterator &other) const;

    int operator*() const;
    SideCrossIterator &operator++();

    size_t getPosition() const{ return pos;};

    SideCrossIterator &begin();
    SideCrossIterator &end();
};

class PrimeIterator
{
private:
    MagicalContainer *magicalContainer;
    std::vector<int>::iterator it;
    size_t pos;

public:
    PrimeIterator(MagicalContainer &magicalContainer);
    PrimeIterator(const PrimeIterator &other);
    ~PrimeIterator() = default;
    PrimeIterator(PrimeIterator&& other) noexcept = default;
    PrimeIterator& operator=(PrimeIterator&& other) noexcept = default;

    PrimeIterator &operator=(const PrimeIterator &other);
    bool operator==(const PrimeIterator &other) const;
    bool operator!=(const PrimeIterator &other) const;
    bool operator>(const PrimeIterator &other) const;
    bool operator<(const PrimeIterator &other) const;

    int operator*() const;
    PrimeIterator &operator++();

    size_t getPosition() const{ return pos;};

    PrimeIterator &begin();
    PrimeIterator &end();
};
