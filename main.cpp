#include "protos.h"



using namespace std;

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "ru");

	string path_source, path_dest, path_error_log;
	bool in_console = false;
	/*
		читаем параметры командной строки и определ€ем откуда читать данные и куда писать
	*/
	if (argc > 1) {
		switch (argc) {
		case 2:
			path_source = argv[1];
			break;
		case 3:
			path_source = argv[1];
			path_dest = argv[2];
			break;
		case 4:
			path_source = argv[1];
			path_dest = argv[2];
			path_error_log = argv[3];
			break;
		default:
			break;
		}
	}
	else {
		do {
			cout << "¬ведите путь к исходному файлу: ";
			getline(cin, path_source);
		} while (path_source.empty());
		cout << "¬ведите путь к конечному файлу: ";
		getline(cin, path_dest);
		if (path_dest.empty()) {
			in_console = true;
		}
		cout << "¬ведите путь к файлу дл€ логировани€ ошибок: ";
		getline(cin, path_error_log);
		if (path_error_log.empty()) {
			path_error_log = "error.log.txt";
		}
	}

	Validator val;
	val.set_rule("ddddsssddddddd");
	Lexer lex;
	lex.validator = &val;
	lex.set_delimiter(';');
	Builder b;
	b.parser = &lex;

	DStore<Biatlonist> sportsmen;

	b.load_data(path_source, sportsmen);
	uint min_misses = sportsmen.at(0).get_total_misses();
	for (size_t i = 0, size = sportsmen.get_size(); i < size; i++)
	{
		if (sportsmen.at(i).get_total_misses() < min_misses) {
			min_misses = sportsmen.at(i).get_total_misses();
		}
	}

	DStore<Biatlonist> top;
	for (size_t i = 0, size = sportsmen.get_size(); i < size; i++)
	{
		if (sportsmen.at(i).get_total_misses() == min_misses) {
			Biatlonist tmp = sportsmen.at(i);
			top.push(tmp);
		}
	}
	
	if (in_console) {
		system("cls");
		top.show();
		cout << "Logger records:\n";
		Logger::show();
	}
	else {
		b.save_data(path_dest, top);
		b.save_data(path_error_log, Logger::messages);
	}
	
	system("pause");
	return 0;
}