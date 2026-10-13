#include "TVector.h"
#include <stdexcept>
#include <algorithm>
#include <random>

template <typename T>
Vector<T>::Vector(size_t size) {
	_mem = size;
	_front = 0;
	if (_mem.is_empty()) _back = 0;
	_back = _mem._size - 1;
}
template <typename T>
Vector<T>::Vector(std::initializer_list<T> list) {
	_mem = list;
	_front = 0;
	if (_mem._size == 0) _back = 0;
	_back = _mem._size - 1;
}
template <typename T>
Vector<T>::Vector(T* arr, size_t size) {
	_mem = MemData(arr, size);
	_front = 0;
	if (_mem._size == 0) _back = 0;
	_back = _mem._size - 1;
}
template <typename T>
Vector<T>::Vector(const Vector& other) {
	_mem = other._mem;
	_front = other._front;
	_back = other._back;
}
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
	_mem = std::move(other._mem);
	_front = other._front;
	_back = other._back;
	other._front = other._back = 0;
}

template <typename T>
bool Vector<T>::is_empty() const noexcept {
	return _mem.is_empty();
}
template <typename T>
bool Vector<T>::is_full() const noexcept {
	return _mem.is_full();
}

template <typename T>
size_t Vector<T>::size() const noexcept {
	return _mem.size();
}
template <typename T>
size_t Vector<T>::capacity() const noexcept {
	return _mem.capacity();
}
template <typename T>
T Vector<T>::front() const {
	if (is_empty()) {
		throw std::out_of_range("Vector is empthy");
	}
	return _mem._data[_front];
}
template <typename T>
T Vector<T>::back() const {
	if (is_empty()) {
		throw std::out_of_range("Vector is empthy");
	}
	return _mem._data[_back];
}

template <typename T>
T& Vector<T>::front() {
	if (is_empty()) {
		throw std::out_of_range("Vector is empthy");
	}
	return _mem._data[_front];
}
template <typename T>
T& Vector<T>::back() {
	if (is_empty()) {
		throw std::out_of_range("Vector is empthy");
	}
	return _mem._data[_back];
}

template <typename T>
size_t Vector<T>::get_real_index(size_t front, size_t pos, size_t capacity) {
	return (front + pos) % capacity;
}

template <typename T>
void Vector<T>::resize_and_rearrange() {
	size_t new_capacity = _mem._capacity + MEM_STEP;
	T* new_data = new T[new_capacity];

	for (size_t i = 0; i < _mem._size; ++i) {
		new_data[i] = _mem._data[(_front + i) % _mem._capacity];
	}

	delete[] _mem._data;

	_mem._data = new_data;
	_mem._capacity = new_capacity;

	_front = 0;
	_back = _mem._size - 1;
}

template <typename T>
void Vector<T>::push_front(const T& value) noexcept {
	if (_mem.is_empty()) {
		if (_mem._capacity == 0) _mem.reset_memory(MEM_STEP);
		_front = 0;
		_back = 0;
		_mem._data[0] = value;
		_mem._size = 1;
	}
	else {
		if (_mem.is_full()) {
			resize_and_rearrange();
		}
		if (_front == 0) {
			_front = _mem._capacity - 1;
		}
		else {
			_front = _front - 1;
		}
		_mem._data[_front] = value;
		_mem._size++;
	}
}
template <typename T>
void Vector<T>::push_back(const T& value) noexcept {
	if (_mem.is_empty()) {
		if (_mem._capacity == 0) _mem.reset_memory(MEM_STEP);
		_front = _back = 0;
		_mem._data[0] = value;
		_mem._size = 1;
	}
	else {
		if (_mem.is_full()) {
			resize_and_rearrange();
		}
		_back = (_back + 1) % _mem._capacity;
		_mem._data[_back] = value;
		_mem._size++;
	}
}
template <typename T>
void Vector<T>::insert(const T& value, size_t pos) {
	if (pos > _mem._size) throw std::out_of_range("Invalid position");

	if (_mem.is_full()) {
		resize_and_rearrange();
	}

	if (pos == 0) {
		push_front(value);
	}
	else if (pos == _mem._size) {
		push_back(value);
	}
	else {
		size_t shift_left = pos;
		size_t shift_right = _mem._size - pos;

		if (shift_left <= shift_right) {
			size_t new_front = (_front == 0) ? _mem._capacity - 1 : _front - 1;
			for (size_t i = 0; i < shift_left; i++) {
				size_t src = (_front + i) % _mem._capacity;
				size_t dst = (new_front + i) % _mem._capacity;
				_mem._data[dst] = _mem._data[src];
			}
			_front = new_front;
			_mem._data[(_front + pos) % _mem._capacity] = value;
		}
		else {
			for (size_t i = shift_right; i > 0; i--) {
				size_t src = (_front + pos + i - 1) % _mem._capacity;
				size_t dst = (_front + pos + i) % _mem._capacity;
				_mem._data[dst] = _mem._data[src];
			}
			_mem._data[(_front + pos) % _mem._capacity] = value;
			_back = (_back + 1) % _mem._capacity;
		}
		_mem._size++;
	}
}

template <typename T>
bool Vector<T>::should_shrink() const noexcept {
	return _mem._capacity > MEM_STEP && _mem._size <= _mem._capacity - MEM_STEP;
}

