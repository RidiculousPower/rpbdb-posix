/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_SecondaryKeys
 *
 *
 */

#ifndef RPBDB_SECONDARY_KEYS
	#define RPBDB_SECONDARY_KEYS

	#include "BaseStandardInclude.h"

	#include <string.h>

	/****************
	*  Prototypes  *
	****************/
	
	RPbdb_SecondaryKeysUnused*						RPbdb_SecondaryKeys_new(			RPbdb_Record*	parent_record );

	void							RPbdb_SecondaryKeys_free(	RPbdb_SecondaryKeysUnused** key );
	RPbdb_Record* RPbdb_SecondaryKeys_parentRecord(	RPbdb_DatabaseRecordSettingsController* key );

	void RPbdb_SecondaryKeys_addSecondaryKey(	RPbdb_SecondaryKeysUnused*	keys,
	 											RPbdb_Key*				key );
	RPbdb_Key* RPbdb_SecondaryKeys_secondaryKeyForIndex(	RPbdb_SecondaryKeysUnused*	keys,
															int						index );
	void RPbdb_SecondaryKeys_addRawSecondaryKey(	RPbdb_SecondaryKeysUnused*	keys,
	 												void*					raw_key,
	 												uint32_t				key_size );
	void* RPbdb_SecondaryKeys_rawSecondaryKeyForIndex(	RPbdb_SecondaryKeysUnused*	keys,
														int						index );

#endif

