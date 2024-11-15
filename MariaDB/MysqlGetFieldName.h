
#ifndef Extensions_Maria_MysqlGetFieldName_h
#define Extensions_Maria_MysqlGetFieldName_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace MariaDB {


class MysqlGetFieldName : public Extensions::ExtensionMethod
{
public:
	MysqlGetFieldName()
	: ExtensionMethod(0, "mysql_get_field_name", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("field_index", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();
			int param_field_index = (*it++).value().toInt();

			MYSQL_RES *myResult = mMariaDBResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
			}

			std::string my_result;
			if ( myResult->fields[param_field_index].name ) {
				my_result = std::string(myResult->fields[param_field_index].name);
			}

			*result = Runtime::StringType(my_result);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
