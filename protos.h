#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "DStore.h"


using namespace std;

class Lexer;
class Builder;
class Stage;
class Biatlonist;
class Validator;

struct Stage {
	// номер этапа гонки
	ushort number;
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
	ushort misses;
	// время прохождения штрафных кругов
	uint penalty_time;
	// призовое место
	uint place;
};



class Biatlonist {
private:
	DStore<Stage> *stages;
	string surname;
	string name;
	string country;
	string hash;
public:
	Biatlonist();
	//~Biatlonist();
	Biatlonist(string, string, string);
	void set_name(string);
	void set_surname(string);
	void set_country(string);
	string get_name();
	string get_surname();
	string get_country();
	string get_hash();
};



class Validator {
private:
	string rule;
	//DStore<string> rules;
	//uint rule_count;
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
	void set_rule(string);
	void remove_rule(string);
	string get_rule(uint);
	void set_qual_stages(uint);
	void set_qual_records(uint);
	void set_fact_records(uint);
	bool is_start_valid();
	bool is_format_valid(string);
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
	void set_delimiter(char);
	void parse_header(string);
	void parse_footer(string);
	string get_footer_attr();
	string get_header_attr();
	string get_schema(const DStore<string>&);
	Biatlonist parse(string, DStore<Biatlonist>&);

};


class Builder{
private:
	ifstream fin;
	ofstream fout;
	unsigned long filesize;
	
	uint lines;
	// Для получения первой строки обрабатываемого файла
	string get_first_line();
	// Для получения последней строки обрабатываемого файла
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










