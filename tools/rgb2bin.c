#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT(i)	1<<(i) // i counts from right to left

// This takes a raw image file that has an r-g-b-r-g-b-r-g-b-... scheme
// The file must only contain black and white. Yes, terrible waste, isn't it?
// And this is converted to an 8-pixel-per-byte c-array, as used for TobKit icons.

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("Usage: rgb2bin icon.rgb\n");
        exit(0);
    }

	FILE *infile, *outfile;
	infile = fopen(argv[1], "rb");
	
	char* ppos = strchr(argv[1],'.');
	
	strcpy(ppos,".bin");
	outfile = fopen(argv[1], "wt");
	
	unsigned char r, g, b, bitcounter = 0, colorbyte = 0;
	
	while(!feof(infile)) {
		r = (unsigned char)fgetc(infile);
		g = (unsigned char)fgetc(infile);
		b = (unsigned char)fgetc(infile);
		
		if((r==0)&&(g==0)&&(b==0)) {
			colorbyte |= BIT(bitcounter);
		}
		bitcounter++;
		bitcounter %= 8;
		
		if((bitcounter == 0)||(feof(infile))) { // The byte is full or we are at the end of the file
			fwrite(&colorbyte,1,1,outfile);
			
			colorbyte = 0;
		}
	}
	
	fclose(infile);
	fclose(outfile);
}
