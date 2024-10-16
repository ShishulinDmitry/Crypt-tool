/**
@file main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cryptkey.h"

///\brief key size in bits (32 bytes)
#define KEY_SIZE 256


/** 	
	\brief The function that print information about usage 
*/
void print_usage_info(){
    printf("crypttool -(e/d) -i <filename> -o <filename> -p <password>\n");
    printf("\t-e\t\tEncrypt file\n");
    printf("\t-d\t\tDecrypt file\n");
    printf("\t-i <filename>\tInput filename\n");
    printf("\t-o <filename>\tOutput filename\n");
    printf("\t-p <password>\tPassword for key generation\n");
}

/**
	\brief The entry point to the program.
	@param argc Number of arguments
	@param argv Array of arguments
	
*/
int main(int argc, char *argv[]) {

    char *input_file  = NULL;
    char *output_file = NULL;
    char *password    = NULL;

    unsigned char key[KEY_SIZE / 8];
    int opt;
    int option = 0;
    
    while ((opt = getopt(argc, argv, "edi:o:p:")) != -1) {
        switch (opt) {
       	    case 'e':
                option = 1;
                break;
            case 'd':
                option = 2;
                break;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            default:
                print_usage_info();
                exit(EXIT_FAILURE);
        }
    }

    if (input_file == NULL || output_file == NULL || password == NULL) {
    	printf("ERROR: Wrong usage \n");
        print_usage_info();
        exit(EXIT_FAILURE);
    }

    generate_key(password, key);

    if (option == 2){decrypt_file(input_file, output_file, key);}
    else if (option == 1){encrypt_file(input_file, output_file, key);}
    return 0;
}