template <typename T>
void Vector<T>::shrink_to_fit() noexcept {
	if (_mem._size == 0) {
		_mem.clear_memory();
		_front = _back = 0;
		return;
	}

	size_t new_capacity = calculate_capacity(_mem._size);
	if (new_capacity == _mem._capacity) return;

	T* new_data = new T[new_capacity];

	for (size_t i = 0; i < _mem._size; ++i) {
		new_data[i] = _mem._data[(_front + i) % _mem._capacity];
	}

	delete[] _mem._data;
	_mem._data = new_data;
	_mem._capacity = new_capacity;
	_front = 0;
	if (_mem._size > 0) {
		_back = _mem._size - 1;
	}
	else {
		_back = 0;
	}
}

template <typename T>
void Vector<T>::pop_front() {
	if (is_empty()) throw std::out_of_range("Vector is empty");

	_front = (_front + 1) % _mem._capacity;
	_mem._size--;

	if (should_shrink()) {
		shrink_to_fit();
	}
}
template <typename T>
void Vector<T>::pop_back() {
	if (is_empty()) throw std::out_of_range("Vector is empty");

	if (_back == 0) {
		_back = _mem._capacity - 1;
	}
	else {
		_back--;
	}
	_mem._size--;

	if (should_shrink()) {
		shrink_to_fit();
	}
}
template <typename T>
void Vector<T>::erase(size_t pos) {
	if (is_empty()) throw std::out_of_range("Vector is empty");
	if (pos >= _mem._size) throw std::out_of_range("Invalid position");

	if (pos == 0) {
		pop_front();
	}
	else if (pos == _mem._size - 1) {
		pop_back();
	}
	else {
		size_t shift_left = pos;
		size_t shift_right = _mem._size - pos - 1;

		if (shift_left <= shift_right) {
			for (size_t i = shift_left; i > 0; i--) {
				size_t src = (_front + i - 1) % _mem._capacity;
				size_t dst = (_front + i) % _mem._capacity;
				_mem._data[dst] = _mem._data[src];
			}
			_front = (_front + 1) % _mem._capacity;
		}
		else {
			for (size_t i = 0; i < shift_right; i++) {
				size_t src = (_front + pos + i + 1) % _mem._capacity;
				size_t dst = (_front + pos + i) % _mem._capacity;
				_mem._data[dst] = _mem._data[src];
			}
			if (_back == 0) {
				_back = _mem._capacity - 1;
			}
			else {
				_back = _back - 1;
			}
		}
		_mem._size--;

		if (should_shrink()) {
			shrink_to_fit();
		}
	}
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) noexcept {
	if (this != &other) {
		_mem = other._mem;
		_front = other._front;
		_back = other._back;
	}
	return *this;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
	if (this != &other) {
		_mem = std::move(other._mem);
		_front = other._front;
		_back = other._back;
		other._front = other._back = 0;
	}
	return *this;
}

template <typename T>
T Vector<T>::operator[](size_t index) const noexcept {
	return _mem._data[(_front + index) % _mem._capacity];
}
template <typename T>
T& Vector<T>::operator[](size_t index) noexcept {
	return _mem._data[(_front + index) % _mem._capacity];
}

template <typename T>
void Vector<T>::push_front(const std::initializer_list<T>& values) {
	for (auto it = values.end(); it != values.begin(); ) {
		--it;
		push_front(*it);
	}
}

template <typename T>
void Vector<T>::push_back(const std::initializer_list<T>& values) {
	for (const auto& val : values) {
		push_back(val);
	}
}

template <typename T>
void Vector<T>::pop_front(size_t count) {
	for (size_t i = 0; i < count; i++) {
		pop_front();
	}
}

template <typename T>
void Vector<T>::pop_back(size_t count) {
	for (size_t i = 0; i < count; i++) {
		pop_back();
	}
}

template <typename T>
static void quick_sort(Vector<T>& vec, int left, int right) {
	if (left >= right) return;

	T pivot = vec[(left + right) / 2];
	int i = left, j = right;

	while (i <= j) {
		while (vec[i] < pivot) i++;
		while (vec[j] > pivot) j--;
		if (i <= j) {
			std::swap(vec[i], vec[j]);
			i++;
			j--;
		}
	}

	if (left < j) {
		quick_sort(vec, left, j);
	}
	if (i < right) {
		quick_sort(vec, i, right);
	}
}
template <typename T>
void sort(Vector<T>& vec) {
	if (vec.size() <= 1) return;

	for (size_t i = 1; i < vec.size(); i++) {
		T key = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] > key) {
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
	}
}
template <typename T>
void shuffle(Vector<T>& vec) {
	if (vec.size() <= 1) return;

	static std::random_device rd;
	static std::mt19937 gen(rd());

	for (size_t i = vec.size() - 1; i > 0; --i) {
		std::uniform_int_distribution<size_t> dist(0, i);
		size_t j = dist(gen);
		std::swap(vec[i], vec[j]);
	}

}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
	os << "{ ";
	for (size_t i = 0; i < vec.size(); i++) {
		os << vec[i];
		if (i < vec.size() - 1) os << ", ";
	}
	os << " }";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vec) {
	size_t size;
	is >> size;
	vec = Vector();
	for (size_t i = 0; i < size; i++) {
		double val;
		is >> val;
		vec.push_back(val);
	}
	return is;
}
