
#ifndef Extensions_Maria_MysqlRowSeek_h
#define Extensions_Maria_MysqlRowSeek_h

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace MariaDB {


class MysqlRowSeek : public Extensions::ExtensionMethod
{
public:
	MysqlRowSeek()
	: ExtensionMethod(0, "mysql_row_seek", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("offset", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();
			long param_offset = (*it++).value().toInt();

			MYSQL_RES *myResult = mMariaDBResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid mysql result!");
			}

			*result = Runtime::IntegerObject(
				mysql_row_seek(myResult, (MYSQL_ROW_OFFSET)param_offset)
			);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
