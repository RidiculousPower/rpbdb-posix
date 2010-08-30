/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_SecondaryKeys
 *
 *
 */

#ifndef RPDB_SECONDARY_KEYS
	#define RPDB_SECONDARY_KEYS

	#include "RPDB_BaseStandardInclude.h"

	#include <string.h>

	/****************
	*  Prototypes  *
	****************/
	
	RPDB_SecondaryKeys*						RPDB_SecondaryKeys_new(			RPDB_Record*	parent_record );

	void							RPDB_SecondaryKeys_free(	RPDB_SecondaryKeys** key );
	RPDB_Record* RPDB_SecondaryKeys_parentRecord(	RPDB_DatabaseRecordSettingsController* key );

	void RPDB_SecondaryKeys_addSecondaryKey(	RPDB_SecondaryKeys*	keys,
	 											RPDB_Key*				key );
	RPDB_Key* RPDB_SecondaryKeys_secondaryKeyForIndex(	RPDB_SecondaryKeys*	keys,
															int						index );
	void RPDB_SecondaryKeys_addRawSecondaryKey(	RPDB_SecondaryKeys*	keys,
	 												void*					raw_key,
	 												uint32_t				key_size );
	void* RPDB_SecondaryKeys_rawSecondaryKeyForIndex(	RPDB_SecondaryKeys*	keys,
														int						index );

#endif

