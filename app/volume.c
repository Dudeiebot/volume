'''
Modifies the volume of an audio file 
We are going to do these by reading the input audio file and writing it to a new output file with a factor that determins the volume of the input audio file.
Then these new output audio file is created from a loop that reads the input audio file byte by byte.
'''

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");      // Open files and determine scaling factor
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    uint8_t header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, input);   // Copying header from input file to output file
    fwrite(header, 1, HEADER_SIZE, output);
    
    int16_t buffer;  // this is created for a 2byte sample and temporary for the loop of the sound
    while (fread(&buffer, sizeof(int16_t), 1, input)) {
        buffer *= factor;  //update the volume
    }
    fwrite(&buffer, sizeof(int16_t), 1, output);  //Read samples from input file and write updated data to output file
    
    fclose(input);      // Close files
    fclose(output);
}
