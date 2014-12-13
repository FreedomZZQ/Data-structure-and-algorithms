#ifndef SORT_H
#define SORT_H

#include "help.h"

template<typename E>
void bubsort(E A[], int n)
{
	for (int i = 0; i < n - 1; i++){
		for (int j = n - 1; j > i; j--){
			if (z_comp(A[j - 1], A[j])) z_swap(A, j, j-1);
		}
	}
}

template<typename E>
void selsort(E A[], int n)
{
	for (int i = 0; i < n - 1; i++){
		int lowindex = i;
		for (int j = n - 1; j >i; j--){
			if (z_comp(A[lowindex], A[j]))
				lowindex = j;
		}
		z_swap(A, i, lowindex);
	}
}

template<typename E>
void inssort2(E A[], int n, int incr)
{
	for (int i = incr; i < n; i += incr){
		for (int j = i; (j >= incr) && (z_comp(A[j = incr], A[j])); j -= incr)
			z_swap(A, j, j - incr);
	}
}

template<typename E>
void shellsort(E A[], int n)
{
	for (int i = n / 2; i >2; i /= 2){
		for (int j = 0; j < i; j++)
			inssort2<E>(&A[j], n - j, i);
	}
	inssort2<E>(A, n, 1);
}


//Quicksort
template<typename E>
inline int findpivot(E A[], int i, int j)
{
	return (i + j) / 2;
}

template<typename E>
inline int partition(E A[], int i, int j, E &pivot)
{
	do{
		while (z_comp<E>(pivot, A[++i]));
		while ((i < j) && z_comp<E>(A[--j], pivot));
		z_swap<E>(A, i, j);

	} while (i < j);
	return i;
}

template<typename E> 
void qsort(E A[], int i, int j)
{
	if (j <= i) return;
	int pivotindex = findpivot(A, i, j);
	z_swap<E>(A, j, pivotindex);

	int k = partition(A, i-1, j, A[j]);
	z_swap<E>(A, j, k);

	qsort<E>(A, i, k - 1);
	qsort<E>(A, k + 1, j);
}

#include<cmath>
//Look at more values when selecting a pivot
//选取第一个，中间和最后一个进行比较，返回中间值
//说明参见课本P250第二段
template<typename E>
inline E min(E a, E b){
	return a < b ? a : b;
}

template<typename E>
inline int findpivot_2(E A[], int i, int j){
	int mid = (i + j) / 2;
	int res[3] = { 0, 0, 0 };
	int temp = (A[i] + A[j] + A[mid]) / 3;

	res[0] = abs(A[i] - temp);
	res[1] = abs(A[mid] - temp);
	res[2] = abs(A[j] - temp);
	temp = min(res[0], min(res[1], res[2]));

	if (res[0] == temp) return i;
	else if (res[1] == temp) return mid;
	else if (res[2] == temp) return j;

}

template<typename E>
inline int partition_2(E A[], int i, int j, E &pivot)
{
	do{
		while (z_comp<E>(pivot, A[++i]));
		while ((i < j) && z_comp<E>(A[--j], pivot));
		z_swap<E>(A, i, j);

	} while (i < j);
	return i;
}

template<typename E>
void qsort_2(E A[], int i, int j)
{
	if (j <= i) return;
	int pivotindex = findpivot(A, i, j);
	z_swap<E>(A, j, pivotindex);

	int k = partition(A, i - 1, j, A[j]);
	z_swap<E>(A, j, k);

	qsort<E>(A, i, k - 1);
	qsort<E>(A, k + 1, j);
}


















#endif