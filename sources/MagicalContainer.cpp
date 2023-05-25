#include "MagicalContainer.hpp"
#include <math.h>

/*------------------------------------------
----------------MagicalContainer------------
--------------------------------------------*/

// Private methods
bool MagicalContainer::isPrime(int num) const{
    if(num <= 1) return false;
    for(int i = 2; i <= sqrt(num); i++){
        if(num % i == 0) return false;
    }
    return true;
}

void MagicalContainer::updateCrossElements() {
    crossElements.clear();  // clear existing elements in list
    bool from_start = true;  
    auto start_it = originalElements.begin(); // iterator to first element
    auto end_it = originalElements.end();   // iterator to last element
    --end_it; // point to last element

    while (start_it <= end_it) { // iterate over all elements to the middle
        if (from_start) { // add element from start
            crossElements.push_back(*start_it); 
            ++start_it; 
        } else { // add element from end
            crossElements.push_back(*end_it);
            --end_it;
        }
        from_start = !from_start; // alternate between start and end
    }
}

// Public methods

void MagicalContainer::addElement(int element) {
    originalElements.push_back(element); // add element to originalElements
    sortedElements.insert(element); // add element to sortedElements
    if (isPrime(element)) { // if element is prime, add to primeElements
        primeElements.push_back(element);
    }
    updateCrossElements(); // update crossElements
}

void MagicalContainer::removeElement(int element) {
    originalElements.erase(std::remove(originalElements.begin(), originalElements.end(), element), originalElements.end()); // remove element from originalElements
    sortedElements.erase(sortedElements.find(element)); // remove element from sortedElements
    if (isPrime(element)) { // if element is prime, remove from primeElements
        primeElements.erase(std::remove(primeElements.begin(), primeElements.end(), element), primeElements.end());
    }
    updateCrossElements(); // update crossElements
}

int MagicalContainer::size() const {
    return originalElements.size(); // return size of originalElements
}

bool MagicalContainer::operator==(const MagicalContainer &other) const {
    return originalElements == other.originalElements; // compare originalElements
}

bool MagicalContainer::operator!=(const MagicalContainer &other) const {
    return originalElements != other.originalElements; // compare originalElements
}

/*------------------------------------------
-------------------------------------------*/


/*------------------------------------------
--------------BaseIterator------------------
--------------------------------------------*/

BaseIterator::BaseIterator(MagicalContainer &mc) : mc(mc), pos(0), it(mc.originalElements.begin()) {}

BaseIterator::BaseIterator(const BaseIterator &other) : mc(other.mc), pos(other.pos), it(other.it) {}

BaseIterator &BaseIterator::operator=(const BaseIterator &other) {
    if (this != &other) { // check for self assignment
        mc = other.mc; // copy MagicalContainer
        pos = other.pos; // copy position
    }
    return *this;
}

bool BaseIterator::operator==(const BaseIterator &other) const {
    if(&mc != &other.mc) throw std::invalid_argument("Iterators are not from the same MagicalContainer"); 
    return pos == other.pos;
}

bool BaseIterator::operator!=(const BaseIterator &other) const {
    if(&mc != &other.mc) throw std::invalid_argument("Iterators are not from the same MagicalContainer");
    return pos != other.pos;
}

bool BaseIterator::operator>(const BaseIterator &other) const {
    if(&mc != &other.mc) throw std::invalid_argument("Iterators are not from the same MagicalContainer");
    return pos > other.pos;
}

bool BaseIterator::operator<(const BaseIterator &other) const {
    if(&mc != &other.mc) throw std::invalid_argument("Iterators are not from the same MagicalContainer");
    return pos < other.pos;
}

int BaseIterator::operator*() const {
    if (it == mc.originalElements.end()) throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

BaseIterator &BaseIterator::operator++() {
    if (it == mc.originalElements.end()) throw std::out_of_range("Iterator is out of range");
    ++it; // increment iterator
    ++pos; // increment position
    return *this;
}

BaseIterator &BaseIterator::begin() {
    it = mc.originalElements.begin(); // set iterator to first element
    pos = 0; // set position to 0
    return *this;
}

BaseIterator &BaseIterator::end() {
    it = mc.originalElements.end(); // set iterator to last element
    pos = mc.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------AscendingIterator-------------
--------------------------------------------*/

AscendingIterator::AscendingIterator(MagicalContainer &mc) : BaseIterator(mc) {
    it = mc.sortedElements.begin(); // set iterator to first element
}

AscendingIterator::AscendingIterator(const AscendingIterator &other) : BaseIterator(other) {
    it = other.it; // copy iterator
}

int AscendingIterator::operator*() const {
    if (it == mc.sortedElements.end()) throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

AscendingIterator &AscendingIterator::operator++() {
    if (it == mc.sortedElements.end()) throw std::out_of_range("Iterator is out of range");
    ++it; // increment iterator
    ++pos; // increment position
    return *this;
}

AscendingIterator& AscendingIterator::begin() {
    it = mc.sortedElements.begin(); // set iterator to first element
    pos = 0; // set position to 0
    return *this;
}

AscendingIterator& AscendingIterator::end() {
    it = mc.sortedElements.end(); // set iterator to last element
    pos = mc.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------SideCrossIterator------------
--------------------------------------------*/

SideCrossIterator::SideCrossIterator(MagicalContainer &mc) : BaseIterator(mc) {
    it = mc.crossElements.begin(); // set iterator to first element
}

SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BaseIterator(other) {
    it = other.it; // copy iterator
}

int SideCrossIterator::operator*() const {
    if (it == mc.crossElements.end()) throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

SideCrossIterator &SideCrossIterator::operator++() {
    if (it == mc.crossElements.end()) throw std::out_of_range("Iterator is out of range");
    ++it; // increment iterator
    ++pos; // increment position
    return *this;
}

SideCrossIterator& SideCrossIterator::begin() {
    it = mc.crossElements.begin(); // set iterator to first element
    pos = 0; // set position to 0
    return *this;
}

SideCrossIterator& SideCrossIterator::end() {
    it = mc.crossElements.end(); // set iterator to last element
    pos = mc.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/

/*------------------------------------------
--------------PrimeIterator-----------------
--------------------------------------------*/

PrimeIterator::PrimeIterator(MagicalContainer &mc) : BaseIterator(mc) {
    it = mc.primeElements.begin(); // set iterator to first element
}

PrimeIterator::PrimeIterator(const PrimeIterator &other) : BaseIterator(other) {
    it = other.it; // copy iterator
}

int PrimeIterator::operator*() const {
    if (it == mc.primeElements.end()) throw std::out_of_range("Iterator is out of range");
    return *it; // return value of iterator
}

PrimeIterator &PrimeIterator::operator++() {
    if (it == mc.primeElements.end()) throw std::out_of_range("Iterator is out of range");
    ++it; // increment iterator
    ++pos; // increment position
    return *this;
}

PrimeIterator& PrimeIterator::begin() {
    it = mc.primeElements.begin(); // set iterator to first element
    pos = 0; // set position to 0
    return *this;
}

PrimeIterator& PrimeIterator::end() {
    it = mc.primeElements.end(); // set iterator to last element
    pos = mc.primeElements.size(); // set position to size of MagicalContainer
    return *this;
}

/*------------------------------------------
-------------------------------------------*/
