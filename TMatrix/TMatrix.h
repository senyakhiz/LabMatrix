#pragma once
#include "TMathVector.h"

template <class T>
class TMatrix : public TMathVector<TMathVector<T>> {
protected:
    size_t _rows;
    size_t _cols;

public:
    TMatrix();
    TMatrix(size_t N, size_t M);
    TMatrix(std::initializer_list<std::initializer_list<T>> list);
    TMatrix(const TMatrix& other);
    virtual ~TMatrix() = default;

    TMatrix& operator=(const TMatrix& other) noexcept;

    inline size_t getN() const noexcept { return _rows; }
    inline size_t getM() const noexcept { return _cols; }

    TMatrix<T> operator+(const TMatrix<T>& other) const;
    TMatrix<T>& operator+=(const TMatrix<T>& other);

    TMatrix<T> operator-(const TMatrix<T>& other) const;
    TMatrix<T>& operator-=(const TMatrix<T>& other);

    TMatrix<T> operator*(const TMatrix<T>& other) const;

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const TMatrix<U>& matrix);
};