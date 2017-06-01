#include "protos.h"



using namespace std;

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "ru");

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