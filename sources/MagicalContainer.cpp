#include "MagicalContainer.hpp"
#include <cmath>
namespace ariel
{
    void MagicalContainer::addElement(int element)
    {
        auto f = Numbers.insert(element);

        if (!f.second)
        {
            return;
        }

        const int *elementPtr = &(*f.first);

        // the prime
        if (isPrime(element))
        {
            std::vector<const int *> primesTemp;
            while (primesNumbers.empty() == false && *primesNumbers.back() > element)
            {
                primesTemp.push_back(primesNumbers.back());
                primesNumbers.pop_back();
            }

            primesNumbers.push_back(elementPtr);

            while (primesTemp.empty() == false)
            {
                primesNumbers.push_back(primesTemp.back());
                primesTemp.pop_back();
            }
        }
        // the growsUpNumbers
        std::vector<const int *> growsTemp;
        while (growsUpNumbers.empty() == false && *growsUpNumbers.back() > element)
        {
            growsTemp.push_back(growsUpNumbers.back());
            growsUpNumbers.pop_back();
        }

        growsUpNumbers.push_back(elementPtr);

        while (growsTemp.empty() == false)
        {
            growsUpNumbers.push_back(growsTemp.back());
            growsTemp.pop_back();
        }

        // the cross numbers

        SideCrossNum.clear();
        if (growsUpNumbers.size() == 1)
        {
            SideCrossNum.push_back(growsUpNumbers.back());
            return;
        }
        size_t start = 0;
        size_t end = growsUpNumbers.size() - 1;

        while (start <= end)
        {
            SideCrossNum.push_back(growsUpNumbers.at(start));
            if (start != end)
            {
                SideCrossNum.push_back(growsUpNumbers.at(end));
            }
            start++;
            end--;
        }
    }

    void MagicalContainer::removeElement(int element)
    {
        auto f = std::find(Numbers.begin(), Numbers.end(), element);
        if (f == Numbers.end())
        {
            throw std::runtime_error("not exist");
        }
        const int *ptr = &(*f);

        // Remove the element from growsUpNumbers list
        auto it1 = std::find(growsUpNumbers.begin(), growsUpNumbers.end(), ptr);
        growsUpNumbers.erase(it1);

        // Remove the element from SideCrossNum vector
        auto it2 = std::find(SideCrossNum.begin(), SideCrossNum.end(), ptr);
        SideCrossNum.erase(it2);

        // Remove the element from primesNumbers vector
        if (isPrime(element))
        {
            auto it3 = std::find(primesNumbers.begin(), primesNumbers.end(), ptr);
            primesNumbers.erase(it3);
        }

        // Remove the element from Numbers vector
        Numbers.erase(f);
    }

    size_t MagicalContainer::size() const
    {
        return Numbers.size();
    }

    bool MagicalContainer::isPrime(int number)
    {
        if (number <= 1)
        {
            return false;
        }

        for (int i = 2; i <= sqrt(number); ++i)
        {
            if (number % i == 0)
            {
                return false;
            }
        }

        return true;
    }
    /***************************************************************************************/
    /*
    AscendingIterator

    */
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (now >= container.growsUpNumbers.size())
        {
            throw std::runtime_error("Iterator out of range");
        }

        now++;
        return *this;
    }
    bool MagicalContainer::AscendingIterator::operator!=(const Iterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now != otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now != other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator==(const Iterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);

        if (otherPtr == nullptr)
            throw std::runtime_error("Cannot compare iterators of different types");

        if (&container != &otherPtr->container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now == otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now == other.now)
        {
            return true;
        }
        return false;
    }

    bool MagicalContainer::AscendingIterator::operator<(const Iterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now < otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now < other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator>(const Iterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now < otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now > other.now)
        {
            return true;
        }
        return false;
    }
    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (now >= container.growsUpNumbers.size())
            throw std::out_of_range("Iterator out of range");

        return *(container.growsUpNumbers.at(now));
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this != &other)
        {
            if (&container != &other.container)
                throw std::runtime_error("Cannot assign iterators from different containers");

            now = other.now;
        }

        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            now = other.now;
        }

        return *this;
    }
    /***************************************************************************************/
    /*
    PrimeIterator

    */

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (now >= container.primesNumbers.size())
        {
            throw std::runtime_error("Iterator out of range");
        }

        ++now;
        return *this;
    }
    bool MagicalContainer::PrimeIterator::operator!=(const Iterator &other) const
    {
        const PrimeIterator *otherPtr = dynamic_cast<const PrimeIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now != otherPtr->now)
        {
            return true;
        }
        return false;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now != other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::PrimeIterator::operator==(const Iterator &other) const
    {
        const PrimeIterator *otherPtr = dynamic_cast<const PrimeIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now == otherPtr->now)
        {
            return true;
        }
        return false;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now == other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::PrimeIterator::operator<(const Iterator &other) const
    {
        const PrimeIterator *otherPtr = dynamic_cast<const PrimeIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now < otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now < other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::PrimeIterator::operator>(const Iterator &other) const
    {
        const PrimeIterator *otherPtr = dynamic_cast<const PrimeIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now > otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now > other.now)
        {
            return true;
        }
        return false;
    }
    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (now >= container.primesNumbers.size())
            throw std::out_of_range("Iterator out of range");

        return *(container.primesNumbers.at(now));
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this != &other)
        {
            if (&container != &other.container)
                throw std::runtime_error("Cannot assign iterators from different containers");

            now = other.now;
        }

        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            now = other.now;
        }

        return *this;
    }
    /***************************************************************************************/
    /*
    SideCrossIterator

    */
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {

        if (now >= container.SideCrossNum.size())
        {
            throw std::runtime_error("Iterator out of range");
        }

        ++now;
        return *this;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const Iterator &other) const
    {
        const SideCrossIterator *otherPtr = dynamic_cast<const SideCrossIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now != otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now != other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const Iterator &other) const
    {
        const SideCrossIterator *otherPtr = dynamic_cast<const SideCrossIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now == otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now == other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const Iterator &other) const
    {
        const SideCrossIterator *otherPtr = dynamic_cast<const SideCrossIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now < otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now < other.now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const Iterator &other) const
    {
        const SideCrossIterator *otherPtr = dynamic_cast<const SideCrossIterator *>(&other);

        if (otherPtr == nullptr)
        {
            throw std::runtime_error("Cannot compare iterators of different types");
        }

        else if (&container != &otherPtr->container)
        {
            throw std::runtime_error("you cant compare iterators from different containers");
        }

        if (now > otherPtr->now)
        {
            return true;
        }
        return false;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        if (&container != &other.container)
            throw std::runtime_error("Cannot compare iterators from different containers");

        if (now > other.now)
        {
            return true;
        }
        return false;
    }
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (now >= container.SideCrossNum.size())
            throw std::out_of_range("Iterator out of range");

        return *(container.SideCrossNum.at(now));
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this != &other)
        {
            if (&container != &other.container)
                throw std::runtime_error("Cannot assign iterators from different containers");

            now = other.now;
        }

        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            now = other.now;
        }

        return *this;
    }
}