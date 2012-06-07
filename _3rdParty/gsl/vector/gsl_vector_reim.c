//#include <config.h>
//Seems to be the only thing required from config.h here
#define RETURN_IF_NULL(x) if (!x) { return ; }
#include <stdlib.h>
#include <gsl/gsl_vector.h>

#include "view.h"

#define BASE_GSL_COMPLEX_LONG
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX_LONG

#define BASE_GSL_COMPLEX
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX

#define BASE_GSL_COMPLEX_FLOAT
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX_FLOAT

#define USE_QUALIFIER
#define QUALIFIER const

#define BASE_GSL_COMPLEX_LONG
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX_LONG

#define BASE_GSL_COMPLEX
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX

#define BASE_GSL_COMPLEX_FLOAT
#include "../templates_on.h"
#include "gsl_vector_reim_source.c"
#include "../templates_off.h"
#undef  BASE_GSL_COMPLEX_FLOAT
