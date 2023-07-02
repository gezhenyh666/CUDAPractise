#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int kM = 1024;
const int kK = 1024;
const int kN = 1024;
/*
A x B = C
for i in M:
  for j in N:
    for k in K:
      C[i][j] += A[i][k] * B[j][k]
*/

float** ConstructTwoDimArray(const int array_m, const int array_n) {
  float **two_dim_array = (float**)malloc(sizeof(float*) * array_m);

  for (int i = 0; i < array_m; i++) {
    two_dim_array[i] = (float*)malloc(sizeof(float) * array_n);
  }
  return two_dim_array;
}

void ConstructInputData(float** input_data, int array_m, int array_n) {
  for (int i = 0; i < array_m; i++) {
    for (int j = 0; j < array_n; j++) {
      input_data[i][j] = 1;
    }
  }
}

void CpuNaiveGemmwTwoDimArray(float **input_a, float **input_b, float **output_c) 
{
  for (int i = 0; i < kM; i++) {
    for (int j = 0; j < kN; j++) {
      for (int k = 0; k < kK; k++) {
        output_c[i][j] += input_a[i][k] * input_b[k][j];
      }
    }
  }
}

//程序数据引用的局部性
void CpuRecordingGemmwTwoDimArray(float **input_a, float **input_b, float **output_c) 
{
  for (int i = 0; i < kM; i++) {
    for (int k = 0; k < kK; k++) {
      for (int j = 0; j < kN; j++) {
        output_c[i][j] += input_a[i][k] * input_b[k][j];
      }
    }
  }
}

void ShowOputData(float** input_data, int array_m, int array_n) {
  for (int i = 0; i < array_m; i++) {
    for (int j = 0; j < array_n; j++) {
      printf("output data is %f\n", input_data[i][j]);
    }
  }
}

int main()
{
  float **input_a = ConstructTwoDimArray(kM, kK);
  float **input_b = ConstructTwoDimArray(kK, kN);
  float **output_c = ConstructTwoDimArray(kM, kN);
  
  ConstructInputData(input_a, kM, kN);
  ConstructInputData(input_b, kK, kN);
  clock_t start_time_naive, end_time_naive,
  start_time_recorder, end_time_recorder;
  start_time_naive = clock();
  CpuNaiveGemmwTwoDimArray(input_a, input_b, output_c);
  end_time_naive = clock();
  printf("Naive use time is %f s\n", double(end_time_naive - start_time_naive)/CLOCKS_PER_SEC);
  start_time_recorder = clock();
  CpuRecordingGemmwTwoDimArray(input_a, input_b, output_c);
  end_time_recorder = clock();
  printf("Record use time is %f s\n", double(end_time_recorder - start_time_recorder)/CLOCKS_PER_SEC);
  //ShowOputData(output_c, kM, kN);
  return 0;
}