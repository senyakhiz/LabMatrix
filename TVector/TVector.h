#pragma once
#include <iostream>
#include "TMemdata.h"

template <typename T>
class Vector {
    MemData<T> _mem;         // хранилище данных + размер  + вместимость
    size_t _front;        // индекс первого элемента
    size_t _back;         // индекс последнего элемента
public:
    Vector(size_t size = 0);                 // конструктор по размеру + по умолчанию
    Vector(std::initializer_list<T>);   // конструктор по списку инициализации
    Vector(T*, size_t);                 // конструктор инициализации
    Vector(const Vector&);                   // конструктор копирования
    Vector(Vector&&) noexcept;                        // конструктор с move-семантикой
    ~Vector() = default;                     // деструктор

    bool is_empty() const noexcept;          // проверка на пустоту
    bool is_full() const noexcept;           // проверка на переполнение

    size_t size() const noexcept;            // геттер размера
    size_t capacity() const noexcept;        // геттер вместимости
    T front() const;                    // геттер первого элемента
    T back() const;                     // геттер последнего элемента

    T& front();                         // сеттер первого элемента
    T& back();                          // сеттер последнего элемента

    size_t get_real_index(size_t front, size_t pos, size_t capacity);
    void resize_and_rearrange();

    void push_front(const T&) noexcept;               // вставка элемента в начало
    void push_back(const T&) noexcept;                // вставка элемента в конец
    void insert(const T&, size_t);                    // вставка элемента по позиции

    bool should_shrink() const noexcept;
    void shrink_to_fit() noexcept;

    void pop_front();                               // удаление элемента из начала
    void pop_back();                                // удаление элемента из конца
    void erase(size_t);                             // удаление элемента по позиции

    Vector& operator=(const Vector&) noexcept;      // оператор присваивания
    Vector& operator=(Vector&&) noexcept;           // оператор присваивания с move-семантикой

    T operator[](size_t) const noexcept;       // оператор обращения по индексу константный
    T& operator[](size_t) noexcept;            // оператор обращения по индексу

    void push_front(const std::initializer_list<T>& values);
    void push_back(const std::initializer_list<T>& values);
    void pop_front(size_t count);
    void pop_back(size_t count);

    template <typename U> 
    friend void sort(Vector<U>& vec);
    template <typename U> 
    friend void shuffle(Vector<U>& vec);

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const Vector<U>&);     // вывод
    template <typename U>
    friend std::istream& operator>>(std::istream&, Vector<U>&);           // ввод
};
