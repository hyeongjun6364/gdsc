#include<stdio.h>

int main() {
	int nums[] = { 8, 31,48, 73, 3, 65, 20, 29, 11, 15 };
	int N = sizeof(nums) / sizeof(int);
	int temp;
	int count=0;
	int root;
	//heapify
	for (int i = 1; i < N ; i++) {
		int j = i;
		do {
			root = (j - 1) / 2;
			if (nums[j] > nums[root]) {
				temp = nums[j];
				nums[j] = nums[root];
				nums[root] = temp;
				
			}
			j = root;
		} while (j>0);
	}
	for (int i = 0; i < N; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");
	//크기줄여가며 반복적 힙구성
	for (int i = N - 1; i >= 0; i--) {
		int root = 0;
		temp = nums[i];
		nums[i] = nums[0];
		nums[0] = temp;
		int child=1;
		do {
			child = 2 * root + 1;
			//자식중에 더큰값찾기
			if (nums[child] < nums[child + 1] && child<i-1) {
				child++;
			}
			if (nums[root] < nums[child] && child < i - 1) {
				temp = nums[child];
				nums[child] = nums[root];
				nums[root] = temp;
			}
			root = child;
		} while (child<i-1);
		
	}
	for (int i = 0; i < N; i++) {
		printf("%d ", nums[i]);
	}
}