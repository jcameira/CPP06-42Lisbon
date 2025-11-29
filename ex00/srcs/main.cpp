#include <ScalarConverter.hpp>
#include <iostream>

int main( int argc, char **argv )
{
    if ( argc != 2 )
    {
        std::cerr << "Usage: ./scalar_converter <literal>\n";
        return ( 1 );
    }

    try
    {
        ScalarConverter::convert( argv[ 1 ] );
    }
    catch ( const ScalarConverter::ErrorException &e )
    {
        std::cerr << e.what() << std::endl;
        return ( 1 );
    }

    return ( 0 );
}