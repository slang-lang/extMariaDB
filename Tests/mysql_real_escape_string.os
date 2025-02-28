#!/usr/local/bin/slang

public void Main(int argc, string argv) modify {
	int handle = mysql_init();
	writeln("mysql_init() = " + handle);

	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "root", "ts_parking");
	writeln("mysql_real_connect()");

	string query = "SELECT * FROM parking_zones";
	writeln("mysql_real_escape_string(" + handle + ", \"" + query + "\") = " + mysql_real_escape_string(handle, query));

	mysql_close(handle);

	writeln("done.");
}
