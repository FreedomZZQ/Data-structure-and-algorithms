#ifndef DICTIONARY_H
#define DICTIONARY_H

#include"list.h"
#include<iostream>

//The dictionary abstract class 
template<typename Key, typename E>
class Dictionary{
private:
	void operator = (const Dictionary&){ }
	Dictionary(const Dictionary&){}
public:
	Dictionary(){}
	virtual ~Dictionary(){}
	virtual void clear() = 0;
	virtual void insert(const Key& k, const E& e) = 0;
	virtual E remove(const Key& k) = 0;
	virtual E removeAny() = 0;
	virtual E find(const Key& k) const = 0;
	virtual int size() = 0;
};

//container for a key-value pair
template<typename Key, typename E>
class KVpair{
private:
	Key k;
	E e;
public:
	KVpair(){}
	KVpair(Key kval, E eval){
		k = kval;
		e = eval;
	}
	KVpair(const KVpair& o){
		k = o.k;
		e = o.k;
	}
	void operator =(const KVpair& o){
		k = o.k;
		e = o.k;
	}
	Key key(){ return k; }
	void setKey(Key ink){ k = ink; }
	E value() { return e; }
};

template<typename Key, typename E>
class UALdict :public Dictionary<Key, E>{
private:
	AList<KVpair<Key, E>> *list;
public:
	UALdict(int size = DEFAULI_SIZE){ list = new AList<KVpair<Key, E>>(size); }
	~UALdict(){ delete list; }
	void clear(){
		list->clear();
	}
	void insert(const Key& k, const E& e){
		KVpair<key, E> temp(k, e);
		list->append(temp);
	}

	//use sequential search to find the element to remove
	E remove(const Key &k){
		E temp = find(k);
		if (temp != NULL) list->remove();
		return temp;
	}

	//remove the last element
	E removeAny(){
		Assert(size() != 0, "Dictionary is empty.");
		list->moveToEnd();
		list->prev();
		KVpair<Key, E> e = list->remove();
		return e.value();
	}

	//find "k" using sequential search
	E find(const Key& k) const{
		for (list->moveToStart(); list->currPos() < list->length(); list->next()){
			KVpair<Key, E> temp = list->getValue();
			if (k == temp.key())
				return temp.value();
		}
		return NULL;
	}
};

//Sorted array_based list
//Inherit from AList as a protected base class
template<typename Key, typename E>
class SAList : protected AList<KVpair<Key, E>>{
public:
	SAList(int size = DEFAULI_SIZE):
		AList<KVpair<Key, E>>(size){}
	~SAList(){}

	//Redefine insert function to keep values sorted
	void insert(KVpair<Key, E>& it){
		KVpair<Key, E> curr;
		for (moveToStart(); currPos() < length(); next()){
			curr = getValue();
			if (curr.key() > it.key())
				break;
		}
		AList<KVpair<Key, E>>::insert(it);
	}

	AList<KVpair<Key, E>>::clear;
	AList<KVpair<Key, E>>::remove;
	AList<KVpair<Key, E>>::moveToStart;
	AList<KVpair<Key, E>>::moveToEnd;
	AList<KVpair<Key, E>>::prev;
	AList<KVpair<Key, E>>::next;
	AList<KVpair<Key, E>>::length;
	AList<KVpair<Key, E>>::currPos;
	AList<KVpair<Key, E>>::moveToPos;
	AList<KVpair<Key, E>>::getValue;

};

//dictionary implemented with a sorted array-based list
template<typename Key, typename E>
class SALdict :public Dictionary<Key, E>{
private:
	SAList<Key, E>* list;
public:
	SALdict(int size = DEFAULI_SIZE){
		list = new SAList<Key, E>(size);
	}
	~SALdict(){
		delete list;
	}
	void clear(){ list->clear(); }

	void insert(const Key &k, const E& e){
		KVpair<Key, E> temp(k, e);
		list->insert(temp);
	}
	E remove(const Key &k){
		E temp = find(k);
		if (temp != NULL) list->remove();
		return temp;
	}

	E removeAny(){
		Assert(size() != 0, "Dictionary is empty.");
		list->moveToEnd();
		list->prev();
		KVpair<Key, E> e = list->remove();
		return e.value();
	}

	E find(const Key &k) const{
		int l = -1;
		int r = list->length();
		while (l + 1 != r){
			int i = (l + r) / 2;
			list->moveToPos(i);
			KVpair<Key, E> temp = list->getValue();
			if (k < temp.key()) r = i;
			if (k == temp.key()) return temp.value();
			if (k > temp.key()) l = i;
		}
		return NULL;
	}

	int size(){
		return list->length();
	}
};


#endif