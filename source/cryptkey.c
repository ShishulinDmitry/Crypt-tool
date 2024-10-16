/**
@file cryptkey.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

///\brief key size in bits (32 bytes)
#define KEY_SIZE 256 
/// \brief block size in bits (16 bytes)
#define BLOCK_SIZE 128		


/** 	
	\brief The function that generates a key based on entered password
	Creating a key based on a hash of a password:
	- Calculates the hash of the password using the SHA-256 algorithm.
	- Copies the hash result to the key array.
	- Uses the EVP_Digest function from the OpenSSL library to calculate the hash.
	- EVP_Digest: a function from the OpenSSL library for calculating cryptographic hashes.
	- EVP_sha256(): function that provides context for calculating the SHA-256 hash.
	@param password pointer to the string containing the password to generate the key
	@param key pointer to an array of unsigned char where the generated key will be written
*/
void generate_key(const char *password, const unsigned char *key) { 
    

    unsigned char hash[KEY_SIZE / 8]; 
    EVP_Digest(password, strlen(password), hash, NULL, EVP_sha256(), NULL);
    memcpy(key, hash, KEY_SIZE / 8);
}


/**
	\brief The function encrypts a file using the AES algorithm in CBC mode
	Algorithm: 
	- Opens the input (input_file) and output (output_file) files for reading and writing, respectively
	- Generates a random initialization vector (IV) using the RAND_bytes function.
	- Sets the key for encryption using AES_set_encrypt_key.
	- Writes the IV to the beginning of the output file.
	- Reads the input file in blocks of BLOCK_SIZE / 8 bytes.
	- Encrypts each block using the AES_cbc_encrypt function in CBC mode.
	- Writes the encrypted block to the output file.
	- Closes the input and output files.
	@param input_file Pointer to a string containing the name of the input file.
	@param output_file Ppointer to a string containing the name of the output file.
	@param key Pointer to an array of 32 bytes containing the encryption key.
*/
void encrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    AES_KEY aes_key;
    unsigned char iv[BLOCK_SIZE / 8];
    unsigned char in_block[BLOCK_SIZE / 8], out_block[BLOCK_SIZE / 8];
    FILE *in_fp, *out_fp;
    if ((in_fp = fopen(input_file, "rb")) == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    if ((out_fp = fopen(output_file, "wb")) == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    RAND_bytes(iv, BLOCK_SIZE / 8);
    AES_set_encrypt_key(key, KEY_SIZE, &aes_key);
    fwrite(iv, sizeof(char), BLOCK_SIZE / 8, out_fp);
    while (fread(in_block, sizeof(char), BLOCK_SIZE / 8, in_fp) == BLOCK_SIZE / 8) {
        AES_cbc_encrypt(in_block, out_block, BLOCK_SIZE / 8, &aes_key, iv, AES_ENCRYPT);
        fwrite(out_block, sizeof(char), BLOCK_SIZE / 8, out_fp);
    }
    fclose(in_fp);
    fclose(out_fp);
}

/**
	\brief The function decrypts a file using the AES algorithm in CBC mode
	Algorithm:
	- Creating a key based on a hash of a password: 
	- The objects `AES_KEY`, `iv`, `in_block`, `out_block`, as well as the files `in_fp` and `out_fp` are created.
	- The success of opening the input and output files is checked using `fopen`. 
	- If the files cannot be opened, an error is displayed and the program terminates.
	- Reading the initialization vector from the beginning of the input file using `fread`.
	- Setting the decryption key using `AES_set_decrypt_key`.
	- Loop through 16-byte blocks of data from the input file.
	- Decrypt each block using `AES_cbc_encrypt` and write the decrypted block to the output file.
	- Close files using `fclose`
	@param input_file Pointer to a string containing the name of the input file.
	@param output_file Ppointer to a string containing the name of the output file.
	@param key Pointer to an array of 32 bytes containing the encryption key.
*/
void decrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    AES_KEY aes_key;
    unsigned char iv[BLOCK_SIZE / 8];
    unsigned char in_block[BLOCK_SIZE / 8], out_block[BLOCK_SIZE / 8];
    FILE *in_fp, *out_fp;

    if ((in_fp = fopen(input_file, "rb")) == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    if ((out_fp = fopen(output_file, "wb")) == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fread(iv, sizeof(char), BLOCK_SIZE / 8, in_fp);

    AES_set_decrypt_key(key, KEY_SIZE, &aes_key);

    while (fread(in_block, sizeof(char), BLOCK_SIZE / 8, in_fp) == BLOCK_SIZE / 8) {
        AES_cbc_encrypt(in_block, out_block, BLOCK_SIZE / 8, &aes_key, iv, AES_DECRYPT);
        fwrite(out_block, sizeof(char), BLOCK_SIZE / 8, out_fp);
    }

    fclose(in_fp);
    fclose(out_fp);
}
