#include "PmergeMe.hpp"

		PmergeMe::PmergeMe(void): _name("John Doe")
		{
		}

		PmergeMe::PmergeMe(const  PmergeMe& copy)
		{
			*this = copy;
		}

		PmergeMe::~PmergeMe(void)
		{
		}

PmergeMe&	PmergeMe::operator=(PmergeMe const &src)
		{
			if (this == &src)
				return (*this);
			_lcont = src.getLcont();
			_dcont = src.getDcont();
			return (*this);
		}

std::deque<int>	PmergeMe::getDcont(void) const
		{
			return (_dcont);
		}

std::list<int>	PmergeMe::getLcont(void) const
		{
			return (_lcont);
		}

void		PmergeMe::setData(std::string numbers)
		{
			size_t	pos;

			pos = numbers.find_first_not_of(" ");
			while (pos != std::string::npos)
			{

