#include "MagicalContainer.hpp"
namespace ariel
{
    void MagicalContainer::addElement(int element)
    {
        auto f = std::find(Numbers.begin(), Numbers.end(), element);
        if (f != Numbers.end())
            return;
        containerSize++;
        Numbers.push_back(element); // the numbers
        int *elementPtr = &Numbers.back();

        // the prime
        if (isPrime(element))
        {
            std::vector<int *> primesTemp;
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
        std::vector<int *> growsTemp;
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
        SideCrossNum.push_back(elementPtr);
        std::vector<int *> output;

        // Check if the input vector has only one element
        if (SideCrossNum.size() == 1)
        {
            output.push_back(SideCrossNum.at(0));
            SideCrossNum = output;
            return;
        }

        int start = 0;                     // Index for the first vector
        int end = SideCrossNum.size() - 1; // Index for the last vector

        while (start <= end)
        {
            output.push_back(SideCrossNum.at((size_t)start)); // Copy first element
            if (start != end)
            {
                output.push_back(SideCrossNum.at((size_t)end)); // Copy last element if start and end are different
            }
            start++; // Increment start index
            end--;   // Decrement end index
        }

        SideCrossNum = output;
    }

    void MagicalContainer::removeElement(int element)
    {
        auto f = std::find(Numbers.begin(), Numbers.end(), element);
        if (f == Numbers.end())
        {
            throw std::runtime_error("not exist");
        }
        int *ptr = &(*f);
        // Remove the element from growsUpNumbers list
        for (auto it = growsUpNumbers.begin(); it != growsUpNumbers.end();)
        {
            if (*it == ptr)
            {
                it = growsUpNumbers.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Remove the element from SideCrossNum vector
        for (auto it = SideCrossNum.begin(); it != SideCrossNum.end();)
        {
            if (*it == ptr)
            {
                it = SideCrossNum.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }

        // Remove the element from primesNumbers vector
        for (auto it = primesNumbers.begin(); it != primesNumbers.end();)
        {
            if (*it == ptr)
            {
                it = primesNumbers.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }

        // Remove the element from Numbers vector
        for (auto it = Numbers.begin(); it != Numbers.end();)
        {
            if (*it == element)
            {
                it = Numbers.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }

        containerSize--;
    }

    size_t MagicalContainer::size() const
    {
        return containerSize;
    }

    bool MagicalContainer::isPrime(int number)
    {
        if (number <= 1)
        {
            return false;
        }

        for (int i = 2; i <= (number); ++i)
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