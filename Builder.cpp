#include "protos.h"

/*
	����������� �� ���������
*/
Builder::Builder(){
}

/*
	��� �������� ����� �� ������/��������
*/
Builder::Builder(string path) {
	if (path != "") {
		fin.open(path);
		if (fin.is_open()) {
			fin.seekg(0, ios::end);
			set_filesize(fin.tellg());
			fin.seekg(0, ios::beg);
		}
	}
}

/*
	��� ��������� ������� �����
*/
void Builder::set_filesize(ulong bytes) {
	if (bytes != NULL) {
		filesize = bytes;
	}
}

/*
	����������
*/
Builder::~Builder(){
	fin.close();
	fout.close();
}

/*
	��� ���������� � ������, ����� ��� ����������� ����������� ��� ����������
*/
void Builder::read(string path) {
	fin.open(path);
	if (fin.is_open()) {
		parser->parse_header(get_first_line());
		parser->parse_footer(get_last_line());

		fin.close();
	}
}

/*
	��� ���������� � ������ �������� ������� � ������� ������������ � 
	����������
*/
void Builder::read() {
	if (fin.is_open()) {
		parser->parse_header(get_first_line());
		parser->parse_footer(get_last_line());
		fin.close();
	}
}

// ��� ��������� ������ ������ ��������������� �����
string Builder::get_first_line()
{	
	string buffer = "";
	if (fin.is_open()) {
		fin.seekg(0, ios::beg);
		getline(fin, buffer);
	}
	return buffer;
}


/* 
	��� ��������� ��������� ������ ��������������� �����
	����������� �������� ������ �� ������ http://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file 
*/
string Builder::get_last_line()
{
	string buffer = "";
	if (fin.is_open()) {
		// ������������ �� ������� ����� ������ �����
		fin.seekg(-1, ios_base::end);

		bool keepLooping = true;
		while (keepLooping) {
			char ch;
			// �������� ������� ������ �� �����
			fin.get(ch);

			if ((int)fin.tellg() <= 1) {
				// ���� ��������� ����� �������� ����� ������� ��������
				// �� ������ ������ ����� ������������ � ���������
				fin.seekg(0, ios::beg);
				// � ������ �� ����� ��������� ����
				keepLooping = false;
			}
			else if (ch == '\n') {
				// If the data was a newline
				// ���� ������� ������ �������� �������� �������� ������
				// ��������� ��������� �� ������� �������
				keepLooping = false;
			}
			else {
				// � ��������� ������
				// ���������� ��������� �� ������ ����� �������
				fin.seekg(-2, ios_base::cur);
			}
		}
		// ����� ��������� ����� ��������� � ����� ����� ������ ����������
		// ���� �� ������ �����, ���� �� ��������� ������ �������� ������
		getline(fin, buffer);
	}

	return buffer;
}

/*
	��� ��������� ���-�� ����� � �����
*/
uint Builder::get_numberof_lines() {
	uint count = 0;
	if (fin.is_open()) {
		string buffer;
		fin.seekg(0, ios::beg);
		while (getline(fin, buffer)) {
			count++;
		}
		return count;
	}
	return NULL;
}

void Builder::load_data(string path, DStore<Biatlonist> &sportsmen)
{
	fin.open(path);
	if (fin.is_open()) {
		// �������� ����������
		string header = get_first_line();
		parser->parse_header(header);
		// �������� �������
		string footer = get_last_line();
		parser->parse_footer(footer);
		
		uint numberof_lines = get_numberof_lines();
		uint fact_lines = numberof_lines - 2;
		
		parser->validator->set_fact_records(fact_lines);

		if (parser->validator->is_start_valid()) {
			// ���������� ������ � �������� �� ������
			uint cur_line = 1;
			// todo: debug this!!
			goto_line(cur_line);
			string buffer;
			
			while (cur_line++ < fact_lines) {
				getline(fin, buffer);
				parser->parse(buffer, sportsmen);

			}

		
		
		}


	}

}

void Builder::goto_line(uint number) {
	if (fin.is_open()) {
		string buf;
		uint i = 0;
		fin.seekg(0, ios::beg);
		while (i++ < number) {
			getline(fin, buf);		
		}
		fin.seekg(1, ios::cur);
	}
}
