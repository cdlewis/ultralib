#ifndef __ASSERT_H__
#define __ASSERT_H__

#ifdef NDEBUG
#undef assert
#define assert(EX) ((void)0)
#else
extern void __assert(const char *, const char *, int);
#define assert(EX)  ((EX)?((void)0):__assert("EX", __FILE__, __LINE__))
#endif /* NDEBUG */

#define force_assert(EX)  ((EX)?((void)0):__assert("EX", __FILE__, __LINE__))

#endif /* !__ASSERT_H__ */
