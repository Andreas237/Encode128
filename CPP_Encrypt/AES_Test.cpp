#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hrtimer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <iostream>

/*
        About: run the AES encryption on the same block for a set amount of time.

        Examples:
            Crypto++ CBC Mode is the template for this program: https://cryptopp.com/wiki/CBC
            Crypto++ Benchmark for the while loop https://cryptopp.com/wiki/Benchmarks#Sample_Program
*/


// 1 hour
// const double runTimeInSeconds = 60 * 60 ;
const double runTimeInSeconds = 6;





int main(int argc, char* argv[]) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock( key, key.size() );

    byte iv[ AES::BLOCKSIZE ];
    prng.GenerateBlock( iv, sizeof(iv) );

    std::string plain = "02AFE3Du";
    // string plain = "CBC Mode Test";
    std::string cipher, encoded, recovered;



    /*********************************\
    \*********************************/
/** TODO: replicate in while loop for 1 hour
    try
    {
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
*/
    // Example from https://cryptopp.com/wiki/Benchmarks#Sample_Program
    double elapsedTimeInSeconds;
    ThreadUserTimer timer;
    timer.StartTimer();
    int encryptionCount = 0;
    //TODO: change from CBC mode to CTR or other stream mode...

    // initialize first round of cipher
    CBC_Mode< AES >::Encryption e;
    e.SetKeyWithIV( key, key.size(), iv );

    try
    {
        std::cout << "plain text: " << plain << std::endl;



        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource ss( plain, true,
            new StreamTransformationFilter( e,
                new StringSink( cipher )
            ) // StreamTransformationFilter
        ); // StringSource
        encryptionCount++;
    }
    catch( const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }


    do {
        try
        {
            plain = cipher;
            StringSource ss( plain, true,
                new StreamTransformationFilter( e,
                    new StringSink( cipher )
                ) // StreamTransformationFilter
            ); // StringSource


            encryptionCount++;
        }// end try
        catch( const CryptoPP::Exception& e )
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }//end catch
        elapsedTimeInSeconds = timer.ElapsedTimeAsDouble();
        std::cout << "Current elapsed time: " << elapsedTimeInSeconds << std::endl;
    }while( elapsedTimeInSeconds < runTimeInSeconds);
    /*********************************\
    \*********************************/

    std::cout << "Ran encryption " << encryptionCount << "iterations." << std::endl;


    // Pretty print cipher text
    /*
    StringSource ss( cipher, true,
        new CryptoPP::HexEncoder(
            new StringSink( encoded )
        ) // HexEncoder
    ); // StringSource
    std::cout << "cipher text: " << encoded << std::endl;
    */
    /*********************************\
    \*********************************/

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV( key, key.size(), iv );
        while(encryptionCount){
            std::cout << "Running decryption " << encryptionCount << "more iterations." << std::endl;

            // The StreamTransformationFilter removes
            //  padding as required.
            StringSource ss( cipher, true,
                new StreamTransformationFilter( d,
                    new StringSink( recovered )
                ) // StreamTransformationFilter
            ); // StringSource
            cipher = recovered;
            encryptionCount--;
        }//end while

        std::cout << "recovered text: " << recovered << std::endl;
    }//end try
    catch( const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}// end main
