#pragma once

#include <vector>
#include <iterator>
#include <set>
#include <list>

namespace ariel
{

    class MagicalContainer
    {
        std::vector<int> originalElements; // stores original insertion order
        std::vector<int *> crossElements;  // stores elements pointers in cross order
        std::vector<int *> sortedElements; // stores elements pointers in ascending order
        std::vector<int *> primeElements;  // stores elements pointers that are prime numbers in original order

        bool isPrime(int number) const;
        void updateCrossElements();
        void updateSortedElements();
        void updatePrimeElements();

        class BasicIterator; // forward declaration of nested class 

    public:
        MagicalContainer() = default;
        ~MagicalContainer() = default;
        MagicalContainer(const MagicalContainer &other) = default;
        MagicalContainer &operator=(const MagicalContainer &other) = default;
        MagicalContainer(MagicalContainer &&other) noexcept = default;
        MagicalContainer &operator=(MagicalContainer &&other) noexcept = default;

        void addElement(int element);
        void removeElement(int element);
        size_t size() const;

        bool operator==(const MagicalContainer &other) const;
        bool operator!=(const MagicalContainer &other) const;

        // Nested classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::BasicIterator
    {
    protected:
        MagicalContainer *magicalContainer;
        size_t pos;

    public:
        BasicIterator(MagicalContainer &magicalContainer);
        BasicIterator(const BasicIterator &other);
        ~BasicIterator() = default;
        BasicIterator(BasicIterator &&other) noexcept = default;
        BasicIterator &operator=(BasicIterator &&other) noexcept = default;
        BasicIterator &operator=(const BasicIterator &other) = default;

        bool operator==(const BasicIterator &other) const;
        bool operator!=(const BasicIterator &other) const;
        bool operator>(const BasicIterator &other) const;
        bool operator<(const BasicIterator &other) const;
    };

    class MagicalContainer::AscendingIterator : public MagicalContainer::BasicIterator
    {
    private:
        std::vector<int *>::iterator it;

    public:
        AscendingIterator(MagicalContainer &magicalContainer);
        AscendingIterator(const AscendingIterator &other);
        ~AscendingIterator() = default;
        AscendingIterator(AscendingIterator &&other) noexcept = default;
        AscendingIterator &operator=(AscendingIterator &&other) noexcept = default;

        AscendingIterator &operator=(const AscendingIterator &other);

        int operator*() const;
        AscendingIterator &operator++();

        AscendingIterator begin();
        AscendingIterator end();
    };

    class MagicalContainer::SideCrossIterator : public MagicalContainer::BasicIterator
    {
    private:
        std::vector<int *>::iterator it;

    public:
        SideCrossIterator(MagicalContainer &magicalContainer);
        SideCrossIterator(const SideCrossIterator &other);
        ~SideCrossIterator() = default;
        SideCrossIterator(SideCrossIterator &&other) noexcept = default;
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept = default;

        SideCrossIterator &operator=(const SideCrossIterator &other);

        int operator*() const;
        SideCrossIterator &operator++();

        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class MagicalContainer::PrimeIterator : public MagicalContainer::BasicIterator
    {
    private:
        std::vector<int *>::iterator it;

    public:
        PrimeIterator(MagicalContainer &magicalContainer);
        PrimeIterator(const PrimeIterator &other);
        ~PrimeIterator() = default;
        PrimeIterator(PrimeIterator &&other) noexcept = default;
        PrimeIterator &operator=(PrimeIterator &&other) noexcept = default;

        PrimeIterator &operator=(const PrimeIterator &other);

        int operator*() const;
        PrimeIterator &operator++();

        PrimeIterator begin();
        PrimeIterator end();
    };
} // namespace ariel