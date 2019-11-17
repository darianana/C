#define CATCH_CONFIG_MAIN
#include <iostream>
#include <utility>
#include "Matrix.h"
#include "Vector.h"
#include "catch.hpp"

using namespace mat_vec;
using namespace std;
double e = 0.00000001;

TEST_CASE("Vector constructor", "[vector]"){
    Vector vec(4, 5);
    REQUIRE(vec.size() == 4);
    for(int i = 0; i <  vec.size(); i++){
        REQUIRE(vec[i] - 5 < e);
    }
}

TEST_CASE("Copy", "[vector]"){
    Vector vec(4, 5);
    Vector vec2(vec);
    REQUIRE(vec2.size() == vec.size());
    for(int i = 0; i <  vec.size(); i++){
        REQUIRE(vec2[i] - 5 < e);
    }
}

TEST_CASE("Assign", "[vector]"){
    Vector vec(4, 5);
    Vector  vec2(5, 6);
    vec2 = vec;
    REQUIRE(vec2.size() == vec.size());
    for(int i = 0; i <  vec.size(); i++){
        REQUIRE(vec2[i] - 5 < e);
    }
}

TEST_CASE("Size", "[vector]"){
    Vector vec(6, 3);
    REQUIRE(vec.size() == 6);
}

TEST_CASE("Access", "[vector]"){
    Vector vec(6, 3);
    vec[2] = 5;
    REQUIRE( vec[2] - 5 < e);
}

TEST_CASE("Norma vector", "[vector]"){
    Vector vec(4, 5);
    double ev = vec.norm();
    REQUIRE(ev - 10 < e);
}

TEST_CASE("Normalized", "[vector]"){
    Vector vec(4, 5);
    Vector vec2(4, 5);
    vec2 = vec.normalized();
    for (int i = 0; i < vec2.size(); i++){
        REQUIRE(vec2[i] - 0.5 < e);
    }
}

TEST_CASE("Normalize", "[vector]"){
    Vector vec(4, 5);
    vec.normalize();
    for (int i = 0; i < vec.size(); i++){
        REQUIRE(vec[i] - 0.5 < e);
    }
}

TEST_CASE("Plus +", "[vector]"){
    Vector vec(4, 5);
    Vector vec2(4, 5);
    Vector c(4, 0);
    c = vec + vec2;
    for (int i = 0; i < c.size(); i++){
        REQUIRE(c[i] - 10 < e);
    }
}

TEST_CASE("Plus +=", "[vector]"){
    Vector vec(4, 5);
    Vector vec2(4, 5);
    vec += vec2;
    for (int i = 0; i < vec.size(); i++){
        REQUIRE(vec[i] - 10 < e);
    }
}

TEST_CASE("Minus -", "[vector]"){
    Vector vec(4, 6);
    Vector vec2(4, 5);
    Vector c(4, 0);
    c = vec - vec2;
    for (int i = 0; i < c.size(); i++){
        REQUIRE(c[i] - 1 < e);
    }
}

TEST_CASE("Minus -=", "[Vector]"){
    Vector vec(4, 6);
    Vector vec2(4, 5);
    vec -= vec2;
    for (int i = 0; i < vec.size(); i++){
        REQUIRE(vec[i] - 1 < e);
    }
}

TEST_CASE("Multiplication *", "[Vector]"){
    Vector vec(4, 6);
    Vector vec2(4, 5);
    Vector c(4, 0);
    c = vec ^ vec2;
    for (int i = 0; i < c.size(); i++){
        REQUIRE(c[i] - 30 < e);
    }
}

TEST_CASE("Multiplication *=", "[Vector]"){
    Vector vec(4, 6);
    Vector vec2(4, 5);
    vec ^= vec2;
    for (int i = 0; i < vec.size(); i++){
        REQUIRE(vec[i] - 30 < e);
    }
}

TEST_CASE("Scalar", "[Vector]") {
    Vector a(4, 5);
    Vector b(4, 3);
    double scal = a * b;
    REQUIRE(scal - 60 < e);
}

TEST_CASE("Multiplying a Vector left", "[vector]"){
    Vector a(4, 5);
    Vector b(4, 0);
    double k = 5;
    b = k * a;
    for (int i = 0; i < b.size(); i++){
        REQUIRE(b[i] - 25 < e);
    }
}

TEST_CASE("Multiplying a Vector right *", "[vector]"){
    Vector a(4, 5);
    Vector b(4, 0);
    double k = 10;
    b = a * k;
    for (int i = 0; i < b.size(); i++){
        REQUIRE(b[i] - 50 < e);
    }
}

TEST_CASE("Multiplying a Vector left *=", "[vector]"){
    Vector a(4, 5);
    double k = 10;
    a *= k;
    for (int i = 0; i < a.size(); i++){
        REQUIRE(a[i] - 50 < e);
    }
}

TEST_CASE("Division /", "[vector]"){
    Vector a(4, 25);
    Vector c(4, 0);
    double b = 5;
    c = a / b;
    for (int i = 0; i < c.size(); i++){
        REQUIRE(c[i] - 5 < e);
    }
}

