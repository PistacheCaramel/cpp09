#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <list>
# include <iostream>

class	RPN
{
	private:
			std::list<int>	_res;
	public:
					RPN(void);
					RPN( RPN&);
					~RPN(void);
		RPN&		operator=( RPN const &src);
		std::list<int>	getRes(void) const;
		int			setRes(std::string arg);
		void			printRes(void);
};

std::ostream &	operator<<(std::ostream & o, RPN const & i);
#endif

