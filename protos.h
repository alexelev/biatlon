#include <iostream>
#include <string>
#include <fstream>

#include <vector>

#define MAX_SIZE 2047
#define uint unsigned int
#define ulong unsigned long


using namespace std;

class Lexer;
class Builder;
template <typename T>
class DStore;
class Stage;
class Biatlonist;
class Validator;

/*
контейнер-хранилище данных
*/
template <typename T>
class DStore {
private:
	T *store;
	uint size;
	T *ptr;
	T* copy();
	void copy_partial(T*, T*);
public:
	DStore();
	~DStore();
	//DStore(DStore const &obj);
	void push(T obj);
	T pop();
};

class Stage {
public:
	// номер этапа гонки
	unsigned short number;
	// время подхода спортсмена к первому рубежу
	uint forth_time1;
	// время отхода спортсмена от первого рубежа
	uint back_time1;
	// время подхода спортсмена к первому рубежу
	uint forth_time2;
	// время отхода спортсмена от первого рубежа
	uint back_time2;
	// номер спортсмена в данном этапе гонки
	uint start_number;
	// общее время прохождения этапа
	uint common_time;
	// кол-во промахов
	unsigned short misses;
	// время прохождения штрафных кругов
	uint penalty_time;

	Stage();
	//~Stage();
};



class Biatlonist {
private:
	DStore<Stage> stages;
	string surname;
	string fname;
	string country;
public:
	Biatlonist();
	//~Biatlonist();
	Biatlonist(string);

};



class Validator {
private:
	//DStore<string> rules;
	uint rule_count;
	// кол-во этапов
	uint stages;
	// кол-во записей
	uint records;
	// правильна ли первая строка
	bool is_header_right;
	// правильна ли последняя строка
	bool is_footer_right;
	bool is_records_right;



public:
	Validator();
	~Validator();
	void add_rule(string);
	void remove_rule(string);
	string get_rule(uint);
	void set_qual_stages(uint);
	void set_qual_records(uint);
	void set_fact_records(uint);
	bool is_start_valid();
};


class Lexer {
private:
	char delim;
	string data;
	
	string header_attr;
	string footer_attr;
public:
	Lexer();
	~Lexer();
	Lexer(string);
	Validator *val;
	void setDelim(char);
	void parse_header(string);
	void parse_footer(string);
	string get_footer_attr();
	string get_header_attr();
};


class Builder{
private:
	ifstream fin;
	ofstream fout;
	unsigned long filesize;
	Lexer *lex;
	uint lines;
	// Для получения первой строки обрабатываемого файла
	string get_first_line();
	// Для получения последней строки обрабатываемого файла
	string get_last_line();

public:
	Builder();
	~Builder();
	Builder(string);
	void set_filesize(unsigned long);
	void read();
	void read(string);
	void write(string);
	// получение фактического кол-ва строк
	uint get_numberof_lines();
	// загрузка данных из файла в контейнер биатлонистов
	void load_data(string, DStore<Biatlonist>&);
};










