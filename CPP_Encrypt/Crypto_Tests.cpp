#include <iostream>
#include <cryptopp/hrtimer.h>
#include <cstring>		// compare argv[1]
#include "LEA_run.h"
#include "AES_run.h"



void runAES(std::string);
void runAES_timed(std::string);
void runLEA(std::string);
void runLEA_timed(std::string);
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
    if( !strcmp(argv[1],lea)) 
	runLEA(plain);
    else if( !strcmp(argv[1], aes))
	runAES(plain);
    else if( !strcmp(argv[1], naive))
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
    std::cout << "Running LEA. CTRL+C to end." << std::endl;
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



















// In a naive scheme the ID is updated at every iteration
void runNaive(std::string plain){
	std::cout << "Runnng Naive.  CTRL+C to end." << std::endl;
	// no key or value in this scheme
	CryptoPP::SecByteBlock k;
	CryptoPP::SecByteBlock iv;
	
	int plainLen = plain.size();
	

	std::string const perm = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    	int permLen = perm.size();
	
	int test = 0;
	do{
		
		    // For every character of the input string
    		for(int currentPos = 0; currentPos < plainLen; currentPos++){
        		int currentPerm = perm.find(plain[currentPos]);
        		// increment that character one full cycle
        		for(int inc = 0; inc < permLen; inc++){
            			//std::cout << "before: " << plain;
            			plain[currentPos] = perm[   (currentPerm + inc) % permLen ];
            			//std::cout << "\tafter: " << plain << std::endl;
				EncryptionParameters(k,iv,plain);
			}//for(int inc = 0; inc < permLen; inc++)
    		}// end for(int currentPos = 0; currentPos < permLen; currentPos++)
	}while(1);
}// end void runNaive
