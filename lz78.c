#include "bitio.h"
#include "header.h"
#include "compressor.h"
#include "decompressor.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
//#include <strings.h>


#define DICT_SIZE 1000

void print_help()
{
    printf("Usage:\n\
			lz78 -c -i <input_file> -o <output_file>\tfor compression\n\
			lz78 -d -i <input_file> -o <output_file>\tfor decompression\n\n\
			Other options:\n\
			-s <dictionary_size>\n\
			-h \thelp\n\n");
}

int main(int argc, char *argv []) {
    int fd, compr=-1, s=0, h=0;
    //compr is set to 1 if we want to compress, set to 2 if we want to decompress
    char* source=NULL, *dest=NULL;
    unsigned int dict_size=DICT_SIZE, d_dict_size;
    struct bitio* fd_bitio;
    int opt;

    while ((opt = getopt(argc,argv,"cdi:o:s:h"))!=-1) {
        switch (opt) {
			case 'c':
				compr=0;
				break;
			case 'd':
				compr=1;
				break;
			case 'i':
				source=optarg; //take the input name from optarg
				break;
			case 'o':
				dest=optarg; //take the output name from optarg
				break;
			case 's':
				s=1;
				dict_size=atoi(optarg);
				break;
			case 'h':
				h=1;
				print_help();
            break;
        case '?':
            if(optopt=='i'){
                fprintf(stderr,"An input file is required\n");
                exit(1);
            } else if (optopt=='o'){
                fprintf(stderr,"No name specified for destination file\n");
                exit(1);
            } else if (optopt=='s'){
                fprintf(stderr,"No dimension specified for dictionary size\n");
                exit(1);
            } else if (isprint(optopt)){
          		fprintf (stderr, "Unknown option `-%c'\n", optopt);
				exit(1);
			}else {
                fprintf(stderr, "Unknown option character `\\x%x'.\n Try -h for help\n", optopt);
                exit(1);
            }
            break;
			default:
				abort();
         } //switch (opt)
    } //while ()
		
	return 0;
}