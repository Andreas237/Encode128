/**
 This module tests the encryption algorithms:
    * Lightweight Encryption Algorithm
    * Left
*/


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "mycrypt.h"



int main(int argc, char** argv){

  uint16_t start_state16 = 0xACE1u;                   //given by wiki
  uint64_t start_state64 =  0x02AFE3Du;               //actual Schraeder ID
  LFSR * crypted;

  crypted = lfsr16b(start_state16);
  printf("16-bit seed: %" PRIu64 "\n", start_state16);
  printf("Rounds: %" PRId8 "\n", crypted->period);
  printf("16-bit out: %" PRId8 "\n", crypted->lfsr16);


  crypted = lfsr64b(start_state64);
  printf("64-bit seed: %" PRIu64 "\n", start_state64);
  printf("Rounds: %" PRId8 "\n", crypted->period);
  printf("64-bit out: %" PRId8 "\n", crypted->lfsr64);


  return 0;
}// end main
