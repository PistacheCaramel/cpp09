/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:32:31 by ybendavi          #+#    #+#             */
/*   Updated: 2023/03/31 15:05:49 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <list>
# include <iostream>
# include <limits.h>

class	RPN
{
	private:
			std::list<long long int>	_res;
	public:
					RPN(void);
					RPN( RPN&);
					~RPN(void);
		RPN&		operator=( RPN const &src);
		std::list<long long int>	getRes(void) const;
		int			setRes(std::string arg);
		void			printRes(void);
};

std::ostream &	operator<<(std::ostream & o, RPN const & i);
#endif

