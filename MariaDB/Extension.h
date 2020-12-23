
#ifndef MariaDB_Extension_h
#define MariaDB_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace MariaDB {


class Extension : public Slang::Extensions::AExtension
{
public:
	Extension();

public:
	void initialize( Slang::IScope* scope );
	void provideMethods( Slang::Extensions::ExtensionMethods& methods );
};


}



#endif

