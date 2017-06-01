#include "protos.h"
/*
	Для "разбиения" исходной строки на массив строк по разделителю (;)
*/
DStore<string> Lexer::split(string text)
{
	DStore<string> set;
	size_t pos = 0;
	size_t start = 0;
	string tmp = "";
	while ((pos = text.find_first_of(delim)) != string::npos) {
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

void Lexer::set_delimiter(char d)
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
			string str_records = data.substr(0, pos_delim);
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
	Для получения фактической "схемы" формата строки файла
*/
string Lexer::get_schema(const DStore<string> &set)
{
	uint size = set.get_size();
	string schema = "";
	for (size_t i = 0; i < size; i++) {
		try {
			string tmp = set.at(i);
			if (tmp != "null") {
				// конвертация строки в число, если удачно - записываем d, иначе - s
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
	Для разбора строки и десериализации объекта Biatlonist
*/
void Lexer::parse(const DStore<string> &set, DStore<Biatlonist> &group) {
	int index;
	Stage stage = make_stage(set);
	if (validator->is_stage_valid(stoi(set.at(0)))) {
		string hash = Biatlonist::make_hash(set.at(5), set.at(4), set.at(6));
		if ((index = Find::biatlonist_by_hash(group, hash)) != -1) {
			group.at(index).stages.push(stage);
		}
		else {
			Biatlonist member(set.at(5), set.at(4), set.at(6));
			member.stages.push(stage);
			group.push(member);
		}
	}
	else {
		Logger::invalid_stage_number(set.at(0));
	}
}


Stage & Lexer::make_stage(const DStore<string> &set)
{
	Stage st;
	st.number = stoi(set.at(1));
	st.start_number = stoi(set.at(2));
	st.forth_time1 = stoi(set.at(8));
	st.forth_time2 = stoi(set.at(9));
	st.back_time1 = stoi(set.at(10));
	st.back_time2 = stoi(set.at(11));
	st.misses = stoi(set.at(12));
	st.penalty_time = stoi(set.at(13));
	st.place = stoi(set.at(3));
	return st;
}
