#include <stdio.h>

// Define the image size we are using
#define SIZEX 50
#define SIZEY 50
#define MAX_LENGTH 1024

// Include the functions to read / write the images
#include "imgUtils.c"
// ----------------------------------------------------------------------------

#ifndef __testing__ 

int main()
{
  unsigned char input[SIZEY][SIZEX];
  unsigned char output[SIZEY][SIZEX];
  int xCoordinate;
  int yCoordinate;

  // Initialize output array to have colour black (0)
  for (int y = 0; y < SIZEY; y++)
  {
    for (int x = 0; x < SIZEX; x++)
    {
      output[y][x] = 0;
    }
  }
  
  //name your input and output file here, dont forget to add the pgm extension
  char inputFile[MAX_LENGTH] = "input-1.pgm";
  char outputFile[MAX_LENGTH] = "output.pgm";
  xCoordinate = 24;
  yCoordinate = 16;

  // Read the selected input image into input[][]
  readPGM(inputFile, &input[0][0]);

  printf("\nCalling find_connected_region() on %s...\n",inputFile);
  find_connected_region(input, xCoordinate, yCoordinate, output); // Staring position is (24, 16)

  // Write the connected region to the output image
  writePGM(outputFile, &output[0][0]);

  printf("Done!\n\n");
  return 0;
}

#endif
