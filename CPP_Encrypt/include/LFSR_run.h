#include <cstdint>
#include <iomanip>
#include <string>
#include "encryption_parameters.h"









void encryptLFSR(int&);
void lfsr64(int&);
void lfsr128(int&);
void padder(std::string&,int);



















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
// int encryptLFSR(int hexint){ operating on a single number until it's needed
void encryptLFSR(int & hexint){
    // empty since naive doesn't require these
    CryptoPP::SecByteBlock key, iv;


    std::cout << "Int before rotation: " << std::hex << hexint;
    lfsr128(hexint);
    std::cout << "\tInt after rotation: " << std::hex << hexint << std::endl;




    //TODO:
    /*
        1) Convert string to integer, show as hex to verify
            Note: int cut short to whatever the size is (uint_fast16_t,uint_fast64_t)
        2) Copy+paste LFSR 16-bit from wiki Galois
        3) Understand the shifts described in wiki
    */



    // return EncryptionParameters(key,iv,std::to_string(hexint));
}//end EncryptionParameters encryptLFSR16(std::string plain)



















/**
    function:   void lfsr64(int& input)
    input:      int input to shift and XOR
    output:     void
    purpose:    Perform bit shifting and XOR to accomplish one round of LFSR on
                a 64-bit number
    method:     Given the big-endian systems we're on the MSB is located in the
                byte with the lowest address. The taps are given in: https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
*/
void lfsr64(int& input){

    int bit = ((input>>0) ^ (input>>1) ^ (input>>3) ^ (input>>4) );
    input = (input >> 1) | (bit << 63);

}//void lfsr16(int& input)



















/**
    function:   void lfsr64(int& input)
    input:      int input to shift and XOR
    output:     void
    purpose:    Perform bit shifting and XOR to accomplish one round of LFSR on
                a 64-bit number
    method:     Given the big-endian systems we're on the MSB is located in the
                byte with the lowest address. The taps are given in: https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
*/
void lfsr128(int& input){

    int bit = ((input>>0) ^ (input>>2) ^ (input>>27) ^ (input>>29) );
    input = (input >> 1) | (bit << 127);

}//void lfsr128(int& input)
