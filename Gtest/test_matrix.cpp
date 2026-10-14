#include "pch.h"
#include "TMatrix.h"

TEST(Matrix, InitList) {
    TMatrix<int> m = {
        {1, 2, 3},
        {4, 5, 6}
    };
    EXPECT_EQ(m.getN(), 2);
    EXPECT_EQ(m.getM(), 3);
}

TEST(Matrix, ReadElement) {
    TMatrix<int> m = {
        {1, 2, 3},
        {4, 5, 6}
    };
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][2], 6);
}

TEST(Matrix, WriteElement) {
    TMatrix<int> m = {
        {1, 2, 3},
        {4, 5, 6}
    };
    m[1][1] = 99;
    EXPECT_EQ(m[1][1], 99);
}

TEST(Matrix, ZeroInitialization) {
    TMatrix<int> m(2, 3);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][2], 0);
}

TEST(Matrix, Addition) {
    TMatrix<int> a = {
        {1, 2},
        {3, 4}
    };
    TMatrix<int> b = {
        {5, 6},
        {7, 8}
    };
    TMatrix<int> c = a + b;
    EXPECT_EQ(c[0][0], 6);
    EXPECT_EQ(c[0][1], 8);
    EXPECT_EQ(c[1][0], 10);
    EXPECT_EQ(c[1][1], 12);
}

TEST(Matrix, AddAssign) {
    TMatrix<int> a = {
        {1, 2},
        {3, 4}
    };
    TMatrix<int> b = {
        {5, 6},
        {7, 8}
    };
    a += b;
    EXPECT_EQ(a[0][0], 6);
    EXPECT_EQ(a[1][1], 12);
}

TEST(Matrix, Subtraction) {
    TMatrix<int> a = {
        {5, 6},
        {7, 8}
    };
    TMatrix<int> b = {
        {1, 2},
        {3, 4}
    };
    TMatrix<int> c = a - b;
    EXPECT_EQ(c[0][0], 4);
    EXPECT_EQ(c[0][1], 4);
    EXPECT_EQ(c[1][0], 4);
    EXPECT_EQ(c[1][1], 4);
}

TEST(Matrix, SubAssign) {
    TMatrix<int> a = {
        {5, 6},
        {7, 8}
    };
    TMatrix<int> b = {
        {1, 2},
        {3, 4}
    };
    a -= b;
    EXPECT_EQ(a[0][0], 4);
    EXPECT_EQ(a[1][1], 4);
}

TEST(Matrix, Multiplication) {
    TMatrix<int> a = {
        {1, 2, 3},
        {4, 5, 6}
    };
    TMatrix<int> b = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    TMatrix<int> c = a * b;
    EXPECT_EQ(c.getN(), 2);
    EXPECT_EQ(c.getM(), 2);
    EXPECT_EQ(c[0][0], 58);
    EXPECT_EQ(c[0][1], 64);
    EXPECT_EQ(c[1][0], 139);
    EXPECT_EQ(c[1][1], 154);
}