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
#include "omp.h"
#include <windows.h>
#include <iostream>
#include "operations.h"
#include <ctime>
#include <clocale>


using namespace std;

#pragma comment(linker, "/stack:160000000")

const int P = 4;

int main()
{
	vector A = new int[N], B, E, V;
	matrix MO, MK, MR, MM;
	MM = initMatrix();
	V = initVector();
	int alfa;
	

	const int H = N / P;
	omp_lock_t lock_Copy;
	
	setlocale(LC_ALL, "Russian");
	omp_init_lock(&lock_Copy);
	omp_set_num_threads(P);
#pragma omp parallel
	{
		int tid = omp_get_thread_num();
	
		cout << "Задача " << tid << " стартувала" << endl;
		/*Якщо tid = 3, Ввести α, B, E, MO, MK, MR, */
		if (tid==3){
			alfa = 1;
			B = inputVector(1);
			E = inputVector(1);
			MO = inputMatrix(1);
			MK = inputMatrix(1);
			MR = inputMatrix(1);
		}
		/*Бар’єр для усіх задач. Синхронізація по вводу*/
#pragma omp barrier
		matrix MRid;
		vector Bid;
		int alfaId;

		/*Копіювати MOi= MO, MRi=MR, αi = α, */
		omp_set_lock(&lock_Copy);
		MRid = copyMatrix(MR);
		Bid = copyVector(B);
		alfaId = alfa;
		omp_unset_lock(&lock_Copy);

		/*Обчислення 1: VH = MO∙BH*/
		for (int i = tid*H; i < (tid + 1)*H; i++)
		{
			V[i] = 0;
			for (int j = 0; j < N; j++)
			{
				V[i] += Bid[j] * MO[j][i];
			}
		}
		/*Обчислення 2: MMH = MKH∙MR*/
		int sum;
		for (int i = tid * H; i < (tid + 1) * H; i++) {
			for (int j = 0; j < N; j++) {
				sum = 0;
				for (int z = 0; z < N; z++) {
					sum += MRid[i][j] * MK[j][z];
				}
				MM[i][j] = sum;
			}
		}
		/*Бар’єр для усіх задач. Синхронізація обчислення 2*/
#pragma omp barrier
		vector Vid;
		/*Копіювати Vi=V*/
#pragma omp critical
		{
			Vid = copyVector(V);
		}

		/*Обчислення 3 AH = MMH∙V + EH∙αi*/
		int buf;
		for (int i = tid*H; i < (tid + 1)*H; i++)
		{
			A[i] = 0;
			for (int j = 0; j < N; j++)
			{
				A[i] += Vid[j] * MM[j][i];
			}
			A[i] = A[i] + E[i]*alfaId;
		}
		/*Бар’єр для усіх задач. Синхронізація обчислення 3*/
#pragma omp barrier
		/*Якщо tid = 3, Вивести A*/
		if (tid==3){
			output(A);
		}
		cout << "Задача " << tid << " завершилась" << endl;
	}

	return 0;
}
