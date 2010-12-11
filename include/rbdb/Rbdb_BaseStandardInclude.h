
//	Rbdb Universal Standard Include: included by every Rbdb base type.

#ifndef RBDB_BASE_STANDARD_INCLUDE
	#define RBDB_BASE_STANDARD_INCLUDE
	
	//	calloc and malloc
	#include <stdlib.h>

	//	BDB Types
	#include <db.h>

	//	Rbdb Types
	#include "Rbdb_Types.h"

	//	Rbdb Constants
	#include "Rbdb_Constants.h"
	
	//	Error handling
	#include "Rbdb_ErrorController.h"
	#include "Rbdb_ErrorController_internal.h"
	#include "Rbdb_Error.h"
	#include "Rbdb_Error_internal.h"

#endif