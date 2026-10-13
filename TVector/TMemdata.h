#pragma once
#include <initializer_list>

#define MEM_STEP 15

size_t calculate_capacity(size_t size);

template <typename T> class Vector;

template <typename T> class MemData {
    T* _data;             // хранилище данных
    size_t _size;              // размер заполненной части хранилища
    size_t _capacity;          // вместимость хранилища
public:
    MemData(size_t size = 0);                // конструктор по размеру + по умолчанию
    MemData(std::initializer_list<T>);  // конструктор по списку инициализации
    MemData(const T*, size_t);                // конструктор инициализации
    MemData(const MemData&);                 // конструктор копирования
    MemData(MemData&&) noexcept;                      // конструктор с move-семантикой
    ~MemData();                              // деструктор

    bool is_empty() const noexcept;   // проверка на пустоту
    bool is_full() const noexcept;    // проверка на переполнение

    size_t size() const noexcept;                 // геттер размера
    size_t capacity() const noexcept;             // геттер вместимости
    const T* const data() const noexcept;    // геттер хранилища

    void set_memory(size_t) noexcept;                                         // установка памяти без сохранения данных
    void reset_memory(size_t size, size_t start_index = 0) noexcept;          // перевыделение памяти с сохранением данных
    void clear_memory() noexcept;                                             // очистка памяти

    MemData& operator=(const MemData&) noexcept;         // оператор присваивания
    MemData& operator=(MemData&&) noexcept;              // оператор присваивания с move-семантикой

    void set_size_for_test(size_t new_size);

    template <typename U> friend class Vector;
};
