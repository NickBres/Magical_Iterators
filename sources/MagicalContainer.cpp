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
    auto end_it = sortedElements.rbegin(); // iterator to last element (reversed)

    bool add_from_start = true;

    for (int i = 0; i < sortedElements.size(); i++)
    {
        if (add_from_start)
        {
            crossElements.push_back(*start_it);
            ++start_it;
        }
        else
        {
            crossElements.push_back(*end_it);
            ++end_it;
        }
        add_from_start = !add_from_start;  // switch between adding from start and end
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
    if(std::find(originalElements.begin(), originalElements.end(), element) == originalElements.end()) // if element is not in originalElements
        throw std::runtime_error("Element not found in container");
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
--------------BasicIterator-------------
--------------------------------------------*/

MagicalContainer::BasicIterator::BasicIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0) {};
MagicalContainer::BasicIterator::BasicIterator(const BasicIterator &other): magicalContainer(other.magicalContainer), pos(other.pos) {};



bool MagicalContainer::BasicIterator::operator==(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos == other.pos; // compare position
}

bool MagicalContainer::BasicIterator::operator!=(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos != other.pos; // compare position
}

bool MagicalContainer::BasicIterator::operator<(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos < other.pos; // compare position
}

bool MagicalContainer::BasicIterator::operator>(const BasicIterator &other) const
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::invalid_argument("Cant compare iterators from different MagicalContainers");

    return pos > other.pos; // compare position
}

/*------------------------------------------
-------------------------------------------*/




/*------------------------------------------
--------------AscendingIterator-------------
--------------------------------------------*/

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) :  BasicIterator(magicalContainer) {
    it = magicalContainer.sortedElements.begin(); // set iterator to first element
};

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : BasicIterator(other) {};

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container"); // added only to pass the tests... there is no need for this
    magicalContainer = other.magicalContainer; // copy MagicalContainer reference
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const
{
    if (it == magicalContainer->sortedElements.end())
        throw std::runtime_error("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (it == magicalContainer->sortedElements.end()){
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    AscendingIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->sortedElements.begin(); // set iterator to first element
    temp.pos = 0;                                       // set position to 0
    return temp;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->sortedElements.end(); // set iterator to last element
    temp.pos = magicalContainer->sortedElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------SideCrossIterator------------
--------------------------------------------*/

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer) {
    it = magicalContainer.crossElements.begin(); // set iterator to first element
};

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BasicIterator(other) {};

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer; // copy MagicalContainer reference
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (it == magicalContainer->crossElements.end())
        throw std::runtime_error("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (it == magicalContainer->crossElements.end()){
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->crossElements.begin(); // set iterator to first element
    temp.pos = 0;                                       // set position to 0
    return temp;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->crossElements.end(); // set iterator to last element
    temp.pos = magicalContainer->crossElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------PrimeIterator-----------------
--------------------------------------------*/

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer) {
    it = magicalContainer.primeElements.begin(); // set iterator to first element
};

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : BasicIterator(other) {};

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer; // copy MagicalContainer reference 
    pos = other.pos; // copy position
    it = other.it;   // copy iterator
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (it == magicalContainer->primeElements.end())
        throw std::runtime_error("Iterator is out of range");
    return *it; // return value of iterator
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (it == magicalContainer->primeElements.end()){
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->primeElements.begin(); // set iterator to first element
    temp.pos = 0;                                       // set position to 0
    return temp;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator temp(*this); // create copy of iterator
    temp.it = magicalContainer->primeElements.end(); // set iterator to last element
    temp.pos = magicalContainer->primeElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/
