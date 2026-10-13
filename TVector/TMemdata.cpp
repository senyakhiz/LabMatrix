#include "TMemdata.h"
#include <algorithm>
#include <cstring>

size_t calculate_capacity(size_t size) {
	if (size == 0) {
		return 0;
	}
	size_t res = ((size + MEM_STEP - 1) / MEM_STEP) * MEM_STEP;
	return res;
}

template <typename T>
MemData<T>::MemData(size_t size) {
	if (size == 0) {
		_data = nullptr;
	}
	else {
		_data = new T[calculate_capacity(size)];
	}
	_size = 0;
	_capacity = calculate_capacity(size);
}
template <typename T>
MemData<T>::MemData(std::initializer_list<T> list) {
	_size = list.size();
	_capacity = calculate_capacity(_size);
	if (_capacity > 0) {
		_data = new T[_capacity];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = list.begin()[i];
		}
	}
	else {
		_data = nullptr;
	}
}
template <typename T>
MemData<T>::MemData(const T* arr, size_t size) {
	_size = size;
	_capacity = calculate_capacity(size);
	if (_capasity > 0) {
		_data = new T[_capacity(size)];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = arr[i];
		}
	}
}
template <typename T>
MemData<T>::MemData(const MemData& other) {
	_size = other._size;
	_capacity = other._capacity;
	if (_capacity > 0) {
		_data = new T[_capacity(size)];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = other._data[i];
		}
	}
}
template <typename T>
MemData<T>::MemData(MemData&& other) noexcept {
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}
template <typename T>
MemData<T>::~MemData() {
	delete[] _data;
}

template <typename T>
bool MemData<T>::is_empty() const noexcept {
	return _size == 0;
}
template <typename T>
bool MemData<T>::is_full() const noexcept {
	return _capacity > 0 && _size == _capacity;
}

template <typename T>
size_t MemData<T>::size() const noexcept {
	return _size;
}
template <typename T>
size_t MemData<T>::capacity() const noexcept {
	return _capacity;
}
template <typename T>
const T* const MemData<T>::data() const noexcept {
	return _data;
}

template <typename T>
void MemData<T>::set_memory(size_t new_capacity) noexcept {
	T* new_data = nullptr;
	if (new_capacity > 0) {
		new_data = new T[new_capacity];
	}
	delete[] _data;
	_data = new_data;
	_size = 0;
	_capacity = new_capacity;
}
template <typename T>
void MemData<T>::reset_memory(size_t size, size_t start_index) noexcept {
	size_t new_capacity = calculate_capacity(size);

	size_t elements_to_copy = 0;
	if (_data != nullptr && _capacity > 0 && _size > start_index) {
		elements_to_copy = std::min(_size - start_index, size);
	}

	double* new_data = nullptr;
	if (new_capacity > 0) {
		new_data = new T[new_capacity];
	}

	if (new_data != nullptr && _data != nullptr && elements_to_copy > 0) {
		for (size_t i = 0; i < elements_to_copy; ++i) {
			new_data[i] = _data[(start_index + i) % _capacity];
		}
	}

	delete[] _data;
	_data = new_data;
	_size = elements_to_copy;
	_capacity = new_capacity;
}
template <typename T>
void MemData<T>::clear_memory() noexcept {
	delete[] _data;
	_data = nullptr;
	_size = 0;
	_capacity = 0;
}

template <typename T>
MemData<T>& MemData<T>::operator=(const MemData& other) noexcept {
	if (this != &other) {
		T* new_data = nullptr;
		if (other._capacity > 0) {
			new_data = new T[other._capacity];
			for (size_t i = 0; i < other._size; ++i) new_data[i] = other._data[i];
		}
		delete[] _data;
		_data = new_data;
		_size = other._size;
		_capacity = other._capacity;
	}
	return *this;
}
template <typename T>
MemData<T>& MemData<T>::operator=(MemData&& other) noexcept {
	if (this != &other) {
		delete[] _data;
		_data = other._data;
		_size = other._size;
		_capacity = other._capacity;
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}
	return *this;
}

template <typename T>
void MemData<T>::set_size_for_test(size_t new_size) {
	_size = new_size;
}