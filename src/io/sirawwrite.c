#include "PR/os_internal.h"
#include "PRinternal/siint.h"
#include "assert.h"









































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

const char sirawwrite_rodata_0000[] = "EX";
const char sirawwrite_rodata_0004[] = {'s', 'i', 'r', 'a', 'w', 'w', 'r', 'i', 't', 'e', '.', 'c'};

s32 __osSiRawWriteIo(u32 devAddr, u32 data) {
    ((devAddr & 0x3) == 0)?((void)0):__assert(sirawwrite_rodata_0000, sirawwrite_rodata_0004, __LINE__);

    if (__osSiDeviceBusy()) {
        return -1;
    }

    IO_WRITE(devAddr, data);
    return 0;
}
