/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:31:34 by ybendavi          #+#    #+#             */
/*   Updated: 2023/03/30 17:31:38 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::string					str;

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
	if (!fsa.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (0);
	}
	if (std::getline(fsa, str).eof())
	{
		std::cerr << "File empty or no data in." << std::endl;
		return (0);
	}
	if (str.compare("date | value") != 0)
	{
		std::cerr << "File not well formated." << std::endl;
		return (0);
	}
	str.erase();
	while (!(std::getline(fsa, str).eof()))
	{
		bitex.findDate(str);
		str.erase();
	}
	fsa.close();
	//bitex.printDatabase();
	return (0);
}



