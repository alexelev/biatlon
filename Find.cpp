#include "protos.h"



Find::Find()
{
}


Find::~Find()
{
}

int Find::biatlonist_by_hash(const DStore<Biatlonist> &group, const string hash)
{
	for (size_t i = 0, size = group.get_size(); i < size; i++)
	{
		if (group.at(i).get_hash().compare(hash)) {
			return i;
		}
	}
	return -1;
}
