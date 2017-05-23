#include <iostream>
#include "protos.h"
#include <Windows.h>
//#include <fstream>
#include <vector>


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

	DStore<int> test;

	test.push(1);
	test.push(2);
	test.show();




	//cout << 
	system("pause");
	return 0;
}