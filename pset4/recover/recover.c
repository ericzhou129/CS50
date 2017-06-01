/**
 * 
 * Harvard CS50 Problem Set 4 Recover
 * This script searches and recovers jpg files from a corrupted memory card
 * 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover infile");
        return 1;
    }
    
    //open input and error check
    FILE *file = fopen(argv[1], "r");
    
    if(file == NULL){
        fprintf(stderr, "Could not open file");
        return 2;
    }
    
    BYTE buffer[512];
    
    int found_jpeg = 0;
    int count_jpeg = 0;
    char *filename = malloc(8);
    //char filename[8];
    FILE *img = NULL;
        
    // read 512 bytes into a buffer
    while(fread(&buffer, 1, 512, file) == 512){
        // start of a new JPEG?
        // yes
        
        if (buffer[0] == 0xff && 
            buffer[1] == 0xd8 && 
            buffer[2] == 0xff && 
            (buffer[3] & 0xf0) == 0xe0){
                
                //already found a JPEG?
                // no
                if(found_jpeg != 1){
                    // write to the very first JPEG
                    sprintf(filename, "%03i.jpg", count_jpeg);
                    img = fopen(filename, "w");
                    fwrite(&buffer, 512, 1, img);
                }
                // yes
                else{
                    // close previous jpeg
                    fclose(img);
                    count_jpeg ++; 

                    // write to new jpeg
                    sprintf(filename, "%03i.jpg", count_jpeg);
                    img = fopen(filename, "w");
                    fwrite(&buffer, 512, 1, img);
                    
                }
                
                found_jpeg = 1;
            }
        
        // not the start of a new jpeg
        // is there already a jpeg? --> yes
        else if(found_jpeg == 1){
                // write to existing jpeg
                fwrite(&buffer, 512, 1, img);
        } 
        
    }
    
    free(filename);
    fclose(img);
    
    return 0;
}
