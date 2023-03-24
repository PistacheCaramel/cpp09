#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	int		i;
	std::string	numbers;
	PmergeMe	sorter;

	if (ac < 2)
	{
		std:::cerr << "Need at least one number" << std::endl;
		return (0);
	}
	i = 1;
	while (av[i])
	{
		numbers.append(av[i]);
		numbers.push_back(' ');
		i++;
	}
	numbers.pop_back();
	if (numbers.find_first_not_of("0123456789 ") != std::string::npos)
	{
		std::cerr << "Bad entry." << std::endl;
		return (0);
	}
	sorter.setData(numbers);
	return (0);;
}
