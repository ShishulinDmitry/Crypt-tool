/**
@file cryptkey.h
*/

#ifndef CRYPTKEY_H
#define CRYPTKEY_H


void generate_key(const char *password, const unsigned char *key);

void encrypt_file(const char *input_file, const char *output_file, const unsigned char *key);

void decrypt_file(const char *input_file, const char *output_file, const unsigned char *key);


#endif