TEST_CASE("Division /=", "[vector]"){
    Vector a(4, 25);
    double b = 5;
    a /= b;
    for (int i = 0; i < a.size(); i++){
        REQUIRE(a[i] - 5 < e);
    }
}

TEST_CASE("Vec on Matrix *", "[vector]"){
    Matrix a(3, 3, 6);
    Vector b(3, 1);
    Vector c(3, 0);
    c = b * a;
    for (int i = 0; i < c.size(); i++){
        REQUIRE(c[i] - 18 < e);
    }
}

TEST_CASE("Vec on Matrix *=", "[vector]"){
    Matrix a(3, 3, 6);
    Vector b(3, 1);
    b *= a;
    for (int i = 0; i < b.size(); i++){
        REQUIRE(b[i] - 18 < e);
    }
}

TEST_CASE("Сompare == true", "[vector]"){
    Vector a(4, 4);
    Vector b(4, 4);
    bool flag = false;
    flag = (a == b);
    REQUIRE(flag == true);
}

TEST_CASE("Сompare == false", "[vector]"){
    Vector a(4, 4);
    Vector b(4, 1);
    bool flag = false;
    flag = (a == b);
    REQUIRE(flag == false);
}

TEST_CASE("Сompare != false", "[vector]"){
    Vector a(4, 4);
    Vector b(4, 4);
    bool flag = false;
    flag = (a != b);
    REQUIRE(flag == false);
}

TEST_CASE("Сompare != true", "[vector]"){
    Vector a(4, 4);
    Vector b(4, 1);
    bool flag = false;
    flag = (a != b);
    REQUIRE(flag == true);
}

TEST_CASE("Matrix constructor", "[matrix]"){
    Matrix mat(3, 3.0);
    pair<size_t, size_t> size = mat.shape();
    bool flag = ((size.first == 3) && (size.second == 3));
    REQUIRE(flag);
    for (int i = 0; i < size.first; i++){
        for (int j = 0; j < size.second; j++){
            REQUIRE(mat.get(i, j) - 3 < e);
        }
    }
}

TEST_CASE("Eye", "[matrix]"){
    Matrix one = Matrix :: eye(4);
    pair<size_t, size_t> size = one.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++) {
            if (i == j)
                REQUIRE(one.get(i, j) == 1);
        }
}

TEST_CASE("Matrix ROW x COL", "[matrix]") {
    Matrix mat(3, 4, 1);
    pair<size_t, size_t> size = mat.shape();
    bool flag = ((size.first == 3) && (size.second == 4));
    REQUIRE(flag);
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            REQUIRE(mat.get(i, j) - 1 < e);
        }
    }
}

TEST_CASE("COPY", "[matrix]"){
    Matrix mat1(4, 5, 6);
    Matrix mat2(mat1);
    pair<size_t, size_t> size_mat1 = mat1.shape();
    pair<size_t, size_t> size_mat2 = mat2.shape();
    bool flag = ((size_mat1.first == size_mat2.first) && (size_mat1.second == size_mat2.second));
    REQUIRE(flag);
    for (int i = 0; i < size_mat1.first; i++) {
        for (int j = 0; j < size_mat1.second; j++) {
            REQUIRE(mat1.get(i, j) == mat2.get(i, j));
        }
    }
}

TEST_CASE("Assign matrix", "[matrix]"){
    Matrix mat1(4, 5, 6);
    Matrix mat2(3, 1, 0);
    mat2 = mat1;
    pair<size_t, size_t> size_mat1 = mat1.shape();
    pair<size_t, size_t> size_mat2 = mat2.shape();
    bool flag = ((size_mat1.first == size_mat2.first) && (size_mat1.second == size_mat2.second));
    REQUIRE(flag);
    for (int i = 0; i < size_mat1.first; i++) {
        for (int j = 0; j < size_mat1.second; j++) {
            REQUIRE(mat1.get(i, j) == mat2.get(i, j));
        }
    }
}

TEST_CASE("Reshape", "[matrix]"){
    Matrix mat(4, 2, 1);
    mat.reshape(2, 4);
    pair<size_t, size_t> size = mat.shape();
    bool flag = ((size.first == 2) && (size.second == 4));
    REQUIRE(flag);
}

TEST_CASE("Shape", "[matrix]"){
    Matrix mat(10, 12, 10);
    pair<size_t, size_t> size = mat.shape();
    bool flag = ((size.first == 10) && (size.second == 12));
    REQUIRE(flag);
}

TEST_CASE("Get", "[matrix]"){
    Matrix mat(3, 125.0);
    double chiselka = mat.get(1, 1);
    REQUIRE(chiselka - 125.0 < e);
}

TEST_CASE("Sum +", "[matrix]"){
    Matrix a(3, 4, 5);
    Matrix b(3, 4, 6);
    Matrix c(3, 4, 0);
    c = a + b;
    pair<size_t, size_t> size = c.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(c.get(i, j) - 11 < e);
        }
}

