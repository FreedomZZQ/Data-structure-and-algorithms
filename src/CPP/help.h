#ifndef HELP_H
#define HELP_H

//swap two elements in an array.
template<typename E>
void z_swap(E a[], int be, int en)
{
	E temp = a[be];
	a[be] = a[en];
	a[en] = temp;
	return;
}

//compare two elements.
//if a > b, return true.
template<typename E>
bool z_comp(E a, E b)
{
	return a > b;
}

#endif
