// One of the imports was causing a minor mismatch. Not sure why but just inline the things
// we actually need to power this function.
typedef unsigned long u32;
typedef signed long s32;
typedef volatile unsigned long vu32;
#define PI_STATUS_IO_BUSY (1 << 1)
#define PI_BASE_REG 0x04600000
#define PI_STATUS_REG (PI_BASE_REG + 0x10)
#define IO_READ(addr) (*(vu32 *)PHYS_TO_K1(addr))
#define WAIT_ON_IOBUSY(stat)                                    \
    {                                                           \
        stat = IO_READ(PI_STATUS_REG);                          \
        while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) \
            stat = IO_READ(PI_STATUS_REG);                      \
    }                                                           \
    (void)0
#define PI_STATUS_DMA_BUSY (1 << 0)
#define PHYS_TO_K1(x) ((u32)(x) | 0xA0000000)
extern void __assert(const char *exp, const char *filename, int line);
extern void *osRomBase;

// We want 4 bytes of padding on rodata
static const int pad = 0;

































s32 __osPiRawReadIo(u32 devAddr, u32 *data)
{
    register u32 stat;

    (data != 0) ? ((void)0) : __assert("EX", __FILE__, __LINE__);

    WAIT_ON_IOBUSY(stat);
    *data = IO_READ((u32)osRomBase | devAddr);

    return 0;
}
