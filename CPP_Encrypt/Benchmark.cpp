#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hrtimer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/lea.h>
#include <iostream>



















void benchmarkAes(std::string);
void benchmarkLea(std::string);
const double runTimeInSeconds = 3.0;                // run for 3 seconds
const double cpuFreq = 900 * 1000 * 1000;           // set to match OS, Pi 2B
// const double cpuFreq = 2.4 * 1000 * 1000 * 1000;    // 2019 Macbook


















// Run both the benchmark codes and print to stdout
int main(int argc, char * argv[]){

    std::string plain = "02AFE3Du";


    benchmarkAes(plain);
    benchmarkLea(plain);

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

    double elapsedTimeInSeconds;
    unsigned long i=0, blocks=1;

    ThreadUserTimer timer;
    timer.StartTimer();

    ////////////////////////////////////////////////////////////////////////////
    // Metrics for many rounds
    ////////////////////////////////////////////////////////////////////////////
    do
    {
        blocks *= 2;
        for (; i<blocks; i++)
            cipher.ProcessString(buf, BUF_SIZE);
        elapsedTimeInSeconds = timer.ElapsedTimeAsDouble();
    }
    while (elapsedTimeInSeconds < runTimeInSeconds);



    const double bytes = static_cast<double>(BUF_SIZE) * blocks;
    const double ghz = cpuFreq / 1000 / 1000 / 1000;
    const double mbs = bytes / elapsedTimeInSeconds / 1000 / 1000;
    const double cpb = elapsedTimeInSeconds * cpuFreq / bytes;
    const double tpc = cpb * mbs / 1000 / 1000;

    std::cout << cipher.AlgorithmName() << " benchmarks..." << std::endl;
    std::cout << "  " << ghz << " GHz cpu frequency"  << std::endl;
    std::cout << "  " << cpb << " cycles per byte (cpb)" << std::endl;
    std::cout << "  " << mbs << " throughput MiB per second (MiB)" << std::endl;
    std::cout << "  " << tpc << " execution time for one cycle (seconds)" << std::endl;

    // std::cout << "  " << elapsedTimeInSeconds << " seconds passed" << std::endl;
    // std::cout << "  " << (word64) bytes << " bytes processed" << std::endl;


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

        double elapsedTimeInSeconds;
        unsigned long i=0, blocks=1;

        ThreadUserTimer timer;
        timer.StartTimer();

        ////////////////////////////////////////////////////////////////////////////
        // Metrics for many rounds
        ////////////////////////////////////////////////////////////////////////////
        do
        {
            blocks *= 2;
            for (; i<blocks; i++)
                cipher.ProcessString(buf, BUF_SIZE);
            elapsedTimeInSeconds = timer.ElapsedTimeAsDouble();
        }
        while (elapsedTimeInSeconds < runTimeInSeconds);



        const double bytes = static_cast<double>(BUF_SIZE) * blocks;
        const double ghz = cpuFreq / 1000 / 1000 / 1000;
        const double mbs = bytes / elapsedTimeInSeconds / 1000 / 1000;
        const double cpb = elapsedTimeInSeconds * cpuFreq / bytes;
        const double tpc = cpb * mbs / 1000 / 1000;

        std::cout << cipher.AlgorithmName() << " benchmarks..." << std::endl;
        std::cout << "  " << ghz << " GHz cpu frequency"  << std::endl;
        std::cout << "  " << cpb << " cycles per byte (cpb)" << std::endl;
        std::cout << "  " << mbs << " throughput MB per second (MB)" << std::endl;
        std::cout << "  " << tpc << " execution time for one cycle (seconds)" << std::endl;

        // std::cout << "  " << elapsedTimeInSeconds << " seconds passed" << std::endl;
        // std::cout << "  " << (word64) bytes << " bytes processed" << std::endl;

}// end void benchmarkLea(std::string)