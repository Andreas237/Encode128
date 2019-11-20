/**
This class is meant to save and transmit encryption parameters, such as key and
initialization vector (IV), between sender and receiver.
*/

#pragma once
#include <cryptopp/secblock.h>
#include <cryptopp/hex.h>       // for print function....


// struct pointing to key, iv and cipher text
class EncryptionParameters {
    public:
        CryptoPP::SecByteBlock * k;
        CryptoPP::SecByteBlock * iv;
        std::string ciperText;


        EncryptionParameters(){
            k           = new CryptoPP::SecByteBlock();
            iv          = new CryptoPP::SecByteBlock();
        }//end EncryptionParameters


        // allocate vars and fill class members
        EncryptionParameters(CryptoPP::SecByteBlock &inK, CryptoPP::SecByteBlock &inIv, const std::string &inStr){
            setKey(inK);
            setIv(inIv);
            setCipherText(inStr);
        }// end


        std::string getCipherText(void) const { return ciperText;}
        void setCipherText(const std::string &inStr){ ciperText.append(inStr);}


        CryptoPP::SecByteBlock getKey(void) const { return *k;}
        void setKey(const CryptoPP::SecByteBlock &inK){ k = new CryptoPP::SecByteBlock(inK);}


        CryptoPP::SecByteBlock getIv(void) const { return *iv;}
        void setIv(const CryptoPP::SecByteBlock &inIv){ iv = new CryptoPP::SecByteBlock(inIv);}


};//end class EncryptionParameters



















// https://www.cryptopp.com/wiki/LEA
// print function called by LEA and AES
void Print(const std::string& label, const std::string& val){
    using namespace CryptoPP;
   std::string encoded;
   StringSource(val, true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource

   std::cout << label << ": " << encoded << std::endl;
}//end using namespace CryptoPP;
