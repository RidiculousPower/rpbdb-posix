#ifndef RPDB_MAIN
	#define RPDB_MAIN

	/****************
	*  Includes  *
	****************/

	#include "RPDB_BaseStandardInclude.h"

	char* RPDB_version();
	int RPDB_versionMajor();
	int RPDB_versionMinor();
	int RPDB_versionPatch();
	char* RPDB_versionData(	int*						major,
							int*						minor, 
							int*						patch );

#endif