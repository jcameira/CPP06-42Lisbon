#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
#include <string>
#include <iostream>
#include <stdint.h>
#include <Data.h>

class Serializer
{
	private:
		Serializer();
		Serializer( const Serializer &src );

		~Serializer();
		
		Serializer &operator=( const Serializer &src );
		
	public:
		static uintptr_t serialize( Data *ptr );
		static Data *deserialize( uintptr_t raw );

};

#endif