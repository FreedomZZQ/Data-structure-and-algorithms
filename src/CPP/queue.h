#ifndef QUEUE_H
#define QUEUE_H
#define DEFAULI_SIZE 1050
#include "link.h"
//abstract queue class
template<typename E> class Queue{
private:
	void operator =(const Queue&){}
	Queue(const Queue&){}
public:
	Queue(){}
	virtual ~Queue(){}
	virtual void clear() = 0;
	virtual void enqueue() = 0;
	virtual E dequeue() = 0;
	virtual const E& frontValue() = 0;
	virtual int length() const = 0;
};

//Array based queue implementation
template<typename E> class AQueue :public Queue<E>{
private:
	int maxSize;
	int front;
	int rear;
	E *listArray;
public:
	AQueue(int size = DEFAULI_SIZE){
		maxSize = size + 1;
		rear = 0;
		front = 1;
		listArray = new E[maxSize];
	}
	~AQueue(){ delete[] listArray; }
	void clear(){ rear = 0; front = 1; }
	void enqueue(const E& it){
		Assert(((rear + 2) % maxSize) != front, "Queue is full");
		rear = (rear + 1) % maxSize;
		listArray[rear] = it;
	}
	E dequeue(){
		Assert(length() != 0, "Queue is empty");
		E it = listArray[front];
		front = (front + 1) % maxSize;
		return it;
	}
	const E& frontValue()const{
		Assert(length() != 0, "Queue is empty");
		return listArray[front];
	}
	virtual int length()const{
		return ((rear + maxSize) - front + 1) % maxSize);
	}
};

//linked queue implementation
template<typename E>class LQueue :public Queue<E>{
private:
	Link<E>* front;
	Link<E>* rear;
	int size;

public:
	LQueue(int sz = DEFAULT_SIZE)
	{
		front = rear = new Link<E>();
		size = 0;
	}
	~LQueue(){ clear(); delete front; }
	void clear(){
		while (front->next != NULL){
			rear = front;
			delete rear;
		}
		rear = front;
		size = 0;
	}

	void enqueue(const E& it){
		rear->next = new Link<E>(it, NULL);
		rear = rear->next;
		size++;
	}

	E dequeue(){
		Assert(size != 0, "Queue is empty");
		E it = front->next->element;
		Link<E>* ltemp = front->next;
		front->next = ltemp->next;
		if (rear = ltemp) rear = front;
		delete ltemp;
		size--;
		return it;
	}

	const E& frontValue() const{
		Assert(size != 0, "Queue is empty");
		return front->next->element;
	}

	virtual int length() const { return size; }
};
#endif