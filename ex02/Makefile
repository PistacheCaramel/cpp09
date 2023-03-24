NAME	= PmergeMe

CXX		= c++

CXXFLAGS	= -Wall -Wextra -Werror -MMD -std=c++98 -g3

SRCS	= main.cpp PmergeMe.cpp
OBJS	= $(SRCS:.cpp=.o)

DEPS	= $(OBJS:.o=.d)

IFLAGS	= -I.

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ $^

%.o		:	%.cpp
			$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

clean	:
			$(RM) $(DEPS)
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY	:	all fclean clean re
