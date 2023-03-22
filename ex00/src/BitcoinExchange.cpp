#include "BitcoinExchange.hpp"

	BitcoinExchange::BitcoinExchange(void){}

	BitcoinExchange::~BitcoinExchange(void){}

	BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
	{
		*this = copy;
	}

	BitcoinExchange::BitcoinExchange(std::fstream& fs)
	{
		std::map<std::string, std::string>::iterator	it;
		std::string					str;

		std::getline(fs, str);
		while (!(std::getline(fs, str).eof()))
		{
			_database.insert(std::pair<std::string, std::string>(str.substr(0,str.find_first_of(",")), str.substr(str.find_first_of(",") + 1, str.size() - str.find_first_of(",") + 1)));
			str.erase();
		}
	}

BitcoinExchange&	BitcoinExchange::operator=( BitcoinExchange const &src)
			{
				if (this == &src)
					return (*this);
				_database = src.getDatabase();
				return (*this);
			}

void			BitcoinExchange::setDatabase(std::fstream& fs)
			{
				std::map<std::string, std::string>::iterator	it;
				std::string					str;

				std::getline(fs, str);
				while (!(std::getline(fs, str).eof()))
				{
					_database.insert(std::pair<std::string, std::string>(str.substr(0,str.find_first_of(",")), str.substr(str.find_first_of(",") + 1, str.size() - str.find_first_of(",") + 1)));
					str.erase();
				}
			}

void			BitcoinExchange::printDatabase(void)
			{
				std::map<std::string, std::string>::iterator	it;

				it = _database.begin();
				while (it != _database.end())
				{
					std::cout << it->first << "," << it->second <<std::endl;
					it++;
				}
			}

std::map<std::string, std::string>	BitcoinExchange::getDatabase(void) const
					{
						return (_database);
					}
