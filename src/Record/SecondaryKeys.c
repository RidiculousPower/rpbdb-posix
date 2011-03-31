/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_SecondaryKeys
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "SecondaryKeys.h"

#include "Key.h"
#include "Data.h"
#include "DBT_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_SecondaryKeysUnused* RPbdb_SecondaryKeys_new( RPbdb_Record* parent_record )	{

	RPbdb_SecondaryKeysUnused*	secondary_keys	=	calloc( 1, sizeof( RPbdb_SecondaryKeysUnused ) );
	
	secondary_keys->parent_record	=	parent_record;
	
	//	Alloc the DBT
	secondary_keys->wrapped_bdb_dbt	=	calloc( 1, sizeof( DBT ) );

	return secondary_keys;
}

/***************************
*  free  *
***************************/
void RPbdb_SecondaryKeys_free(	RPbdb_SecondaryKeysUnused** keys )	{

	free( *keys );
	*keys	=	NULL;
}

/***************************************
*  parentRecord  *
***************************************/
RPbdb_Record* RPbdb_SecondaryKeys_parentRecord(	RPbdb_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/*****************
*  keyData  *
*****************/

void RPbdb_SecondaryKeys_addSecondaryKey(	RPbdb_SecondaryKeysUnused*	keys,
																					RPbdb_Key*				key )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	RPbdb_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( RPbdb_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( RPbdb_Key* ) );

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

RPbdb_Key* RPbdb_SecondaryKeys_secondaryKeyForIndex(	RPbdb_SecondaryKeysUnused*	keys,
														int						index )	{

	return (RPbdb_Key*) (RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT( NULL, & ( (DBT*) keys->wrapped_bdb_dbt->data )[ index ] );
}


/*****************
*  keyData  *
*****************/

void RPbdb_SecondaryKeys_addRawSecondaryKey(	RPbdb_SecondaryKeysUnused*	keys,
 												void*					raw_key,
 												uint32_t				key_size )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	RPbdb_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( RPbdb_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( RPbdb_Key* ) );

//			free memory space pointed to by the existing pointer
		free( keys->key_pointers_array );
	}
	
	//	store our new pointer
	keys->key_pointers_array	=	key_pointers_array;

	//	allocate space for DBT at pointer location
	keys->key_pointers_array[ keys->key_count ]	=	RPbdb_Key_new( NULL );

	//	store data in new DBT
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->data = raw_key;
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->size = key_size;

	//	increment key count for added key
	keys->key_count++;
}

/******************
*  setKeyData  *
******************/

void* RPbdb_SecondaryKeys_rawSecondaryKeyForIndex(	RPbdb_SecondaryKeysUnused*	keys,
													int						index )	{

	return ( (DBT*)( keys->wrapped_bdb_dbt->data ) )[ index ].data;
}




