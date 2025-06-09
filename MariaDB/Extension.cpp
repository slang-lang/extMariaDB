
// Header
#include "Extension.h"

// Library includes

// Project includes
#include "MysqlAffectedRows.h"
#include "MysqlClose.h"
#include "MysqlDataSeek.h"
#include "MysqlErrno.h"
#include "MysqlError.h"
#include "MysqlFetchRow.h"
#include "MysqlFieldCount.h"
#include "MysqlFieldSeek.h"
#include "MysqlFieldTell.h"
#include "MysqlFreeResult.h"
#include "MysqlGetClientInfo.h"
#include "MysqlGetFieldName.h"
#include "MysqlGetFieldValue.h"
#include "MysqlInfo.h"
#include "MysqlInit.h"
#include "MysqlNextResult.h"
#include "MysqlNumFields.h"
#include "MysqlNumRows.h"
#include "MysqlPing.h"
#include "MysqlQuery.h"
#include "MysqlRealConnect.h"
#include "MysqlRealEscapeString.h"
#include "MysqlRowCount.h"
#include "MysqlRowSeek.h"
#include "MysqlRowTell.h"
#include "MysqlSelectDB.h"
#include "MysqlStat.h"
#include "MysqlStoreResult.h"
#include "MysqlUseResult.h"

// Namespace declarations


namespace MariaDB {


Extension::Extension()
: AExtension( "extMariaDB", "0.5.1" )
{
	mMariaDBConnections[0] = mysql_init( nullptr );

	/* get user name for current connection */
	const char *version;
	mariadb_get_infov(mMariaDBConnections[0], MARIADB_CLIENT_VERSION, (void *)&version);

	mName = "extMariaDB (using libMariaDB " + std::string( version ) + ")";
}

void Extension::initialize( Slang::Extensions::ExtensionNamespace* /*scope*/ )
{
	// nothing to do here
}

void Extension::provideMethods( Slang::Extensions::ExtensionMethods& methods )
{
	assert( methods.empty() );

	methods.push_back( new MariaDB::MysqlAffectedRows() );
	methods.push_back( new MariaDB::MysqlClose() );
	methods.push_back( new MariaDB::MysqlDataSeek() );
	methods.push_back( new MariaDB::MysqlErrno() );
	methods.push_back( new MariaDB::MysqlError() );
	methods.push_back( new MariaDB::MysqlFetchRow() );
	methods.push_back( new MariaDB::MysqlFieldCount() );
	methods.push_back( new MariaDB::MysqlFieldSeek() );
	methods.push_back( new MariaDB::MysqlFieldTell() );
	methods.push_back( new MariaDB::MysqlFreeResult() );
	methods.push_back( new MariaDB::MysqlGetClientInfo() );
	methods.push_back( new MariaDB::MysqlGetFieldName() );
	methods.push_back( new MariaDB::MysqlGetFieldValueByIndex() );
	methods.push_back( new MariaDB::MysqlGetFieldValueByName() );
	methods.push_back( new MariaDB::MysqlInfo() );
	methods.push_back( new MariaDB::MysqlInit() );
	methods.push_back( new MariaDB::MysqlNextResult() );
	methods.push_back( new MariaDB::MysqlNumFields() );
	methods.push_back( new MariaDB::MysqlNumRows() );
	methods.push_back( new MariaDB::MysqlPing() );
	methods.push_back( new MariaDB::MysqlQuery() );
	methods.push_back( new MariaDB::MysqlRealConnect() );
	methods.push_back( new MariaDB::MysqlRealEscapeString() );
	methods.push_back( new MariaDB::MysqlRowCount() );
	methods.push_back( new MariaDB::MysqlRowSeek() );
	methods.push_back( new MariaDB::MysqlRowTell() );
	methods.push_back( new MariaDB::MysqlSelectDB() );
	methods.push_back( new MariaDB::MysqlStat() );
	methods.push_back( new MariaDB::MysqlStoreResult() );
	methods.push_back( new MariaDB::MysqlUseResult() );
}


}


extern "C" Slang::Extensions::AExtension* factory( void ) {
	return dynamic_cast<Slang::Extensions::AExtension*>( new MariaDB::Extension() );
}

