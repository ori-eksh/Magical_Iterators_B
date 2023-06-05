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
        virtual ~Iterator() = default;
        virtual bool operator!=(const Iterator &other) const = 0;

        virtual bool operator==(const Iterator &other) const = 0;

        virtual bool operator<(const Iterator &other) const = 0;

        virtual bool operator>(const Iterator &other) const = 0;
    };
}