#include "protos.h"

template <typename T> 
DStore<T>::DStore(){
	size = 0;
	store = new T[size];
}

template <typename T> 
DStore<T>::~DStore(){
	size = 0;
	delete [] store;
}

template <typename T> 
void DStore<T>::push(T obj){
	T *tmp = copy();
	delete [] store;
	size++;
	store = new T[size];
	copy_partial(store, tmp);
	store[size - 1] = obj;
}

template <typename T> 
T* DStore<T>::copy(){
	T* ptr = new T[size];
	for (int i = 0; i < size; i++)
	{
		*(ptr + i) = *(store + i);
	}
	return ptr;
}

template <typename T> 
void DStore<T>::copy_partial(T* to, T* from){
	T* ptr = new T[size];
	for (int i = 0; i < size; i++)
	{
		*(ptr + i) = *(store + i);
	}
	return ptr;
}