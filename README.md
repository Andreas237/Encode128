# Encode128

## Purpose
This project was used to take measurements of encryption algorithms AES and LEA for the purpose of encrypting the TPMS ID.
Windows systems were not tested on, and will not work due to the configuration of the `Makefile`.

Install the Crypto++ library [here](https://cryptopp.com/) before use.


### [CPP_Encrypt](https://github.com/Andreas237/Encode128/tree/master/CPP_Encrypt)
`make` will generate executables `Benchmark` and `Cryptest`. `Benchmark.cpp` has a static variable for CPU speed, configured for the
Raspberry Pi model 2B.  Modify the `cpuFreq` to match your CPU speed.
  * `Benchmark` measures throughput, cycles per byte, bytes per second
  * `Cryptest` runs the AES and LEA algorithms for two minutes each, allowing power measures to be taken


### [C_Encrypters](https://github.com/Andreas237/Encode128/tree/master/C_Encrypters)
Linear Feedback Shift Register is an important stream cipher, which was not implemented in this project, but will be in a future work.



## What I Learned

### `Makefile`
The `Makefile` in this project allowed me to learn about compiling for target
operating systems rather than with generic commands.  
The `-l` option is finally clear: link to some library!
The `-L` option allows you to add an additional location for the linker to look for libraries.
There is a way to [view hex](http://www.cplusplus.com/forum/windows/51591/) in C++!


### Open Source Libraries
Using open source libraries is not new to me.  Crypto++ fought me though.  The project
is intended to run on a Raspberry Pi, however development was done on OSx Sierra.
Installing Crypto++ with Brew worked with no problem.
When using `apt install` on the Raspberry Pi the `lea.h` header was excluded for some
reason.  This taught me to look for the headers, download the library source, and
compile on my own to guarantee the headers I need are included.
