#include "protos.h"

/*
	����������� �� ���������
*/
Builder::Builder() {
}

///*
//	��� �������� ����� �� ������/��������
//*/
//Builder::Builder(string path) {
//	if (path != "") {
//		fin.open(path);
//		if (fin.is_open()) {
//			fin.seekg(0, ios::end);
//			set_filesize(fin.tellg());
//			fin.seekg(0, ios::beg);
//		}
//	}
//}

///*
//	��� ��������� ������� �����
//*/
//void Builder::set_filesize(ulong bytes) {
//	if (bytes != NULL) {
//		filesize = bytes;
//	}
//}

/*
	����������
*/
Builder::~Builder() {
	fin.close();
	fout.close();
}

///*
//	��� ���������� � ������, ����� ��� ����������� ����������� ��� ����������
//*/
//void Builder::read(string path) {
//	fin.open(path);
//	if (fin.is_open()) {
//		parser->parse_header(get_first_line());
//		parser->parse_footer(get_last_line());
//
//		fin.close();
//	}
//}

///*
//	��� ���������� � ������ �������� ������� � ������� ������������ �
//	����������
//*/
//void Builder::read() {
//	if (fin.is_open()) {
//		parser->parse_header(get_first_line());
//		parser->parse_footer(get_last_line());
//		fin.close();
//	}
//}

// ��� ��������� ������ ������ ��������������� �����
string Builder::get_first_line()
{
	string buffer = "";
	fin.open(path);
	if (fin.is_open()) {
		fin.seekg(0, ios::beg);
		getline(fin, buffer);
	}
	fin.close();
	return buffer;
}


/*
	��� ��������� ��������� ������ ��������������� �����
	����������� �������� ������ �� ������ http://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
*/
string Builder::get_last_line()
{
	string buffer = "";
	fin.open(path);
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
	fin.close();
	return buffer;
}

/*
	��� ��������� ���-�� ����� � �����
*/
uint Builder::get_numberof_lines() {
	uint count = 0;
	fin.open(path);
	if (fin.is_open()) {
		string buffer;
		fin.seekg(0, ios::beg);
		while (getline(fin, buffer)) {
			count++;
		}
		fin.close();
		return count;
	}
	fin.close();
	return NULL;
}

void Builder::load_data(string path, DStore<Biatlonist> &sportsmen)
{
	this->path = path;
	// �������� ����������
	string header = get_first_line();
	parser->parse_header(header);
	// �������� �������
	string footer = get_last_line();
	parser->parse_footer(footer);

	uint numberof_lines = get_numberof_lines();
	uint fact_lines = numberof_lines - 2;

	parser->validator->set_fact_records(fact_lines);

	fin.open(path);
	if (fin.is_open()) {

		if (parser->validator->is_start_valid()) {
			// ���������� ������ � �������� �� ������
			uint cur_line = 1;
			string buffer;
			uint i = 0;

			while (i++ < cur_line) {
				getline(fin, buffer);
			}

			while (cur_line++ <= fact_lines) {
				getline(fin, buffer);
				DStore<string> set = parser->split(buffer);
				string cur_schema = parser->get_schema(set);
				if (parser->validator->is_format_valid(cur_schema)) {
					parser->parse(set, sportsmen);
				}
				else {
					Logger::invalid_format(cur_line - 1);
					break;
				}
			}

			uint cur_total_misses = 0;
			for (size_t i = 0, size = sportsmen.get_size(); i < size; i++)
			{
				cur_total_misses += sportsmen.at(i).get_total_misses();
			}

			if (!parser->validator->is_misses_valid(cur_total_misses)) {
				Logger::invalid_total_misses();
			}
		}
		else {
			Logger::invalid_start_validation();
		}
		fin.close();
	}
	else {
		Logger::invalid_phisycal_state();
	}

}

void Builder::save_data(string path, const DStore<Biatlonist> &data)
{
	fout.open(path, ios::out);
	if (fout.is_open()) {
		for (size_t i = 0, size = data.get_size(); i < size; i++)
		{
			fout << data.at(i);
		}
	}
	else {
		Logger::invalid_phisycal_state();
	}
}

void Builder::save_data(string path, const DStore<string> &data)
{
	fout.open(path, ios::out);
	if (fout.is_open()) {
		for (size_t i = 0, size = data.get_size(); i < size; i++)
		{
			fout << data.at(i);
		}
	}
	else {
		Logger::invalid_phisycal_state();
	}
}
