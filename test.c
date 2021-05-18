#include <stdio.h>

// Define the image size we are using
#define SIZEX 50
#define SIZEY 50

// Include the functions to read / write the images
#include "imgUtils.c"

// ----------------------------------------------------------------------------

#ifndef __testing__ // You know the drill, don't remove this.

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

  // --------------------------------------------------------------------------
  //                      Testing with floo-region-1.pgm
  //                     Output file will be output-1.pgm
  // --------------------------------------------------------------------------

  // Read the selected input image into input[][]
  readPGM("input-1.pgm", &input[0][0]);

  printf("Calling find_connected_region() on image 1...\n");
  xCoordinate = 24;
  yCoordinate = 16;
  find_connected_region(input, xCoordinate, yCoordinate, output); // Staring position is (24, 16)

  // Write the connected region to the output image
  writePGM("output-1.pgm", &output[0][0]);

  // --------------------------------------------------------------------------
  //                      Testing with floo-region-2.pgm
  //                     Output file will be output-2.pgm
  // --------------------------------------------------------------------------

  // Read the selected input image into input[][]
  readPGM("input-2.pgm", &input[0][0]);

  // Don't forget to reset the output array!
  for (int y = 0; y < SIZEY; y++)
  {
    for (int x = 0; x < SIZEX; x++)
    {
      output[y][x] = 0;
    }
  }

  printf("Calling find_connected_region() on image 2...\n");
  xCoordinate = 4;
  yCoordinate = 35;
  find_connected_region(input, xCoordinate, yCoordinate, output); // Staring position is (4, 35)

  // Write the connected region to the output image
  writePGM("output-2.pgm", &output[0][0]);

  printf("Done!\n");
  return 0;
}

#endif
