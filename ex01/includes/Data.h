#ifndef DATA_HPP
# define DATA_HPP

# include <string>

typedef struct Data
{
	std::string	name;
	size_t		age;
	Data		*next;
}			    Data;

#endif