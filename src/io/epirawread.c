#include "PRinternal/piint.h"
#include "PR/ultraerror.h"




extern void __assert(const char *, const char *, int);
#define force_assert(EX)  ((EX)?((void)0):__assert("EX", __FILE__, __LINE__))
















// Adjust line numbers to match assert
#if BUILD_VERSION < VERSION_J
#line 28
#endif

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register u32 stat;
    register u32 domain;

#ifdef _DEBUG
    if (devAddr & 0x3) {
        __osError(ERR_OSPIRAWREADIO, 1, devAddr);
        return -1;
    }
#endif
    force_assert(data != NULL);

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}

static const int pad[] = {0, 0, 0};
