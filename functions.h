#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define INCREMENT_SIZE 5000

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

void printArr(int* arr,int n);
void printRange(int* arr,int l,int r);

// insertionsort
void insertionSort(int arr[], int n);

// returns pivot index
int partition(int *arr,int l,int r);
void quickSort(int* arr,int l,int r);
void quickSortItr(int* arr, int len);
void merge(int* arr,int l,int m,int r);
int min(int a,int b);


// heapsort related
void maxHeapify(int* a,int len);
void heapSort(int* a,int len) ;
// moves the element conseptually high in the tree if suitable
void siftUp(int* arr,int i,int len);
void siftDown(int* a,int i,int len);
int left(int i,int len);
int right(int i,int len);
int parent(int i);

// heapsort iterative
int extractMaxIter(int* arr,int len);
void maxHeapifyIter(int* a,int len);
void heapSortIter(int* a,int len) ;
void siftDownIter(int* a,int i,int len);

// merge sort
void mergeSortIter(int* arr,int l, int r);
void mergeSort(int* arr,int l, int r);


int* generateRandArr(int size);
int verifySorted(int* arr,int n);

#endif