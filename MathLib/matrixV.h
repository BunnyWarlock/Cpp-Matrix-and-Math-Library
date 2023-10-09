#ifndef matrixV_H_INCLUDED
#define matrixV_H_INCLUDED

class MismatchedSize{};
class InverseDoesNotExist{};

template <class T>
class matrixV{
    private:
        std::vector<std::vector<T> > mArr;
        int row;
        int column;

        void init(int r, int c);

    public:
        //Constructors
        matrixV(int r, int c);
        matrixV(int r, int c, T item);
        matrixV(int r, int c, std::vector<std::vector<T> > arr);
        matrixV(int r, int c, T arr[]);
        matrixV(int r, int c, std::vector<T> arr);

        //Basic Stuff
        void fillMatrix(T item);
        void fillDiagonal(T item);
        T getElement(int r, int c);
        int getRow();
        int getColumn();
        matrixV<T> getMatrix();
        void toString();
        void setElement(int r, int c, T item);
        void addScalar(T var);

        //Operator Overloading
        matrixV<T> operator+(matrixV<T>& m);
        matrixV<T> operator-(matrixV<T>& m);
        bool operator==(matrixV<T>& m);
        bool operator!=(matrixV<T>& m);
        matrixV<T> operator*(T var);
        matrixV<T> operator*(matrixV<T>& m);

        //Advanced Stuff
        matrixV<T> transpose();
        matrixV<T> mModified(int ri, int ci);
        T det();
        T minor(int ri, int ci);
        matrixV<T> mMinor();
        matrixV<T> cofactor();
        matrixV<T> adjoint();
        matrixV<T> inverse();
        matrixV<T> psudoInverse();
        matrixV<T> inv();

        //Static
        static matrixV<int> identity(int r);
};

#endif // matrixV_H_INCLUDED
