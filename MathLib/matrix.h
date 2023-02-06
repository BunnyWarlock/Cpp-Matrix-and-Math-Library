#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
//#include <vector>

class MismatchedSize{};

template <class T>
class matrix{
    private:
        T **mArr;
        int row;
        int column;

        void init(int r, int c);
    public:
        //Constructors
        matrix(int r, int c);
        matrix(int r, int c, T item);
        matrix(int r, int c, T **arr);
        matrix(int r, int c, T arr[]);
        //matrix(int r, int c, std::vector<T> arr);

        //Destructor
        ~matrix();

        //Basic Stuff
        void fillMatrix(T item);
        void fillDiagonal(T item);
        T getElement(int r, int c);
        int getRow();
        int getColumn();
        void toString();
        void setElement(int r, int c, T item);
        void addScalar(T var);

        //Operator Overloading
        matrix<T> operator+(matrix<T>& m);
        matrix<T> operator-(matrix<T>& m);
        bool operator==(matrix<T>& m);
        bool operator!=(matrix<T>& m);
        matrix<T> operator*(T var);
        matrix<T> operator*(matrix<T>& m);

        //Advanced Stuff
        matrix<T> transpose();
        matrix<T> mModified(int ri, int ci);
        T det();
        T minor(int ri, int ci);
        matrix<T> mMinor();
        matrix<T> cofactor();
        matrix<T> adjoint();
        matrix<T> inverse();

        //Static
        static matrix<int> identity(int r);
};

#endif // MATRIX_H_INCLUDED
