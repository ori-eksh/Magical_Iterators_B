#pragma once
#include "Iterator.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <algorithm> // for remove function

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::set<int> Numbers;
        std::vector<const int *> growsUpNumbers;
        std::vector<const int *> primesNumbers;
        std::vector<const int *> SideCrossNum;

    public:
        MagicalContainer() {}
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        static bool isPrime(int number);

        /****************************************************************************************/
        class AscendingIterator : public Iterator
        {
        private:
            MagicalContainer &container;
            size_t now;

        public:
            AscendingIterator(MagicalContainer &other) : container(other), now(0) {}

            AscendingIterator(MagicalContainer &other, size_t index) : container(other), now(index) {}

            ~AscendingIterator() override = default;
            AscendingIterator &operator++();
            bool operator!=(const Iterator &other) const override;
            bool operator!=(const AscendingIterator &other) const;

            bool operator==(const Iterator &other) const override;
            bool operator==(const AscendingIterator &other) const;

            bool operator<(const Iterator &other) const override;
            bool operator<(const AscendingIterator &other) const;

            bool operator>(const Iterator &other) const override;
            bool operator>(const AscendingIterator &other) const;
            int operator*() const;
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator=(AscendingIterator &&other) noexcept;
            AscendingIterator begin()
            {
                return AscendingIterator(container, 0);
            }

            AscendingIterator end() const
            {
                return AscendingIterator(container, container.growsUpNumbers.size());
            }
        };
        /******************/
        class PrimeIterator : public Iterator
        {
        private:
            MagicalContainer &container;
            size_t now;

        public:
            PrimeIterator(MagicalContainer &other) : container(other), now(0) {}

            PrimeIterator(MagicalContainer &other, size_t index) : container(other), now(index) {}

            ~PrimeIterator() override = default;
            PrimeIterator &operator++();
            int operator*() const;
            bool operator!=(const Iterator &other) const override;
            bool operator!=(const PrimeIterator &) const;

            bool operator==(const Iterator &other) const override;
            bool operator==(const PrimeIterator &) const;

            bool operator<(const Iterator &other) const override;
            bool operator<(const PrimeIterator &) const;

            bool operator>(const Iterator &other) const override;
            bool operator>(const PrimeIterator &) const;
            PrimeIterator &operator=(const PrimeIterator &other);
            PrimeIterator &operator=(PrimeIterator &&other) noexcept;
            PrimeIterator begin()
            {
                return PrimeIterator(container, 0);
            }

            PrimeIterator end() const
            {
                return PrimeIterator(container, container.primesNumbers.size());
            }
        };

        /******************/

        class SideCrossIterator : public Iterator
        {
        private:
            MagicalContainer &container;
            size_t now;

        public:
            SideCrossIterator(MagicalContainer &other) : container(other), now(0) {}

            SideCrossIterator(MagicalContainer &other, size_t index) : container(other), now(index) {}

            ~SideCrossIterator() override = default;

            SideCrossIterator &operator++();
            int operator*() const;
            bool operator!=(const Iterator &other) const override;
            bool operator!=(const SideCrossIterator &other) const;

            bool operator==(const Iterator &other) const override;
            bool operator==(const SideCrossIterator &other) const;

            bool operator<(const Iterator &other) const override;
            bool operator<(const SideCrossIterator &other) const;

            bool operator>(const Iterator &other) const override;
            bool operator>(const SideCrossIterator &other) const;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;
            SideCrossIterator begin()
            {
                return SideCrossIterator(container, 0);
            }

            SideCrossIterator end() const
            {
                return SideCrossIterator(container, container.SideCrossNum.size());
            }
        };
    };
}