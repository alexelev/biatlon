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
    is_footer_right = true;
	records = qual;
}

void Validator::set_qual_stages(uint qual) {
    is_header_right = true;
	stages = qual;
}

void Validator::set_fact_records (uint fact) {
	is_records_right = fact == records;
}

void Validator::set_declared_misses(uint number)
{
	misses = number;
}

bool Validator::is_start_valid() {
	bool a = is_header_right,
        b = is_footer_right,
        c = is_records_right;
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


bool Validator::is_stage_valid(uint stage_number)
{
	if (stage_number <= stages) {
		return true;
	}
	return false;
}

bool Validator::is_misses_valid(uint cur_misses)
{
	return cur_misses == misses;
}
