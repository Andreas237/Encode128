#include <cstdint>
#include <iomanip>
#include <string>
#include "encryption_parameters.h"









EncryptionParameters encryptLFSR16(std::string&);
EncryptionParameters encryptLFSR64(std::string);
EncryptionParameters encryptLFSR128(std::string);
void lfsr64(int&);
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

















/**
 function:  EncryptionParameters encryptLFSR16(std::string &plain)
 input:     a hexadecimal represented as a string
 output:    EncryptionParameters object with empty iv and key,
            one round of LFSR
 purpose:   Encrypt a string using 16-bit LFSR
 method:
            Convert the input string to an input integer
            Perform the shift and XOR on the input integer
            return  EncryptionParameters of the
*/
EncryptionParameters encryptLFSR16(std::string &plain){

    // empty since naive doesn't require these
    CryptoPP::SecByteBlock key, iv;

    // Convert hex-string to corresponding integer
    int hexint = std::stoi(plain,0,16);
    int bit;
    std::cout << "Int before rotation: " << std::hex << hexint;
    lfsr64(hexint);
    std::cout << "\tInt after rotation: " << std::hex << hexint << std::endl;




    //TODO:
    /*
        1) Convert string to integer, show as hex to verify
            Note: int cut short to whatever the size is (uint_fast16_t,uint_fast64_t)
        2) Copy+paste LFSR 16-bit from wiki Galois
        3) Understand the shifts described in wiki
    */



    return EncryptionParameters(key,iv,std::to_string(hexint));
}//end EncryptionParameters encryptLFSR16(std::string plain)



















/**
    function: void lfsr64(int& input)
    input:
    output:
    purpose:
    method:

*/
void lfsr64(int& input){

    // 64 bit LFSR
    int bit = ((input>>0) ^ (input>>1) ^ (input>>3) ^ (input>>4) );
    input = (input >> 1) | (bit << 63);
}//void lfsr16(int& input)
