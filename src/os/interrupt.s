#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"
#include "PR/os_version.h"
#include "threadasm.h"

.text
.set noreorder
LEAF(__osDisableInt)
    mfc0    t0, C0_SR
    and     t1, t0, ~SR_IE
    mtc0    t1, C0_SR
    andi    v0, t0, SR_IE
    nop
    jr      ra
     nop
END(__osDisableInt)

LEAF(__osRestoreInt)
    mfc0    t0, C0_SR
    or      t0, t0, a0
    mtc0    t0, C0_SR
    nop
    nop
    jr      ra
     nop
END(__osRestoreInt)
