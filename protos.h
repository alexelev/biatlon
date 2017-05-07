#include <iostream>
#include <string>
#include <fstream>

#define MAX_SIZE 2047;

using namespace std;

template <typename T>
class DStore {
private:
	T *store;
	unsigned int size;
	T *ptr;
	T* copy();
	void copy_partial(T*, T*);
public:
	DStore();
	~DStore();
	void push(T obj);
	T pop();
};

class Builder{
private:
	ifstream fin;
	ofstream fout;

public:
	Builder();
	~Builder();
	void read(string);
	void write(string);
};

class Lexer {
private:
	char delim;
	string data;
public:
	Lexer();
	~Lexer();
	Lexer(string);
	void setDelim(char);

};

class Validator {
private:
	DStore<string> rules;
	unsigned int rule_count;
public:
	Validator();
	~Validator();
	void add_rule(string);
	void remove_rule(string);
	string get_rule(unsigned int);

};

class Stage {
public:
	// номер этапа гонки
	unsigned short number;
	// время подхода спортсмена к первому рубежу
	unsigned int forth_time1;
	// время отхода спортсмена от первого рубежа
	unsigned int back_time1;
	// время подхода спортсмена к первому рубежу
	unsigned int forth_time2;
	// время отхода спортсмена от первого рубежа
	unsigned int back_time2;
	// страна проведения этапа
	string country;
	// номер спортсмена в данном этапе гонки
	unsigned int start_number;
	// общее время прохождения этапа
	unsigned int common_time;
	// кол-во промахов
	unsigned short misses;
	// время прохождения штрафных кругов
	unsigned int penalty_time;

	Stage();
	~Stage();
};

class Biatlonist {
private:
	DStore<Stage> stages;
	string surname;
	string fname;
	
public:
	Biatlonist();
	~Biatlonist();
	Biatlonist(string);

};
