/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_SecondaryKeys
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_SecondaryKeys.h"

#include "Rbdb_Key.h"
#include "Rbdb_Data.h"
#include "Rbdb_DBT_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_SecondaryKeysUnused* Rbdb_SecondaryKeys_new( Rbdb_Record* parent_record )	{

	Rbdb_SecondaryKeysUnused*	secondary_keys	=	calloc( 1, sizeof( Rbdb_SecondaryKeysUnused ) );
	
	secondary_keys->parent_record	=	parent_record;
	
	//	Alloc the DBT
	secondary_keys->wrapped_bdb_dbt	=	calloc( 1, sizeof( DBT ) );

	return secondary_keys;
}

/***************************
*  free  *
***************************/
void Rbdb_SecondaryKeys_free(	Rbdb_SecondaryKeysUnused** keys )	{

	free( *keys );
	*keys	=	NULL;
}

/***************************************
*  parentRecord  *
***************************************/
Rbdb_Record* Rbdb_SecondaryKeys_parentRecord(	Rbdb_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/*****************
*  keyData  *
*****************/

void Rbdb_SecondaryKeys_addSecondaryKey(	Rbdb_SecondaryKeysUnused*	keys,
																					Rbdb_Key*				key )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	Rbdb_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( Rbdb_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( Rbdb_Key* ) );

//			free memory space pointed to by the existing pointer
		free( keys->key_pointers_array );
	}
	
	//	store our new pointer
	keys->key_pointers_array	=	key_pointers_array;

	//	store address of existing dbt
	keys->key_pointers_array[ keys->key_count ]	=	key;

	//	increment key count for added key
	keys->key_count++;
}

/******************
*  setKeyData  *
******************/

Rbdb_Key* Rbdb_SecondaryKeys_secondaryKeyForIndex(	Rbdb_SecondaryKeysUnused*	keys,
														int						index )	{

	return (Rbdb_Key*) (Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT( NULL, & ( (DBT*) keys->wrapped_bdb_dbt->data )[ index ] );
}


/*****************
*  keyData  *
*****************/

void Rbdb_SecondaryKeys_addRawSecondaryKey(	Rbdb_SecondaryKeysUnused*	keys,
 												void*					raw_key,
 												uint32_t				key_size )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	Rbdb_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( Rbdb_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( Rbdb_Key* ) );

//			free memory space pointed to by the existing pointer
		free( keys->key_pointers_array );
	}
	
	//	store our new pointer
	keys->key_pointers_array	=	key_pointers_array;

	//	allocate space for DBT at pointer location
	keys->key_pointers_array[ keys->key_count ]	=	Rbdb_Key_new( NULL );

	//	store data in new DBT
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->data = raw_key;
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->size = key_size;

	//	increment key count for added key
	keys->key_count++;
}

/******************
*  setKeyData  *
******************/

void* Rbdb_SecondaryKeys_rawSecondaryKeyForIndex(	Rbdb_SecondaryKeysUnused*	keys,
													int						index )	{

	return ( (DBT*)( keys->wrapped_bdb_dbt->data ) )[ index ].data;
}




