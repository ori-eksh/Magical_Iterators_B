#pragma once
namespace ariel
{
    class Iterator
    {
    private:
    public:
        Iterator()
        {
        }
        // Add copy constructor
        Iterator(const Iterator &other) {}

        // Add copy assignment operator
        Iterator &operator=(const Iterator &other) { return *this; }

        // Add move constructor
        Iterator(Iterator &&other) noexcept {}

        // Add move assignment operator
        Iterator &operator=(Iterator &&other) noexcept { return *this; }
        virtual ~Iterator() = default;
        virtual bool operator!=(const Iterator &other) const = 0;

        virtual bool operator==(const Iterator &other) const = 0;

        virtual bool operator<(const Iterator &other) const = 0;

        virtual bool operator>(const Iterator &other) const = 0;
    };
}