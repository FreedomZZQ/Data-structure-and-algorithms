#ifndef SORT_H
#define SORT_H

#include "help.h"

template<typename E>
void inssort(E A[], int n)
{
	for (int i = 1; i < n;i++)
	for (int j = i; (j > 0) && (z_comp(A[j - 1], A[j])); j--)
		z_swap(A, j, j - 1);
}

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

//����qsort
#include<cmath>
#define THRESHOLD 5 //���ڴ�ֵ�������в��ٵݹ飬ʹ�ò����������
template<typename E>
void inssort_2(E A[], int m, int n)
{
	for (int i = m; i <= n; i++)
	for (int j = i; (j > 0) && (z_comp<E>(A[j - 1], A[j])); j--)
		z_swap<E>(A, j, j - 1);
}

//1.Look at more values when selecting a pivot
//ѡȡ��һ�����м�����һ�����бȽϣ������м�ֵ
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

//2.�Ӷγ���С�ڶ�ֵʱʹ�ò����������ݹ�
template<typename E>
void qsort_2(E A[], int i, int j)
{
	if (j <= i) return;
	int pivotindex = findpivot_2(A, i, j);
	z_swap<E>(A, j, pivotindex);

	int k = partition_2(A, i - 1, j, A[j]);
	z_swap<E>(A, j, k);

	if (j - i > THRESHOLD){
		qsort<E>(A, i, k - 1);
		qsort<E>(A, k + 1, j);
	}
	else{
		inssort_2<E>(A, i, k - 1);
		inssort_2<E>(A, k + 1, j);
	}
}

//3.ʹ��stack����ݹ�
#include<stack>
struct node{
	int i, j;
};
template<typename E>
void qsort_3(E A[], int i, int j)
{
	stack<node> s;
	node n;
	n.i = i, n.j = j;
	s.push(n);
	while (s.size() > 0){
		i = s.top().i, j = s.top().j;
		s.pop();
		
		int pivotindex = findpivot_2(A, i, j);
		z_swap<E>(A, j, pivotindex);

		int k = partition_2(A, i - 1, j, A[j]);
		z_swap<E>(A, j, k);

		if (i < k - 1) {
			n.i = i, n.j = k - 1;
			s.push(n);
		}
		if (k + 1 < j) {
			n.i = k + 1, n.j = j;
			s.push(n);
		}

	}
}

//2+3�����
template<typename E>
void qsort_4(E A[], int i, int j)
{
	stack<node> s;
	node n;
	int x = i, y = j;
	n.i = x, n.j = y;
	s.push(n);
	while (s.size() > 0){
		x = s.top().i, y = s.top().j;
		s.pop();

		int pivotindex = findpivot_2(A, x, y);
		z_swap<E>(A, y, pivotindex);

		int k = partition_2(A, x - 1, y, A[y]);
		z_swap<E>(A, y, k);

		if (y - x > THRESHOLD){
			if (x < k - 1) {
				n.i = x, n.j = k - 1;
				s.push(n);
			}
			if (k + 1 < y) {
				n.i = k + 1, n.j = y;
				s.push(n);
			}

		}
		else{
			inssort_2<E>(A, i, j);
			break;
		}
	}
}

#endif