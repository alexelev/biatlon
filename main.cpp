#include "protos.h"



using namespace std;

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "ru");

	//string path_source, path_dest;
	//bool in_console = false;
	///*	читаем параметры командной строки и определ€ем откуда читать данные и куда писать
	//*/
	//if (argc > 1) {
	//	switch (argc) {
	//	case 2:
	//		path_source = argv[1];
	//		break;
	//	case 3:
	//		path_source = argv[1];
	//		path_dest = argv[2];
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else {
	//	// todo: обеспечить гарантированный ввод пути к файлу, при необходимости - зациклить, пока не будет что-то введено
	//	cout << "¬ведите путь к исходному файлу: ";
	//	getline(cin, path_source);
	//	cout << "¬ведите путь к конечному файлу: ";
	//	getline(cin, path_dest);
	//	if (path_dest.empty()) {
	//		in_console = true;
	//	}
	//}



	Validator val;
	val.set_rule("ddddsssddddddd");
	Lexer lex;
	lex.validator = &val;
	lex.set_delimiter(';');
	Builder b;
	b.parser = &lex;

	DStore<Biatlonist> sportsmen;

	b.load_data("test.txt", sportsmen);
	sportsmen.show();

	system("pause");
	return 0;
}