#pragma once
#include "defs.h"

/*
контейнер-хранилище данных
*/
template <typename T>
class DStore {
private:
	T *store;
	uint size;
	
	void copy(T *to, T *from) {
		for (int i = 0; i < size; i++)
		{
			*(to + i) = *(from + i);
		}
	}
public:
	
	DStore() { 
		size = 0; 
		store = new T[size + 1];
	}
	
	~DStore() { 
		size = 0; 
		delete[]store;
	}
	
	void push(T obj) {
		size++;
		T *tmp = new T[size];
		copy(tmp, store);
		delete[] store;
		store = new T[size];
		copy(store, tmp);
		delete[]tmp;
		store[size - 1] = obj;
	}
	
	T pop();
	
	void show() {
		for (int i = 0; i < size; i++) {
			cout << store[i] << endl;
		}
	}
};