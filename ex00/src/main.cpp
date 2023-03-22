#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

int	main(int ac, char **av)
{
	std::fstream 					fs;
	std::string					str;
	std::map<std::string, std::string>		database;
	std::map<std::string, std::string>::iterator	it;

	(void) ac;
	(void) av;
	fs.open("data.csv", std::fstream::in);
	std::getline(fs, str);
	while (!(std::getline(fs, str).eof()))
	{
		database.insert(std::pair<std::string,
						std::string>(str.substr(0,str.find_first_of(",")), 
								str.substr(str.find_first_of(",") + 1,
									str.size() - str.find_first_of(",") + 1)));
		str.erase();
	}
	it = database.begin();
	while (it != database.end())
	{
		std::cout << it->first << "," << it->second << std::endl;
		it++;
	}
	fs.close();
	return (0);
}



