/*
 *		Rbdb
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_main.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
																Version Info
*******************************************************************************************************************************************************************************************/

/************
*  version  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_version.html
char* Rbdb_version()	{
	
	return db_version(	NULL,
						NULL,
						NULL	);
}

/*****************
*  versionMajor  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_version.html
int Rbdb_versionMajor()	{
	
	int		major	=	0;
	
	db_version(	& major,
				NULL,
				NULL	);	
	
	return major;
}

/*****************
*  versionMinor  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_version.html
int Rbdb_versionMinor()	{
	
	int		minor	=	0;
	
	db_version(	NULL,
				& minor,
				NULL );	
	
	return minor;
}

/*****************
*  versionPatch  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_version.html
int Rbdb_versionPatch()	{
	
	int		patch	=	0;
	
	db_version(	NULL, 
				NULL, 
				& patch );	
	
	return patch;
}

/****************
*  versionData  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_version.html
char* Rbdb_versionData(	int*						major,
						int*						minor, 
						int*						patch )	{
	
	return db_version( major, minor, patch );	
}