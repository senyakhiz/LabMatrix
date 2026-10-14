#pragma once
#include "TVector.h"
#include <iostream>

template <class T>
class TMathVector : public TVector<T> {
protected:
    size_t _start_index = 0;

public:
    TMathVector();
    TMathVector(size_t s, const T* data);
    TMathVector(std::initializer_list<T> data);
    TMathVector(const TMathVector& other);
    virtual ~TMathVector() = default;

    TMathVector& operator=(const TMathVector& other) noexcept;

    double operator*(const TMathVector<T>& other) const noexcept;
    TMathVector<T> operator*(T val) const noexcept;
    TMathVector<T>& operator*=(double val) noexcept;

    TMathVector<T> operator+(const TMathVector<T>& other) const;
    TMathVector<T>& operator+=(const TMathVector<T>& other) noexcept;

    TMathVector<T> operator-(const TMathVector<T>& other) const;
    TMathVector<T>& operator-=(const TMathVector<T>& other) noexcept;

    bool operator==(const TMathVector<T>& other) const noexcept;
    bool operator!=(const TMathVector<T>& other) const noexcept;

    T& operator[](size_t i) noexcept; 
    const T& operator[](size_t i) const noexcept;

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const TMathVector<U>& vec);

    template <class U>
    friend std::istream& operator>>(std::istream& is, TMathVector<U>& vec);
};
