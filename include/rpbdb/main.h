#ifndef RPBDB_MAIN
	#define RPBDB_MAIN

	/****************
	*  Includes  *
	****************/

	#include "BaseStandardInclude.h"

	char* RPbdb_version();
	int RPbdb_versionMajor();
	int RPbdb_versionMinor();
	int RPbdb_versionPatch();
	char* RPbdb_versionData(	int*						major,
							int*						minor, 
							int*						patch );

#endif