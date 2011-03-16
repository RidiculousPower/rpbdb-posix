#ifndef RBDB_DBT_INTERNAL
	#define RBDB_DBT_INTERNAL
	
	#include <cerialize.h>
	
	Rbdb_DBT* Rbdb_DBT_internal_newFromBDBDBT(	Rbdb_Record*	parent_record, 
																							DBT*			bdb_dbt );

void Rbdb_DBT_internal_verifyKeyDataTyping(	Rbdb_DBT*												dbt,
																						CerializeType	type	);

#endif