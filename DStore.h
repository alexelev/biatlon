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
			cout << store[i] << endl;
		}
	}

	DStore<T> &operator = (const DStore<T>& obj) {
		this->size = obj.size;
		this->store = new T[size];
		copy(store, obj.store);

		return *this;
	}
};

// todo: �������� �����, ������������ �������� �������� ���������� �� �������