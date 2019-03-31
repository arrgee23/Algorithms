#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define INCREMENT_SIZE 5000
#define START_SIZE 10000
#define END_SIZE 150001
#define BIG_INT 99999999
#define MAX_ARR_SIZE 150001
#define ITERATION_FOR_AVG 5
#define DEBUG

struct pair
{
    int x;
    int y;
};
typedef struct pair PAIR;

struct triple
{
    int compCount;
    int swapCount;
    double time;
};
typedef struct triple TRIPLE;

void printArr(int* arr,int n);
void printRange(int* arr,int l,int r);

// insertionsort
void insertionSort(int arr[], int n);

// returns pivot index
int partition(int *arr,int l,int r,TRIPLE* t);
void quickSort(int* arr,int l,int r,TRIPLE* t);
void quickSortItr(int* arr, int len,TRIPLE* t);


int min(int a,int b);


int left(int i,int len);
int right(int i,int len);
int parent(int i);


// heapsort related
void maxHeapify(int* a,int len,TRIPLE* t);
void heapSort(int* a,int len,TRIPLE* t) ;
// moves the element conseptually high in the tree if suitable
void siftUp(int* arr,int i,int len,TRIPLE* t);
void siftDown(int* a,int i,int len,TRIPLE* t);

// heapsort iterative
int extractMaxIter(int* arr,int len, TRIPLE* t);
void maxHeapifyIter(int* a,int len, TRIPLE* t);
void heapSortIter(int* a,int len,TRIPLE* t) ;
void siftDownIter(int* a,int i,int len, TRIPLE* t);

// merge sort
void mergeSortIter(int* arr,int l, int r,TRIPLE* t);
void mergeSort(int* arr,int l, int r,TRIPLE* t);
void merge(int* arr,int l,int m,int r,TRIPLE* t);


int* generateRandArr(int size);
int verifySorted(int* arr,int n);


// main interface function
TRIPLE quickSortIF(int* arr,int l,int r);

TRIPLE quickSortIterativeIF(int* arr,int l,int r);

TRIPLE mergeSortIF(int* arr,int l,int r);

TRIPLE mergeSortIterativeIF(int* arr,int l,int r);

TRIPLE heapSortIF(int* arr,int l,int r);

TRIPLE heapSortIterativeIF(int* arr,int l,int r);


#endif