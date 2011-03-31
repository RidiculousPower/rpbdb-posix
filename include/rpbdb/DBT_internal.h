#ifndef RPBDB_DBT_INTERNAL
	#define RPBDB_DBT_INTERNAL
	
	#include <cerialize.h>
	
	RPbdb_DBT* RPbdb_DBT_internal_newFromBDBDBT(	RPbdb_Record*	parent_record, 
																							DBT*			bdb_dbt );

void RPbdb_DBT_internal_verifyKeyDataTyping(	RPbdb_DBT*												dbt,
																						CerializeType	type	);

#endif