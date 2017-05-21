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

void Validator::set_fact_records (uint fact) {
	is_records_right = fact == records;
}

bool Validator::is_start_valid() {
	
	if (is_header_right && is_footer_right && is_records_right) {
		return true;
	}
	
	return false;
}