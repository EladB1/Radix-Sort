#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

void correct(int* src, int size);

int cntNegatives(int* array, int size){
	int i, cnt = 0;
	for(i = 0; i < size; i++){
		if(array[i] < 0)
			cnt++;
	}	
	return cnt;
} 

int* negativeIndexes(int* array, int size){
	int numOfNegatives = cntNegatives(array, size);
	int* neg = malloc(sizeof(int) * numOfNegatives);
	int i, cnt = 0;
	for(i = 0; i < size; i++){
		if(array[i] < 0){
			neg[cnt] = i;
			cnt++;
		}
	}
	return neg;
}

int* randomizeArray(int size, int maxVal, int minVal){ 
	int* temp = malloc(sizeof(int) * size);
	int i;
	for(i = 0; i < size; i++)
		temp[i] = (rand() % maxVal) + minVal;
	return temp;
}	

void printArray(int* arr, int size){
  int num;
  for(num = 0; num < size; num++){ //start at 1 if these are arrays of command line args
    printf("%d ", arr[num]); 
  }
  printf("\n");
}

void rSort(int* src, int size, int radix){
	int* temp = malloc(sizeof(int) * size);
	int i, j;
	int buckets = 1 << radix;
	int *cnt = malloc(sizeof(int) * buckets);
	int *map = malloc(sizeof(int) * buckets);
	if(src[i] < 0){
		//count-count each instance of a digit
		for(i = 0; i < size; i++){
				cnt[(~src[i]) & (buckets-1)]++;
		}

		//map-map each element to its appropriate place in the array based on which ever digit you're on		
j = 0;
		for(i = 0; i < buckets; i++){
			map[i] = j;
			j = map[i] + cnt[i];
		}

		//move-move each element to its appropriate position based on where it's mapped to
		for(i = 0; i < size; i++){
				temp[map[(~src[i])&(buckets-1)]++] = src[i];
		}
	
		//place into original array
		for(i = 0; i < size; i++){
			src[i] = temp[i];
		}
	}
	else{
		//count-count each instance of a digit
		for(i = 0; i < size; i++){
				cnt[(src[i]) & (buckets-1)]++;
		}

		//map-map each element to its appropriate place in the array based on which ever digit you're on
		j = 0;
		for(i = 0; i < buckets; i++){
			map[i] = j;
			j = map[i] + cnt[i];
		}

		//move-move each element to its appropriate position based on where it's mapped to
		for(i = 0; i < size; i++){
				temp[map[(src[i])&(buckets-1)]++] = src[i];
		}
	
		//place into original array
		for(i = 0; i < size; i++){
			src[i] = temp[i];
		}
	}
	free(temp);
	free(cnt);
	free(map);
}
void radixSort(int* src, int size){
	int i, radix = 16;
	for(i = 0; i < 32; i+=radix){ //pass through the array twice
		rSort(src, size, i);
	}
	if(cntNegatives(src, size) != 0)
		correct(src, size);
}
bool isSorted(int* arr, int size){
	printf("\nArray size: %d\n", size);
	int i;
	for(i = 0; i < size; i++){
		if(i == 0){
			if(arr[0] > arr[1]){
				printf("\nThe array was NOT sorted correctly.\n");
				return false;
			}
		}
		else if(i >= 1){
			if(arr[i] < arr[i-1]){
				printf("\nThe array was NOT sorted correctly.\n");
				return false;
			}
		}
	}
	printf("\nThe array was sorted correctly!\n");
	return true;
}

void correct(int* semiSortedArray, int size){
	int* newArray = malloc(sizeof(int) * size);
	int* negatives = negativeIndexes(semiSortedArray, size);
	int num = cntNegatives(semiSortedArray, size);
	int i, j = 0;
	for(i = 0; i < num; i++)
		newArray[i] = semiSortedArray[negatives[i]];
 	for(i = num; i < size; i++){
		newArray[i] = semiSortedArray[j];
		j++;
	}
	for(i = 0; i < size; i++)
		semiSortedArray[i] = newArray[i];
	free(newArray);
}

int main(){
	int a[5] = {300, -1056, -111, 0, -301}; //small array to try things out on
	int num = 5000; //amount of elements to print
	int num2 = 1000000; //size of the array to be sorted; 1,000,000 performs pretty well
	int* A = randomizeArray(num2, 65000, 0); //can only sort 450,000,000 values up to 65000
	printf("Before: ");
	printArray(A, num);
	//printArray(a, 5);
	printf("\n");
	printf("After: ");
	radixSort(A, num2);
	printArray(A, num);
	isSorted(A, num2);
	/*radixSort(a, 5);
	printArray(a, 5);
	isSorted(a, 5);*/
	printf("\n");
	
	return 0;
}
