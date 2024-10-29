#ifndef __CM_LIB_ASSERT_H__
#define __CM_LIB_ASSERT_H__

#ifdef __cplusplus
extern "C"
{
#endif
int * ASSERT_FAIL(const char * msg, const char *filename , int line);
#ifdef __cplusplus
}
#endif


#ifdef  NDEBUG
#define ASSERT(expr)           ( (void)(0))
#else
#define ASSERT(expr)	(void)((expr)?1:(*ASSERT_FAIL(#expr,__FILE__,__LINE__) = 0)) 
#endif

#endif

