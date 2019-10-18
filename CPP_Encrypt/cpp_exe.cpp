#include <iostream>
#include <cryptopp/hex.h>


int main(void){

    CryptoPP::byte decoded[] = { 0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
    std::string encoded;

    CryptoPP::HexEncoder encoder;
    encoder.Put(decoded, sizeof(decoded));
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((CryptoPP::byte*)&encoded[0], encoded.size());
    }

    std::cout << encoded << std::endl;


    std::string key = "AndreasSlovacek11";
    std::cout << sizeof(key) << std::endl;

    return 0;



}// end main
