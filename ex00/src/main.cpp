#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

int	main(int ac, char **av)
{
	std::fstream 					fs;
	std::fstream 					fsa;
	BitcoinExchange					bitex;

	(void) ac;
	(void) av;
	if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (0);
	}
	
	fs.open("data.csv", std::fstream::in);
	if (!fs.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return (0);
	}
	bitex.setDatabase(fs);
	fs.close();
	fsa.open(av[1], std::fstream::in);
	if (!fs.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (0);
	}
	bitex.printDatabase();
	return (0);
}



