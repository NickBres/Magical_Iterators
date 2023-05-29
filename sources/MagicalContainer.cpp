#include "MagicalContainer.hpp"
#include <math.h>
#include <iostream>

using namespace ariel;

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
    auto start_it = sortedElements.begin(); // iterator to first element
    auto end_it = sortedElements.end();     // iterator to last element
    --end_it;                                 // point to last element

    while (start_it != sortedElements.end())
    {
        // insert the smaller element first
        crossElements.push_back(*start_it);
        if(start_it != end_it){
            // if there is another element, insert the bigger element next
            crossElements.push_back(*end_it);
        }
        ++start_it;
        if (end_it != start_it && start_it != sortedElements.end()) {  // to avoid decrementing past the start
            --end_it;
        }
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

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0), it(magicalContainer.sortedElements.begin()) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : magicalContainer(other.magicalContainer), pos(other.pos), it(other.it) {}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos; // compare position
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos; // compare position
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int MagicalContainer::AscendingIterator::operator*() const
{
    if (it == magicalContainer->sortedElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (it == magicalContainer->sortedElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin()
{
    it = magicalContainer->sortedElements.begin(); // set iterator to first element
    pos = 0;                        // set position to 0
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end()
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

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), it(magicalContainer.crossElements.begin()), pos(0) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : magicalContainer(other.magicalContainer), it(other.it), pos(other.pos) {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos; // compare position
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos; // compare position
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (it == magicalContainer->crossElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (it == magicalContainer->crossElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin()
{
    it = magicalContainer->crossElements.begin(); // set iterator to first element
    pos = 0;                       // set position to 0
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end()
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

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), it(magicalContainer.primeElements.begin()), pos(0) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : magicalContainer(other.magicalContainer), it(other.it), pos(other.pos) {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    magicalContainer = other.magicalContainer;   // copy MagicalContainer
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");
    return pos == other.pos; // compare position
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");
    return pos != other.pos; // compare position
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (it == magicalContainer->primeElements.end())
        throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (it == magicalContainer->primeElements.end()){
        throw std::out_of_range("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin()
{
    it = magicalContainer->primeElements.begin(); // set iterator to first element
    pos = 0;                       // set position to 0
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end()
{
    it = magicalContainer->primeElements.end();   // set iterator to last element
    pos = magicalContainer->primeElements.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/
