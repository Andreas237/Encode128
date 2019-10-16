// Implementation of LFSR
#include <stdint.h>            // For LFSR integer
#include <inttypes.h>
#include <stdlib.h>             // for rand, srand
#include <time.h>               // for seed value to rand









// not actually extern, just down the bottom
extern uint64_t byte_feedback[];









/**
return value containing the LFSR value and period
*/
typedef struct
{
  uint16_t lfsr16;
  uint64_t lfsr64;
  unsigned period;

} LFSR;









/**
Galois 16-bit LFSR Implementation per LFSR Wiki
https://en.wikipedia.org/wiki/Linear-feedback_shift_register
Stahnke's primitive 64-bit tap positions as used by the inner loop from
http://users.ece.cmu.edu/~koopman/lfsr/index.html
*/
//unsigned lfsr16b(uint16_t start_state)
LFSR * lfsr16b(uint16_t start_state)
{
    LFSR * out = malloc(sizeof(LFSR));

    // Seed random
    srand (time(NULL));
    // For the time being do 10 - 1050 iterations
    int rounds = rand() % 1050 + 10;


    uint16_t lfsr = start_state; /* Any nonzero start state will work. */
    unsigned period = 0;

    do
    {
#ifndef LEFT
        unsigned lsb = lfsr & 1u;  /* Get LSB (i.e., the output bit). */
        lfsr >>= 1;                /* Shift register */
        if (lsb)                   /* If the output bit is 1, */
            lfsr ^= 0xB400u;       /*  apply toggle mask. */
#else
        unsigned msb = (uint16_t) lfsr < 0;   /* Get MSB (i.e., the output bit). */
        lfsr <<= 1;                          /* Shift register */
        if (msb)                             /* If the output bit is 1, */
            lfsr ^= 0x002Du;                 /*  apply toggle mask. */
#endif
        ++period;
    }
    while (period < rounds);

    out->lfsr16 = lfsr;
    out->period = period;
    // return period;
    return out;
}// end unsigned lfsr16b(uint64_t start_state)









/**
Galois 16-bit LFSR Implementation per LFSR Wiki
https://en.wikipedia.org/wiki/Linear-feedback_shift_register
Stahnke's primitive 64-bit tap positions as used by the inner loop from
http://users.ece.cmu.edu/~koopman/lfsr/index.html
*/
//unsigned lfsr16b(uint16_t start_state)
LFSR * lfsr64b(uint16_t start_state)
{
    LFSR * out = malloc(sizeof(LFSR));

    // Seed random
    srand (time(NULL));
    // For the time being do 10 - 1050 iterations
    int rounds = rand() % 1050 + 10;


    uint64_t lfsr = start_state; /* Any nonzero start state will work. */
    unsigned period = 0;
//TODO: mod for 64 bit mask
    do
    {
#ifndef LEFT
        unsigned lsb = lfsr & 1u;  /* Get LSB (i.e., the output bit). */
        lfsr >>= 1;                /* Shift register */
        if (lsb)                   /* If the output bit is 1, */
            lfsr ^= 0xB400u;       /*  apply toggle mask. */
#else
        unsigned msb = (uint64_t) lfsr < 0;   /* Get MSB (i.e., the output bit). */
        lfsr <<= 1;                          /* Shift register */
        if (msb)                             /* If the output bit is 1, */
            lfsr ^= 0x002Du;                 /*  apply toggle mask. */
#endif
        ++period;
    }
    while (period < rounds);

    out->lfsr64 = lfsr;
    out->period = period;
    // return period;
    return out;
}// end unsigned lfsr16b(uint64_t start_state)









