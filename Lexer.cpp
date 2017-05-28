#include "protos.h"
/*
	��� "���������" �������� ������ �� ������ ����� �� ����������� (;)
*/
DStore<string> Lexer::split(string text)
{
	DStore<string> set;
	size_t pos = 0;
	size_t start = 0;
	string tmp = "";
	while ((pos = text.find_first_of(delim)) != string::npos){
		tmp.assign(text, 0, pos);
		text = text.substr(pos + 1);
		set.push(tmp);
	}
	set.push(text);
	return set;
}

Lexer::Lexer() {
	delim = ';';
	header_attr = "header:";
	footer_attr = "footer:";
}

Lexer::~Lexer() {
}

Lexer::Lexer(string)
{
}

void Lexer::setDelim(char d)
{
	delim = d;
}

void Lexer::parse_header(string str) {
	int pos = str.find(header_attr);
	if (pos != string::npos) {
		uint hl = header_attr.length();
		string data = str.substr(hl, str.length() - hl);
		validator->set_qual_stages(stoi(data));
	}
	else {
		validator->set_qual_stages(NULL);
	}
}

void Lexer::parse_footer(string str) {
	int pos = str.find(footer_attr);
	if (pos != string::npos) {
		uint fl = footer_attr.length();
		string data = str.substr(fl, str.length() - fl);
		fpos_t pos_delim = data.find(delim);
		if (pos_delim != string::npos) {
			string str_records = data.substr(0, pos_delim - 1);
			validator->set_qual_records(stoi(str_records));
		}
	}
	else {
		validator->set_qual_records(NULL);
	}
}

string Lexer::get_footer_attr() {
	return footer_attr;
}
string Lexer::get_header_attr()
{
	return string();
}
/*
	��� ��������� "�����" ������� ������ �����
*/
string Lexer::get_schema(const DStore<string> &set)
{
	uint size = set.get_size();
	string schema = "";
	for (size_t i = 0; i < size; i++) {
		// http://ru.cppreference.com/w/cpp/string/byte/strtof
		try {
			string tmp = set.at(i);
			if (tmp != "null") {
				double digit = stod(tmp);
				schema.append("d");
			}
		}
		catch (const invalid_argument &ia) {
			schema.append("s");
		}
	}

	return schema;
}
/*
	��� ������� ������ � �������������� ������� Biatlonist
*/
Biatlonist Lexer::parse(string src) {
	DStore<string> set = this->split(src);
	Biatlonist b;
	return b;
}
