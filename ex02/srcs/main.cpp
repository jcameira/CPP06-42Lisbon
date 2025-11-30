#include <Base.hpp>
#include <A.hpp>
#include <B.hpp>
#include <C.hpp>

#include <cstdlib>
#include <cstdio>

static Base *generate( void )
{
	switch ( rand() % 3 ) {
	case 0:
		return ( new A() );
	case 1:
		return ( new B() );
	case 2:
		return ( new C() );
	default:
		std::cerr << "Error: Something went wrong with the random generator" << std::endl;
		return ( NULL );
	}
}

static void identify( Base *Test )
{
	if ( dynamic_cast<A *>( Test ) )
		std::cout << "A is the identified type" << std::endl;
	else if ( dynamic_cast<B *>( Test ) )
		std::cout << "B is the identified type" << std::endl;
	else if ( dynamic_cast<C *>( Test ) )
		std::cout << "C is the identified type" << std::endl;
	else
		std::cout << "unknown type" << std::endl;
}

static int i = 0;
static std::string classes[] = { "A", "B", "C" };

static void identify( Base &Test )
{
	while ( i < 3 ) {
		void *foo = NULL;
		Base &unused = ( Base & )foo;
		try {
			if ( i == 0 )
				unused = dynamic_cast<A &>( Test );
			else if ( i == 1 )
				unused = dynamic_cast<B &>( Test );
			else if ( i == 2 )
				unused = dynamic_cast<C &>( Test );
			else
				std::cout << "unknow type" << std::endl;
			( void )unused;
		}
		catch ( std::exception &e ) {
			i++;
			identify( Test );
			return;
		}
		std::cout << classes[ i ] << " is the identified type" << std::endl;
		i = 0;
		break;
	}
}

int main()
{
	srand( time( NULL ) );
	for ( int j = 0; j < 5; j++ ) {
		Base *Test = generate();
		Base &TestRef = *Test;
		if ( Test == NULL )
			return ( 1 );
		else {
			identify( Test );
			identify( TestRef );
			delete ( Test );

			std::cout << std::endl;
		}
	}
	return ( 0 );
}