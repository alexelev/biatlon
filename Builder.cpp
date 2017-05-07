#include "protos.h"

/*
	Конструктор по умолчанию
*/
Builder::Builder(){
	lex = new Lexer();
}

Builder::Builder(string path) {
	
}

/*
	Деструктор
*/
Builder::~Builder(){

}

void Builder::read(string path) {
	fin.open(path);
	fin.seekg(0, ios::end);
	filesize = fin.tellg();
	fin.seekg(0);

	string buffer;
	getline(fin, buffer);
	lex->parse_header(buffer);
	buffer.clear();

	fin.seekg(0, ios::end);
	fpos_t curpos = fin.tellg();
	if (filesize > MAX_SIZE) {
		fin.seekg(curpos - MAX_SIZE);
	}
	else {
		fpos_t pos = fin.tellg();
		// todo: читать футер
		for (size_t i = pos - 1; buffer.find(lex->get_footer_attr()) != string::npos; --i) {
			getline(fin, buffer);
			fin.seekg(i);
		}

		//fin.seekg(0);
	}
	
	getline(fin, buffer);
	lex->parse_footer(buffer);

	fin.close();
	/*while (getline(fin, buffer)) {
		
	}*/
}