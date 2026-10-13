#include "pch.h"

#define VECTOR_TESTS
#ifdef VECTOR_TESTS
#include "TVector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    Vector<double> vec;
    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector<double> vec(10);
    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(15, vec.capacity());
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(15, vec.capacity());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_create_with_init_constructor) {
    double arr[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    Vector<double> vec(arr, 5);
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(15, vec.capacity());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector<double> vec1({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    Vector<double> vec2(vec1);
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    for (size_t i = 0; i < vec1.size(); ++i) {
        EXPECT_DOUBLE_EQ(vec1[i], vec2[i]);
    }
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector<double> vec1({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    Vector<double> vec2(std::move(vec1));
    EXPECT_EQ(0, vec1.size());
    EXPECT_EQ(0, vec1.capacity());
    EXPECT_EQ(5, vec2.size());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(i + 1, vec2[i]);
    }
}

TEST(ClassVector, can_is_empty) {
    Vector<double> vec1;
    EXPECT_TRUE(vec1.is_empty());
    Vector<double> vec2({ 1.0 });
    EXPECT_FALSE(vec2.is_empty());
    Vector<double> vec3({ 1.0, 2.0, 3.0 });
    EXPECT_FALSE(vec3.is_empty());
}

TEST(ClassVector, can_is_full) {
    Vector<double> vec(15);
    for (size_t i = 0; i < 15; ++i) {
        vec.push_back(i + 1);
        if (i < 14) EXPECT_FALSE(vec.is_full());
    }
    EXPECT_TRUE(vec.is_full());

    vec.pop_back();
    EXPECT_FALSE(vec.is_full());
}

TEST(ClassVector, can_get_front) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    EXPECT_DOUBLE_EQ(1.0, vec.front());
}

TEST(ClassVector, can_get_back) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    EXPECT_DOUBLE_EQ(5.0, vec.back());
}

TEST(ClassVector, can_set_front) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.front() = 100.0;
    EXPECT_DOUBLE_EQ(100.0, vec.front());
    EXPECT_DOUBLE_EQ(100.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
}

TEST(ClassVector, can_set_back) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.back() = 500.0;
    EXPECT_DOUBLE_EQ(500.0, vec.back());
    EXPECT_DOUBLE_EQ(500.0, vec[4]);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.front(), std::out_of_range);
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.back(), std::out_of_range);
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.front() = 1.0, std::out_of_range);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.back() = 1.0, std::out_of_range);
}

TEST(ClassVector, can_output_with_operator_cout) {
    Vector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector<int> vec;
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_push_front) {
    Vector<double> vec({ 2.0, 3.0, 4.0, 5.0 });
    vec.push_front(1.0);
    EXPECT_EQ(5, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(5.0, vec[4]);
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector<double> vec;
    vec.push_front(1.0);
    EXPECT_EQ(1, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
}

TEST(ClassVector, can_push_front_with_reallocation) {
    Vector<double> vec(15);
    for (size_t i = 0; i < 15; ++i) {
        vec.push_front(i + 1);
    }
    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());

    vec.push_front(16);
    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec[0]);
    EXPECT_DOUBLE_EQ(15.0, vec[1]);
    EXPECT_DOUBLE_EQ(1.0, vec[15]);
}

TEST(ClassVector, can_push_back) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0 });
    vec.push_back(5.0);
    EXPECT_EQ(5, vec.size());
    EXPECT_DOUBLE_EQ(5.0, vec[4]);
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector<double> vec;
    vec.push_back(1.0);
    EXPECT_EQ(1, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
}

TEST(ClassVector, can_push_back_with_reallocation) {
    Vector<double> vec(15);
    for (size_t i = 0; i < 15; ++i) {
        vec.push_back(i + 1);
    }
    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());

    vec.push_back(16);
    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec[15]);
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
}

