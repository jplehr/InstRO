/** \mainpage
 * InstRO is an instrumentation framework initially based on the ROSE compiler infrastructure.
 * It is in development at TU Darmstadt, Germany.
 * Development started at RWTH Aachen, Germany.
 *
 * define INSTRUMENT_COMPILER_INSTANTIATED_TEMPLATES compiler flag to use InstRO experimental
 * instrumentation of templated c++ code.
 * This depends on ROSE and its capability of handling template sources.
 * 
 * Its goal is to provide a powerful tool for performance analysis of C/C++ and Fortran codes.
 * 
 *
 */

// InstRO includes
#ifndef DEFAULT_INSTRO
#define USING_ROSE
#define USING_LLVM
#endif

#include "instro/interface.h"

#ifdef USING_ROSE
#include "instro/roseInstRO.h"
#endif

#ifdef USING_LLVM
#include "instro/llvmInstRO.h"
#endif 