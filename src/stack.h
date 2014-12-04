#ifndef STACK_H
#define STACK_H
#define DEFAULT_SIZE 1050
#include "link.h"
//stack abstract class
template<typename E> class Stack{
private:
	void operator =(const Stack&){}
	Stack(const Stack&){}
public:
	Stack(){}
	virtual ~Stack(){}

	virtual void clear() = 0;
	virtual void push(const E& it) = 0;
	virtual E pop() = 0;
	virtual const E& topValue() const = 0;
	virtual int length() const = 0;

};

//Array based stack implementation
template<typename E> class AStack :public Stack<E>{
private:
	int maxSize;
	int top;
	E *listArray;
public:
	AStack(int size = DEFAULT_SIZE)
	{
		maxSize = size; 
		top = 0;
		listArray = new E[size];
	}
	~AStack(){ delete[] listArray; }

	void clear(){ top = 0; }
	void push(const E& it){
		Assert(top != maxSize, "Stack is full");
		listArray[top++] = it;
	}
	E pop(){
		Assert(top != 0, "Stack is empty");
		return listArray[--top];
	}
	const E& topValue() const{
		Assert(top != 0, "Stack is empty");
		return listArray[top - 1];
	}
	int length()const { return top; }
};

//Linked stack implementation
template<typename E> class LStack : public Stack<E>{
private:
	Link<E>* top;
	int size;
public:
	LStack(int sz = DEFAULT_SIZE){
		top = NULL;
		size = 0;
	}
	~LStack(){ clear(); }
	void clear() {
		while (top != NULL){
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}
	void push(const E& it){
		top = new Link<E>(it, top);
		size++;
	}
	E pop(){
		Assert(top != 0, "Stack is empty.");
		E it = top->element;
		Link<E>* ltemp = top->next;
		delete top;
		top = ltemp;
		size--;
		return it;
	}

	const E& topValue() const{
		Assert(top != NULL, "Stack is empty.");
		return top->element;
	}
	int length() const{ return size; }
};

#endif