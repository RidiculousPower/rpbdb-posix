
//	RPDB Universal Standard Include: included by every RPDB base type.

#ifndef RPDB_BASE_STANDARD_INCLUDE
	#define RPDB_BASE_STANDARD_INCLUDE
	
	//	calloc and malloc
	#include <stdlib.h>

	//	BDB Types
	#include <db.h>

	//	RPDB Types
	#include "RPDB_Types.h"

	//	RPDB Constants
	#include "RPDB_Constants.h"
	
	//	Error handling
	#include "RPDB_ErrorController.h"
	#include "RPDB_ErrorController_internal.h"
	#include "RPDB_Error.h"
	#include "RPDB_Error_internal.h"

#endif