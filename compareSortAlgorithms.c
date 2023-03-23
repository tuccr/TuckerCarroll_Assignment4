#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;
// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void mergeSort(int pData[], int l, int r) {
	if(l < r) {
		int m = ((l + r) / 2);
		mergeSort(pData, m+1, r);
		mergeSort(pData, l, m);

		int sizeL = m - l + 1;
		int sizeR = r - m;

		int * tempL = (int *)malloc(sizeof(int) * sizeL);
		for(int i = 0; i < (m-l+1); ++i) {
			tempL[i] = pData[l + i];
		}

		int * tempR = (int *)malloc(sizeof(int) * sizeR);
		for(int i = 0; i < (r - m); ++i) {
			tempR[i] = pData[m + i + 1];
		}

		int iL = 0;
		int iR = 0;
		int k = l;
		while(iL < sizeL && iR < sizeR) {
			if(tempL[iL] <= tempR[iR]) {
				pData[k] = tempL[iL];
				++iL;
			}
			else {
				pData[k] = tempR[iR];
				++iR;
			}
			++k;
		}
	
		while(iL < sizeL) {
			pData[k] = tempL[iL];
			++iL;
			++k;
		}
		while(iR < sizeR) {
			pData[k] = tempR[iR];
			++iR;
			++k;
		}
		free(tempL);
		free(tempR);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int temp;
    for(int i = 1; i < n; i++) {  
        temp = pData[i];
        int j = i - 1;
        while(j >= 0 && pData[j] > temp) { 
            pData[j + 1] = pData[j];
            j--;
        }
        pData[j+1] = temp; 
    }
}


// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int temp;
	for(int i = 0; i < (n-1); ++i) {
		for(int j = 0; j < (n-i-1);++j) {
			if(pData[j] > pData[j+1]) {
				temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int minI, temp;
    for(int i = 0; i < n; ++i) {
        minI = i;
        for(int j = i; j < n; ++j) {
            if(pData[j] < pData[minI]) {
                minI = j;
            }
        }
        temp = pData[i];
        pData[i] = pData[minI];
        pData[minI] = temp;
    }
}


// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile) {
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++) {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }
	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz); 
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);  
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1); 
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}
	
}