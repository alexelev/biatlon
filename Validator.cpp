#include "protos.h"

Validator::Validator() {
}

void Validator::set_qual_records(uint qual) {
	//cout <<
	records = qual;
	cout << "records = " << qual << endl;
}

void Validator::set_qual_stages(uint qual) {
	stages = qual;	
	cout << "stages = " << qual << endl;
}