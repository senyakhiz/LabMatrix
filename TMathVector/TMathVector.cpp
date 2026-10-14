#pragma once
#include "TMathVector.h"
#include <cmath>

template <class T>
TMathVector<T>::TMathVector() : TVector<T>() {}

template <class T>
TMathVector<T>::TMathVector(size_t s, const T* data) : TVector<T>(s, data) {}

template <class T>
TMathVector<T>::TMathVector(std::initializer_list<T> data) : TVector<T>(data) {}

template <class T>
TMathVector<T>::TMathVector(const TMathVector& other) : TVector<T>(other) {}

template <class T>
TMathVector<T>& TMathVector<T>::operator=(const TMathVector& other) noexcept {
    TVector<T>::operator=(other);
    return *this;
}

template <class T>
double TMathVector<T>::operator*(const TMathVector<T>& other) const noexcept {
    double result = 0;
    for (size_t i = 0; i < this->_size; ++i) {
        result += this->_data[i] * other[i];
    }
    return result;
}

template <class T>
TMathVector<T> TMathVector<T>::operator*(T val) const noexcept {
    TMathVector<T> result(*this);
    for (size_t i = 0; i < result.size(); ++i) result[i] *= val;
    return result;
}

template <class T>
TMathVector<T>& TMathVector<T>::operator*=(double val) noexcept {
    for (size_t i = 0; i < this->_size; ++i) this->_data[i] *= val;
    return *this;
}

template <class T>
TMathVector<T> TMathVector<T>::operator+(const TMathVector<T>& other) const {
    TMathVector<T> result(*this);
    result += other;
    return result;
}

template <class T>
TMathVector<T>& TMathVector<T>::operator+=(const TMathVector<T>& other) noexcept {
    size_t min_size = std::min(this->_size, other.size());
    for (size_t i = 0; i < min_size; ++i) this->_data[i] += other[i];
    return *this;
}

template <class T>
TMathVector<T> TMathVector<T>::operator-(const TMathVector<T>& other) const {
    TMathVector<T> result(*this);
    result -= other;
    return result;
}

template <class T>
TMathVector<T>& TMathVector<T>::operator-=(const TMathVector<T>& other) noexcept {
    size_t min_size = std::min(this->_size, other.size());
    for (size_t i = 0; i < min_size; ++i) this->_data[i] -= other[i];
    return *this;
}

template <class T>
bool TMathVector<T>::operator==(const TMathVector<T>& other) const noexcept {
    if (this->_size != other.size()) return false;
    for (size_t i = 0; i < this->_size; ++i) {
        if (this->_data[i] != other[i]) return false;
    }
    return true;
}

template <class T>
bool TMathVector<T>::operator!=(const TMathVector<T>& other) const noexcept {
    return !(*this == other);
}

template <class T>
T& TMathVector<T>::operator[](size_t i) noexcept { 
    return TVector<T>::operator[](i); 
}

template <class T>
const T& TMathVector<T>::operator[](size_t i) const noexcept { 
    return TVector<T>::operator[](i); 
}

template <class U>
std::ostream& operator<<(std::ostream& os, const TMathVector<U>& vec) {
    os << "[ ";
    for (size_t i = 0; i < vec.size(); ++i) os << vec[i] << " ";
    os << "]";
    return os;
}

template <class U>
std::istream& operator>>(std::istream& is, TMathVector<U>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) is >> vec[i];
    return is;
}