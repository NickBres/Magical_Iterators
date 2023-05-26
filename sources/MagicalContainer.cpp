#include "MagicalContainer.hpp"
#include <math.h>
#include <iostream>

/*------------------------------------------
----------------MagicalContainer------------
--------------------------------------------*/

// Private methods
bool MagicalContainer::isPrime(int num) const
{
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void MagicalContainer::updateCrossElements()
{
    crossElements.clear(); // clear existing elements in list
    bool from_start = true;
    auto start_it = originalElements.begin(); // iterator to first element
    auto end_it = originalElements.end();     // iterator to last element
    --end_it;                                 // point to last element

    while (start_it <= end_it)
    { // iterate over all elements to the middle
        if (from_start)
        { // add element from start
            crossElements.push_back(*start_it);
            ++start_it;
        }
        else
        { // add element from end
            crossElements.push_back(*end_it);
            --end_it;
        }
        from_start = !from_start; // alternate between start and end
    }
}

// Public methods

void MagicalContainer::addElement(int element)
{
    originalElements.push_back(element); // add element to originalElements
    sortedElements.insert(element);      // add element to sortedElements
    if (isPrime(element))
    { // if element is prime, add to primeElements
        primeElements.push_back(element);
    }
    updateCrossElements(); // update crossElements
}

void MagicalContainer::removeElement(int element)
{
    originalElements.erase(std::remove(originalElements.begin(), originalElements.end(), element), originalElements.end()); // remove element from originalElements
    sortedElements.erase(sortedElements.find(element));                                                                     // remove element from sortedElements
    if (isPrime(element))
    { // if element is prime, remove from primeElements
        primeElements.erase(std::remove(primeElements.begin(), primeElements.end(), element), primeElements.end());
    }
    updateCrossElements(); // update crossElements
}

size_t MagicalContainer::size() const
{
    return originalElements.size(); // return size of originalElements
}

bool MagicalContainer::operator==(const MagicalContainer &other) const
{
    return originalElements == other.originalElements; // compare originalElements
}

bool MagicalContainer::operator!=(const MagicalContainer &other) const
{
    return originalElements != other.originalElements; // compare originalElements
}

/*------------------------------------------
-------------------------------------------*/
/*------------------------------------------
--------------AscendingIterator-------------
--------------------------------------------*/

AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0), it(magicalContainer.sortedElements.begin()) {}

AscendingIterator::AscendingIterator(const AscendingIterator &other) : magicalContainer(other.magicalContainer), pos(other.pos), it(other.it) {}

AscendingIterator &AscendingIterator::operator=(const AscendingIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool AscendingIterator::operator==(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos; // compare position
}

bool AscendingIterator::operator!=(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos; // compare position
}

bool AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int AscendingIterator::operator*() const
{
    if (it == magicalContainer->sortedElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

AscendingIterator &AscendingIterator::operator++()
{
    if (it == magicalContainer->sortedElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

AscendingIterator &AscendingIterator::begin()
{
    it = magicalContainer->sortedElements.begin(); // set iterator to first element
    pos = 0;                        // set position to 0
    return *this;
}

AscendingIterator &AscendingIterator::end()
{
    it = magicalContainer->sortedElements.end(); // set iterator to last element
    pos = magicalContainer->size();              // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------SideCrossIterator------------
--------------------------------------------*/

SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), it(magicalContainer.crossElements.begin()), pos(0) {}

SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : magicalContainer(other.magicalContainer), it(other.it), pos(other.pos) {}

SideCrossIterator &SideCrossIterator::operator=(const SideCrossIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos; // compare position
}

bool SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos; // compare position
}

bool SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int SideCrossIterator::operator*() const
{
    if (it == magicalContainer->crossElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

SideCrossIterator &SideCrossIterator::operator++()
{
    if (it == magicalContainer->crossElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

SideCrossIterator &SideCrossIterator::begin()
{
    it = magicalContainer->crossElements.begin(); // set iterator to first element
    pos = 0;                       // set position to 0
    return *this;
}

SideCrossIterator &SideCrossIterator::end()
{
    it = magicalContainer->crossElements.end(); // set iterator to last element
    pos = magicalContainer->size();             // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------PrimeIterator-----------------
--------------------------------------------*/

PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), it(magicalContainer.primeElements.begin()), pos(0) {}

PrimeIterator::PrimeIterator(const PrimeIterator &other) : magicalContainer(other.magicalContainer), it(other.it), pos(other.pos) {}

PrimeIterator &PrimeIterator::operator=(const PrimeIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");
    return pos == other.pos; // compare position
}

bool PrimeIterator::operator!=(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");
    return pos != other.pos; // compare position
}

bool PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int PrimeIterator::operator*() const
{
    if (it == magicalContainer->primeElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

PrimeIterator &PrimeIterator::operator++()
{
    if (it == magicalContainer->primeElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

PrimeIterator &PrimeIterator::begin()
{
    it = magicalContainer->primeElements.begin(); // set iterator to first element
    pos = 0;                       // set position to 0
    return *this;
}

PrimeIterator &PrimeIterator::end()
{
    it = magicalContainer->primeElements.end();   // set iterator to last element
    pos = magicalContainer->primeElements.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/
