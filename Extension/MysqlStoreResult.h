
#ifndef Extensions_Maria_MysqlStoreResult_h
#define Extensions_Maria_MysqlStoreResult_h


// Library include

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace MariaDB {


class MysqlStoreResult: public Extensions::ExtensionMethod
{
public:
	MysqlStoreResult()
	: ExtensionMethod(0, "mysql_store_result", Designtime::Int32Type::TYPENAME)
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

		MYSQL_RES *myResult = mysql_store_result(myConn);
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result handle: " + std::to_string(param_handle));
		}

		int my_result = ++mNumMariaDBResults;
		mMariaDBResults.insert(std::make_pair(my_result, myResult));

		*result = Runtime::Int32Type(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
