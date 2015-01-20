#ifndef LINK_H
#define LINK_H

//singly linked list node with freelist support
template<typename E> class Link{
private:
	static Link<E> *freelist;
public:
	E element;
	Link *next;

	Link(const E& elemval, Link* nextval = NULL){
		element = elemval;
		next = nextval;
	}
	Link(Link* nextval = NULL){ next = nextval; }
	void* operator new(size_t){
		if (freelist == NULL) return ::new Link;
		Link<E>* temp = freelist;
		freelist = freelist->next;
		return temp;
	}
	void operator delete(void* ptr){
		((Link<E>*)ptr)->next = freelist;
		freelist = (Link<E>*)ptr;
	}
};



template<typename E>
Link<E>* Link<E>::freelist = NULL;

//Doubly linked list node with freelist support
template<typename E> class DLink{
private:
	static DLink<E> *freelist;
public:
	E element;
	DLink *next;
	DLink *prev;

	DLink(const E& it, DLink *prevp, DLink* nextp){
		element = it;
		prev = prevp;
		next = nextp;
	}
	DLink(DLink *prevp = NULL, DLink *nextp = NULL){
		prev = prevp;
		next = nextp;
	}
	void * operator new(size_t){
		if (freelist == NULL) return ::new DLink;
		DLink<E> *temp = freelist;
		freelist = freelist->next;
		return temp;
	}
	void operator delete(void *ptr){
		((DLink<E>*)ptr)->next = freelist;
		freelist = (DLink<E> *)ptr;
	}
};

template<typename E>
DLink<E>* DLink<E>::freelist = NULL;

#endif