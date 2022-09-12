#include <assert.h>
#include <iostream>

#define ASSERT(A,B) { if(!A){ std::cout << B << std::endl; assert(A);} }