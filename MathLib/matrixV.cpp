#include <vector>
#include <iostream>
#include "matrixV.h"

template <class T>
void matrixV<T>::init(int r, int c){
    row = r;
    column = c;
    mArr.assign(r, *(new std::vector<T>(c)));
}

template <class T>
matrixV<T>::matrixV(int r, int c){
    init(r, c);
}

template <class T>
matrixV<T>::matrixV(int r, int c, T item){
    init(r, c);
    fillMatrix(item);
}

template <class T>
matrixV<T>::matrixV(int r, int c, std::vector<std::vector<T> > arr){
    row = r;
    column = c;
    mArr = arr;
}

template <class T>
matrixV<T>::matrixV(int r, int c, T arr[]){
    init(r, c);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            mArr[i][j] = arr[i*c + j];
}

template <class T>
matrixV<T>::matrixV(int r, int c, std::vector<T> arr){
    init(r, c);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            mArr[i][j] = arr[i*c + j];
}

template <class T>
void matrixV<T>::fillMatrix(T item){
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            mArr[i][j] = item;
}

template <class T>
void matrixV<T>::fillDiagonal(T item){
    if (row != column)
        throw MismatchedSize();
    for (int i = 0; i < row; ++i)
        mArr[i][i] = item;
}

template <class T>
T matrixV<T>::getElement(int r, int c){
    return mArr[r-1][c-1];
}

template <class T>
int matrixV<T>::getRow(){
    return row;
}

template <class T>
int matrixV<T>::getColumn(){
    return column;
}

template <class T>
matrixV<T> matrixV<T>::getMatrix(){
    matrixV<T> temp(row, column, mArr);
    return temp;
}

template <class T>
void matrixV<T>::toString(){
    std::cout<<"This is a ("<<row<<"x"<<column<<") matrix"<<std::endl;
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < column; ++j)
            std::cout<<mArr[i][j]<<", ";
        std::cout<<std::endl;
    }
}

template <class T>
void matrixV<T>::setElement(int r, int c, T item){
    mArr[r-1][c-1] = item;
}

template <class T>
void matrixV<T>::addScalar(T var){
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            mArr[i][j] += var;
}

template <class T>
matrixV<T> matrixV<T>::operator+(matrixV<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        throw MismatchedSize();
    matrixV<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i+1, j+1, mArr[i][j] + m.getElement(i+1, j+1));
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::operator-(matrixV<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        throw MismatchedSize();
    matrixV<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i+1, j+1, mArr[i][j] - m.getElement(i+1, j+1));
    return temp;
}

template <class T>
bool matrixV<T>::operator==(matrixV<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        return false;
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            if (mArr[i][j] != m.getElement(i+1, j+1))
                return false;
    return true;
}

template <class T>
bool matrixV<T>::operator!=(matrixV<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        return true;
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            if (mArr[i][j] != m.getElement(i+1, j+1))
                return true;
    return false;
}

template <class T>
matrixV<T> matrixV<T>::operator*(T var){
    matrixV<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i+1, j+1, mArr[i][j] * var);
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::operator*(matrixV<T>& m){
    if (column != m.getRow())
        throw MismatchedSize();
    matrixV<T> temp(row, m.getColumn());
    for(int i = 0; i < temp.getRow(); ++i)
        for(int j = 0; j < temp.getColumn(); ++j){
            T sum = *(new T());
            for (int k = 0; k < column; ++k)
                sum += mArr[i][k]*m.getElement(k+1, j+1);
            temp.setElement(i+1, j+1, sum);
        }
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::transpose(){
    matrixV<T> temp(column, row);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.setElement(j+1, i+1, mArr[i][j]);
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::mModified(int r, int c){
    matrixV<T> temp(row-1, column-1);
    int i, j, a, b;
    for(i = 0, a = 1; i < row; ++i){
        if (i == r-1)
            continue;
        for (j = 0, b = 1; j < column; ++j){
            if (j == c-1)
                continue;
            temp.setElement(a, b, mArr[i][j]);
            ++b;
        }
        ++a;
    }
    return temp;
}

template <class T>
T matrixV<T>::det(){
    if (row != column)
        throw MismatchedSize();
    if (row == 1)
        return mArr[0][0];

    T ans = *(new T());     //Ensures ans is at the default value of T
    bool plus = true;
    for (int i = 1; i <= row; ++i){
        T temp = minor(1, i);
        temp *= mArr[0][i-1];
        ans += (plus)?temp:-temp;
        plus = !plus;
    }
    return ans;
}

template <class T>
T matrixV<T>::minor(int r, int c){
    return mModified(r, c).det();
}

template <class T>
matrixV<T> matrixV<T>::mMinor(){
    if (row != column)
        throw MismatchedSize();
    matrixV<T> temp(row, column);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.setElement(i+1, j+1, minor(i+1, j+1));
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::cofactor(){
    matrixV<T> temp = mMinor();
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j){
            bool sub = (i+j)&1;
            temp.mArr[i][j] *= (sub)?-1:1;
        }
    return temp;
}

template <class T>
matrixV<T> matrixV<T>::adjoint(){
    return cofactor().transpose();
}

template <class T>
matrixV<T> matrixV<T>::inverse(){
    if (row != column)
        throw MismatchedSize();
    matrixV<T> temp = adjoint();
    T determinant = det();
    if (determinant == *(new T()))
        throw InverseDoesNotExist();
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.mArr[i][j] /= determinant;
    return temp;
}

template <class T>
matrixV<int> matrixV<T>::identity(int r){
    matrixV<int> temp(r, r, 0);
    temp.fillDiagonal(1);
    return temp;
}

// Incorrect Implementation!!!
template <class T>
matrixV<T> matrixV<T>::psudoInverse(){
    matrixV<T> t = transpose();
    matrixV<T> m = getMatrix();
    matrixV<T> x = (m*t).inverse();
    if (row < column)
        return t * x;
    return x * t;
}

template <class T>
matrixV<T> matrixV<T>::inv(){
    if (row != column)
        return psudoInverse();
    return inverse();
}
