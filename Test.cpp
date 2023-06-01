#include "doctest.h"

#include "sources/MagicalContainer.hpp"

#include <iostream>

using namespace std;

using namespace ariel;

TEST_CASE("MagicalContainer")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    CHECK(container.size() == 5);

    container.removeElement(17);
    CHECK(container.size() == 4);

    container.removeElement(2);
    CHECK(container.size() == 3);

    CHECK(container.size() == 3);

    CHECK_THROWS(container.removeElement(1000)); // removing non-existing element
}

TEST_CASE("AscendingIterator")
{
    MagicalContainer container;
    MagicalContainer container2;

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    container2.addElement(12);
    container2.addElement(1);
    container2.addElement(3);
    container2.addElement(100);
    container2.addElement(53);


    MagicalContainer::AscendingIterator ascendingIterator1(container);
    MagicalContainer::AscendingIterator ascendingIterator2(ascendingIterator1); // copy constructor
    MagicalContainer::AscendingIterator ascendingIterator3(container2);


    // Initialization test
    CHECK(*ascendingIterator1.begin() == 2);                           // smallest element
    CHECK(*ascendingIterator1.begin() == *ascendingIterator2.begin()); // same value because of copy constructor
    CHECK(*ascendingIterator3.begin() == 1);                           // smallest element

    // Comparison test
    CHECK((ascendingIterator1 == ascendingIterator2));
    CHECK_THROWS_AS(ascendingIterator1.operator==(ascendingIterator3), std::invalid_argument); // cant compare iterators from different containers
    CHECK_THROWS_AS(ascendingIterator1.operator<(ascendingIterator3), std::invalid_argument);
    CHECK_THROWS_AS(ascendingIterator1.operator>(ascendingIterator3), std::invalid_argument);
    CHECK_THROWS_AS(ascendingIterator1.operator!=(ascendingIterator3), std::invalid_argument);

    // Incrementation test and comparison test
    ++ascendingIterator1;
    CHECK(*ascendingIterator1 == 3);
    CHECK((ascendingIterator1 != ascendingIterator2));
    CHECK((ascendingIterator1 > ascendingIterator2));
    CHECK((ascendingIterator2 < ascendingIterator1));

    // Order test
    int expectedOrder[] = {2, 3, 9, 17, 25};
    int i = 0;
    for (MagicalContainer::AscendingIterator it = ascendingIterator1.begin(); it != ascendingIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder[i]);
    }
    // Container is not detached from iterator test
    container.addElement(1000);
    int expectedOrder2[] = {2, 3, 9, 17, 25, 1000};
    i = 0;
    for (MagicalContainer::AscendingIterator it = ascendingIterator1.begin(); it != ascendingIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder2[i]);
    }
    container.removeElement(17);
    container.removeElement(2);
    int expectedOrder3[] = {3, 9, 25, 1000};
    i = 0;
    for (MagicalContainer::AscendingIterator it = ascendingIterator1.begin(); it != ascendingIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder3[i]);
    }

}

