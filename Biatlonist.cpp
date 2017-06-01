#include "protos.h"


Biatlonist::Biatlonist() {
	name = "";
	surname = "";
	country = "";
	total_misses = 0;
}

Biatlonist::~Biatlonist() {}

Biatlonist::Biatlonist(string name, string surname, string country) {
	this->name = name;
	this->surname = surname;
	this->country = country;
	this->hash = this->name + this->surname + this->country;
}

void Biatlonist::set_name(string name)
{
	if (!name.empty()) {
		this->name = name;
	}
}

void Biatlonist::set_surname(string surname)
{
	if (!surname.empty()) {
		this->surname = surname;
	}
}

void Biatlonist::set_country(string country)
{
	if (!country.empty())
	{
		this->country = country;
	}
}

string Biatlonist::get_name()
{
	return name;
}

string Biatlonist::get_surname()
{
	return surname;
}

string Biatlonist::get_country()
{
	return country;
}

string Biatlonist::get_hash()
{
	return hash;
}

string Biatlonist::make_hash(const string name, const string surname, const string country)
{
	string result = "";
	return result.append(name).append(surname).append(country);
}

void Biatlonist::set_total_misses()
{
	for (size_t i = 0, size = stages.get_size(); i < size; i++)
	{
		total_misses += stages.at(i).misses;
	}
}

uint Biatlonist::get_total_misses()
{
	return total_misses;
}

// для вывода в консоль
ostream& operator << (ostream &os, const Biatlonist &man) {
	os <<
		"name: " << man.name << endl <<
		"surname: " << man.surname << endl <<
		"country: " << man.country << endl;
	for (size_t i = 0, size = man.stages.get_size(); i < size; i++)
	{
		Stage s = man.stages.at(i);
		os <<
			"\t#: " << s.number << endl <<
			"\tmisses: " << s.misses << endl <<
			"\tplace: " << s.place << endl <<
			"++++++++++++++++++++++++++++++++++++++++" << endl;
	}
	os << "=================================================\n";
	return os;
}

