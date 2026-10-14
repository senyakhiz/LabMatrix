#include "TMatrix.h"

template <class T>
TMatrix<T>::TMatrix() : TMathVector<TMathVector<T>>(), _rows(0), _cols(0) {}

template <class T>
TMatrix<T>::TMatrix(size_t N, size_t M) : TMathVector<TMathVector<T>>(N), _rows(N), _cols(M) {
    for (size_t i = 0; i < N; ++i) {
        (*this)[i] = TMathVector<T>(M);
    }
}

template <class T>
TMatrix<T>::TMatrix(std::initializer_list<std::initializer_list<T>> list)
    : TMathVector<TMathVector<T>>(list.size()), _rows(list.size()) {
    _cols = (list.size() > 0) ? list.begin()->size() : 0;
    size_t i = 0;
    for (const auto& row : list) {
        (*this)[i] = TMathVector<T>(row);
        ++i;
    }
}

template <class T>
TMatrix<T>::TMatrix(const TMatrix& other)
    : TMathVector<TMathVector<T>>(other), _rows(other._rows), _cols(other._cols) {}

template <class T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix& other) noexcept {
    if (this != &other) {
        TMathVector<TMathVector<T>>::operator=(other);
        _rows = other._rows;
        _cols = other._cols;
    }
    return *this;
}

template <class T>
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& other) const {
    TMatrix<T> result(*this);
    result += other;
    return result;
}

template <class T>
TMatrix<T>& TMatrix<T>::operator+=(const TMatrix<T>& other) {
    for (size_t i = 0; i < _rows; ++i) {
        (*this)[i] += other[i];
    }
    return *this;
}

template <class T>
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& other) const {
    TMatrix<T> result(*this);
    result -= other;
    return result;
}

template <class T>
TMatrix<T>& TMatrix<T>::operator-=(const TMatrix<T>& other) {
    for (size_t i = 0; i < _rows; ++i) {
        (*this)[i] -= other[i];
    }
    return *this;
}

template <class T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& other) const {
    TMatrix<T> result(_rows, other.getM());
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < other.getM(); ++j) {
            result[i][j] = T();
            for (size_t k = 0; k < _cols; ++k) {
                result[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }
    return result;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const TMatrix<U>& matrix) {
    for (size_t i = 0; i < matrix.getN(); ++i) {
        os << "[ ";
        for (size_t j = 0; j < matrix.getM(); ++j) {
            os << matrix[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}