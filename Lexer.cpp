#include "protos.h"

Lexer::Lexer() {
	val = new Validator();
	delim = ';';
	header_attr = "header:";
	footer_attr = "footer:";
}

void Lexer::parse_header(string str) {
	int pos = str.find(header_attr);
	if (pos != string::npos) {
		uint hl = header_attr.length();
		string data = str.substr(hl, str.length() - hl);
		val->set_qual_stages(stoi(data));
	}
	else {
		val->set_qual_stages(NULL);
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
			val->set_qual_records(stoi(str_records));
		}
	}
	else {
		val->set_qual_records(NULL);
	}
}

string Lexer::get_footer_attr() {
	return footer_attr;
}