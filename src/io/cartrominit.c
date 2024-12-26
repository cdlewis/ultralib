#include "PRinternal/macros.h"
#include "PR/os_version.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PRinternal/piint.h"

OSPiHandle __CartRomHandle ALIGNED(0x8);

OSPiHandle* osCartRomInit(void) {
    u32 value = 0;
    u32 saveMask;
    static int first = 1;
    u32 stat;

    __osPiGetAccess();

    if (!first) {
        __osPiRelAccess();
        return &__CartRomHandle;
    }

    first = 0;
    __CartRomHandle.type = DEVICE_TYPE_CART;
    __CartRomHandle.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR2);
    __CartRomHandle.domain = PI_DOMAIN1;
    __CartRomHandle.speed = 0;

    bzero(&__CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    WAIT_ON_IOBUSY(stat);

    IO_WRITE(PI_BSD_DOM1_LAT_REG, 0xFF);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, 0);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, 3);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, 0xFF);

    value = IO_READ(__CartRomHandle.baseAddress);
    __CartRomHandle.latency = value & 0xFF;
    __CartRomHandle.pulse = (value >> 8) & 0xFF;
    __CartRomHandle.pageSize = (value >> 0x10) & 0xF;
    __CartRomHandle.relDuration = (value >> 0x14) & 0xF;

    IO_WRITE(PI_BSD_DOM1_LAT_REG, __CartRomHandle.latency);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, __CartRomHandle.pageSize);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, __CartRomHandle.relDuration);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, __CartRomHandle.pulse);
    
    __osCurrentHandle[__CartRomHandle.domain]->type = __CartRomHandle.type;
    __osCurrentHandle[__CartRomHandle.domain]->latency = __CartRomHandle.latency;
    __osCurrentHandle[__CartRomHandle.domain]->pageSize = __CartRomHandle.pageSize;
    __osCurrentHandle[__CartRomHandle.domain]->relDuration = __CartRomHandle.relDuration;
    __osCurrentHandle[__CartRomHandle.domain]->pulse = __CartRomHandle.pulse;

    saveMask = __osDisableInt();
    __CartRomHandle.next = __osPiTable;
    __osPiTable = &__CartRomHandle;
    __osRestoreInt(saveMask);
    __osPiRelAccess();

    return &__CartRomHandle;
}
