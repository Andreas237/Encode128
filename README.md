# Encode128
This project was used to take measurements of encryption algorithms AES and LEA for the purpose of encrypting the TPMS ID.
Windows systems were not tested on, and will not work due to the configuration of the `Makefile`.

Install the Crypto++ library (here)[https://cryptopp.com/] before use.


### [CPP_Encrypt](https://github.com/Andreas237/Encode128/tree/master/CPP_Encrypt
`make` will generate executables `Benchmark` and `Cryptest`. `Benchmark.cpp` has a static variable for CPU speed, configured for the 
Raspberry Pi model 2B.  Modify the `cpuFreq` to match your CPU speed. 
  * `Benchmark` measures throughput, cycles per byte, bytes per second
  * `Cryptest` runs the AES and LEA algorithms for two minutes each, allowing power measures to be taken
