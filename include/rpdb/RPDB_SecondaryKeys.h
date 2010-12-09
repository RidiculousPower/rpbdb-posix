/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::Rbdb_DBT => Rbdb_SecondaryKeys
 *
 *
 */

#ifndef Rbdb_SECONDARY_KEYS
	#define Rbdb_SECONDARY_KEYS

	#include "Rbdb_BaseStandardInclude.h"

	#include <string.h>

	/****************
	*  Prototypes  *
	****************/
	
	Rbdb_SecondaryKeys*						Rbdb_SecondaryKeys_new(			Rbdb_Record*	parent_record );

	void							Rbdb_SecondaryKeys_free(	Rbdb_SecondaryKeys** key );
	Rbdb_Record* Rbdb_SecondaryKeys_parentRecord(	Rbdb_DatabaseRecordSettingsController* key );

	void Rbdb_SecondaryKeys_addSecondaryKey(	Rbdb_SecondaryKeys*	keys,
	 											Rbdb_Key*				key );
	Rbdb_Key* Rbdb_SecondaryKeys_secondaryKeyForIndex(	Rbdb_SecondaryKeys*	keys,
															int						index );
	void Rbdb_SecondaryKeys_addRawSecondaryKey(	Rbdb_SecondaryKeys*	keys,
	 												void*					raw_key,
	 												uint32_t				key_size );
	void* Rbdb_SecondaryKeys_rawSecondaryKeyForIndex(	Rbdb_SecondaryKeys*	keys,
														int						index );

#endif

