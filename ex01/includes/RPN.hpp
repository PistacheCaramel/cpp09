#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <vector>
# include <iostream>

class	RPN
{
	private:
			std::vector<int>	_res;
	public:
					RPN(void);
					RPN( RPN&);
					~RPN(void);
		RPN&		operator=( RPN &src);
		std::vector<int>	getRes(void);
		void			setRes(std::string arg);
		void			printRes(void);
};

std::ostream &	operator<<(std::ostream & o, RPN const & i);
#endif

