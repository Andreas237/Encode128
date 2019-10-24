#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hrtimer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/lea.h>
#include <iostream>
#include <ctime>           // benchmark Naive
#include <ratio>           // benchmark Naive
#include <chrono>           // benchmark Naive
#include "naive.h"


















void benchmarkAes(std::string);
void benchmarkLea(std::string);
void benchmarkNaive(std::string);
const int rounds = 15;                              // run 15 rounds
const double cpuFreq = 900 * 1000 * 1000;           // set to match OS, Pi 2B
// const double cpuFreq = 2.4 * 1000 * 1000 * 1000; // 2019 Macbook


















// Run both the benchmark codes and print to stdout
int main(int argc, char * argv[]){

    std::string plain = "02AFE3Du";


    benchmarkAes(plain);
    benchmarkLea(plain);
    benchmarkNaive(plain);

    return 1;
}// end int main(int argc, char * argv[])



















/**
Use the benchmark code at https://cryptopp.com/wiki/Benchmarks#Sample_Program
to get:
    - execution time (seconds) of one round
    - Throughput (bytes/second)
    - cycles per byte
*/
void benchmarkAes(std::string plain){
    std::cout << "\n\n===============================" << std::endl;
    std::cout << "|\tMetrics for AES       |" << std::endl;
    std::cout << "===============================" << std::endl;
    using namespace CryptoPP;
    AutoSeededRandomPool prng;

    SecByteBlock key(16);
    prng.GenerateBlock(key, key.size());

    CBC_Mode<AES>::Encryption cipher;
    cipher.SetKeyWithIV(key, key.size(), key);

    const int BUF_SIZE = RoundUpToMultipleOf(2048U,
        dynamic_cast<StreamTransformation&>(cipher).OptimalBlockSize());

    AlignedSecByteBlock buf(BUF_SIZE);
    prng.GenerateBlock(buf, buf.size());


        unsigned long i=0, blocks=1;


            auto timeBegin = std::chrono::high_resolution_clock::now();

            ////////////////////////////////////////////////////////////////////////////
            // Metrics for many rounds
            ////////////////////////////////////////////////////////////////////////////
            int count = 0;
            do
            {
                blocks *= 2;
                for (; i<blocks; i++)
                    cipher.ProcessString(buf, BUF_SIZE);
            }
            while (rounds > count++);


            auto timeEnd = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(timeEnd - timeBegin);
            const double elapsedTimeInSeconds = time_span.count();


            const double bytes = static_cast<double>(BUF_SIZE) * blocks;
            const double ghz = cpuFreq / 1000 / 1000 / 1000;
            const double mbs = bytes / elapsedTimeInSeconds / 1024 / 1024;
            const double cpb = elapsedTimeInSeconds * cpuFreq / bytes;
            const double tpc = cpb * mbs / 1024 / 1024;

            std::cout << cipher.AlgorithmName() << " benchmarks..." << std::endl;
            std::cout << "  " << ghz << " GHz cpu frequency"  << std::endl;
            std::cout << "  " << cpb << " cycles per byte (cpb)" << std::endl;
            std::cout << "  " << mbs << " throughput MB per second (MB)" << std::endl;
            std::cout << "  " << tpc << " execution time for one cycle (seconds)" << std::endl;
            std::cout << "  " << elapsedTimeInSeconds << " seconds passed" << std::endl;
            std::cout << "  " << (word64) bytes << " bytes processed" << std::endl;


}// end void benchmarkAes(std::string plain)



















