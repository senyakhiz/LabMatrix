#include "pch.h"
#include "TMathVector.h"

TEST(MathVector, ReadElement) {
    TMathVector<int> v = { 1, 2, 3 };
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(MathVector, WriteElement) {
    TMathVector<int> v = { 1, 2, 3 };
    v[1] = 99;
    EXPECT_EQ(v[1], 99);
}

TEST(MathVector, DotProduct) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 4, 5, 6 };
    EXPECT_DOUBLE_EQ(a * b, 32.0);
}

TEST(MathVector, MultiplyByScalar) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> c = a * 2;
    EXPECT_EQ(c[0], 2);
    EXPECT_EQ(c[1], 4);
    EXPECT_EQ(c[2], 6);
}


TEST(MathVector, Addition) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 4, 5, 6 };
    TMathVector<int> s = a + b;
    EXPECT_EQ(s[0], 5);
    EXPECT_EQ(s[1], 7);
    EXPECT_EQ(s[2], 9);
}

TEST(MathVector, Subtraction) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 4, 5, 6 };
    TMathVector<int> d = a - b;
    EXPECT_EQ(d[0], -3);
    EXPECT_EQ(d[1], -3);
    EXPECT_EQ(d[2], -3);
}

TEST(MathVector, Equality) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 1, 2, 3 };
    EXPECT_TRUE(a == b);
}

TEST(MathVector, Inequality) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 4, 5, 6 };
    EXPECT_TRUE(a != b);
}

TEST(MathVector, MultiplyAssign) {
    TMathVector<int> a = { 1, 2, 3 };
    a *= 3;
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 6);
    EXPECT_EQ(a[2], 9);
}

TEST(MathVector, AddAssign) {
    TMathVector<int> a = { 1, 2, 3 };
    TMathVector<int> b = { 4, 5, 6 };
    a += b;
    EXPECT_EQ(a[0], 5);
    EXPECT_EQ(a[1], 7);
    EXPECT_EQ(a[2], 9);
}