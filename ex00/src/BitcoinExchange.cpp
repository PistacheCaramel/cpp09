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

std::string				BitcoinExchange::findDate(std::string line)
					{
						if (check_line_format(line) == 1)
							std::cerr << "Error bad input => " << line << std::endl;
						return (line);
					}

int			check_date_format(std::string str)
			{
				size_t pos;

				pos = str.find_first_not_of("0123456789", 0);
				if (pos == std::string::npos || pos != 4 || str[pos] != '-')
					return (1);
				pos = str.find_first_not_of("0123456789", pos + 1);
				if (pos == std::string::npos || pos != 7 || str[pos] != '-')
					return (1);
				if (str[pos + 3] != 0)
					return (1);
				pos = str.find_first_not_of("0123456789", pos + 1);
				if (pos != std::string::npos)
					return (1);
				return (0);
			}

int			check_line_format(std::string str)
			{
				size_t	pos;

				pos = str.find_first_of(" ");
				if (pos == std::string::npos)
					return (1);
				if (str[pos + 1] != '|')
					return (1);
				if (check_date_format(str.substr(0, pos)) == 1)
					return (1);
				if (str[pos + 1] == 0 || str[pos + 2] == 0)
					return (1);
				if (isdigit(str[pos + 3]) == 0)
					return (1);
				pos = str.find_first_not_of("0123456789", pos + 3);
				if (pos == std::string::npos)
					return (0);
				if (str[pos] != '.')
					return (1);
				if (str[pos + 1] == 0)
					return (0);
				if (isdigit(str[pos + 1]) == 0)
					return (1);
				pos = str.find_first_not_of("0123456789", pos + 1);
				if (pos != std::string::npos)
					return (1);
				return (0);
			}