/**
Galois 64-bit LFSR Implementation based on LFSR wiki, also referencing
russm@git's implementation.

https://github.com/russm/lfsr64

Stahnke's primitive 64-bit tap positions as used by the inner loop from
http://users.ece.cmu.edu/~koopman/lfsr/index.html

*/
LFSR * lfsr64b_russ(uint64_t start_state)
{
    LFSR * out = malloc(sizeof(LFSR));

    // Seed random
    srand (time(NULL));
    // For the time being do 10 - 1050 iterations
    int rounds = rand() % 1050 + 10;


    uint64_t lfsr = start_state; /* Any nonzero start state will work. */
    unsigned period = 0;

    do
    {   // thanks https://github.com/russm/lfsr64/blob/master/lfsr64.c
        lfsr = (lfsr >> 8) ^ byte_feedback[lfsr & 0xff];
        ++period;
    }
    while (period < rounds);

    out->lfsr64 = lfsr;
    out->period = period;
    //return period;
    return out;
}// end unsigned lfsr64b_russ(uint64_t start_state)









// pre-computed feedback terms
uint64_t byte_feedback[256] = {
  0x0000000000000000, 0xc70000000000000b, 0x8e0000000000000d, 0x4900000000000006,
  0x1c00000000000001, 0xdb0000000000000a, 0x920000000000000c, 0x5500000000000007,
  0x3800000000000002, 0xff00000000000009, 0xb60000000000000f, 0x7100000000000004,
  0x2400000000000003, 0xe300000000000008, 0xaa0000000000000e, 0x6d00000000000005,
  0x7000000000000004, 0xb70000000000000f, 0xfe00000000000009, 0x3900000000000002,
  0x6c00000000000005, 0xab0000000000000e, 0xe200000000000008, 0x2500000000000003,
  0x4800000000000006, 0x8f0000000000000d, 0xc60000000000000b, 0x0100000000000000,
  0x5400000000000007, 0x930000000000000c, 0xda0000000000000a, 0x1d00000000000001,
  0xe000000000000008, 0x2700000000000003, 0x6e00000000000005, 0xa90000000000000e,
  0xfc00000000000009, 0x3b00000000000002, 0x7200000000000004, 0xb50000000000000f,
  0xd80000000000000a, 0x1f00000000000001, 0x5600000000000007, 0x910000000000000c,
  0xc40000000000000b, 0x0300000000000000, 0x4a00000000000006, 0x8d0000000000000d,
  0x900000000000000c, 0x5700000000000007, 0x1e00000000000001, 0xd90000000000000a,
  0x8c0000000000000d, 0x4b00000000000006, 0x0200000000000000, 0xc50000000000000b,
  0xa80000000000000e, 0x6f00000000000005, 0x2600000000000003, 0xe100000000000008,
  0xb40000000000000f, 0x7300000000000004, 0x3a00000000000002, 0xfd00000000000009,
  0xc00000000000000b, 0x0700000000000000, 0x4e00000000000006, 0x890000000000000d,
  0xdc0000000000000a, 0x1b00000000000001, 0x5200000000000007, 0x950000000000000c,
  0xf800000000000009, 0x3f00000000000002, 0x7600000000000004, 0xb10000000000000f,
  0xe400000000000008, 0x2300000000000003, 0x6a00000000000005, 0xad0000000000000e,
  0xb00000000000000f, 0x7700000000000004, 0x3e00000000000002, 0xf900000000000009,
  0xac0000000000000e, 0x6b00000000000005, 0x2200000000000003, 0xe500000000000008,
  0x880000000000000d, 0x4f00000000000006, 0x0600000000000000, 0xc10000000000000b,
  0x940000000000000c, 0x5300000000000007, 0x1a00000000000001, 0xdd0000000000000a,
  0x2000000000000003, 0xe700000000000008, 0xae0000000000000e, 0x6900000000000005,
  0x3c00000000000002, 0xfb00000000000009, 0xb20000000000000f, 0x7500000000000004,
  0x1800000000000001, 0xdf0000000000000a, 0x960000000000000c, 0x5100000000000007,
  0x0400000000000000, 0xc30000000000000b, 0x8a0000000000000d, 0x4d00000000000006,
  0x5000000000000007, 0x970000000000000c, 0xde0000000000000a, 0x1900000000000001,
  0x4c00000000000006, 0x8b0000000000000d, 0xc20000000000000b, 0x0500000000000000,
  0x6800000000000005, 0xaf0000000000000e, 0xe600000000000008, 0x2100000000000003,
  0x7400000000000004, 0xb30000000000000f, 0xfa00000000000009, 0x3d00000000000002,
  0x800000000000000d, 0x4700000000000006, 0x0e00000000000000, 0xc90000000000000b,
  0x9c0000000000000c, 0x5b00000000000007, 0x1200000000000001, 0xd50000000000000a,
  0xb80000000000000f, 0x7f00000000000004, 0x3600000000000002, 0xf100000000000009,
  0xa40000000000000e, 0x6300000000000005, 0x2a00000000000003, 0xed00000000000008,
  0xf000000000000009, 0x3700000000000002, 0x7e00000000000004, 0xb90000000000000f,
  0xec00000000000008, 0x2b00000000000003, 0x6200000000000005, 0xa50000000000000e,
  0xc80000000000000b, 0x0f00000000000000, 0x4600000000000006, 0x810000000000000d,
  0xd40000000000000a, 0x1300000000000001, 0x5a00000000000007, 0x9d0000000000000c,
  0x6000000000000005, 0xa70000000000000e, 0xee00000000000008, 0x2900000000000003,
  0x7c00000000000004, 0xbb0000000000000f, 0xf200000000000009, 0x3500000000000002,
  0x5800000000000007, 0x9f0000000000000c, 0xd60000000000000a, 0x1100000000000001,
  0x4400000000000006, 0x830000000000000d, 0xca0000000000000b, 0x0d00000000000000,
  0x1000000000000001, 0xd70000000000000a, 0x9e0000000000000c, 0x5900000000000007,
  0x0c00000000000000, 0xcb0000000000000b, 0x820000000000000d, 0x4500000000000006,
  0x2800000000000003, 0xef00000000000008, 0xa60000000000000e, 0x6100000000000005,
  0x3400000000000002, 0xf300000000000009, 0xba0000000000000f, 0x7d00000000000004,
  0x4000000000000006, 0x870000000000000d, 0xce0000000000000b, 0x0900000000000000,
  0x5c00000000000007, 0x9b0000000000000c, 0xd20000000000000a, 0x1500000000000001,
  0x7800000000000004, 0xbf0000000000000f, 0xf600000000000009, 0x3100000000000002,
  0x6400000000000005, 0xa30000000000000e, 0xea00000000000008, 0x2d00000000000003,
  0x3000000000000002, 0xf700000000000009, 0xbe0000000000000f, 0x7900000000000004,
  0x2c00000000000003, 0xeb00000000000008, 0xa20000000000000e, 0x6500000000000005,
  0x0800000000000000, 0xcf0000000000000b, 0x860000000000000d, 0x4100000000000006,
  0x1400000000000001, 0xd30000000000000a, 0x9a0000000000000c, 0x5d00000000000007,
  0xa00000000000000e, 0x6700000000000005, 0x2e00000000000003, 0xe900000000000008,
  0xbc0000000000000f, 0x7b00000000000004, 0x3200000000000002, 0xf500000000000009,
  0x980000000000000c, 0x5f00000000000007, 0x1600000000000001, 0xd10000000000000a,
  0x840000000000000d, 0x4300000000000006, 0x0a00000000000000, 0xcd0000000000000b,
  0xd00000000000000a, 0x1700000000000001, 0x5e00000000000007, 0x990000000000000c,
  0xcc0000000000000b, 0x0b00000000000000, 0x4200000000000006, 0x850000000000000d,
  0xe800000000000008, 0x2f00000000000003, 0x6600000000000005, 0xa10000000000000e,
  0xf400000000000009, 0x3300000000000002, 0x7a00000000000004, 0xbd0000000000000f,
};
