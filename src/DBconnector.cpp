/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#include "DBconnector.h"

#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "sqlite3x.hpp"
using namespace sqlite3x;

// --------------------------------------------------------------------------------------
#define CATCHDBERRORS																	\
	catch(exception &ex)																\
	{																					\
		cout << "Database error: " << ex.what() << endl;	                            \
	}																					\
// --------------------------------------------------------------------------------------

DBconnector::DBconnector(const string& databasePath)
:
m_databasePath(databasePath)
{
    //ctor
}

DBconnector::~DBconnector()
{
    //dtor
}
