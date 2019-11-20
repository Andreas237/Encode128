#include <cstdint>
#include <iomanip>
#include <string>
#include "encryption_parameters.h"









EncryptionParameters encryptLFSR16(std::string&);
EncryptionParameters encryptLFSR64(std::string);
EncryptionParameters encryptLFSR128(std::string);
void padder(std::string&,int);
// Sizes used for padding the input in bits to corresponding bytes
enum lfsr_size {size16b=2, size64b=8, size128b=16};



















// alphabet: string showing the next letter in line
// plain: plaintext to be incremented
// current: current letter to be incrememented
// Pad to target BYTE size
void padder(std::string &plain, int size){
    while( plain.size() < size)
        plain.append("0");
} //end void mapper(const std::string &alphabet, std::string &plain, int current)



















// Encrypt a string using 16-bit LFSR
EncryptionParameters encryptLFSR16(std::string &plain){
    CryptoPP::SecByteBlock key, iv;   // empty since naive doesn't require these

    //TODO:
    /*
        1) Convert string to integer, show as hex to verify
            Note: int cut short to whatever the size is (uint_fast16_t,uint_fast64_t)
        2) Copy+paste LFSR 16-bit from wiki Galois
        3) Understand the shifts described in wiki
    */



    return EncryptionParameters(key,iv,plain);
}//end EncryptionParameters encryptLFSR16(std::string plain)
