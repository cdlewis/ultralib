#ifndef __ASSERT_H__
#define __ASSERT_H__

#define assert(EX)  ((EX)?((void)0):__assert("EX", __FILE__, __LINE__))

#endif /* !__ASSERT_H__ */
