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


#include "stdafx.h"
#include <windows.h>

using namespace std;


#include "operations.h"
#include <iostream>

vector inputVector(int value){
	vector result = new int[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = value;
	}
	return result;
}

matrix inputMatrix(int value){
	matrix result = new vector[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = new int[N];
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result[i][j] = value;
		}
	}
	return result;
}

void output(vector v) {
	if (N <= 40) {
		for (int i = 0; i < N; i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}
}

vector copyVector(vector v){
	vector result = new int[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = v[i];
	}
	return result;
}

matrix copyMatrix(matrix m){
	matrix result = new vector[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = new int[N];
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result[i][j] = m[i][j];
		}
	}
	return result;
}

matrix initMatrix(){
	matrix result = new vector[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			result[i][j] = 0;
		}
	}
	return result;
}
vector initVector(){
	vector result = new int[N];
	for (int i = 0; i < N; i++)
	{
		result[i] = 0;
	}
	return result;
}