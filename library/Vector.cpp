#include "Vector.h"
#include <math.h>
#include "Matrix.h"

namespace mat_vec {

    Vector :: Vector(size_t size, double value) {
        arr_size = size;
        array = new double[size];
        for (int i = 0; i < size; i++) {
            array[i] = value;
        }
    }
    Vector :: Vector(const Vector &src){
        arr_size = src.arr_size;
        array = new double[arr_size];
        for (int i = 0; i < arr_size; i++) {
            array[i] = src.array[i];
        }
    }
    Vector :: ~Vector(){
        delete [] array;
    }
     Vector &Vector :: operator = (const Vector &rhs){
         this->~Vector();
        arr_size = rhs.arr_size;
        array = new double[arr_size];
         for (int i = 0; i < arr_size; i++) {
             array[i] = rhs.array[i];
         }
         return *this;
    }
    size_t Vector :: size() const{
        return arr_size;
    }
    double Vector :: operator[](size_t n) const{
        return array[n];
    }
    double &Vector :: operator[](size_t n){
        return array[n];
    }
    double Vector :: norm() const{
        double L2 = 0;
        for (int i = 0; i < arr_size; i++){
            L2 += array[i] * array[i];
        }
        L2 = sqrt(L2);
        return L2;
    }

    Vector Vector :: normalized() const{
        Vector res(*this);
        double norma = norm();
        for (int i = 0; i < arr_size; i++){
            res.array[i] = array[i] / norma;
        }
        return res;
    }

   void Vector :: normalize(){
       double norma = norm();
       for (int i = 0; i < arr_size; i++){
           array[i] = array[i] / norma;
       }
    }

    Vector Vector :: operator+(const Vector &rhs) const{
        Vector sum(arr_size);
        for (int i = 0; i < arr_size; i++){
            sum.array[i] = this->array[i] + rhs.array[i];
        }
        return sum;
    }

    Vector &Vector :: operator+=(const Vector &rhs){
        for (int i = 0; i < arr_size ; i++){
           array[i] = array[i] + rhs.array[i];
        }
        return *this;
    }

    Vector Vector :: operator-(const Vector &rhs) const{
        Vector dif(arr_size);
        for (int i = 0; i < arr_size; i++){
            dif.array[i] = this->array[i] - rhs.array[i];
        }
        return dif;
    }

    Vector &Vector :: operator-=(const Vector &rhs){
        for (int i = 0; i < arr_size ; i++){
            array[i] = array[i] - rhs.array[i];
        }
        return *this;
    }

    Vector Vector :: operator^(const Vector &rhs) const{
        Vector mul(arr_size);
        for (int i = 0; i < arr_size; i++){
            mul.array[i] = this->array[i] * rhs.array[i];
        }
        return mul;
    }

    Vector &Vector :: operator^=(const Vector &rhs){
        for (int i = 0; i < arr_size; i++){
            array[i] = array[i] * rhs.array[i];
        }
        return *this;
    }

    Vector operator*(double k, const Vector &v){
        Vector mul(v.size());
        for (int i = 0; i < v.size(); i++){
            mul[i] = v[i] * k;
        }
        return mul;
    }

    double Vector :: operator*(const Vector &rhs) const{
        double scalar = 0;
        for (int i = 0; i < arr_size; i++){
            scalar += array[i] * rhs.array[i];
        }
        return scalar;
    }

    Vector Vector :: operator*(double k) const{
        Vector mul(arr_size);
        for (int i = 0; i < arr_size; i++){
            mul[i] = k * this->array[i];
        }
        return mul;
    }

    Vector &Vector :: operator*=(double k){
        for (int i = 0; i < arr_size; i++){
            array[i] = k * this->array[i];
        }
        return *this;
    }

    Vector Vector :: operator/(double k) const{
        Vector div(arr_size);
        for (int i = 0; i < arr_size; i++){
            div.array[i] = this->array[i] / k;
        }
        return div;
    }
    Vector &Vector :: operator/=(double k){
        for (int i = 0; i < arr_size; i++){
            array[i] = this->array[i] / k;
        }
        return *this;
    }

    bool Vector :: operator == (const Vector &rhs) const{
        for (int i = 0; i < arr_size; i++) {
            if (array[i] != rhs.array[i])
                return false;
        }
        return true;
    }
   bool Vector :: operator != (const Vector &rhs) const{
       for (int i = 0; i < arr_size; i++) {
           if (array[i] == rhs.array[i])
               return false;
       }
       return true;
   }
    Vector Vector :: operator*(const Matrix &mat) const{
        Vector res(arr_size, 0);
        for (int i = 0; i < arr_size; i++){
            double tmp = 0;
            for (int j = 0; j < mat.col; j++){
                tmp += mat.get(i, j) * array[j];
            }
            res[i] = tmp;
        }
        return res;
    }

    Vector &Vector :: operator*=(const Matrix &mat){
        Vector res(arr_size, 0);
        for (int i = 0; i < arr_size; i++){
            double tmp = 0;
            for (int j = 0; j < mat.col; j++){
                tmp += mat.get(i, j) * array[j];
            }
            res[i] = tmp;
        }
        *this = res;
        return *this;
    }
}


