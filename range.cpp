#include "range.h"

Range::Range(int t_start, int t_end, int t_step) {
    // invalid range checker
    if (
        (t_step == 0) || (t_end < t_start && t_step > 0) || 
        (t_end > t_start && t_step < 0)
    ) {
        return;
    }

    m_size = calculateSize(t_start, t_end, t_step);
    if (!m_size) {
        return;
    }
    
    m_array = new int [m_size];

    unsigned int i = 0;
    int item = t_start;
    while (i < m_size) {
        m_array[i] = item;
        item += t_step;
        i++;
    }
}

Range::Range(int t_start, int t_end) : Range(t_start, t_end, 1) {}

Range::Range(int t_end) : Range(0, t_end, 1) {}

Range::Range(Range const& t_other) {
    *this = t_other;
}

Range::Range(Range&& t_other) {
    *this = std::move(t_other);
}

Range& Range::operator=(Range const& t_other) {
    if (&t_other == this) { // silly goose!
        return *this;
    }
    
    if (m_array) {
        delete [] m_array;
    }

    m_size = t_other.m_size;
    m_array = new int [m_size];
    std::memcpy(m_array, t_other.m_array, sizeof(int) * m_size);

    return *this;
}

Range& Range::operator=(Range&& t_other) {
    if (&t_other == this) { // silly goose!
        return *this;
    }

    if (m_array) {
        delete [] m_array;
    }

    m_array = std::exchange(t_other.m_array, nullptr);
    m_size = std::exchange(t_other.m_size, 0);

    return *this;
}

Range::~Range() {
    delete [] m_array;
}

unsigned int Range::calculateSize(int t_start, int t_end, int t_step) {
    const unsigned int distance = std::abs(t_start - t_end);
    const unsigned int absStep = std::abs(t_step);
    unsigned int size = distance / absStep;
    if (distance % absStep != 0) {
        size++;
    }
    return size;
}

Range::Iterator::Iterator(int* t_item) : m_item(t_item) {}

int const& Range::Iterator::operator*() const {
    return *m_item;
}

bool Range::Iterator::operator!=(Iterator const& t_iterator) const {
    return m_item != t_iterator.m_item;
}

void Range::Iterator::operator++() {
    ++m_item;
}

Range::Iterator Range::begin() const {
    return Iterator(m_array);
}

Range::Iterator Range::end() const {
    return Iterator(m_array + m_size);
}

int const& Range::operator[](unsigned int t_index) const {
    return m_array[t_index];
}

int const& Range::at(unsigned int t_index) const {
    if (t_index >= m_size) {
        throw std::out_of_range(
            "bounds checker: t_index (which is " + 
            std::to_string(t_index) + ") >= m_size (which is " + 
            std::to_string(m_size) + ')'
        );
    }
    return m_array[t_index];
}
