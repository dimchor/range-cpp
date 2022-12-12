#pragma once

#include <stdexcept>
#include <cmath>
#include <cstring>
#include <utility>

class Range {
public:
    Range(int); // end
    Range(int, int); // start, end
    Range(int, int, int); // start, end, step

    Range(Range const&);
    Range(Range&&);
    Range& operator=(Range const&);
    Range& operator=(Range&&);
    
    class Iterator {
    public:
        Iterator(int*);

        int const& operator*() const;
        bool operator!=(Iterator const&) const;
        void operator++();
    private:
        int* m_item = nullptr;
    };

    Range::Iterator begin() const;
    Range::Iterator end() const;

    int const& operator[](unsigned int) const;
    int const& at(unsigned int) const;

    virtual ~Range();
private:
    int* m_array = nullptr;
    unsigned int m_size = 0;

    static unsigned int calculateSize(int, int, int);
};
