#ifndef RBDB_MAIN
	#define RBDB_MAIN

	/****************
	*  Includes  *
	****************/

	#include "Rbdb_BaseStandardInclude.h"

	char* Rbdb_version();
	int Rbdb_versionMajor();
	int Rbdb_versionMinor();
	int Rbdb_versionPatch();
	char* Rbdb_versionData(	int*						major,
							int*						minor, 
							int*						patch );

#endif