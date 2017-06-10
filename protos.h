#define __USE_MINGW_ANSI_STDIO 0

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "DStore.h"

using namespace std;

struct Stage {
	// ����� ����� �����
	ushort number;
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
	ushort misses;
	// ����� ����������� �������� ������
	uint penalty_time;
	// �������� �����
	uint place;
};



class Biatlonist {
private:
	string surname;
	string name;
	string country;
	string hash;
	uint total_misses;
public:
	Biatlonist();
	~Biatlonist();
	Biatlonist(string, string, string);
	DStore<Stage> stages;
	void set_name(string);
	void set_surname(string);
	void set_country(string);
	string get_name();
	string get_surname();
	string get_country();
	string get_hash();
	static string make_hash(const string, const string, const string);
	friend ostream& operator << (ostream&, const Biatlonist &);
	void set_total_misses();
	uint get_total_misses();
};



class Validator {
private:
	string rule;
	// ���-�� ������
	uint stages;
	// ���-�� �������
	uint records;
	// ���-�� ��������
	uint misses;
	// ��������� �� ������ ������
	bool is_header_right;
	// ��������� �� ��������� ������
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
	void set_declared_misses(uint);
	bool is_start_valid();
	bool is_format_valid(string);
	bool is_stage_valid(uint);
	bool is_misses_valid(uint);
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
	void parse(const DStore<string> &, DStore<Biatlonist>&);
	Stage make_stage(const DStore<string>&);
};


class Builder {
private:
	ifstream fin;
	ofstream fout;
	string path;
	uint lines;
	// ��� ��������� ������ ������ ��������������� �����
	string get_first_line();
	// ��� ��������� ��������� ������ ��������������� �����
	string get_last_line();
public:
	void goto_line(uint number);
	Builder();
	~Builder();
	//Builder(string);
	Lexer *parser;
	// ��������� ������������ ���-�� �����
	uint get_numberof_lines();
	// �������� ������ �� ����� � ��������� ������������
	void load_data(string, DStore<Biatlonist>&);
	void save_data(string, const DStore<Biatlonist>&);
	void save_data(string, const DStore<string>&);
};

class Find
{
private:
	Find();

public:
	~Find();
	static int biatlonist_by_hash(const DStore<Biatlonist>&, const string);
};

class Logger
{
private:
	Logger();

public:
	~Logger();
	static DStore<string> messages;
	static void invalid_format(uint);
	static void invalid_stage_number(string);
	static void invalid_total_misses();
	static void invalid_start_validation();
	static void invalid_phisycal_state();
	static void show();
};










