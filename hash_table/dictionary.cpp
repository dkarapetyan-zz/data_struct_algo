#include "dictionary.hpp"

int main()
{
	dictionary my_table;
	my_table.insert_entry(std::make_pair("duck", "an animal that quacks"));
	my_table.insert_entry(std::make_pair("dubl", "collision with duck"));
	my_table.insert_entry(std::make_pair("cow", "an animal that is tasty"));
	my_table.delete_entry("duck");
	my_table.search_entry("dubl");
	my_table.print_entries();

	return 0;
}

