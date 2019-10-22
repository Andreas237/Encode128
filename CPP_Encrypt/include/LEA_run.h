#pragma once

#include <cryptopp/lea.h>
#include <cryptopp/osrng.h>             // needed by AutoSeededRandomPoolS
#include <cryptopp/modes.h>             // needed by CBC_Mode< LEA >::Decryption
#include "encryption_parameters.h"




// CBC run mode
std::string decryptLEA(const EncryptionParameters &enp);
EncryptionParameters encryptLEA(std::string plain);
void Print(const std::string&, const std::string&);



















// Moved from Crypto_Tests.cpp
EncryptionParameters encryptLEA(std::string plain){

    using namespace CryptoPP;

    SecByteBlock key(LEA::DEFAULT_KEYLENGTH);
    SecByteBlock iv(LEA::BLOCKSIZE);

    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string cipher, encoded, recovered;

    /*********************************\
    \*********************************/

    try
    {
        std::cout << "Encrypt LEA" << std::endl;
       std::cout << "plain text: " << plain << std::endl;

       CBC_Mode< LEA >::Encryption e;
       e.SetKeyWithIV(key, key.size(), iv);

       // The StreamTransformationFilter adds padding
       //  as required. ECB and CBC Mode must be padded
       //  to the block size of the cipher.
       StringSource s(plain, true,
          new StreamTransformationFilter(e,
             new StringSink(cipher)
          ) // StreamTransformationFilter
       ); // StringSource
       Print("cipher text after one round", cipher);

   }//end try
    catch(const CryptoPP::Exception& e){
       std::cerr << e.what() << std::endl;
       exit(1);
   }//end catch(const CryptoPP::Exception& e)



    return EncryptionParameters(key, iv, cipher);

}//end EncryptionParameters encryptLEA(std::string plain)



















// Do the decryption of a ciphertext given its key and IV
std::string decryptLEA(const EncryptionParameters &enp){
        using namespace CryptoPP;

        SecByteBlock key = enp.getKey();
        SecByteBlock iv = enp.getIv();
        std::string cipher = enp.getCipherText();

        std::string recovered;

        try
        {
            std::cout << "Decrypt LEA" << std::endl;
           CBC_Mode< LEA >::Decryption d;
           d.SetKeyWithIV(key, key.size(), iv);

           // The StreamTransformationFilter removes
           //  padding as required.
           StringSource s(cipher, true,
              new StreamTransformationFilter(d,
                 new StringSink(recovered)
              ) // StreamTransformationFilter
           ); // StringSource

           std::cout << "recovered text after one decrypt: " << recovered << std::endl;
        }
        catch(const CryptoPP::Exception& e){
           std::cerr << e.what() << std::endl;
           exit(1);
       }//end catch(const CryptoPP::Exception& e)

       return recovered;

}// end std::string decryptLEA(const EncryptionParameters &enp)
