#ifndef RPBDB_LOCK_INTERNAL
	#define RPBDB_LOCK_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		RPbdb_Lock_internal_lockMode(							RPbdb_Lock* lock );
void RPbdb_Lock_internal_freeFromRuntimeStorage(	RPbdb_Lock** lock );


#endif