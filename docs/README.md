# Crypt tool
## Description
The program implements a simple utility for encrypting and decrypting files using the AES algorithm in CBC (Cipher Block Chaining) mode. The encryption key is generated based on the hash of the transferred password.
## Installation
### Requirements
- CMake (3.5)
- OpenSSL
- C compiler (GCC)
### Building the project
1. Clone the repository:
git clone <URL>
2. Build (UNIX)
cd file_encryptor
mkdir build
cd build
cmake ..
make
## Usage
### Syntax
crypt_tool -e/d -f <filename> -o <filename> -p <password>
### File encryption
./crypt_tool -e -f <input file> -o <output file> -p <password>
- -e: encryption option.
- -f <input_file>: file name to encrypt.
- -o <output_file>: encrypted file name.
- -p <password>: password for key generation.

Example:
./crypt_tool -e -f file -o encrypted_file -p passwd

### Decrypting a file
./crypt_tool -d -f <input file> -o <output file> -p <password>
- -d: decryption option.
- -f <input_file>: file name to decrypt.
- -o <output_file>: decrypted file name.
- -p <password>: password for key generation.

Example:
./crypt_tool -d -f encrypted_file -o decrypted_file -p passwd
