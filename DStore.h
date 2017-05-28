#pragma once
#include "defs.h"

/*
���������-��������� ������
*/
template <typename T>
class DStore {
private:
	T *store;
	uint size;
	T *ptr;
	/*
		��� ����������� ����� ������ ���������
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
		��� ���������� ������ �������� � ���������
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
		��� �������� ���������� �������� � ���������
	*/
	T pop() {};
	
	/*
		��� ������ �� ����� ����������� ��������� (�� ��� ���������������� ������, ���� ��� ���, � ���� ������ �������� ������)
	*/
	void show() {
		for (int i = 0; i < size; i++) {
			cout << this->at(i) << endl;
		}
	}

	/*
		��� ����������� ������ ������ ������� � ������
	*/
	DStore<T> operator = (DStore<T>& obj) {
		this->size = obj.size;
		this->store = new T[size];

		copy(store, obj.get_data());

		return *this;
	}

	/*
		����������� �����������. ���������!!!
	*/
	DStore(DStore<T> &obj) {
		this->size = obj.size;
		this->store = new T[size];

		copy(store, obj.get_data());
	}


	/*
		��� ��������� �������� �������� ���������� �� ������
	*/
	T at(uint number) {
		if (number < size) {
			return *(store + number);
		}
		return NULL;
	}

	/*
		��� ��������� ��������� �� ������ ������� ����������
	*/
	T* begin() {
		ptr = store;
		return ptr;
	}

	/*
		��� ��������� ������ �� ���������
	*/
	T* get_data() {
		return store;
	}

	uint get_size() {
		return size;
	}

};
