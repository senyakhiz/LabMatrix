#include "TTriangleMatrix.h"
#include <stdexcept>

template <class T>
TTriangleMatrix<T>::TTriangleMatrix(std::initializer_list<std::initializer_list<T>> list, bool isUpper)
    : TMatrix<T>(list.size(), list.size()), _size(list.size()), _isUpper(isUpper) {

    _data = TMathVector<TMathVector<T>>(_size);

    size_t i = 0;
    for (const auto& row : list) {
        if (_isUpper) {
            TMathVector<T> row_vec(_size - i);
            size_t j = i;
            for (auto it = row.begin() + i; it != row.end(); ++it) {
                row_vec[j - i] = *it;
                ++j;
            }
            _data[i] = row_vec;
        }
        else {
            TMathVector<T> row_vec(i + 1);
            size_t j = 0;
            for (auto it = row.begin(); it != row.begin() + i + 1; ++it) {
                row_vec[j++] = *it;
            }
            _data[i] = row_vec;
        }
        ++i;
    }
}

template <class T>
TTriangleMatrix<T>::ElementProxy::ElementProxy(TTriangleMatrix<T>& matrix, size_t row, size_t col)
    : _matrix(matrix), _row(row), _col(col) {
}

template <class T>
TTriangleMatrix<T>::ElementProxy::operator T() const {
    if (_matrix._isUpper) {
        if (_col < _row) return T(0);
        return _matrix._data[_row][_col - _row];
    }
    else {
        if (_col > _row) return T(0); 
        return _matrix._data[_row][_col];
    }
}

template <class T>
typename TTriangleMatrix<T>::ElementProxy& TTriangleMatrix<T>::ElementProxy::operator=(T value) {
    if (_matrix._isUpper) {
        if (_col < _row) {
            throw std::invalid_argument("Attempt to write to lower triangle of upper triangular matrix!");
        }
        _matrix._data[_row][_col - _row] = value;
    }
    else {
        if (_col > _row) {
            throw std::invalid_argument("Attempt to write to upper triangle of lower triangular matrix!");
        }
        _matrix._data[_row][_col] = value;
    }
    return *this;
}

template <class T>
TTriangleMatrix<T>::ProxyRow::ProxyRow(TTriangleMatrix<T>& matrix, size_t row)
    : _matrix(matrix), _row(row) {
}

template <class T>
typename TTriangleMatrix<T>::ElementProxy TTriangleMatrix<T>::ProxyRow::operator[](size_t col) {
    return ElementProxy(_matrix, _row, col);
}

template <class T>
typename TTriangleMatrix<T>::ProxyRow TTriangleMatrix<T>::operator[](size_t row) {
    return ProxyRow(*this, row);
}

template <class U>
std::ostream& operator<<(std::ostream& os, TTriangleMatrix<U>& matrix) {
    for (size_t i = 0; i < matrix._size; ++i) {
        os << "[ ";
        for (size_t j = 0; j < matrix._size; ++j) {
            os << matrix[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}