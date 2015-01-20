#ifndef LIST_H
#define LIST_H

#include<string>
#include "link.h"
#define DEFAULI_SIZE 1050

//List ADT
template<typename E>class List{
private:
	void operator =(const List&){}
	List(const List&){}
public:
	List(){}
	virtual ~List(){}
	virtual void clear() = 0;
	virtual void insert(const E& item) = 0;
	virtual void append(const E& item) = 0;
	virtual E remove() = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual void prev() = 0;
	virtual void next() = 0;
	virtual int length() const = 0;
	virtual int currPos() const = 0;
	virtual void moveToPos(int pos) = 0;
	virtual const E& getValue() const = 0;
};

//define??
void Assert(bool a, std::string s){
	if (!a)  std::cout << s << std::endl;
}

//Array-based list implementation

template<typename E>
class AList : public List<E>{
private:
	int maxSize;
	int listSize;
	int curr;
	E* listArray;

public:
	AList(int size = DEFAULT_SIZE){
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}

	~AList(){ delete[] listArray; }

	void clear(){
		delete[] listArray;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}

	void insert(const E& it){
		Assert(listSize < maxSize, "List capacity exceeded");
		for (int i = listSize; i>curr; i--)
			listArray[i] = listArray[i - 1];
		listArray[curr] = it;
		listSize++;
	}

	void append(const E& it){
		Assert(listSize < maxSize, "List capacity exceeded");
		listArray[listSize++] = it;
	}

	E remove(){
		Assert((curr >= 0) && (curr < listSize), "List capacity exceeded");
		E it = listArray[curr];
		for (int i = curr; i < listSize - 1; i++)
			listArray[i] = listArray[i + 1];
		listSize--;
		return it;
	}

	void moveToStart(){ curr = 0; }
	void moveToEnd(){ curr = listSize; }
	void prev(){ if (curr != 0) curr--; }
	void next(){ if (curr < listSize) curr++; }

	int length() const { return listSize; }
	int currPos() const { return curr; }

	void moveToPos(int pos){
		Assert((pos >= 0) && (pos <= listSize), "No current element");
		return listArray[curr];
	}

};

template<typename E>class LList : public List<E>{
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *curr;
	int cnt;

	void init(){
		curr = tail = head = new Link<E>;
		cnt = 0;
	}

	void removeall(){
		while (head != NULL){
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	LList(int size = DEFAULI_SIZE){ init(); }
	~LList(){ removeall(); }
	void print(){
		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			cout << this->getValue() << endl;
		}
	}
	void clear(){ removeall(); init(); }
	void insert(const E& it){
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr) tail = curr->next;
		cnt++;	
	}
	void append(const E& it){
		tail = tail->next = new Link<E>(it, NULL);
		cnt++;
	}
	E remove(){
		Assert(curr->next != NULL, "No element");
		E it = curr->next->element;
		Link<E> *ltemp = curr->next;
		if (tail == curr->next) tail = curr;
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}
	void moveToStart(){ curr = head; }
	void moveToEnd(){ curr = tail; }
	void prev(){
		if (curr == head) return;
		Link<E> *temp = head;
		while (temp->next != curr) temp = temp->next;
		curr = temp;
	}
	void next(){ if (curr != tail) curr = curr->next; }
	int length() const { return cnt; }
	int currPos() const{
		Link<E> *temp = head;
		int i; 
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}
	void moveToPos(int pos){
		Assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i = 0; i < pos; i++)curr = curr->next;
	}
	const E& getValue() const{
		Assert(curr->next != NULL, "No Value");
		return curr->next->element;
	}

	//习题4.6
	//利用临时数组，反转链表中的元素
	//共需遍历链表两次，经估计可达到线性时间复杂度
	void reverse(){
		if (head->next == NULL) return;
		E *a = new E[this->length()];
		int k = 0;

		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			a[k++] = this->getValue();
		}

		for (this->moveToStart(); this->currPos() < this->length(); this->next()){
			curr->next->element = a[--k];
		}

		return;
	}

	//习题4.7
	//将有序链表（由低到高）in1与in2合并，结果储存在in1中
	static LList<E>& merge(LList<E>& in1, LList<E>& in2){

		//初始化位置，准备添加
		in1.moveToStart();
		in2.moveToStart();
		in2.next();
		Link<E>* temp;

		//用于记录in2中已添加的元素
		int k = 0;

		while (in1.currPos() <= in1.length()){
			//添加in2中 小于in1中最大元素的 元素
			//同时记录in2中已添加元素的数量k

			if (in2.curr->element < in1.curr->element){
				temp = new Link<E>(in2.curr->element, in1.curr);

				if (in1.curr == in1.head) {
					in1.head->next = temp;
					in1.curr->next = temp;
				}
				else{
					in1.prev();
					in1.curr->next = temp;
				}
				in1.cnt++;
				k++;

				if (in2.curr == in2.tail) return in1;
				in2.next();
			}

			if (in1.currPos() == in1.length()) break;
			in1.next();
		}

		//从位置k开始，添加in2中的其他元素
		for (in2.moveToPos(k); in2.currPos() < in2.length(); in2.next()){
			in1.append(in2.getValue());
		}
	
		return in1;
	}

	//习题4.12

};

template<typename E>class DLList : public List<E>{
private:
	DLink<E> *head;
	DLink<E> *tail;
	DLink<E> *curr;
	int cnt;

	void init(){
		curr = tail = head = new DLink<E>;
		cnt = 0;
	}

	void removeall(){
		while (head != NULL){
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	DLList(int size = DEFAULI_SIZE){ init(); }
	~DLList(){ removeall(); }
	void print() const;
	void clear(){ removeall(); init(); }
	void insert(const E& it){
		curr->next = curr->next->prev = new DLink<E>(it, curr, curr->next);
		cnt++;
	}
	void append(const E& it){
		tail = tail->next = new DLink<E>(it, NULL);
		cnt++;
	}
	E remove(){
		Assert(curr->next != NULL, "No element");
		E it = curr->next->element;
		DLink<E> *ltemp = curr->next;
		if (tail == curr->next) tail = curr;
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}
	void moveToStart(){ curr = head; }
	void moveToEnd(){ curr = tail; }
	void prev(){
		if (curr == head) return;
		DLink<E> *temp = head;
		while (temp->next != curr) temp = temp->next;
		curr = temp;
	}
	void next(){ if (curr != tail) curr = curr->next; }
	int length(){ return cnt; }
	int currPos() const{
		Link<E> *temp = head;
		int i;
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}
	void moveToPos(int pos){
		Assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i = 0; i < pos; i++)curr = curr->next;
	}
	const E& getValue() const{
		Assert(curr->next != NULL, "No Value");
		return curr->next->element;
	}
};



#endif