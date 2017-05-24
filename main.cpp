#include <iostream>
#include "protos.h"
#include <Windows.h>


using namespace std;

int main() {
	
	//Builder b;
//DStore<string> logger;
	//DStore<Biatlonist> sportsmen;
	//b.load_data("text2.txt", sportsmen);

	//vector<int> tt;
	//tt.push_back(11);
	//tt.push_back(12);
	//cout << tt.at(0) << ' ' << tt.at(1) << endl;

	//DStore<int> test;

	//test.push(1);
	//test.push(2);
	//test.show();

	//DStore<string> test;
	//test.push("test1");
	//test.push("test2");
	//test.push("test3");
	//test.push("test4");
	//test.show();

	Stage s1, s2;
	Biatlonist b1("Ivan"), b2("Pedro");
	DStore<Stage> *testS = new DStore<Stage>();
	DStore<Biatlonist> *testB = new DStore<Biatlonist>();
	
	s1.number = 2;
	s2.number = 1;

	testS->push(s1);
	testS->push(s2);
	testB->push(b1);
	testB->push(b2);


	//system("pause");
	return 0;
}