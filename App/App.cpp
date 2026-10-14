#include <iostream>
#include <limits>
#include "TMatrix.h"
#include "TTriangleMatrix.h"

int main() {
    std::cout << "=== Matrix Calculator ===" << std::endl;

    try {
        std::cout << "\n--- TMatrix Demo ---" << std::endl;
        TMatrix<int> A = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        TMatrix<int> B = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };

        std::cout << "Matrix A:\n" << A << std::endl;
        std::cout << "Matrix B:\n" << B << std::endl;

        TMatrix<int> C = A + B;
        std::cout << "A + B:\n" << C << std::endl;

        TMatrix<int> D = A * B;
        std::cout << "A * B:\n" << D << std::endl;

        std::cout << "\n--- TTriangleMatrix Demo ---" << std::endl;

        TTriangleMatrix<int> T({
            { 3, 4, 3, 0, 0 },
            { 0, 4, 3, 5, 1 },
            { 0, 0, 3, 5, 1 },
            { 0, 0, 0, 5, 1 },
            { 0, 0, 0, 0, 1 }
            });

        std::cout << "Initial triangular matrix T:\n" << T << std::endl;

        T[2][3] = -6;
        std::cout << "After T[2][3] = -6:\n" << T << std::endl;

        std::cout << "T[4][1] = " << T[4][1] << std::endl;

        std::cout << "\nAttempting T[4][1] = 5..." << std::endl;
        try {
            T[4][1] = 5;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
    }

    return 0;
}