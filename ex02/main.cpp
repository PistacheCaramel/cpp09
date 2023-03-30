/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:30:31 by ybendavi          #+#    #+#             */
/*   Updated: 2023/03/30 19:31:34 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>

int	main(int ac, char **av)
{
	int		i;
	std::string	numbers;
	PmergeMe	sorter;
	struct timeval	before;
	struct timeval	after;
	long int	time_of_vector;
	long int	time_of_deque;

	if (ac < 2)
	{
		std::cerr << "Need at least one number" << std::endl;
		return (0);
	}
	i = 1;
	while (av[i])
	{
		numbers.append(av[i]);
		numbers.push_back(' ');
		i++;
	}
	if (numbers.find_first_not_of("0123456789 ") != std::string::npos)
	{
		std::cerr << "Bad entry." << std::endl;
		return (0);
	}
	gettimeofday(&before, NULL);
	if (sorter.setDatav(numbers) == 1)
	{
		std::cout << "Only handle integers." << std::endl;
		return (0);
	}
	sorter.vmergeInsertsort();
	gettimeofday(&after, NULL);
	time_of_vector = (after.tv_sec - before.tv_sec) * 1000000;
	time_of_vector += (after.tv_usec - before.tv_usec);
	gettimeofday(&before, NULL);
	sorter.setDatad(numbers);
	sorter.dmergeInsertsort();
	gettimeofday(&after, NULL);
	time_of_deque = (after.tv_sec - before.tv_sec) * 1000000;
	time_of_deque += (after.tv_usec - before.tv_usec);
	sorter.formatedPrint(time_of_vector, time_of_deque);
	std::cout << "size should have:" << ac - 1 << "size of vector:" << sorter.getLcont().size() << "size of deque:" << sorter.getDcont().size() << std::endl;
	//sorter.printNumbers(time_of_vector, time_of_deque);
	
	return (0);;
}
