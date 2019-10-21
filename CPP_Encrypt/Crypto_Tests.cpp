#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hrtimer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
 #include <cryptopp/lea.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>

/*
        About: run the AES encryption on the same block for a set amount of time.

        Examples:
            Crypto++ CBC Mode is the template for this program: https://cryptopp.com/wiki/CBC
            Crypto++ Benchmark for the while loop https://cryptopp.com/wiki/Benchmarks#Sample_Program
*/



















// 1 hour
// const double runTimeInSeconds = 60 * 60 ;
const double runTimeInSeconds = 6;



















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



















// CBC run mode
// doesn't work for our purposes, but saving since the benchmark code is useful.
std::string decryptLEA(const EncryptionParameters &enp);
EncryptionParameters encryptLEA(std::string plain);
EncryptionParameters encryptAES(std::string plain);
std::string decryptAES(const EncryptionParameters &enp);
void Print(const std::string&, const std::string&);



















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



















// Encrypt AES as in the first half of this https://cryptopp.com/wiki/CBC
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
        std::cout << "Encrypt AES" << std::endl;
        std::cout << "plain text: " << plain << std::endl;

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
            std::cout << "Decrypt AES" << std::endl;
           CBC_Mode< AES >::Decryption d;
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

}// end std::string decryptAES(const EncryptionParameters &enp)



















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



















// https://www.cryptopp.com/wiki/LEA
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