TEST_CASE("Sum +=", "[matrix]"){
    Matrix a(3, 4, 5);
    Matrix b(3, 4, 6);
    a += b;
    pair<size_t, size_t> size = a.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(a.get(i, j) - 11 < e);
        }
}

TEST_CASE("Sub -", "[matrix]"){
    Matrix a(3, 4, 10);
    Matrix b(3, 4, 6);
    Matrix c(3, 4, 0);
    c = a - b;
    pair<size_t, size_t> size = c.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(c.get(i, j) - 4 < e);
        }
}

TEST_CASE("Sub -=", "[matrix]"){
    Matrix a(3, 4, 10);
    Matrix b(3, 4, 6);
    a -= b;
    pair<size_t, size_t> size = a.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(a.get(i, j) - 4 < e);
        }
}

TEST_CASE("Mult *", "[matrix]"){
    Matrix a(3, 2.0);
    Matrix b(3, 3.0);
    Matrix c(3, 3, 0);
    c = a * b;
    pair<size_t, size_t> size = c.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(c.get(i, j) - 18 < e);
        }
}

TEST_CASE("Mult *=", "[matrix]"){
    Matrix a(3, 2.0);
    Matrix b(3, 3.0);
    a *= b;
    pair<size_t, size_t> size = a.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(a.get(i, j) - 18 < e);
        }
}

TEST_CASE("Mult with number *", "[matrix]"){
    Matrix a(3, 4, 10);
    Matrix c(3, 4, 0);
    double b = 6;
    c = a * b;
    pair<size_t, size_t> size = c.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(c.get(i, j) - 60 < e);
        }
}

TEST_CASE("Mult with number *=", "[matrix]"){
    Matrix a(3, 4, 10);
    double b = 6;
    a *= b;
    pair<size_t, size_t> size = a.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(a.get(i, j) - 60 < e);
        }
}

TEST_CASE("Div /", "[matrix]"){
    Matrix a(3, 4, 60);
    Matrix c(3, 4, 0);
    double b = 6;
    c = a / b;
    pair<size_t, size_t> size = c.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(c.get(i, j) - 10 < e);
        }
}

TEST_CASE("Div /=", "[matrix]"){
    Matrix a(3, 4, 60);
    double b = 6;
    a /= b;
    pair<size_t, size_t> size = a.shape();
    for (int i = 0; i < size.first; i++)
        for (int j = 0; j < size.second; j++){
            REQUIRE(a.get(i, j) - 10 < e);
        }
}

TEST_CASE("Transposed", "[matrix]"){
    Matrix mat1(3, 2, 6);
    Matrix mat2(2, 3, 0);
    mat2 = mat1.transposed();
    pair<size_t, size_t> size1 = mat1.shape();
    pair<size_t, size_t> size2 = mat2.shape();
    bool flag = ((size1.first == size2.second)&&(size1.second == size2.first));
    REQUIRE(flag);
}

TEST_CASE("Transpose", "[matrix]"){
    Matrix mat1(3, 2, 6);
    pair<size_t, size_t> size1 = mat1.shape();
    mat1.transpose();
    pair<size_t, size_t> size2 = mat1.shape();
    bool flag = ((size1.first == size2.second)&&(size1.second == size2.first));
    REQUIRE(flag);
}

TEST_CASE("Multi with vector", "[matrix]") {
    Matrix a(3, 3, 6);
    Vector b(3, 1);
    b = a * b;
    for (int i = 0; i < b.size(); i++) {
        REQUIRE(b[i] - 18 < e);
    }
}

TEST_CASE("Сomparison on equality when true", "[matrix]"){
    Matrix a(4, 5, 10);
    Matrix b(4, 5, 10);
    bool flag = (a == b);
    REQUIRE(flag);
}

TEST_CASE("Сomparison on equality when false", "[matrix]"){
    Matrix a(4, 5, 10);
    Matrix b(4, 5, 4);
    bool flag = (a == b);
    REQUIRE(flag == false);
}

TEST_CASE("Сomparison on inequality when true ", "[matrix]"){
    Matrix a(4, 5, 10);
    Matrix b(4, 5, 4);
    bool flag = (a != b);
    REQUIRE(flag);
}

TEST_CASE("Сomparison on inequality when false", "[matrix]"){
    Matrix a(4, 5, 10);
    Matrix b(4, 5, 10);
    bool flag = (a != b);
    REQUIRE(flag == false);
}

TEST_CASE("Search det, when = 0", "[matrix]"){
    Matrix a(5, 3.0);
    double det_res = 0;
    det_res = a.det();
    REQUIRE(det_res - 0 < e);
}

TEST_CASE("Search det, when != 0", "[matrix]"){
    Matrix a = Matrix :: eye(3);
    Matrix b(3, 5.0);
    b += a;
    double det_res = b.det();
    REQUIRE(det_res - 16 < e);
 }
