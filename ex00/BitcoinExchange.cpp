/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:30:57 by ybendavi          #+#    #+#             */
/*   Updated: 2023/04/05 17:31:31 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
						size_t						pos;
						std::map<std::string, std::string>::iterator	it;
						double					res;	
						double					value;
						double					calc;
						int					precision;
						int					ret;

						ret = check_line_format(line);
						if (ret == 1)
						{
							std::cerr << "Error bad input => " << line << std::endl;
							return (line);
						}
						else if (ret == 2)
						{
							std::cerr << "Error: not a positive number." << std::endl;
							return (line);
						}
						pos = line.find_first_of(" ");
						it = _database.upper_bound(line.substr(0, pos));
						if (it != _database.begin())
							it--;
						value = atof(line.substr(pos + 3, line.size() - line[pos + 3]).c_str());
						if (value > 1000 || value < 0)
						{
							std::cerr << "Error: too large a number." << std::endl;
							return (line);
						}
						precision = 0;
						res =  atof(it->second.c_str()) * value;
						calc = res;
						while (calc != round(calc) && calc != round(calc) - 1)
						{
							precision++;
							calc *= 10;
						}
						std::cout << line.substr(0, line.find_first_of(" ")) << " => " << std::fixed << std::setprecision(precision) << line.substr(pos + 3, line.size() - line[pos + 3]) << " = " << res;
						std::cout << std::endl;
						return (line);
					}

int			check_date_format(std::string str)
			{
				size_t pos;

				if (str.size() != 10)
					return (1);
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
				if (str[pos + 3] == '-')
					return (2);
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
