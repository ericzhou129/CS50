/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize value infile outfile\n");
        return 1;
    }
   
    float resize_val;
    
    // if the resize_val is greater than 1, round to nearest whole number. 
    if (atof(argv[1]) >= 1){
        resize_val = round(atof(argv[1]));
    }
    
    //TODO: if resize_val is less than 1? what now?
    if (atof(argv[1]) < 1){
        resize_val = round(atof(argv[1]));
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    
    if(resize_val > 100 || resize_val <= 0)
    {
        fprintf(stderr, "the resize value must be between 1 and 100");
        return 1; 
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    // Note: fread reads stream into array pointed to by ptr
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // set padding for the input file
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    /** Adjust  the info and file header
     *      - update file size (bfSize)
     *          - bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
     *      - update image size (biSizeImage)
     *          - bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biwidth) + padding) * abs(bi.biHeight);
     *      - update width (biwidth)
     *      - update height (biheight)
     * 
     *      - will have to define padding first?
     **/ 
    
    // update info-header
    // update biwidth and biheight
    bi.biWidth = bi.biWidth * resize_val;
    bi.biHeight = bi.biHeight * resize_val;

    // determine padding for scanlines(Than) [for the output file]
    int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update image size
    bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth) + out_padding) * abs(bi.biHeight);
    
    // update file-header
    // update file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    if(resize_val >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, h = fabs(bi.biHeight/resize_val); i < h; i++)
        {
            // // iterate each 
            for (int n = 0; n < resize_val; n++) 
            {
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth/resize_val; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
                    // for each pixel, iterate the pixel resize_value # of times
                    for (int k = 0; k < resize_val; k++)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }    
                }
        
                // skip over padding, if any    (INFILE)
                fseek(inptr, in_padding, SEEK_CUR);
        
                // then add it back (to demonstrate how)    (OUTFILE)
                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            
                // go back to the beginning of the line that was just read
                fseek(inptr, -(long int)(bi.biWidth/resize_val*sizeof(RGBTRIPLE)+in_padding), SEEK_CUR);
            }
            // go to the next line
            fseek(inptr, (long int)(bi.biWidth/resize_val*sizeof(RGBTRIPLE)+in_padding), SEEK_CUR);
        }
    }


    if (resize_val < 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, h = fabs(bi.biHeight/resize_val); i < h; i++)
        {
            // iterate each 
            for (int n = 0; n < resize_val; n++) 
            {
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth/resize_val; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    
                    // for each pixel, iterate the pixel resize_value # of times
                    for (int k = 1; k < 1/resize_val; k++)
                    {
                        // write RGB triple to outfile
                        fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                    }    
                }
        
                // skip over padding, if any    (INFILE)
                fseek(inptr, in_padding, SEEK_CUR);
        
                // then add it back (to demonstrate how)    (OUTFILE)
                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            
                // go back to the beginning of the line that was just read
                fseek(inptr, -(long int)(bi.biWidth/resize_val*sizeof(RGBTRIPLE)+in_padding), SEEK_CUR);
            }
            // go to the next line
            fseek(inptr, (long int)(bi.biWidth/resize_val*sizeof(RGBTRIPLE)+in_padding), SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
