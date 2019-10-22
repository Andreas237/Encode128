#include <iostream>
#include <cryptopp/hrtimer.h>
#include "LEA_run.h"
#include "AES_run.h"



void runAES(std::string);
void runAES_timed(std::string);
void runLEA(std::string);
void runLEA_timed(std::string);

/*
        About: run the AES encryption on the same block for a set amount of time.

        Examples:
            Crypto++ CBC Mode is the template for this program: https://cryptopp.com/wiki/CBC
            Crypto++ Benchmark for the while loop https://cryptopp.com/wiki/Benchmarks#Sample_Program
*/
int main(int argc, char* argv[]) {



    std::string plain = "02AFE3Du";


    /* encrypt and recover
    int resultCode;
    std::string recovered;
    EncryptionParameters  enp = encryptLEA(plain);
    recovered.append(decryptLEA(enp));
    */


    // runAES_timed(plain);


    runLEA_timed(plain);

}// end main



















// Run AES encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
void runAES(std::string plain){
    std::cout << "Running AES" << std::endl;
    EncryptionParameters  enp;
    do{
            enp = encryptAES(plain);
    }while(1);
}//end void runAES(std::string plain)



















// Run AES encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
// Benchmark bytes https://cryptopp.com/wiki/Benchmarks#Sample_Program
void runAES_timed(std::string plain){
    std::cout << "Running timed AES" << std::endl;
    const double runTimeInSeconds = 60*2;       // two minutes
    double elapsedTimeInSeconds;
    unsigned long i=0, blocks=1;

    CryptoPP::ThreadUserTimer timer;
    timer.StartTimer();

    EncryptionParameters  enp;
    do{
            enp = encryptAES(plain);
            elapsedTimeInSeconds = timer.ElapsedTimeAsDouble();
    }while(elapsedTimeInSeconds < runTimeInSeconds);

    std::cout << "Ran AES for " << runTimeInSeconds << " seconds "<< std::endl;
}//end void runAES(std::string plain)



















// Run LEA encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
void runLEA(std::string plain){
    std::cout << "Running LEA" << std::endl;
    EncryptionParameters  enp;
    do{
            enp = encryptLEA(plain);
    }while(1);
}//end void runLEA(std::string plain)



















// Run LEA encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
// Benchmark bytes https://cryptopp.com/wiki/Benchmarks#Sample_Program
void runLEA_timed(std::string plain){
    std::cout << "Running timed LEA" << std::endl;
    const double runTimeInSeconds = 60*2;       // two minutes
    double elapsedTimeInSeconds;
    unsigned long i=0, blocks=1;

    CryptoPP::ThreadUserTimer timer;
    timer.StartTimer();

    EncryptionParameters  enp;
    do{
            enp = encryptLEA(plain);
            elapsedTimeInSeconds = timer.ElapsedTimeAsDouble();
    }while(elapsedTimeInSeconds < runTimeInSeconds);

    std::cout << "Ran LEA for " << runTimeInSeconds << " seconds "<< std::endl;
}//end void runLEA(std::string plain)
