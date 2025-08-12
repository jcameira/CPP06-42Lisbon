#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
#include <string>
#include <iostream>
#include <stdint.h>


typedef struct Data
{
	std::string	name;
	size_t		age;
	Data		*next;
}				Data;

class Serializer
{
	public:
		Serializer();
		Serializer( const Serializer &src );

		~Serializer();

		Serializer &operator=( const Serializer &src );

		uintptr_t serialize( Data *ptr );
		Data *deserialize( uintptr_t raw );

};

#endif