#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <stdlib.h>
# include <utility>

class	PmergeMe
{
	private:
			std::vector<int>	_lcont;
			std::vector<int>	_lsorted;
			std::vector<int>	_pending;
			std::vector<std::pair<int, int> >	_lpair;
			std::deque<int>	_dcont;
	public:
					PmergeMe(void);
					PmergeMe(const  PmergeMe&);
					~PmergeMe(void);
		PmergeMe&		operator=( PmergeMe const &src);
		std::deque<int>					getDcont(void) const;
		std::vector<int>					getLcont(void) const;
		void						setData(std::string numbers);
		void						printNumbers(void) const;
		void						sortList(void);
		void						mergeInsertsort(void);
		void						fusion(std::vector<std::pair<int,int> >::iterator it, size_t size, size_t middle);

		void						fusionSort(std::vector<std::pair<int,int> >::iterator it, size_t size);
		void						binarySearch(void);
		void						pushPair(void);
};

int	group_size(int g_size, int power);

#endif

