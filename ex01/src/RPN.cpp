#include "RPN.hpp"

	RPN::RPN(void) {}

	RPN::~RPN(void) {}

	RPN::RPN( RPN& copy)
	{
		*this = copy;
	}

RPN&	RPN::operator=( RPN  &src)
	{
		if (this == &src)
			return (*this);
		_res = src.getRes();
		return (*this);
	}

std::vector<int>	RPN::getRes()
			{
				return (_res);
			}

void	RPN::setRes(std::string arg)
	{
		size_t 	pos;
		int	on;

		pos = arg.find_first_not_of(" ");
		if (pos == std::string::npos || isdigit(arg[pos]) == 0)
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		_res.push_back(arg[pos] - 48);
		pos++;
		while (pos != std::string::npos && arg[pos] != 0)
		{
			pos = arg.find_first_not_of(" ", pos);
			if (arg[pos] == '+' || arg[pos] == '-' || arg[pos] == '/' || arg[pos] == '*')
			{
				if (_res.size() < 2)
				{
					std::cerr << "Error" << std::endl;
					return ;
				}
				if (arg[pos] == '+')
					on = *(_res.end() - 1) + *(_res.end() - 2);
				if (arg[pos] == '-')
					on = *(_res.end() - 2) - *(_res.end() - 1);
				if (arg[pos] == '*')
					on = *(_res.end() - 1) * *(_res.end() - 2);
				if (arg[pos] == '/')
				{
					if (*(_res.end() - 1) == 0)
					{
						std::cerr << "Error" << std::endl;
						return ;
					}	
					on = *(_res.end() - 2) / *(_res.end() - 1);
				}
				_res.pop_back();
				_res.pop_back();
				_res.push_back(on);

			}
			else
			{
				_res.push_back(arg[pos] - 48);
			}
			pos++;
		}
	}
	
void	RPN::printRes(void)
	{
		std::vector<int>::iterator it;

		it = _res.begin();
		while (it != _res.end())
		{
			std::cout << *it << " ";
			it++;
		}
		std::cout << std::endl;
	}
