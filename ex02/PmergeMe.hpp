#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <deque>
# include <string>

class	PmergeMe
{
	private:
			std::list<int>	_lcont;
			std::deque<int>	_dcont;
	public:
					PmergeMe(void);
					PmergeMe(const  PmergeMe&);
					~PmergeMe(void);
		PmergeMe&		operator=( PmergeMe const &src);
		std::deque<int>		getDcont(void) const;
		std::list<int>		getLcont(void) const;
		void			setData(std::string numbers);
};

#endif