TEST_CASE("SideCrossIterator")
{
    MagicalContainer container;
    MagicalContainer container2;

   

    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    container2.addElement(12);
    container2.addElement(1);
    container2.addElement(3);
    container2.addElement(100);
    container2.addElement(53);

    MagicalContainer::SideCrossIterator sideCrossIterator1(container);
    MagicalContainer::SideCrossIterator sideCrossIterator2(sideCrossIterator1); // copy constructor
    MagicalContainer::SideCrossIterator sideCrossIterator3(container2);


    // Initialization test
    CHECK(*sideCrossIterator1.begin() == 2);                          // first element
    CHECK(*sideCrossIterator1.begin() == *sideCrossIterator2.begin()); // same value because of copy constructor
    CHECK(*sideCrossIterator3.begin() == 1);                          // first element

    // Comparison test
    CHECK((sideCrossIterator1 == sideCrossIterator2));
    CHECK_THROWS_AS(sideCrossIterator1.operator==(sideCrossIterator3), std::invalid_argument); // cant compare iterators from different containers
    CHECK_THROWS_AS(sideCrossIterator1.operator<(sideCrossIterator3), std::invalid_argument);
    CHECK_THROWS_AS(sideCrossIterator1.operator>(sideCrossIterator3), std::invalid_argument);
    CHECK_THROWS_AS(sideCrossIterator1.operator!=(sideCrossIterator3), std::invalid_argument);

    // Incrementation test and comparison test
    ++sideCrossIterator1;
    CHECK(*sideCrossIterator1 == 25);
    CHECK((sideCrossIterator1 != sideCrossIterator2));
    CHECK((sideCrossIterator1 > sideCrossIterator2));
    CHECK((sideCrossIterator2 < sideCrossIterator1));

    // Order test
    int expectedOrder[] = {2,25,3,17,9};
    int i = 0;
    for (MagicalContainer::SideCrossIterator it = sideCrossIterator1.begin(); it != sideCrossIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder[i]);
    }

    // Container is not detached from iterator test
    container.addElement(1000);
    int expectedOrder2[] = {2,1000,3,25,9,17};
    i = 0;
    for (MagicalContainer::SideCrossIterator it = sideCrossIterator1.begin(); it != sideCrossIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder2[i]);
    }
    container.removeElement(17);
    container.removeElement(2);
    int expectedOrder3[] = {3,1000,9,25};
    i = 0;
    for (MagicalContainer::SideCrossIterator it = sideCrossIterator1.begin(); it != sideCrossIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder3[i]);
    }
}

TEST_CASE("PrimeIterator")
{
    MagicalContainer container;
    MagicalContainer container2;


    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    container2.addElement(12);
    container2.addElement(1);
    container2.addElement(3);
    container2.addElement(100);
    container2.addElement(53);


    MagicalContainer::PrimeIterator primeIterator1(container);
    MagicalContainer::PrimeIterator primeIterator2(primeIterator1); // copy constructor
    MagicalContainer::PrimeIterator primeIterator3(container2);

    // Initialization test
    CHECK(*primeIterator1.begin() == 17);                          // first prime element
    CHECK(*primeIterator1.begin() == *primeIterator2.begin()); // same value because of copy constructor
    CHECK(*primeIterator3.begin() == 3);                          // first prime element

    // Comparison test
    CHECK((primeIterator1 == primeIterator2));
    CHECK_THROWS_AS(primeIterator1.operator==(primeIterator3), std::invalid_argument); // cant compare iterators from different containers
    CHECK_THROWS_AS(primeIterator1.operator<(primeIterator3), std::invalid_argument);
    CHECK_THROWS_AS(primeIterator1.operator>(primeIterator3), std::invalid_argument);
    CHECK_THROWS_AS(primeIterator1.operator!=(primeIterator3), std::invalid_argument);

    // Incrementation test and comparison test
    ++primeIterator1;
    CHECK(*primeIterator1 == 2);
    CHECK((primeIterator1 != primeIterator2));
    CHECK((primeIterator1 > primeIterator2));
    CHECK((primeIterator2 < primeIterator1));

    // Order test
    int expectedOrder[] = {17, 2, 3};
    int i = 0;
    for (MagicalContainer::PrimeIterator it = primeIterator1.begin(); it != primeIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder[i]);
    }

    // Container is not detached from iterator test
    container.addElement(1009);
    int expectedOrder2[] = {17,2,3,1009};
    i = 0;
    for (MagicalContainer::PrimeIterator it = primeIterator1.begin(); it != primeIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder2[i]);
    }
    container.removeElement(17);
    container.removeElement(2);
    int expectedOrder3[] = {3,1009};
    i = 0;
    for (MagicalContainer::PrimeIterator it = primeIterator1.begin(); it != primeIterator1.end(); ++it, ++i)
    {
        CHECK(*it == expectedOrder3[i]);
    }
}
