/**
 * \file error.h
 * \author Dong Wei
 *
 * Declaration of error handling functions.
 */

#ifndef __PASCAL_ERROR__
#define __PASCAL_ERROR__

extern int yyok;
extern int yyline;
/// Print Error message.
/**
  * The macro ERROR functions much the same as printf. The only difference
  * is that ERROR output to stderr rather than stdout.
  */
#define ERROR(n...) do { yyok = 0; fprintf(stderr, "%s:%d: error: ", file_in, yyline); \
		fprintf(stderr, n);} while (0);
#ifdef DEBUG
#define INFO(n...) do { printf(n); fflush(stdout);} while (0); 
#else
/// The stdout version of ERROR.
/**
  * The macro INFO is used for debugging. The debug information can
  * be turned off by turn off the debug switch.
  */
#define INFO(n...)
#endif

#endif
