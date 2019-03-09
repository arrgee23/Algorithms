#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define BIG_INT 99999999
#define MAX_ARR_SIZE 1000001
#define ITERATION_FOR_AVG 5
#define DEBUG
void printArr(int* arr,int n);
void printRange(int* arr,int l,int r);
// returns pivot index
int partition(int *arr,int l,int r);

void quickSort(int* arr,int l,int r);
void merge(int* arr,int l,int m,int r);
int min(int a,int b);
void mergeSortIter(int* arr,int l, int r);
void mergeSort(int* arr,int l, int r);
int* generateRandArr(int size);
int verifySorted(int* arr,int n);
#endif