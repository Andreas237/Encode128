#include <iostream>

#include "LEA_run.h"
#include "AES_run.h"





/*
        About: run the AES encryption on the same block for a set amount of time.

        Examples:
            Crypto++ CBC Mode is the template for this program: https://cryptopp.com/wiki/CBC
            Crypto++ Benchmark for the while loop https://cryptopp.com/wiki/Benchmarks#Sample_Program
*/
int main(int argc, char* argv[]) {


    int resultCode;
    std::string plain = "02AFE3Du";
    std::string recovered;


    EncryptionParameters  enp = encryptLEA(plain);
    recovered.append(decryptLEA(enp));


    enp = encryptAES(plain);
    recovered.append(decryptAES(enp));


    std::cout << std::endl;
    std::cout << std::endl;


    std::cout << "AES::DEFAULT_KEYLENGTH = " << CryptoPP::AES::DEFAULT_KEYLENGTH << std::endl;
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    std::cout << sizeof(key) << std::endl;


    std::cout << std::endl;
    std::cout << std::endl;

    // make the key 32 bytes in length
    std::string myKey = plain;
    while(myKey.length() < 32 )
        myKey.push_back('0');
        std::cout << myKey << std::endl;
    std::cout << "my new key: " << myKey <<"\t strlen(myKey) = " << myKey.length() << std::endl;


}// end main
