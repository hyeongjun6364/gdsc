/*-----------------------------------------------------------------------
Sorting(정렬) 문제. 다음 정렬 방법을 이용해서 정렬을 구현하고 각 정렬 방법의 수행시간을
비교해 본다.
- Selection sort
- Bubble sort
- Insertion sort
- Merge sort
- Quick sort
- Counting sort
- Radix sort
- Heap sort

입력:
각 입력은 다음과 같이 구성되어 있다.
입력 file 형식
K     // 정렬을 위한 입력 케이스의 수
N1 n1 n2 n3 ... nN1....   // 정렬을 위한 첫 번째 숫자 리스트
N2 n1 n2 n3 ... nN2....   // 정렬을 위한 두 번째 숫자 리스트
N3 n1 n2 n3 ... nN3....   // 정렬을 위한 세 번째 숫자 리스트
:
:

조건:
1. 정렬을 위한 입력 케이스의 수는 10이다.
2. 입력되는 숫자의 갯수는 [1, 100000]이다.
3. 입력되는 숫자의 크기는 [1, 100000]이다.

예시)
입력: input_sortings.txt
3
4 10 20 30 40
3 50 60 70
7 4 5 6 7 6 8 2

출력: output_sortings.txt
10
20
30
40

50
60
70

2
4
5
6
6
7
8

정답은 expected_sortings.txt로 주어짐
결과는 output_sortings.txt file로 출력해야 함

주어진 함수에는 프로그래밍 언어에서 제공하는 정렬 기법을 이용해 정렬이 구현되어 있음.
주어진 정렬 기법을 이용해서 각 정렬 함수를 새롭게 구현하시오. 프로그래밍 언어에서 제공되는
정렬 함수, sort()등을 이용하면 안됨
-----------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100000
int sorted[MAX];
int comp(const void *a, const void *b)
{
    if (*(int *)a > *(int *)b) return  1;
    if (*(int *)a < *(int *)b) return -1;
    return 0;
}

int* selectionsort(int *nums, int N)
{
    
    //qsort(nums, N, sizeof(int), comp);

    int temp;
    //const int N = sizeof(nums) / sizeof(int);
    //int res[size];
    int pos;
    for (int i = 0; i < N; i++) {
        int max = 0;
        for (int j = 0; j < N - i; j++) {

            if (max < nums[j]) {
                max = nums[j];
                pos = j;
            }
        }
        temp = nums[N - 1 - i];
        nums[N - i - 1] = max;
        nums[pos] = temp;



    }
    
    return(nums);
}

int* bubblesort(int *nums, int N)
{
    //qsort(nums, N, sizeof(int), comp);

    int max = nums[0];
    //const int N = sizeof(nums) / sizeof(int);
    int temp;
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;

            }
        }
    }
    return(nums);
}

int* insertionsort(int *nums, int N)
{
    
    int count = 0;
    int temp;
    for (int i = 0; i < N - 1; i++) {
        count = i;
        while (nums[count] > nums[count + 1]) {
            temp = nums[count];
            nums[count] = nums[count + 1];
            nums[count + 1] = temp;
            count--;
        }

    }
    return(nums);
}
void merge(int* nums, int left, int mid, int right) {
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;

    
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j])
            sorted[k++] = nums[i++];
        else
            sorted[k++] = nums[j++];
    }

    
    if (i > mid) {
        for (l = j; l <= right; l++)
            sorted[k++] = nums[l];
    }

    
    else {
        for (l = i; l <= mid; l++)
            sorted[k++] = nums[l];
    }

    
    for (l = left; l <= right; l++) {
        nums[l] = sorted[l];
    }
}
int* mergesort(int *nums, int N,int left,int right)
{
    int mid;

    if (left < right) {
        mid = (left + right) / 2;
        mergesort(nums, N,left, mid); 
        mergesort(nums, N,mid + 1, right); 
        merge(nums, left, mid, right); 
    }
    
   
    return(nums);
}

int* quicksort(int *nums, int start,int N)
{
    if (start >= N) {
        return;
    }

    int pivot = start;	 
    int i = pivot + 1;	 
    int j = N;	 
    int temp;

    while (i <= j) {
       
        while (i <= N && nums[i] <= nums[pivot]) {
            ++i;
        }
        
        while (j > start && nums[j] >= nums[pivot]) {
            --j;
        }

        
        if (i >= j) break;

        
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    
    temp = nums[j];
    nums[j] = nums[pivot];
    nums[pivot] = temp;

    quicksort(nums, start, j - 1);	
    quicksort(nums, j + 1, N);	
    return(nums);
}

int* countingsort(int *nums, int N)
{
    
    int max = 0, i;
    for (i = 0; i < N; i++)
    {
        if (nums[i] > max)
            max = nums[i];
    }
    int* output = (int*)malloc(sizeof(int) * N);
    int* counting = (int*)malloc(sizeof(int) * max);
    for (i = 0; i < max; i++)
        counting[i] = 0;
       
    for (i = 0; i < N; i++)
        counting[nums[i] - 1]++;   
    for (i = 1; i < max; i++)
        counting[i] += counting[i - 1];
      
    for (i = N - 1; i >= 0; i--)
    {
        output[counting[nums[i] - 1] - 1] = nums[i];
        counting[nums[i] - 1]--;
    }
     
    for (i = 0; i < N; i++)
        nums[i] = output[i];
    return(nums);
}

int* radixsort(int *nums, int N)
{
    
    int result[MAX], maxValue = 0;
    int exp = 1;
    for (int i = 0; i < N; i++) {
        if (nums[i] > maxValue) 
            maxValue = nums[i];
    }
    while (maxValue / exp > 0) { 
        int count[10] = { 0 };
        for (int i = 0; i < N; i++) 
            count[nums[i] / exp % 10]++; 
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1]; 
        for (int i = N - 1; i >= 0; i--) { 
            result[--count[nums[i] / exp % 10]] = nums[i];
        }
        for (int i = 0; i < N; i++) 
            nums[i] = result[i]; 
        exp *= 10;
    }
    return(nums);
}
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int * nums, int N, int i) {
    
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && nums[left] > nums[large])
        large = left;

    if (right < N && nums[right] > nums[large])
        large = right;

    
    if (large != i) {
        swap(&nums[i], &nums[large]);
        heapify(nums, N, large);
    }
}
int* heapsort(int *nums, int N)
{
    // max heap
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(nums, N, i);
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
        swap(&nums[0], &nums[i]);
        heapify(nums, i, 0);
    }
    
    return(nums);
}

void compare_output(char *, char *);

int main()
{
    // DO NOT EDIT main() function

    int K, N, i, j, k, m;
    int *sorting_results = NULL;
    int nums[100000];
    char method[256];
    clock_t start_time, end_time;

    FILE *input;
    FILE *output;

    for(m=0; m<8; m++) {
        input = fopen("input_sortings.txt", "r");          // input data
        output = fopen("output_sortings.txt", "w");        // your answer

        fscanf(input, "%i", &K);
        start_time = clock();
        for(i=0; i<K; i++) {
            fscanf(input, "%i", &N);
            for(j=0; j<N; j++) {
                fscanf(input, "%i", &nums[j]);
            }


            switch(m) {
                case 0: sorting_results = selectionsort(nums, N); strcpy(method, "selection"); break;
                case 1: sorting_results = bubblesort(nums, N); strcpy(method, "bubble"); break;
                case 2: sorting_results = insertionsort(nums, N); strcpy(method, "insertion"); break;
                case 3: sorting_results = mergesort(nums, N,0,N-1); strcpy(method, "merge"); break;
                case 4: sorting_results = quicksort(nums, 0,N-1); strcpy(method, "quick"); break;
                case 5: sorting_results = countingsort(nums, N); strcpy(method, "counting"); break;
                case 6: sorting_results = radixsort(nums, N); strcpy(method, "radix"); break;
                case 7: sorting_results = heapsort(nums, N); strcpy(method, "heap");break;
                default: break;
            }
            for(k=0; k<N; k++) {
                fprintf(output, "%d\n", sorting_results[k]);
                fflush(output);
            }
            fprintf(output, "\n");
        }
        end_time = clock();

        // Checking answers
        fclose(input);
        fclose(output);
        printf("Elapsed time: %.2f seconds. ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
        printf("Comparison results for %s sorting methods: ", method);
        compare_output("output_sortings.txt", "expected_sortings.txt");
    }
}

void compare_output(char *file1, char *file2)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    char line1[10000], line2[10000];
    char *s1, *s2;
    int i = 1;
    int success = 1;

    while(!feof(f1) && !feof(f2)) {
        fgets(line1, 10000, f1);
        fgets(line2, 10000, f2);
        s1 = line1;
        s2 = line2;
        while(*s1 == ' ') s1++;
        while(s1[strlen(s1)-1] == ' ' || s1[strlen(s1)-1] == '\n' || s1[strlen(s1)-1] == '\r') s1[strlen(s1)-1] = '\0';
        while(*s2 == ' ') s2++;
        while(s2[strlen(s2)-1] == ' ' || s2[strlen(s2)-1] == '\n' || s2[strlen(s2)-1] == '\r') s2[strlen(s2)-1] = '\0';
        if (strcmp(s1, s2)) {
            printf("[%i] Wrong answer: Yours=\'%s\', Expected=\'%s\'\n", i, s1, s2);
            success = 0;
            break;
        }
        i++;
    }
    if (feof(f2) && success) printf("Success!\n");
    fclose(f1);
    fclose(f2);
}
