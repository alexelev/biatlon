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
	T *ptr;
	/*
		Для копирования части данных хранилища
	*/
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
	
	/*
		для добавления нового элемента в хранилище
	*/
	void push(T obj) {
		if (size)
		{
			T *tmp = new T[size];
			copy(tmp, store);
			delete[] store;
			store = new T[size + 1];
			copy(store, tmp);
			delete[]tmp;
		}
		else {
			delete[] store;
			store = new T[size + 1];
		}
		size++;
		store[size - 1] = obj;
	}
	
	/*
		для удаления последнего элемента в хранилище
	*/
	T pop() {};
	
	/*
		для вывода на экран содержимого хранилища (не для пользовательских данных, либо для тех, у кого описан оператор вывода)
	*/
	void show() {
		for (int i = 0; i < size; i++) {
			cout << this->at(i) << endl;
		}
	}

	/*
		Для возможности записи одного объекта в другой
	*/
	DStore<T> operator = (DStore<T>& obj) {
		this->size = obj.size;
		this->store = new T[size];

		copy(store, obj.get_data());

		return *this;
	}

	/*
		конструктор копирования. Необходим!!!
	*/
	DStore(DStore<T> &obj) {
		this->size = obj.size;
		this->store = new T[size];

		copy(store, obj.get_data());
	}


	/*
		Для получения значения элемента контейнера по номеру
	*/
	T at(uint number) {
		if (number < size) {
			return *(store + number);
		}
		return NULL;
	}

	/*
		Для получения указателя на первый элемент контейнера
	*/
	T* begin() {
		ptr = store;
		return ptr;
	}

	/*
		Для получения данных из хранилища
	*/
	T* get_data() {
		return store;
	}

	uint get_size() {
		return size;
	}

};
