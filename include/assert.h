#ifndef __ASSERT_H__
#define __ASSERT_H__

#define assert(EX)  ((EX)?((void)0):__assert("EX", __FILE__, __LINE__))
#define nop_assert(EX) ((void)0)

#endif /* !__ASSERT_H__ */
