#include <assert.h>
#include <iostream>

/**
*	@brief ASSERT check MACRO
*	
*	@param A Condition to check with the assert
*	@param B Message to display if assert triggers
*/
#ifdef DEBUG
#define ASSERT(A,B) { if(!A){ std::cout << B << std::endl; assert(A);} }
#else
#define ASSERT(A,B)
#endif