TEST(ClassVector, can_insert) {
    Vector<double> vec({ 1.0, 2.0, 4.0, 5.0 });
    vec.insert(3.0, 2);
    EXPECT_EQ(5, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(3.0, vec[2]);
    EXPECT_DOUBLE_EQ(4.0, vec[3]);
    EXPECT_DOUBLE_EQ(5.0, vec[4]);
}

TEST(ClassVector, can_insert_with_reallocation) {
    Vector<double> vec(15);
    for (size_t i = 0; i < 15; ++i) {
        vec.push_back(i + 1);
    }
    vec.insert(100, 7);
    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(100.0, vec[7]);
    EXPECT_DOUBLE_EQ(8.0, vec[8]);
}

TEST(ClassVector, can_insert_to_front) {
    Vector<double> vec({ 2.0, 3.0, 4.0 });
    vec.insert(1.0, 0);
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(3.0, vec[2]);
    EXPECT_DOUBLE_EQ(4.0, vec[3]);
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector<double> vec({ 1.0, 2.0, 3.0 });
    EXPECT_THROW(vec.insert(4.0, 5), std::out_of_range);
    EXPECT_THROW(vec.insert(4.0, 10), std::out_of_range);
}

TEST(ClassVector, can_pop_front) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.pop_front();
    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(2.0, vec[0]);
    EXPECT_DOUBLE_EQ(3.0, vec[1]);
    EXPECT_DOUBLE_EQ(4.0, vec[2]);
    EXPECT_DOUBLE_EQ(5.0, vec[3]);
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    Vector<double> vec;
    for (size_t i = 0; i < 45; ++i) {
        vec.push_back(i + 1);
    }
    EXPECT_EQ(45, vec.capacity());

    for (size_t i = 0; i < 20; ++i) {
        vec.pop_front();
    }
    EXPECT_EQ(25, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(21.0, vec[0]);
    EXPECT_DOUBLE_EQ(45.0, vec[24]);
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.pop_front(), std::out_of_range);
}

TEST(ClassVector, can_pop_back) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.pop_back();
    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(3.0, vec[2]);
    EXPECT_DOUBLE_EQ(4.0, vec[3]);
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    Vector<double> vec;
    for (size_t i = 0; i < 45; ++i) {
        vec.push_back(i + 1);
    }
    EXPECT_EQ(45, vec.capacity());

    for (size_t i = 0; i < 20; ++i) {
        vec.pop_back();
    }
    EXPECT_EQ(25, vec.size());
    EXPECT_EQ(30, vec.capacity());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(25.0, vec[24]);
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 2, vec[i]);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(i + 2, vec[i]);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_front(i + 1);
    }

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());

    vec.pop_back();
    vec.push_front(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.front());

    for (size_t i = 1; i < 15; i++) {
        EXPECT_DOUBLE_EQ(15 - i + 1, vec[i]);
    }

    vec.pop_front();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.front());
}

TEST(ClassVector, can_erase) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.erase(2);
    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(4.0, vec[2]);
    EXPECT_DOUBLE_EQ(5.0, vec[3]);
}

TEST(ClassVector, can_erase_front) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.erase(0);
    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(2.0, vec[0]);
    EXPECT_DOUBLE_EQ(3.0, vec[1]);
    EXPECT_DOUBLE_EQ(4.0, vec[2]);
    EXPECT_DOUBLE_EQ(5.0, vec[3]);
}

TEST(ClassVector, can_erase_back) {
    Vector<double> vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    vec.erase(4);
    EXPECT_EQ(4, vec.size());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);
    EXPECT_DOUBLE_EQ(2.0, vec[1]);
    EXPECT_DOUBLE_EQ(3.0, vec[2]);
    EXPECT_DOUBLE_EQ(4.0, vec[3]);
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector<double> vec;
    for (size_t i = 0; i < 45; ++i) {
        vec.push_back(i + 1);
    }

    for (size_t i = 0; i < 10; ++i) {
        vec.erase(10);
    }

    EXPECT_EQ(35, vec.size());
    EXPECT_EQ(45, vec.capacity());
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.erase(0), std::out_of_range);
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector<double> vec({ 1.0, 2.0, 3.0 });
    EXPECT_THROW(vec.erase(5), std::out_of_range);
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector<int> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - static_cast<int>(i));
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + static_cast<int>(i));
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + static_cast<int>(i));
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(i + 1, vec[i]);
    }
}

TEST(ClassVector, can_assigment) {
    Vector<double> vec1({ 1.0, 2.0, 3.0, 4.0, 5.0 });
    Vector<double> vec2;
    vec2 = vec1;
    EXPECT_EQ(5, vec2.size());
    EXPECT_EQ(15, vec2.capacity());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(i + 1, vec2[i]);
    }
}

TEST(ClassVector, can_move_assigment) {
    Vector<int> vec_1;
    Vector<int> vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + static_cast<int>(i));
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - static_cast<int>(i));
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(0, vec_1.capacity());

    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(15, vec_2.capacity());

    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(i + 1, vec_2[i]);
    }
}

TEST(ClassVector, c) {
    Vector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec1.pop_front();
    vec1.pop_front();
    vec1.pop_front();
    vec1.pop_front();

    for (size_t i = 0; i < 9; ++i) {
        vec1.push_back(static_cast<int>(i) * 10);
    }

    std::stringstream out;
    out << vec1;
    EXPECT_EQ("{ 5, 6, 7, 8, 9, 10, 0, 10, 20, 30, 40, 50, 60, 70, 80 }", out.str());
    out.str("");

    vec1.push_back(90);
    out << vec1;
    EXPECT_EQ("{ 5, 6, 7, 8, 9, 10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 }", out.str());
    out.str("");
}

#endif