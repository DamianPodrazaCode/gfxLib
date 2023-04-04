#include "drvSSD1963.h"

#define ABS(X)                 	( (X) > 0 ? (X) : -(X) )
//#define ABS(X)               	{ int a = X >> 31; X = (( X ^ a ) - a); }
#define SWAP(a, b) 			   	{ int32_t t = a; a = b; b = t; }
//#define SWAP(a, b) 		   		{ a ^= b; b ^= a; a ^= b; }
//#define SWAP(a, b) 		   		{ a -= b; b += a; a = b - a; }
#define SGN(x)			       	( (x > 0) ? 1 : ( (x < 0) ? -1 : 0) )
#define MIN(a,b) 		       	( ((a)<(b)) ? (a) : (b) )
#define MAX(a,b) 		       	( ((a)>(b)) ? (a) : (b) )
