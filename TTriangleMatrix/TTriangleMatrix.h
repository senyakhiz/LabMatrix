#pragma once
#include "TMatrix.h"

template <class T>
class TTriangleMatrix : public TMatrix<T> {
private:
    TMathVector<TMathVector<T>> _data;
    size_t _size;
    bool _isUpper;

public:
    TTriangleMatrix(std::initializer_list<std::initializer_list<T>> list, bool isUpper = true);
    virtual ~TTriangleMatrix() = default;

    class ElementProxy {
    private:
        TTriangleMatrix<T>& _matrix;
        size_t _row, _col;
    public:
        ElementProxy(TTriangleMatrix<T>& matrix, size_t row, size_t col);
        operator T() const;
        ElementProxy& operator=(T value);
    };

    class ProxyRow {
    private:
        TTriangleMatrix<T>& _matrix;
        size_t _row;
    public:
        ProxyRow(TTriangleMatrix<T>& matrix, size_t row);
        ElementProxy operator[](size_t col);
    };

    ProxyRow operator[](size_t row);

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, TTriangleMatrix<U>& matrix);
};