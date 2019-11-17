#include "Matrix.h"
#include "Vector.h"
#include <cmath>
#include <algorithm>

namespace mat_vec{
    Matrix :: Matrix(size_t size, double value){
        row = size; col = size;
        mat = new double*[size];
        for (int i = 0; i < size; i++){
            mat[i] =  new double [size];
        }
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                mat[i][j] = value;
            }
        }
    }

   Matrix Matrix :: eye(size_t size) {
        Matrix sing(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    sing.mat[i][j] = 1;
                }
            }
        }
       return sing;
    }


    Matrix :: Matrix(size_t rows, size_t cols, double value){
        row = rows; col = cols;
        mat = new double*[row];
        for (int i = 0; i < row; i++){
            mat[i] = new double [col];
        }
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = value;
            }
        }
    }

    Matrix :: Matrix(const Matrix &src){
        mat = new double*[src.row];
        for (int i = 0; i < src.row; i++){
            mat[i] = new double [src.col];
        }
        for (int i = 0; i < src.row; i++){
            for (int j = 0; j < src.col; j++){
                mat[i][j] = src.mat[i][j];
            }
        }
        row = src.row;
        col = src.col;
    }

    Matrix &Matrix :: operator=(const Matrix &rhs){
        this->~Matrix();
        mat = new double*[rhs.row];
        for (int i = 0; i < rhs.row; i++){
            mat[i] = new double [rhs.col];
        }
        for (int i = 0; i < rhs.row; i++){
            for (int j = 0; j < rhs.col; j++){
                mat[i][j] = rhs.mat[i][j];
            }
        }
        row = rhs.row;
        col = rhs.col;
        return *this;
    }

   Matrix :: ~Matrix(){

        for (int i = 0; i < row; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }


    void Matrix :: reshape(size_t rows, size_t cols){
        double copy[rows * cols];
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                copy[(i*col)+j] = this->mat[i][j];
            }
        }
        Matrix res_reshape(rows, cols);
        int k = 0;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                 res_reshape.mat[i][j] = copy[k++];
            }
        }
        *this = res_reshape;
    }

    std::pair<size_t, size_t> Matrix :: shape() const{
        return std::make_pair(row, col);
    }
      // Возвращает элемент на позиции [row, col]
  double Matrix :: get(size_t row, size_t col) const{
        return mat[row][col];
    }

    Matrix Matrix :: operator+(const Matrix &rhs) const{
        Matrix sum(rhs.row, rhs.col);
        for (int i = 0; i < rhs.row; i++){
            for (int j = 0; j < rhs.col; j++){
                sum.mat[i][j] = this->mat[i][j] + rhs.mat[i][j];
            }
        }
        return sum;
    }
    Matrix &Matrix :: operator+=(const Matrix &rhs){
        for (int i = 0; i < rhs.row; i++){
            for (int j = 0; j < rhs.col; j++){
                mat[i][j] = mat[i][j] + rhs.mat[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix :: operator-(const Matrix &rhs) const{
        Matrix dif(rhs.row, rhs.col);
        for (int i = 0; i < rhs.row; i++){
            for (int j = 0; j < rhs.col; j++){
                dif.mat[i][j] = this->mat[i][j] - rhs.mat[i][j];
            }
        }
        return dif;
    }

    Matrix &Matrix :: operator-=(const Matrix &rhs){
        for (int i = 0; i < rhs.row; i++){
            for (int j = 0; j < rhs.col; j++){
                mat[i][j] = mat[i][j] - rhs.mat[i][j];
            }
        }
        return *this;
    }
    Matrix Matrix :: operator*(const Matrix &rhs) const{
        Matrix new_multi(row, rhs.col, 0);
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < rhs.col; j++) {
                for (int k = 0; k < rhs.col; k++)
                    new_multi.mat[i][j] += (this->mat[i][k] * rhs.mat[k][j]);
            }
        }
        return new_multi;
    }

    Matrix &Matrix :: operator*=(const Matrix &rhs){
        Matrix new_multi(row, rhs.col, 0);
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < rhs.col; j++) {
                for (int k = 0; k < rhs.col; k++)
                    new_multi.mat[i][j] += (this->mat[i][k] * rhs.mat[k][j]);
            }
        }
        *this = new_multi;
        return *this;
    }

    Matrix Matrix :: operator*(double k) const{
        Matrix mul(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mul.mat[i][j] = this->mat[i][j] * k;
            }
        }
        return mul;
    }
    Matrix &Matrix :: operator*=(double k) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mat[i][j] = mat[i][j] * k;
            }
        }
        return *this;
    }

    Matrix Matrix :: operator/(double k) const{
        Matrix div(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                div.mat[i][j] = this->mat[i][j] / k;
            }
        }
        return div;
    }
    Matrix &Matrix :: operator/=(double k){
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = mat[i][j] / k;
            }
        }
        return *this;
    }
    // Возвращает новую матрицу, полученную транспонированием текущей (this)
    Matrix Matrix :: transposed() const{
        Matrix trans(col, row, 0);
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                trans.mat[i][j] = this->mat[j][i];
            }
        }
        return trans;
    }

    void Matrix :: transpose(){
       Matrix tmp(col, row, 0);
       for (int i = 0; i < col; i++) {
           for (int j = 0; j < row; j++) {
               tmp.mat[i][j] = this->mat[j][i];
            }
        }
       Matrix mat(col, row, 0);
       *this = tmp;
    }
//    double Matrix :: det() const{
//
//    }
    Vector Matrix :: operator*(const Vector &vec) const{
        Vector res(vec.size(), 0);
        for (int i = 0; i < vec.size(); i++){
            double tmp = 0;
            for (int j = 0; j < col; j++){
                tmp += this->mat[i][j] * vec[j];
            }
            res[i] = tmp;
        }
        return res;
    }

    bool Matrix :: operator==(const Matrix &rhs) const{
        for(int i = 0; i < row; i++)
           for(int j = 0; j < col; j++){
               if (this->mat[i][j] != rhs.mat[i][j]){
                   return false;
               }
           }
        return true;
    }

    bool Matrix :: operator!=(const Matrix &rhs) const{
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++){
                if (this->mat[i][j] == rhs.mat[i][j]){
                    return false;
                }
            }
        return true;
    }

    double Matrix :: det() const{
        Matrix a(*this);
        const double EPS = 1E-9;
        double det = 1;
        for (int i = 0; i < row; ++i) {
            int k = i;
            for (int j = i + 1; j < row; ++j)
                if (fabs (a.mat[j][i]) > fabs (a.mat[k][i]))
                    k = j;
            if (fabs (a.mat[k][i]) < EPS) {
                det = 0;
            }
            for (int e = 0; e < a.col; e++){
                double tmp = a.mat[i][e];
                a.mat[i][e] = a.mat[k][e];
                a.mat[k][e] = tmp;
            }
            if (i != k)
                det = -det;
            det *= a.mat[i][i];
            for (int j = i + 1; j < row; ++j)
                a.mat[i][j] /= a.mat[i][i];
            for (int j = 0; j < row; ++j)
                if (j != i && fabs(a.mat[j][i]) > EPS)
                    for (int k = i + 1; k < row; ++k)
                        a.mat[j][k] -= a.mat[i][k] * a.mat[j][i];
        }
        return det;
    }
}
