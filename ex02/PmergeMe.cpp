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
			_vcont = src.getLcont();
			_dcont = src.getDcont();
			return (*this);
		}

std::deque<int>	PmergeMe::getDcont(void) const
		{
			return (_dcont);
		}

std::vector<int>	PmergeMe::getLcont(void) const
		{
			return (_vcont);
		}

void		PmergeMe::setData(std::string numbers)
		{
			size_t		pos;
			long int	current;

			pos = numbers.find_first_not_of(" ");
			while (pos != std::string::npos)
			{
				current = atoi(numbers.substr(pos, numbers.find_first_not_of("0123456789", pos) + 1).c_str());
				_vcont.push_back(current);
				_dcont.push_back(current);
				pos = numbers.find_first_not_of("0123456789", pos);
				if (pos != std::string::npos)
					pos = numbers.find_first_not_of(" ", pos);
			}
		}

void		PmergeMe::printNumbers(void) const
		{
			std::vector<int>::const_iterator	it;
			
			it = _vsorted.begin();
			while (it != _vsorted.end())
			{
				if (it != _vsorted.end() && it + 1 != _vsorted.end() && *it > *(it + 1))
					std::cout << "ERROR:" << std::endl;
				std::cout << *it << " ";
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

void		PmergeMe::pushPair(void)
		{
			std::vector<std::pair<int, int> >::iterator	it;

			it = _vpair.begin();
			_vsorted.push_back(it->second);
			while (it != _vpair.end())
			{
				_vsorted.push_back(it->first);
				it++;
			}
		}

void		PmergeMe::searchPlace(int to_place, std::vector<int>::iterator begin, std::vector<int>::iterator pl)
		{
			int	distance;

			distance = std::distance(begin, pl);

			
			if (begin == pl)
			{
				if (to_place < *pl)
					_vsorted.insert(pl, to_place);
				else
					_vsorted.insert(pl + 1, to_place);
			}
			else
			{
				if (to_place < *pl)
				{
					if (distance >= 2)
						searchPlace(to_place, begin, pl - distance / 2);
					else
						searchPlace(to_place, begin, pl - distance);
				}
				else
				{
					if (distance >= 2)
						searchPlace(to_place, pl, pl + distance / 2);
					else
						searchPlace(to_place, pl, pl + distance);
				}
			}
		}

void		PmergeMe::binarySearch(void)
		{
			int	power;
			size_t	g_size;
			std::vector<std::pair<int, int> >::iterator	begin;
			std::vector<std::pair<int, int> >::iterator	end;
			std::vector<int>::iterator	pl;

			power = 2;
			g_size = 2;
			_vpair.erase(_vpair.begin());
			begin = _vpair.begin();
			end = begin + g_size - 1;
			while (1)
			{
				while (end < _vpair.end() && end != begin)
				{
					pl = find(_vsorted.begin(), _vsorted.end(), end->first);
					searchPlace(end->second, _vsorted.begin(), _vsorted.begin() + std::distance(_vsorted.begin(), pl) / 2);
					end--;
				}
				if (g_size + std::distance(_vpair.begin(), begin) < _vpair.size())
				{
					begin += g_size;
					power *= 2;
					g_size = power - g_size;
					end = begin + g_size - 1;
				}
				else
					break;
			}
		}
			
void		PmergeMe::mergeInsertsort(void)
		{
			size_t	pos;
			int	pend;

			pos = 0;
			if (_vcont.size() == 1)
			{
				_vsorted = _vcont;
				return ;
			}
			while (pos < _vcont.size() - 1)
			{
				if (_vcont[pos] > _vcont[pos + 1])
					_vpair.push_back(std::make_pair(_vcont[pos], _vcont[pos + 1]));
				else
					_vpair.push_back(std::make_pair(_vcont[pos + 1], _vcont[pos]));
				pos = pos + 2;
			}
			if (pos == _vcont.size() - 1)
				pend = _vcont[pos];
			else
				pend = -1;
			fusionSort(_vpair.begin(), _vpair.size());
			pushPair();
			binarySearch();
			if (pend != -1)
			{
				std::cout << "here" << std::endl;
				searchPlace(pend, _vsorted.begin(), _vsorted.begin() + std::distance(_vsorted.begin(), _vsorted.end()) / 2);
			}
		}
