#include "protos.h"

/*
	Конструктор по умолчанию
*/
Builder::Builder(){
}

/*
	Для открытия файла на чтение/дозапись
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
	Для установки размера файла
*/
void Builder::set_filesize(ulong bytes) {
	if (bytes != NULL) {
		filesize = bytes;
	}
}

/*
	Деструктор
*/
Builder::~Builder(){
	fin.close();
	fout.close();
}

/*
	Для применения в случае, когда был использован конструктор без параметров
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
	Для применения в случае создания объекта с помощью конструктора с 
	параметром
*/
void Builder::read() {
	if (fin.is_open()) {
		parser->parse_header(get_first_line());
		parser->parse_footer(get_last_line());
		fin.close();
	}
}

// Для получения первой строки обрабатываемого файла
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
	Для получения последней строки обрабатываемого файла
	использован материал ответа на вопрос http://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file 
*/
string Builder::get_last_line()
{
	string buffer = "";
	if (fin.is_open()) {
		// перемещаемся на позицию перед концом файла
		fin.seekg(-1, ios_base::end);

		bool keepLooping = true;
		while (keepLooping) {
			char ch;
			// Получаем текущий символ из файла
			fin.get(ch);

			if ((int)fin.tellg() <= 1) {
				// если указатель файла оказался перед нолевым символом
				// то первая строка будет одновременно и последней
				fin.seekg(0, ios::beg);
				// и дальше не стоит выполнять цикл
				keepLooping = false;
			}
			else if (ch == '\n') {
				// If the data was a newline
				// если текущий символ является символом перевода строки
				// оставляем указатель на текущей позиции
				keepLooping = false;
			}
			else {
				// в противном случае
				// перемещаем указатель на символ перед текущим
				fin.seekg(-2, ios_base::cur);
			}
		}
		// после отработки цикла указатель в файле будет стоять установлен
		// либо на начало файла, либо на последний символ перевода строки
		getline(fin, buffer);
	}

	return buffer;
}

/*
	Для получения кол-ва строк в файле
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
		// проверка заголовока
		string header = get_first_line();
		parser->parse_header(header);
		// проверка подвала
		string footer = get_last_line();
		parser->parse_footer(footer);
		
		uint numberof_lines = get_numberof_lines();
		uint fact_lines = numberof_lines - 2;
		
		parser->validator->set_fact_records(fact_lines);

		if (parser->validator->is_start_valid()) {
			// построчное чтение и передача на разбор
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
