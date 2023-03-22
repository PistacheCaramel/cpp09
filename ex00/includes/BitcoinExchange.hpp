
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>

class	BitcoinExchange
{
	public:
					BitcoinExchange(void);
					BitcoinExchange(const  BitcoinExchange&);
					BitcoinExchange(const std::string name);
					~BitcoinExchange(void);
		BitcoinExchange&		operator=( BitcoinExchange const &src);
};

std::ostream &	operator<<(std::ostream & o, BitcoinExchange const & i);
#endif
