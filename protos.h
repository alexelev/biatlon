#include <iostream>
#include <string>
#include <fstream>
#include "DStore.h"


using namespace std;

class Lexer;
class Builder;
class Stage;
class Biatlonist;
class Validator;

struct Stage {
	// номер этапа гонки
	unsigned short number;
	// врем€ подхода спортсмена к первому рубежу
	uint forth_time1;
	// врем€ отхода спортсмена от первого рубежа
	uint back_time1;
	// врем€ подхода спортсмена к первому рубежу
	uint forth_time2;
	// врем€ отхода спортсмена от первого рубежа
	uint back_time2;
	// номер спортсмена в данном этапе гонки
	uint start_number;
	// общее врем€ прохождени€ этапа
	uint common_time;
	// кол-во промахов
	unsigned short misses;
	// врем€ прохождени€ штрафных кругов
	uint penalty_time;
};



class Biatlonist {
private:
	DStore<Stage> *stages;
	string surname;
	string name;
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
	// правильна ли перва€ строка
	bool is_header_right;
	// правильна ли последн€€ строка
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
	DStore<string> split(string);
	Lexer();
	~Lexer();
	Lexer(string);
	Validator *validator;
	void setDelim(char);
	void parse_header(string);
	void parse_footer(string);
	string get_footer_attr();
	string get_header_attr();
	string get_schema(string);

};


class Builder{
private:
	ifstream fin;
	ofstream fout;
	unsigned long filesize;
	
	uint lines;
	// ƒл€ получени€ первой строки обрабатываемого файла
	string get_first_line();
	// ƒл€ получени€ последней строки обрабатываемого файла
	string get_last_line();
	void goto_line(uint number);

public:
	Builder();
	~Builder();
	Builder(string);
	Lexer *parser;
	void set_filesize(unsigned long);
	void read();
	void read(string);
	void write(string);
	// получение фактического кол-ва строк
	uint get_numberof_lines();
	// загрузка данных из файла в контейнер биатлонистов
	void load_data(string, DStore<Biatlonist>&);
};










