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
���������-��������� ������
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
	// ����� ����� �����
	unsigned short number;
	// ����� ������� ���������� � ������� ������
	uint forth_time1;
	// ����� ������ ���������� �� ������� ������
	uint back_time1;
	// ����� ������� ���������� � ������� ������
	uint forth_time2;
	// ����� ������ ���������� �� ������� ������
	uint back_time2;
	// ����� ���������� � ������ ����� �����
	uint start_number;
	// ����� ����� ����������� �����
	uint common_time;
	// ���-�� ��������
	unsigned short misses;
	// ����� ����������� �������� ������
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
	// ���-�� ������
	uint stages;
	// ���-�� �������
	uint records;
	// ��������� �� ������ ������
	bool is_header_right;
	// ��������� �� ��������� ������
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
	// ��� ��������� ������ ������ ��������������� �����
	string get_first_line();
	// ��� ��������� ��������� ������ ��������������� �����
	string get_last_line();

public:
	Builder();
	~Builder();
	Builder(string);
	void set_filesize(unsigned long);
	void read();
	void read(string);
	void write(string);
	// ��������� ������������ ���-�� �����
	uint get_numberof_lines();
	// �������� ������ �� ����� � ��������� ������������
	void load_data(string, DStore<Biatlonist>&);
};










