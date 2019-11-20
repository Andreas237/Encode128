#include <iostream>
#include <cryptopp/hrtimer.h>
#include <cstring>		// compare argv[1]
#include "AES_run.h"
#include "LEA_run.h"
#include "LFSR_run.h"
#include "naive.h"



void runAES(std::string);
void runAES_timed(std::string);
void runLEA(std::string);
void runLEA_timed(std::string);
void runLFSR(std::string);
void runNaive(std::string);

/*
        About: run the AES encryption on the same block for a set amount of time.

        Examples:
            Crypto++ CBC Mode is the template for this program: https://cryptopp.com/wiki/CBC
            Crypto++ Benchmark for the while loop https://cryptopp.com/wiki/Benchmarks#Sample_Program
*/
int main(int argc, char* argv[]) {


    char aes[] = "AES";
    char lea[] = "LEA";
    char lfsr[] = "LFSR";
    char naive[] = "naive";
    std::string plain = "02AFE3Du";


    /* encrypt and recover
    int resultCode;
    std::string recovered;
    EncryptionParameters np = encryptLEA(plain);
    recovered.append(decryptLEA(enp));
    */

    // run each algorithm for two minutes to allow time to record
   // runAES_timed(plain);

    // Run the given algorithm, or a loop for the baseline
    if(!strcmp(argv[1], aes))
	   runAES(plain);
    else if(!strcmp(argv[1],lea))
	   runLEA(plain);
    else if(!strcmp(argv[1], lfsr))
       runLFSR(plain);
    else if(!strcmp(argv[1], naive))
	   runNaive(plain);
    else
    	return 1;

}// end main



















// Run AES encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
void runAES(std::string plain){
    std::cout << "Running AES. CTRL+C to end." << std::endl;
    EncryptionParameters  enp;
    do{
            enp = encryptAES(plain);
    }while(1);
}//end void runAES(std::string plain)



















// Run LEA encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
void runLEA(std::string plain){
    std::cout << "Running LEA. CTRL+C to end." << std::endl;
    EncryptionParameters  enp;
    do{
            enp = encryptLEA(plain);
    }while(1);
}//end void runLEA(std::string plain)



















// Run LEA encryption until keyboard interrupt so that power can be measured on
// the J7-C USB.
void runLFSR(std::string plain){
    std::cout << "Running LFSR. CTRL+C to end." << std::endl;
    EncryptionParameters  enp;
    int counter = 0;
    do{
            enp = encryptLFSR16(plain);
            std::cout << "Round:" << counter << "\tCipherText:" << enp.getCipherText() << std::endl;
            counter++;
    }while(counter<=2);
}//end void runLEA(std::string plain)



















// In a naive scheme the ID is updated at every iteration
void runNaive(std::string plain){
	std::cout << "Runnng Naive.  CTRL+C to end." << std::endl;

    EncryptionParameters  enp;

	do{
        enp = encryptNaive(plain);
	}while(1);
}// end void runNaive
