#include "protos.h"


Biatlonist::Biatlonist() {}

//Biatlonist::~Biatlonist() {}

Biatlonist::Biatlonist(string name) {
	this->name = name;
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
