// zadanie9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;
const int n = 5;
double resA = 0, resB = 0;
double Sum(DOUBLE matrix[n][2])
{
    double expectedSum = 0;
    for (int i = 0; i < n; i++)
    {
        expectedSum += matrix[i][0] * matrix[i][1];
    }
    return expectedSum;
}
double SumX(DOUBLE matrix[n][2])
{
    double expectedSumX = 0;
    for (int i = 0; i < n; i++)
    {
        expectedSumX += matrix[i][0];
    }
    return expectedSumX;
}
double SumY(DOUBLE matrix[n][2])
{
    double expectedSumY = 0;
    for (int i = 0; i < n; i++)
    {
        expectedSumY += matrix[i][1];
    }
    return expectedSumY;
}
double Sum2X(DOUBLE matrix[n][2])
{
    double expectedSum2X = 0;
    for (int i = 0; i < n; i++)
    {
        expectedSum2X += pow(matrix[i][0], 2);
    }
    return expectedSum2X;
}
double A(DOUBLE matrix[n][2])
{
    double a = (n * Sum(matrix) - SumX(matrix) * SumY(matrix))
        / (n * Sum2X(matrix) - SumX(matrix) * SumX(matrix));
    return a;
}
double B(DOUBLE matrix[5][2])
{
    double b = (SumY(matrix) - A(matrix) * SumX(matrix)) / n;
    return b;
}
double Y(DOUBLE a, DOUBLE b)
{
    double y = (a * 6) - b;
    return y;
}

DWORD WINAPI A(LPVOID data) {
    double(*matrix)[2] = (double(*)[2])data;
    double a = A(matrix);
    cout << "A = "<< a << endl;
    resA = a;
    return 0;
}

DWORD WINAPI B(LPVOID data) {
    double(*matrix)[2] = (double(*)[2])data;
    double b = B(matrix);
    cout << "B = " << b << endl;
    resB = b;
    return 0;
}
DWORD WINAPI Y(LPVOID data) {

    double(*matrix)[2] = (double(*)[2])data;

    HANDLE hThread1;
    HANDLE hThread2;
    hThread1 = CreateThread(NULL, 0, A, matrix, 0, NULL);
    hThread2 = CreateThread(NULL, 0, B, matrix, 0, NULL);

    if (hThread1 == NULL && hThread2 == NULL)
        return GetLastError();

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    double y = Y(resA, resB);
    cout << "Y = "<< y << endl;
    return 0;
}





int main()
{
    double matrix[n][2] = {{1, 1.1}, {2, 3.8}, {3, 6.5}, {4, 10.2}, {5, 13.1}};

    HANDLE hThread;
    hThread = CreateThread(NULL, 0, Y, matrix, 0, NULL);
    
    if (hThread == NULL)
        return GetLastError();

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    return 0;


    //for (int i = 0; i < n; i++)
    //{
    //    
    //    expectedSum += matrix[i][0] * matrix[i][1];
    //    expectedSumX += matrix[i][0];
    //    expectedSumY += matrix[i][1];
    //    expectedSum2X += pow(matrix[i][0], 2);
    //}

    //double a = (n * expectedSum - expectedSumX * expectedSumY) 
    //         / (n * expectedSum2X - expectedSumX * expectedSumX);

    //double b = (expectedSumY - a * expectedSumX) / n;
    //
    //double y = (a * 6) - b;
    //cout << a << endl;
    //cout << b << endl;
    //cout << y << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
