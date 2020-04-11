// your C program without sse instructions
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double *wct)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  *wct = (double)(tp.tv_sec + tp.tv_usec / 1000000.0);
}

int main()
{
  int ROWS = N;
  int COLUMNS = M;
  double ts, te;
  float constants[] = {0.5, 0.5, 0.5, 0.5, 5.0, 0.5, 0.5, 0.5, 0.5};

  float *image = malloc(ROWS * COLUMNS * sizeof(float));
  float *transformedImage = malloc(ROWS * COLUMNS * sizeof(float));

  float color = (float)((rand() % 100) / 255.0);
  for (int i = 0; i < ROWS * COLUMNS; i++)
  {
    image[i] = color;
    transformedImage[i] = -i;
  }

  get_walltime(&ts);

  for (int x = 0; x < ROWS; x++)
  {
    for (int y = 0; y < COLUMNS; y++)
    {
      int topLeftIndex = ((x - 1) * COLUMNS) + y - 1;
      int topMiddleIndex = (x * COLUMNS) + y - 1;
      int topRightIndex = ((x + 1) * COLUMNS) + y - 1;
      int leftIndex = ((x - 1) * COLUMNS) + y;
      int pixelIndex = (x * COLUMNS) + y;
      int rightIndex = ((x + 1) * COLUMNS) + y;
      int bottomLeftIndex = ((x - 1) * COLUMNS) + y + 1;
      int bottomMiddleIndex = (x * COLUMNS) + y + 1;
      int bottomRightIndex = ((x + 1) * COLUMNS) + y + 1;

      float topLeftPixel = (y != 0 && x != 0) ? image[topLeftIndex] : 0.0;
      float topMiddlePixel = (y != 0) ? image[topMiddleIndex] : 0.0;
      float topRightPixel =
          (y != 0 && x != ROWS - 1) ? image[topRightIndex] : 0.0;

      float leftPixel = (x != 0) ? image[leftIndex] : 0.0;
      float rightPixel = (x != ROWS - 1) ? image[rightIndex] : 0.0;

      float bottomLeftPixel =
          (y != COLUMNS - 1 && x != 0) ? image[bottomLeftIndex] : 0.0;
      float bottomMiddlePixel =
          (y != COLUMNS - 1) ? image[bottomMiddleIndex] : 0.0;
      float bottomRightPixel =
          (y != COLUMNS - 1 && x != ROWS - 1) ? image[bottomRightIndex] : 0.0;

      float value = topLeftPixel * constants[0] + topMiddlePixel * constants[1] + topRightPixel * constants[2] + leftPixel * constants[3] + image[pixelIndex] * constants[4] + rightPixel * constants[5] + bottomLeftPixel * constants[6] + bottomMiddlePixel * constants[7] + bottomRightPixel * constants[8];

      // printf("image[%d][%d] = %f\n", x, y, value);
      transformedImage[pixelIndex] = value;
    }
  }

  get_walltime(&te);

  printf("Megaflops: %f\n", (2.0 * (double)ROWS * COLUMNS) / ((te - ts) * 1e6));
  printf("Time taken: %f sec\n", (te - ts));

  free(image);
  free(transformedImage);

  return 0;
}