/**
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                             *
*            Програмування паралельний комп'ютерних сисем     *
*             Лабораторна робота №4. Бібліотека OpenMP        *
*                                                             *
* Завдання: A = (B∙MO)∙(MK∙MR) + α∙E                          *
*                                                             *
* Автор Кузьменко Володимир                                   *
* Група ІО-21                                                 *
* Дата 07.04.15                                               *
*                                                             *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/


typedef int* vector;
typedef int** matrix;

const int N = 4;

vector inputVector(int);
matrix inputMatrix(int);
void output(vector);
void output(matrix);
vector copyVector(vector);
matrix copyMatrix(matrix);
matrix initMatrix();
vector initVector();