#include "PmergeMe.hpp"

		PmergeMe::PmergeMe(void)
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

std::vector<int>	PmergeMe::getLcont(void) const
		{
			return (_lcont);
		}

void		PmergeMe::setData(std::string numbers)
		{
			size_t		pos;
			long int	current;

			pos = numbers.find_first_not_of(" ");
			while (pos != std::string::npos)
			{
				current = atoi(numbers.substr(pos, numbers.find_first_not_of("0123456789", pos) + 1).c_str());
				_lcont.push_back(current);
				_dcont.push_back(current);
				pos = numbers.find_first_not_of("0123456789", pos);
				if (pos != std::string::npos)
					pos = numbers.find_first_not_of(" ", pos);
			}
		}

void		PmergeMe::printNumbers(void) const
		{
			std::vector<std::pair<int, int> >::const_iterator	it;
			
			it = _lpair.begin();
			while (it != _lpair.end())
			{
				std::cout << it->first << " ";
				it++;
			}
			std::cout << std::endl;
		}

void		PmergeMe::fusion(std::vector<std::pair<int,int> >::iterator it, size_t size, size_t middle)
		{
			std::vector<std::pair<int, int> > sorted;
			std::vector<std::pair<int,int> >::iterator begin;
			std::vector<std::pair<int,int> >::iterator middleit;
			size_t					size2;

			begin = it;
			middleit = it + middle;
			size2 = 0;
			while (size2 < size)
			{
				if (middleit != it + size && begin->first > middleit->first)
				{
					sorted.push_back(*middleit);
					middleit++;
				}
				else if (middleit == it + size)
				{
					sorted.push_back(*begin);
					begin++;
				}
				else if (begin == it + middle)
				{
					sorted.push_back(*middleit);
					middleit++;
				}
				else
				{
					sorted.push_back(*begin);
					begin++;;
				}
				size2 = sorted.size() - 1;
			}
			begin = it;
			middleit = sorted.begin();
			while (begin != it + size)
			{
				std::cout << "valeur a changer:" << begin->first << "    valeur remplace:" << middleit->first << std::endl;
				*begin = *middleit;
				begin++;
				middleit++;
			}
		}


			

void		PmergeMe::fusionSort(std::vector<std::pair<int,int> >::iterator it, size_t size)
{
		if (size < 2)
			return;
		fusionSort(it, size / 2);
		fusionSort(it + size / 2, size - size / 2);
		fusion(it, size, size / 2);
}

void		PmergeMe::mergeInsertsort(void)
		{
			size_t	pos;
			int	pend;

			pos = 0;
			while (pos < _lcont.size() - 1)
			{
				if (_lcont[pos] > _lcont[pos + 1])
					_lpair.push_back(std::make_pair(_lcont[pos], _lcont[pos + 1]));
				else
					_lpair.push_back(std::make_pair(_lcont[pos + 1], _lcont[pos]));
				pos = pos + 2;
			}
//ne pas oublier de gerer le cas ou yen a un qui est tout seul dans son goupe
			fusionSort(_lpair.begin(), _lpair.size());
		}

std::vector<std::pair<int,int> >::iterator PmergeMe::increase_iterator(size_t inc, std::vector<std::pair<int,int> >::iterator it)
					{
						size_t	i;

						i = 0;
						while (i < inc)
						{
							it++;
							i++;
						}

						return (it);
					}
