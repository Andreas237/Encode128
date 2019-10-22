#pragma once

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>             // needed by AutoSeededRandomPool
#include <cryptopp/modes.h>             // needed by CBC_Mode< AES >::Decryption
#include "encryption_parameters.h"



// CBC run mode
EncryptionParameters encryptAES(std::string plain);
std::string decryptAES(const EncryptionParameters &enp);



















// Encrypt AES as in the first half of this https://cryptopp.com/wiki/CBC
// StreamTransformationFilter has a
EncryptionParameters encryptAES(std::string plain){

    using namespace CryptoPP;

    SecByteBlock key(AES::DEFAULT_KEYLENGTH); // 32 bytes
    SecByteBlock iv(AES::BLOCKSIZE);

    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string cipher, encoded, recovered;


    try
    {

        //std::cout << "Encrypt AES" << std::endl;
        //std::cout << "plain text: " << plain << std::endl;

        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV( key, key.size(), iv );






        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource ss( plain, true,
            new StreamTransformationFilter( e,
                new StringSink( cipher )
            ) // StreamTransformationFilter
        ); // StringSource


        // Attempt to encrypt a second round.
        // ERROR: incorrect padding.  First round padded, so this should work....
        // https://cryptopp.com/wiki/Advanced_Encryption_Standard#ECB_and_CBC_mode_remarks
        // StringSource(cipher, true, new StreamTransformationFilter(e, new StringSink(cipher), CryptoPP::BlockPaddingSchemeDef::NO_PADDING));

    }
    catch( const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return EncryptionParameters(key, iv, cipher);
}// end EncryptionParameters encryptAES(std::string plain)



















// Do the decryption of a ciphertext given its key and IV
std::string decryptAES(const EncryptionParameters &enp){
        using namespace CryptoPP;

        SecByteBlock key = enp.getKey();
        SecByteBlock iv = enp.getIv();
        std::string cipher = enp.getCipherText();

        std::string recovered;

        try
        {
           CBC_Mode< AES >::Decryption d;
           d.SetKeyWithIV(key, key.size(), iv);

           // The StreamTransformationFilter removes
           //  padding as required.
           StringSource s(cipher, true,
              new StreamTransformationFilter(d,
                 new StringSink(recovered)
              ) // StreamTransformationFilter
           ); // StringSource
           // std::cout << "recovered text after one decrypt: " << recovered << std::endl;
        }
        catch(const CryptoPP::Exception& e){
           std::cerr << e.what() << std::endl;
           exit(1);
       }//end catch(const CryptoPP::Exception& e)

       return recovered;

}// end std::string decryptAES(const EncryptionParameters &enp)
