# Build From Source

If you dislike the compiled code from the CI/CL or the releases tab because (though it doesnt contain one) you think every file is subject to a spyware, or virus, then here are guidelines on how to build from source. (Though if you aint in the big leagues of Win32, Linux or MacOS, then im sorry, you have to build from the source :| Sorry Solaris users :c )

Since this project is open source*, You can copy the code and modify it (under terms of GPL v3), and you can also build from source.

## Pre-requistes 

Since this project is made from C++, you must have these tools installed in your system - 
- CMake (Latest version recommended)
- A Compiler (GCC v13 or later, clang v20 or later and msvc, idk. Should support C++23 properly)
- Ninja 
- Maybe Unity (This project is large :c )
- Git 
- OpenSSL 

## Additional Pre requistes for Individual OSes

### Linux 

On linux, please install libssl-dev package from apt, using command
```bash
sudo apt install libssl-dev
```
in your terminal.

### MacOS

Note that Apple Clang is NOT Supported (arm64 symbol errors ugh). Use GCC instead (latest version)

## Configuring process

For Configuring - 

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER={0} -DCMAKE_CXX_COMPILER={1} 
```

where 0 - Compiler (C) and 1 - CXX Compiler 

Options can be - 

| Compiler | C Value | CXX Value |
|----------|---------|-----------|
| clang | clang | clang++ |
| MSVC | cl | cl |
| clang-cl | clang-cl | clang-cl |
| GNU | gcc | g++ |

### Additional Note for Windows Users 

If, for some reason, you are compiling through an old version of cmake, you should set up the pointer to the OpenSSL Libraries.

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER={0} -DCMAKE_CXX_COMPILER={1} -DOPENSSL_MSVC_STATIC_RT=ON -DOPENSSL_ROOT-DIR="C:/Program Files/OpenSSL-Win64" -DOPENSSL_CRYPTO_LIBRARY="C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libcrypto.lib" -DOPENSSL_SSL_LIBRARY="C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libssl.lib"
```

Put `-DOPENSSL_MSVC_STATIC_RT` On if the OpenSSL is found to be compiled with MSVC Runtime. you can check the project structure if it has folders like VC, MDd, MTd, MD, etc. Otherwise, Dont enable it and Replace the Variables with the folders. Contact the C++ Discord (where im actively present, im too lazy to make a server) for more info.

## Building the Executable

After Configuration is succeded, run this command - 
```bash
cmake --build build
```

This will take some time but, ultimately, your executable will be ready. 
The name should be - 
- tpedia.exe on Windows
- tpedia (no extension) on MacOS/Linux

If you are contributing, please read this document. 