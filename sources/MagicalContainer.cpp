#include "MagicalContainer.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace ariel;
using namespace std;

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
    crossElements.clear();                  // clear existing elements in list
    auto start_it = sortedElements.begin(); // iterator to first element
    auto end_it = sortedElements.rbegin();  // iterator to last element (reversed)

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
        add_from_start = !add_from_start; // switch between adding from start and end
    }
}
void MagicalContainer::updateSortedElements()
{
    sortedElements.clear(); // Clear existing elements in the list

    for (auto it = originalElements.begin(); it != originalElements.end(); ++it)
    {
        sortedElements.push_back(&(*it)); // Store the address of each element
    }

    std::sort(sortedElements.begin(), sortedElements.end(), [](int *a, int *b)
              {
                  return *a < *b; // Sort the pointers based on the pointed values
              });
}

void MagicalContainer::updatePrimeElements()
{
    primeElements.clear(); // Clear existing elements in the list

    for (auto it = originalElements.begin(); it != originalElements.end(); ++it)
    {
        if (isPrime(*it))
        {
            primeElements.push_back(&(*it));
        }
    }
}

// Public methods

void MagicalContainer::addElement(int element)
{
    originalElements.push_back(element); // add element to sortedElements
    updatePrimeElements();
    updateSortedElements(); // update sortedElements
    updateCrossElements();  // update crossElements
}

void MagicalContainer::removeElement(int element)
{
    // find the iterator for the element to be removed
    auto it = std::find(originalElements.begin(), originalElements.end(), element);

    if (it == originalElements.end()) // if element is not in originalElements
    {
        throw std::runtime_error("Element not found in container");
        return;
    }

    // Get the address of the element to be removed
    int *p = &(*it);

    // Remove the element from originalElements
    originalElements.erase(it);

    // Remove the pointer from sortedElements
    sortedElements.erase(std::find(sortedElements.begin(), sortedElements.end(), p));

    if (isPrime(element))
    { // if element is prime, remove from primeElementss
        primeElements.erase(std::find(primeElements.begin(), primeElements.end(), p));
    }
    updatePrimeElements();
    updateCrossElements(); // update crossElements
    updateSortedElements();
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

MagicalContainer::BasicIterator::BasicIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0){};
MagicalContainer::BasicIterator::BasicIterator(const BasicIterator &other) : magicalContainer(other.magicalContainer), pos(other.pos){};

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

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.sortedElements.begin(); // set iterator to first element
};

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : BasicIterator(other){};

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container"); // added only to pass the tests... there is no need for this
    magicalContainer = other.magicalContainer;                        // copy MagicalContainer reference
    pos = other.pos;                                                  // copy position
    it = other.it;                                                    // copy iterator
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const
{
    if (it == magicalContainer->sortedElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it; // return value of iterator
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (it == magicalContainer->sortedElements.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    AscendingIterator temp(*this);                      // create copy of iterator
    temp.it = magicalContainer->sortedElements.begin(); // set iterator to first element
    temp.pos = 0;                                       // set position to 0
    return temp;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator temp(*this);                      // create copy of iterator
    temp.it = magicalContainer->sortedElements.end();   // set iterator to last element
    temp.pos = magicalContainer->sortedElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------SideCrossIterator------------
--------------------------------------------*/

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.crossElements.begin(); // set iterator to first element
};

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BasicIterator(other){};

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer; // copy MagicalContainer reference
    pos = other.pos;                           // copy position
    it = other.it;                             // copy iterator
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (it == magicalContainer->crossElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it; // return value of iterator
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (it == magicalContainer->crossElements.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator temp(*this);                     // create copy of iterator
    temp.it = magicalContainer->crossElements.begin(); // set iterator to first element
    temp.pos = 0;                                      // set position to 0
    return temp;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator temp(*this);                     // create copy of iterator
    temp.it = magicalContainer->crossElements.end();   // set iterator to last element
    temp.pos = magicalContainer->crossElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------PrimeIterator-----------------
--------------------------------------------*/

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : BasicIterator(magicalContainer)
{
    it = magicalContainer.primeElements.begin(); // set iterator to first element
};

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : BasicIterator(other){};

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->magicalContainer != other.magicalContainer)
        throw std::runtime_error("Cant copy from another container");
    magicalContainer = other.magicalContainer; // copy MagicalContainer reference
    pos = other.pos;                           // copy position
    it = other.it;                             // copy iterator
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (it == magicalContainer->primeElements.end())
        throw std::runtime_error("Iterator is out of range");
    return **it; // return value of iterator
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (it == magicalContainer->primeElements.end())
    {
        throw std::runtime_error("Iterator is out of range");
        return *this;
    }
    ++it;  // increment iterator
    ++pos; // increment position
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator temp(*this);                         // create copy of iterator
    temp.it = magicalContainer->primeElements.begin(); // set iterator to first element
    temp.pos = 0;                                      // set position to 0
    return temp;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator temp(*this);                         // create copy of iterator
    temp.it = magicalContainer->primeElements.end();   // set iterator to last element
    temp.pos = magicalContainer->primeElements.size(); // set position to size of container
    return temp;
}

/*------------------------------------------
-------------------------------------------*/
