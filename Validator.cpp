#include "protos.h"

Validator::Validator() {
}

Validator::~Validator()
{
}

void Validator::set_rule(string pattern)
{
	rule = pattern;
}

void Validator::remove_rule(string)
{
}

void Validator::set_qual_records(uint qual) {
	//cout <<
	records = qual;
}

void Validator::set_qual_stages(uint qual) {
	stages = qual;	
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

bool Validator::is_format_valid(string format)
{
	if (!rule.compare(format)) {
		return true;
	}
	return false;
}
