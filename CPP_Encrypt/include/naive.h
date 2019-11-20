#include <string>
#include "encryption_parameters.h"



















// alphabet: string showing the next letter in line
// plain: plaintext to be incremented
// current: current letter to be incrememented
void padder(std::string &plain){
    while(sizeof(plain) < 16)
        plain.append("0");
} //end void mapper(const std::string &alphabet, std::string &plain, int current)



















// Encrypt a string by incrementing each character by 1
EncryptionParameters encryptNaive(std::string plain){

    std::string const perm = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int permLen = perm.size();

    // pad the input to 16 bytes
    padder(plain);

    int myLen = plain.size();



    CryptoPP::SecByteBlock key, iv;   // empty since naive doesn't require these


    // For every character of the input string
    for(int currentPos = 0; currentPos < myLen; currentPos++){
        int currentPerm = perm.find(plain[currentPos]);
        // increment that character one full cycle
        // permLen-1 so that it ends on a different character than it began
        for(int inc = 0; inc < permLen; inc++){
            plain[currentPos] = perm[   (currentPerm + inc) % permLen ];
        }//for(int inc = 0; inc < permLen; inc++)
    }// end for(int currentPos = 0; currentPos < permLen; currentPos++)

    return EncryptionParameters(key,iv,plain);

}// end EncryptionParameters encryptNaive(std::string plain)



















// Naive benchmark
/*
    Measurements to collect:
        - Cycles-per-byte: (time of one round)/[(clock speed)*(size of one round)]
        - MB per second:
        - execution time for one round: (time one iteration of encryption)-> seconds
*/
void encryptNaive_Benchmark(std::string plain){

    auto t1 = std::chrono::high_resolution_clock::now();
    encryptNaive(plain);
    auto t2 = std::chrono::high_resolution_clock::now();

    const auto singleRound = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    //const double cyclesPerByte =

}//end void encryptNaive_Benchmark(std::string plain)
