#include "Funtions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long int get_result(int nr_numere, int dimension, unsigned short *numere,
                    unsigned short *operand, int x, char *vect_operatori) {
  long int rezult = 0;

  int k = 0;
  for (int i = 0; i < nr_numere; i++) {
    scanf("%hu", &numere[i]);
    for (int j = 0; j < x; j++) {
      operand[j] = numere[i] << (dimension * j);
      operand[j] = operand[j] >> (dimension * (x - 1));
      if ((i == 0) && (j == 0)) {
        rezult = operand[0];
      } else {
        rezult = rezult;

        switch (vect_operatori[k]) {
        case '+':
          rezult = operand[j] + rezult;
          break;
        case '-':
          rezult = rezult - operand[j];
          break;
        case '*':
          rezult = rezult * operand[j];
          break;
        case '/':
          rezult = rezult / operand[j];
          break;
        }

        k++;
      }
    }
  }
  return rezult;
}

int main() {

  struct timespec start_time, end_time;
  double execution_time;

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  unsigned int inst = 0;
  scanf("%u", &inst);

  int N = 0;
  N = get_number_of_instruction(inst);

  unsigned short *numere = calloc(NR_MAX_numere, sizeof(unsigned short));
  char *vect_operatori = calloc(NR_MAX_numere, sizeof(char));

  initialize_operators(vect_operatori, inst, N);

  unsigned int dimension = get_dimension(inst, N);
  int x;
  x = 16 / dimension;

  // nr_numere is a variable used to store the number of unsigned short numbers
  // (operands) that need to be read from the input
  int nr_numere = get_nr_of_op(dimension, N);

  unsigned short *operand = calloc(NR_MAX_numere, sizeof(unsigned short));

  long int rezult =
      get_result(nr_numere, dimension, numere, operand, x, vect_operatori);

  printf("%ld\n", rezult);

  free_memory(operand, numere, vect_operatori);

  clock_gettime(CLOCK_MONOTONIC, &end_time);
  execution_time = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  FILE *output_file = fopen("execution_time_task2.txt", "w");
  if (output_file == NULL) {
    printf("Error opening the output file.\n");
    return 1;
  }

  fprintf(output_file, "Execution time: %.7f seconds\n", execution_time);
  fclose(output_file);

  return 0;
}