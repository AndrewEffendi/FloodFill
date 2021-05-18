#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIZEX
  #define SIZEX 50
  #define SIZEY 50
#endif

void rec(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned char output[SIZEY][SIZEX],unsigned char checked[SIZEY][SIZEX]){
  output[py][px] = 255;
  checked[py][px]=1;
  if(px + 1 < SIZEX && checked[py][px+1] == 0 && input[py][px+1] == input[py][px]) rec(input,px+1,py,output,checked);
  if(py + 1 < SIZEY && checked[py+1][px] == 0 && input[py+1][px] == input[py][px]) rec(input,px,py+1,output,checked);
  if(px - 1 >= 0 && checked[py][px-1] == 0 && input[py][px-1] == input[py][px]) rec(input,px-1,py,output,checked);
  if(py - 1 >= 0 && checked[py-1][px] == 0 && input[py-1][px] == input[py][px]) rec(input,px,py-1,output,checked);
}

void find_connected_region(unsigned char input[SIZEY][SIZEX], int px, int py,
                           unsigned char output[SIZEY][SIZEX])
{
  /**
   * The function takes in the input image array (input) representing the
   * elevation maps of our newly discovered planet, and the initial position
   * of the rover (px, py). Each element of `input` has values 0-255 inclusive.
   * Each element of the array represents the color of the corresponding pixel,
   * where 0 represents the colour black, and 255 represents the colour white.
   *
   * NOTE: Because of how 2D arrays are stored in memory, we need to be careful
   *       when trying to access the correct pixel. PGM images use the math
   *       convention where the first index is the ROW, and the second index
   *       is the COLUMN. So, to get the color of pixel (x, y), you will
   *       need to do:
   *                                input[y][x]
   *
   *
   * Given
   * - The input elevation map in `input`
   * - An initially empty image called `output` (all the pixels have colour 0)
   * - And initial coordinates of the rover (px, py)
   *
   * Your task is to find all *connected* pixels that have the same elevation
   * as the one at (px,py) in `input`, and mark these pixels on `output`.
   *
   * For instance, if the initial coordinates are (px=5, py=10), your program
   * must check the elevation at input[10][5], then set the colour of all
   * connected pixels to white (255) in the levelset_map.
   *
   * Example with a very tiny sample image:
   *
   * input:
   *                       1    1    1    2    3    3
   *                       1    1    2    3    3    4
   *                       1    2    2    2    4    3
   *                       1    1    1    2    4    3
   *                       1    1    2    2    3    3
   *                       4    4    4    4    2    2
   *
   *
   * If we call the function with the `input` above, and initial coordinates
   * (1,1), it should produce
   *
   * output:
   *
   *                      255  255  255   0    0    0
   *                      255  255   0    0    0    0
   *                      255   0    0    0    0    0
   *                      255  255  255   0    0    0
   *                      255  255   0    0    0    0
   *                       0    0    0    0    0    0
   *
   * If we call the function with initial coordinates (4, 0) it will produce
   *
   * output:
   *
   *                       0    0    0    0   255  255
   *                       0    0    0   255  255   0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *
   * In effect, this function extracts the connected region in the image
   * array with the same elevation as that of the pixel at (px, py).
   *
   * NOTE: A pixel can be 'connected' to it's it's 4 neighbours above, below,
   *       to the left and right of it, if they have the same colour. In
   *       particular, we will NOT count pixels along the diagonal. Carefully
   *       look at the examples above to make sure you understand this.
   *
   * - You should NOT change the contents of the input array.
   *
   * There are many ways to approach this problem, you're free to choose
   * whatever makes more sense to you. Make reasonable assumptions where
   * needed, and solve the problem!
   */
  unsigned char checked[SIZEY][SIZEX];
  for (int y = 0; y < SIZEY; y++) for (int x = 0; x < SIZEX; x++) checked[y][x] = 0;
  rec(input,px,py,output,checked);
}

// ----------------------------------------------------------------------------
//       The following functions deal with reading and writing the 
//          images from disk. You do NOT need to understand how 
//            they work, or even read their implementation
// ----------------------------------------------------------------------------

void writePGM(const char *filename, unsigned char *data) {
  /**
   * Output a PGM image given the pixel data at the given filename. If the file
   * already exists it will be overwritten. The image array should be of size
   * SIZEY x SIZEX
   */

  FILE *f = fopen(filename, "wb");
  if (f != NULL) {
    // Write the header for the PGM file
    fprintf(f, "P5\n%d %d\n255\n", SIZEX, SIZEY);
    // Write the pixel data to the file
    fwrite(data, SIZEX * SIZEY * sizeof(unsigned char), 1, f);
    fclose(f);
  }
}

void readPGM(const char *filename, unsigned char *data) {
  /**
   * Read in a PGM file with a given file name, and return the pixel data
   * array (data) only if the input image size matches sx and sy.
   */

  char buffer[1024];
  int sx, sy;

  FILE *f = fopen(filename, "rb+");
  if (f == NULL) {
    printf("Unable to open %s. Make sure the path is correct\n", filename);
    exit(1);
  }
  fgets(buffer, 1024, f);
  if (strcmp(buffer, "P5\n")) {
    printf("%s is not a valid input PGM file.\n", filename);
    fclose(f);
    exit(1);
  }
  // Skip over comments
  do {
    fgets(buffer, 1024, f);
  } while (buffer[0] == '#');
  // Read the file size from the image into sx and sy
  sscanf(buffer, "%d %d\n", &sx, &sy);
  if (sx != SIZEX || sy != SIZEY) {
    printf("PGM image does not match expected size.\n");
    fclose(f);
    exit(1);
  }
  // Read the remaining header line
  fgets(buffer, 1024, f); 
  // Read the image data into the given array.
  fread(data, sx * sy * sizeof(unsigned char), 1, f);
  fclose(f);
  return;
}
