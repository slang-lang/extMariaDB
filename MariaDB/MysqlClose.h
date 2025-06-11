
#ifndef Extensions_Maria_MysqlClose_h
#define Extensions_Maria_MysqlClose_h


// Library include

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace MariaDB {


class MysqlClose: public Extensions::ExtensionMethod
{
public:
	MysqlClose()
	: ExtensionMethod(0, "mysql_close", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		MYSQL *myConn = mMariaDBConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		mysql_close(myConn);

		*result = Runtime::Int32Type(0);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