void benchmarkLea(std::string){
        std::cout << "\n\n===============================" << std::endl;
        std::cout << "|\tMetrics for LEA       |" << std::endl;
        std::cout << "===============================" << std::endl;
        using namespace CryptoPP;
        AutoSeededRandomPool prng;

        SecByteBlock key(16);
        prng.GenerateBlock(key, key.size());

        CBC_Mode<LEA>::Encryption cipher;
        cipher.SetKeyWithIV(key, key.size(), key);

        const int BUF_SIZE = RoundUpToMultipleOf(2048U,
            dynamic_cast<StreamTransformation&>(cipher).OptimalBlockSize());

        AlignedSecByteBlock buf(BUF_SIZE);
        prng.GenerateBlock(buf, buf.size());

        unsigned long i=0, blocks=1;


        auto timeBegin = std::chrono::high_resolution_clock::now();

        ////////////////////////////////////////////////////////////////////////////
        // Metrics for many rounds
        ////////////////////////////////////////////////////////////////////////////
        int count = 0;
        do
        {
            blocks *= 2;
            for (; i<blocks; i++)
                cipher.ProcessString(buf, BUF_SIZE);
        }
        while (rounds > count++);


        auto timeEnd = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(timeEnd - timeBegin);
        const double elapsedTimeInSeconds = time_span.count();


        const double bytes = static_cast<double>(BUF_SIZE) * blocks;
        const double ghz = cpuFreq / 1000 / 1000 / 1000;
        const double mbs = bytes / elapsedTimeInSeconds / 1024 / 1024;
        const double cpb = elapsedTimeInSeconds * cpuFreq / bytes;
        const double tpc = cpb * mbs / 1024 / 1024;

        std::cout << cipher.AlgorithmName() << " benchmarks..." << std::endl;
        std::cout << "  " << ghz << " GHz cpu frequency"  << std::endl;
        std::cout << "  " << cpb << " cycles per byte (cpb)" << std::endl;
        std::cout << "  " << mbs << " throughput MB per second (MB)" << std::endl;
        std::cout << "  " << tpc << " execution time for one cycle (seconds)" << std::endl;
        std::cout << "  " << elapsedTimeInSeconds << " seconds passed" << std::endl;
        std::cout << "  " << (word64) bytes << " bytes processed" << std::endl;


}// end void benchmarkLea(std::string)



















// Naive benchmark
/*
    Measurements to collect:
        - Cycles-per-byte: (time of one round)/[(clock speed)*(size of one round)]
        - MB per second:
        - execution time for one round: (time one iteration of encryption)-> seconds
*/
void benchmarkNaive(std::string plain){
        std::cout << "\n\n===============================" << std::endl;
        std::cout << "|\tMetrics for Naive       |" << std::endl;
        std::cout << "===============================" << std::endl;


        EncryptionParameters enp = encryptNaive(plain);


        int count = 0;
        int bytesProcessed = 0;
        int bytesize = 16;
        auto t1 = std::chrono::high_resolution_clock::now();


        do {
            bytesProcessed += bytesize;
            enp = encryptNaive(enp.getCipherText());
        } while(rounds*1000 > count++);

        auto t2 = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
        const double elapsedTimeInSeconds = time_span.count();
        //const double cyclesPerByte =
        const double ghz = cpuFreq / 1000 / 1000 / 1000;
         // size of id * number of times processed / time / (1MB/1000^2 B)
        const double mbs = bytesProcessed / elapsedTimeInSeconds / 1024 / 1024;
        const double cpb = elapsedTimeInSeconds * cpuFreq / bytesProcessed;
        const double tpc = cpb * mbs / 1024 / 1024;


        std::cout << "Naive" << " benchmarks..." << std::endl;
        std::cout << "  " << ghz << " GHz cpu frequency"  << std::endl;
        std::cout << "  " << cpb << " cycles per byte (cpb)" << std::endl;
        std::cout << "  " << mbs << " throughput MB per second (MB)" << std::endl;
        std::cout << "  " << tpc << " execution time for one cycle (seconds)" << std::endl;
        std::cout << "  " << elapsedTimeInSeconds << " elapsed time (seconds)" << std::endl;
        std::cout << "  " << bytesProcessed << " bytes processed" << std::endl;

}// end void benchmarkLea(std::string)
