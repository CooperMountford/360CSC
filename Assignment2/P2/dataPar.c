#include <float.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SAR_calc(double data[], int datapoints) {
  double slope = 0;
  double intercept = 0;
  double sum = 0;
  double temp_sum = DBL_MAX; // use DBL_MAX to minimize sum
  double temp_slope = 0;
  double temp_intercept = 0;

  for (int x = 1; x < (datapoints + 1); x++) { // loop through each datapoint pair
    for (int y = datapoints; y > x; y--) {
      slope = (data[y] - data[x - 1]) / (y - (x - 1));
      intercept = data[x - 1] - ((x - 1) * slope);

      sum = 0;
      for (int h = 0; h < datapoints; h++) { // calculate SAR of line
        sum = sum + fabs(data[h] - ((slope * h) + intercept));
      }
      if (sum < temp_sum) { // minimize SAR
        temp_sum = sum;
        temp_slope = slope;
        temp_intercept = intercept;
        }
    }
  }
  printf("\n%d Point SAR: %lf\n", datapoints, temp_sum);
  printf("\tIntercept: %lf\n", temp_intercept);
  printf("\tSlope: %lf\n", temp_slope);
}

int main(int argc, char **argv) {
  FILE *my_file = fopen("starterdata.txt", "r");
  double records[18];
  size_t count = 0;

  for (; count < sizeof(records) / sizeof(records[0]); ++count) { // scan data
    int got = fscanf(my_file, "%lf", &records[count]);
    if (got != 1) // eof
      break;
  }
  fclose(my_file);

  SAR_calc(records, 6);
  SAR_calc(records, 10);
  SAR_calc(records, 14);
  SAR_calc(records, 18);

  // clock_t begin = clock(); // begin execution timer
  // clock_t end = clock(); // end execution timer
  // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  // printf("Time Spent: %f\n", time_spent);

  return 0;
}