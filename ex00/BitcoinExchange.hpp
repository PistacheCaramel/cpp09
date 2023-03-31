/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:31:23 by ybendavi          #+#    #+#             */
/*   Updated: 2023/03/31 16:58:10 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <iomanip>
# include <math.h>
# include <fstream>
# include <map>
# include <iostream>
# include <ctype.h>
# include <stdlib.h>

class	BitcoinExchange
{
	private:
			std::map<std::string, std::string>		_database;

	public:
					BitcoinExchange(void);
					BitcoinExchange(const  BitcoinExchange&);
					BitcoinExchange(std::fstream& fs);
					~BitcoinExchange(void);
		BitcoinExchange&		operator=( BitcoinExchange const &src);
		std::map<std::string, std::string>	getDatabase(void) const;
		void			setDatabase(std::fstream& fs);
		void			printDatabase(void);
		std::string		findDate(std::string line);
};

int	check_date_formt(std::string str);
int	check_line_format(std::string str);

std::ostream &	operator<<(std::ostream & o, BitcoinExchange const & i);
#endif
