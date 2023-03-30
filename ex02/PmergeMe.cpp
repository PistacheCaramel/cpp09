/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:30:06 by ybendavi          #+#    #+#             */
/*   Updated: 2023/03/30 19:28:06 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		PmergeMe::setDatav(std::string numbers)
		{
			size_t		pos;
			unsigned long int	current;

			pos = numbers.find_first_not_of(" ");
			while (pos != std::string::npos)
			{
				current = atoi(numbers.substr(pos, numbers.find_first_not_of("0123456789", pos) + 1).c_str());
				if (current > INT_MAX)
					return (1);
				_vcont.push_back(current);
				pos = numbers.find_first_not_of("0123456789", pos);
				if (pos != std::string::npos)
					pos = numbers.find_first_not_of(" ", pos);
			}
			return (0);
		}

void		PmergeMe::setDatad(std::string numbers)
		{
			size_t		pos;
			long int	current;

			pos = numbers.find_first_not_of(" ");
			while (pos != std::string::npos)
			{
				current = atoi(numbers.substr(pos, numbers.find_first_not_of("0123456789", pos) + 1).c_str());
				_dcont.push_back(current);
				pos = numbers.find_first_not_of("0123456789", pos);
				if (pos != std::string::npos)
					pos = numbers.find_first_not_of(" ", pos);
			}
		}

void		PmergeMe::printNumbers(long int time_of_vector, long int time_of_deque) const
		{
			std::vector<int>::const_iterator	it;
			std::deque<int>::const_iterator	ite;
			
			it = _vsorted.begin();
			std::cout << "VECTOR:" << time_of_vector << "usec" << std::endl;
			while (it != _vsorted.end())
			{
				if (it != _vsorted.end() && it + 1 != _vsorted.end() && *it > *(it + 1))
					std::cout << "ERROR:" << std::endl;
				std::cout << *it << " ";
				it++;
			}
			std::cout << std::endl;
			std::cout << "DEQUE:" << time_of_deque << "usec" << std::endl;
			ite = _dsorted.begin();
			while (ite != _dsorted.end())
			{
				if (ite != _dsorted.end() && ite + 1 != _dsorted.end() && *ite > *(ite + 1))
					std::cout << "ERROR:" << std::endl;
				std::cout << *ite << " ";
				ite++;
			}
			std::cout << std::endl;

		}

//		vector		//

void		PmergeMe::vfusion(std::vector<std::pair<int,int> >::iterator it, size_t size, size_t middle)
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


			

void		PmergeMe::vfusionSort(std::vector<std::pair<int,int> >::iterator it, size_t size)
{
		if (size < 2)
			return;
		vfusionSort(it, size / 2);
		vfusionSort(it + size / 2, size - size / 2);
		vfusion(it, size, size / 2);
}

void		PmergeMe::vpushPair(void)
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

void		PmergeMe::vsearchPlace(int to_place, std::vector<int>::iterator begin, std::vector<int>::iterator pl)
		{
			int	distance;

			distance = std::distance(begin, pl);

			
			if (begin == pl || pl == _vsorted.end() - 1)
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
						vsearchPlace(to_place, begin, pl - distance / 2);
					else
						vsearchPlace(to_place, begin, pl - distance);
				}
				else if (to_place == *pl)
					_vsorted.insert(pl, to_place);
				else
				{
					if (distance >= 2)
						vsearchPlace(to_place, pl, pl + distance / 2);
					else
						vsearchPlace(to_place, pl, pl + distance);
				}
			}
		}

void		PmergeMe::vbinarySearch(void)
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
					vsearchPlace(end->second, _vsorted.begin(), _vsorted.begin() + std::distance(_vsorted.begin(), pl) / 2);
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
				{
					if (_vpair.size() == 1)
					{
						pl = find(_vsorted.begin(), _vsorted.end(), _vpair.begin()->first);
						vsearchPlace(_vpair.begin()->second, _vsorted.begin(), _vsorted.begin() + std::distance(_vsorted.begin(), pl) / 2);
					}
					break;
				}
			}
		}

int		PmergeMe::vsortChecker(void) const
		{
			std::vector<int>::const_iterator	it;
			
			it = _vcont.begin();
			while (it != _vcont.end())
			{
				if (it != _vcont.end() && it + 1 != _vcont.end() && *it > *(it + 1))
					return (1);
				it++;
			}
			return (0);
		}

void		PmergeMe::vmergeInsertsort(void)
		{
			size_t	pos;
			int	pend;

			pos = 0;
			if (_vcont.size() == 1 || vsortChecker() == 0)
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
			vfusionSort(_vpair.begin(), _vpair.size());
			vpushPair();
			vbinarySearch();
			if (pend != -1)
				vsearchPlace(pend, _vsorted.begin(), _vsorted.begin() + std::distance(_vsorted.begin(), _vsorted.end() - 1) / 2);
		}

//		deque		//

void		PmergeMe::dfusion(std::deque<std::pair<int,int> >::iterator it, size_t size, size_t middle)
		{
			std::deque<std::pair<int, int> > sorted;
			std::deque<std::pair<int,int> >::iterator begin;
			std::deque<std::pair<int,int> >::iterator middleit;
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


			

void		PmergeMe::dfusionSort(std::deque<std::pair<int,int> >::iterator it, size_t size)
{
		if (size < 2)
			return;
		dfusionSort(it, size / 2);
		dfusionSort(it + size / 2, size - size / 2);
		dfusion(it, size, size / 2);
}

void		PmergeMe::dpushPair(void)
		{
			std::deque<std::pair<int, int> >::iterator	it;

			it = _dpair.begin();
			_dsorted.push_back(it->second);
			while (it != _dpair.end())
			{
				_dsorted.push_back(it->first);
				it++;
			}
		}

void		PmergeMe::dsearchPlace(int to_place, std::deque<int>::iterator begin, std::deque<int>::iterator pl)
		{
			int	distance;

			distance = std::distance(begin, pl);

			
			if (begin == pl || pl == _dsorted.end() - 1)
			{
				if (to_place < *pl)
					_dsorted.insert(pl, to_place);
				else
					_dsorted.insert(pl + 1, to_place);
			}
			else
			{
				if (to_place < *pl)
				{
					if (distance >= 2)
						dsearchPlace(to_place, begin, pl - distance / 2);
					else
						dsearchPlace(to_place, begin, pl - distance);
				}
				else if (to_place == *pl)
					_dsorted.insert(pl, to_place);
				else
				{
					if (distance >= 2)
						dsearchPlace(to_place, pl, pl + distance / 2);
					else
						dsearchPlace(to_place, pl, pl + distance);
				}
			}
		}

void		PmergeMe::dbinarySearch(void)
		{
			int	power;
			size_t	g_size;
			std::deque<std::pair<int, int> >::iterator	begin;
			std::deque<std::pair<int, int> >::iterator	end;
			std::deque<int>::iterator	pl;

			power = 2;
			g_size = 2;
			_dpair.erase(_dpair.begin());
			begin = _dpair.begin();
			end = begin + g_size - 1;
			while (1)
			{
				while (end < _dpair.end() && end != begin)
				{
					pl = find(_dsorted.begin(), _dsorted.end(), end->first);
					dsearchPlace(end->second, _dsorted.begin(), _dsorted.begin() + std::distance(_dsorted.begin(), pl) / 2);
					end--;
				}
				if (g_size + std::distance(_dpair.begin(), begin) < _dpair.size())
				{
					begin += g_size;
					power *= 2;
					g_size = power - g_size;
					end = begin + g_size - 1;
				}
				else
				{
					
					if (_dpair.size() == 1)
					{
						pl = find(_dsorted.begin(), _dsorted.end(), _dpair.begin()->first);
						dsearchPlace(_dpair.begin()->second, _dsorted.begin(), _dsorted.begin() + std::distance(_dsorted.begin(), pl) / 2);
					}
					break;
				}
			}
		}

int		PmergeMe::dsortChecker(void) const
		{
			std::deque<int>::const_iterator	it;
			
			it = _dcont.begin();
			while (it != _dcont.end())
			{
				if (it != _dcont.end() && it + 1 != _dcont.end() && *it > *(it + 1))
					return (1);
				it++;
			}
			return (0);
		}

void		PmergeMe::dmergeInsertsort(void)
		{
			size_t	pos;
			int	pend;

			pos = 0;
			if (_dcont.size() == 1 || dsortChecker() == 0)
			{
				_dsorted = _dcont;
				return ;
			}
			while (pos < _dcont.size() - 1)
			{
				if (_dcont[pos] > _dcont[pos + 1])
					_dpair.push_back(std::make_pair(_dcont[pos], _dcont[pos + 1]));
				else
					_dpair.push_back(std::make_pair(_dcont[pos + 1], _dcont[pos]));
				pos = pos + 2;
			}
			if (pos == _dcont.size() - 1)
				pend = _dcont[pos];
			else
				pend = -1;
			dfusionSort(_dpair.begin(), _dpair.size());
			dpushPair();
			dbinarySearch();
			if (pend != -1)
				dsearchPlace(pend, _dsorted.begin(), _dsorted.begin() + std::distance(_dsorted.begin(), _dsorted.end()) / 2);
		}

void		PmergeMe::formatedPrint(long int time_of_vector, long int time_of_deque) const
		{
			std::vector<int>::const_iterator	it;

			it = _vcont.begin();
			std::cout << "Before: ";
			while (it != _vcont.end())
			{
				std::cout << " " << *it;
				it++;
			}
			std::cout << std::endl << "After: ";
			it = _vsorted.begin();
			while (it != _vsorted.end())
			{
				std::cout << " " << *it;
				it++;
			}
			std::cout << std::endl << "Time to process a range of  " << _vcont.size() << " elements with std::vector : " << time_of_vector << " us" << std::endl;
			std::cout << "Time to process a range of  " << _vcont.size() << " elements with std::deque : " << time_of_deque << " us" << std::endl;
		}
