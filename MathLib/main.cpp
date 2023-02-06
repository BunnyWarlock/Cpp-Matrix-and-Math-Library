#include <iostream>
#include "matrix.cpp"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    matrix<int> testM1(8, 7, 2);
    matrix<int> testM2(8, 7, 4);

    (testM1+testM2).toString();

    testM2.toString();

    (testM1-testM2).toString();

    (testM1*3).toString();

    int **arr1{new int*[2]{new int[3]{1, 2, 3}, new int[3]{4, 5, 6}}};
    int arr2[3*2] = {10, 11, 20, 21, 30, 31};
    matrix<int> testM3(2, 3, arr1);
    matrix<int> testM4(3, 2, arr2);

    testM3.toString();

    testM4.toString();

    (testM3*testM4).toString();

    testM3.transpose().toString();

    int **arr3{new int*[3]{new int[3]{1, -2, 3}, new int[3]{2, 0, 3}, new int[3]{1, 5, 4}}};
    int **arr4{new int*[4]{new int[4]{0, -2, -5, 8}, new int[4]{0, -6, 3, 1}, new int[4]{0, 11, 5, -3}, new int[4]{-1, -2, -1, 3}}};
    matrix<int> testM5(4, 4, arr4);

    testM5.toString();

    testM5.mModified(1, 2).toString();

    cout<<"Determinant is "<<testM5.det()<<endl;
    matrix<int> testM6(3, 3, arr3);

    testM6.toString();

    testM6.adjoint().toString();

    int **arr5{new int*[2]{new int[2]{4, 3}, new int[2]{3, 2}}};
    matrix<int> testM7(2, 2, arr5);

    testM7.inverse().toString();

    double **arr6{new double*[3]{new double[3]{1, -2, 3}, new double[3]{2, 0, 3}, new double[3]{1, 5, 4}}};
    matrix<double> testM8(3, 3, arr6);

    testM8.toString();

    testM8.inverse().toString();

    int arr7[3*3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix<int> testM9(3, 3, arr7);

    testM9.toString();

    matrix<char>::identity(10).toString();

    matrix<int> t(4,4,4);
    matrix<int> t2(4,4,4);
    t.setElement(1, 2, 0);
    t.toString();
    t2.toString();
    if (t == t2) cout<<"Yes 1"<<endl;
    if (t != t2) cout<<"Yes 2"<<endl;
    (t-t2).toString();
    (t*t2).toString();
    (t+t2).toString();
    (t*3).toString();

    return 0;
}
