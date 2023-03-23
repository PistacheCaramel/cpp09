#include "RPN.hpp"
#include <string>

int	main(int ac, char **av)
{
	RPN		calculator;

	if (ac > 2)
	{
		std::cerr << "Too many args." << std::endl;
		return (0);
	}
	if (ac == 1)
	{
		std::cerr << "No args." << std::endl;
		return (0);
	}
	std::string	arg(av[1]);
	if (arg.find_first_not_of("0123456789 +-/*", 0) != std::string::npos)
	{
		std::cerr << "Error" << std::endl;
		return (0);
	}
	calculator.setRes(arg);
	calculator.printRes();
	return (0);
}
