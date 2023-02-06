#include "matrix.h"
#include <iostream>

template <class T>
void matrix<T>::init(int r, int c){
    row = r;
    column = c;
    mArr = new T*[row];
    for(int i = 0; i < row; ++i)
        mArr[i] = new T[column];
}

template <class T>
matrix<T>::matrix(int r, int c){
    init(r, c);
}

template <class T>
matrix<T>::matrix(int r, int c, T item){
    init(r, c);
    fillMatrix(item);
}

template <class T>
matrix<T>::matrix(int r, int c, T **arr){
    row = r;
    column = c;
    mArr = arr;
}

template <class T>
matrix<T>::matrix(int r, int c, T arr[]){
    init(r, c);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            mArr[i][j] = arr[i*c + j];
}

/*template <class T>
matrix<T>::matrix(int r, int c, std::vector<T> arr){
    init(r, c);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            mArr[i][j] = arr[i*c + j];
}*/

template <class T>
matrix<T>::~matrix(){
    for(int i = 0; i < row; ++i)
        delete [] mArr[i];
    delete [] mArr;
}

template <class T>
void matrix<T>::fillMatrix(T item){
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            mArr[i][j] = item;
}

template <class T>
void matrix<T>::fillDiagonal(T item){
    if (row != column)
        throw MismatchedSize();
    for (int i = 0; i < row; ++i)
        mArr[i][i] = item;
}

template <class T>
T matrix<T>::getElement(int r, int c){
    return mArr[r][c];
}

template <class T>
int matrix<T>::getRow(){
    return row;
}

template <class T>
int matrix<T>::getColumn(){
    return column;
}

template <class T>
void matrix<T>::toString(){
    std::cout<<"This is an "<<row<<"x"<<column<<" matrix"<<std::endl;
    for(int i = 0; i < row; ++i){
        std::cout<<"|";
        for(int j = 0; j < column; ++j)
            std::cout<<mArr[i][j]<<" ";
        std::cout<<"\b|"<<std::endl;
    }
}

template <class T>
void matrix<T>::setElement(int r, int c, T item){
    mArr[r][c] = item;
}

template <class T>
void matrix<T>::addScalar(T var){
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            mArr[i][j] += var;
}

template <class T>
matrix<T> matrix<T>::operator+(matrix<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        throw MismatchedSize();
    matrix<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i, j, mArr[i][j] + m.getElement(i, j));
    return temp;
}

template <class T>
matrix<T> matrix<T>::operator-(matrix<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        throw MismatchedSize();
    matrix<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i, j, mArr[i][j] - m.getElement(i, j));
    return temp;
}

template <class T>
bool matrix<T>::operator==(matrix<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        return false;
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            if (mArr[i][j] != m.getElement(i, j))
                return false;
    return true;
}

template <class T>
bool matrix<T>::operator!=(matrix<T>& m){
    if (m.getColumn() != column || m.getRow() != row)
        return true;
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            if (mArr[i][j] != m.getElement(i, j))
                return true;
    return false;
}

template <class T>
matrix<T> matrix<T>::operator*(T var){
    matrix<T> temp(row, column);
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < column; ++j)
            temp.setElement(i, j, mArr[i][j] * var);
    return temp;
}

template <class T>
matrix<T> matrix<T>::operator*(matrix<T>& m){
    if (column != m.getRow())
        throw MismatchedSize();
    matrix<T> temp(row, m.getColumn());
    for(int i = 0; i < temp.getRow(); ++i)
        for(int j = 0; j < temp.getColumn(); ++j){
            T sum = *(new T());
            for (int k = 0; k < column; ++k)
                sum += mArr[i][k]*m.getElement(k, j);
            temp.setElement(i, j, sum);
        }
    return temp;
}

template <class T>
matrix<T> matrix<T>::transpose(){
    matrix<T> temp(column, row);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.setElement(j, i, mArr[i][j]);
    return temp;
}

template <class T>
matrix<T> matrix<T>::mModified(int r, int c){
    matrix<T> temp(row-1, column-1);
    int i, j, a, b;
    for(i = a = 0; i < row; ++i){
        if (i == r-1)
            continue;
        for (j = b = 0; j < column; ++j){
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
T matrix<T>::det(){
    if (row != column)
        throw MismatchedSize();
    if (row == 1)
        return mArr[0][0];
    if (row == 2)
        return mArr[0][0]*mArr[1][1] - mArr[0][1]*mArr[1][0];
    T ans = *(new T());
    bool plus = true;
    for (int j = 1; j <= row; ++j){\
        T temp = minor(1, j);
        temp *= mArr[0][j-1];
        ans += (plus)?temp:-temp;
        plus = !plus;
    }
    return ans;
}

template <class T>
T matrix<T>::minor(int r, int c){
    return mModified(r, c).det();
}

template <class T>
matrix<T> matrix<T>::mMinor(){
    if (row != column)
        throw MismatchedSize();
    matrix<T> temp(row, column);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.setElement(i, j, minor(i+1, j+1));
    return temp;
}

template <class T>
matrix<T> matrix<T>::cofactor(){
    matrix<T> temp = mMinor();
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j){
            bool sub = (i+j)&1;
            temp.mArr[i][j] *= (sub)?-1:1;
        }
    return temp;
}

template <class T>
matrix<T> matrix<T>::adjoint(){
    return cofactor().transpose();
}

template <class T>
matrix<T> matrix<T>::inverse(){
    if (row != column)
        throw MismatchedSize();
    matrix<T> temp = adjoint();
    T determinant = det();
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            temp.mArr[i][j] /= determinant;
    return temp;
}

template <class T>
matrix<int> matrix<T>::identity(int r){
    matrix<int> temp(r, r, 0);
    temp.fillDiagonal(1);
    return temp;
}
