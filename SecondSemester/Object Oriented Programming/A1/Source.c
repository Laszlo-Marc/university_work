#include <stdio.h>

typedef struct {
	int array_structure[50], length_of_array;
}vector;

vector readVector(int number_of_elements) {
	vector list_of_integers;
	list_of_integers.length_of_array = number_of_elements;
	int i;
	for (i = 0; i < list_of_integers.length_of_array; i++) {
		printf("New element: ");
		scanf("%d", &list_of_integers.array_structure[i]);
	}
	return list_of_integers;
}

int isPrime(int CheckedPositiveNumber) {
	int i;
	for (i = 2; i < CheckedPositiveNumber / 2; i++) {
		if (CheckedPositiveNumber % i == 0)
			return 0;
	}
	return 1;
}
void longestContiguousSubsequenceOfPrimeNumbers(vector arr, int* subsequence_start, int* subsequence_end) {
	int maximum_length = 0, subsequence_length = 0, j;
	*subsequence_start = 0;
	*subsequence_end = 0;
	for (int i = 0; i < arr.length_of_array; i++)
	{
		j = i + 1;
		while (j < arr.length_of_array && isPrime(arr.array_structure[j]))
		{
			j++;
		}
		subsequence_length = j - i;
		if (subsequence_length > maximum_length) {
			*subsequence_start = i;
			*subsequence_end = j;
			maximum_length = subsequence_length;
		}
	}
}
void printSubsequence(vector array_for_subsequence, int subsequence_start, int subsequence_end) {

	printf("The longest array is: ");
	for (int i = subsequence_start + 1; i < subsequence_end; i++) {
		printf("%d", array_for_subsequence.array_structure[i]);
		printf(" ");
	}
	printf("\n");
}

void PrintingPascalTriangle(int triangle_dimension) {
	int line, k, i, combination;
	for (line = 1; line <= triangle_dimension; line++) {
		combination = 1;
		for (i = 1; i <= line; i++) {
			printf("%d ", combination);
			combination = combination * (line - i) / i;
		}
		printf("\n");
	}

	printf("\nCombinations: \n");
	for (line = 1; line <= triangle_dimension; line++) {
		printf("Line %d: ", line);
		for (k = 0; k <= line; k++) {
			combination = 1;
			for (i = 1; i <= k; i++) {
				combination = combination * (line - i + 1) / i;
			}
			printf("%d ", combination);
		}
		printf("\n");
	}

}
int main() {
	int continue_loop = 1, option, triangle_dimension, number_of_elements, start_of_subsequence = 0, end_of_subsequence = 0;
	vector array_for_subsequence;
	while (continue_loop == 1)
	{
		printf("Option 1:Print the Pascal triangle of dimension n\n");
		printf("Option 2: Longest subsequence of prime numbers\n");
		printf("Option 3: Exit\n");
		printf("Select option: ");
		scanf("%d", &option);
		if (option == 3)
			continue_loop = 0;

		if (option == 2)
		{
			printf("Number of elements: ");
			scanf("%d", &number_of_elements);
			array_for_subsequence = readVector(number_of_elements);
			longestContiguousSubsequenceOfPrimeNumbers(array_for_subsequence, &start_of_subsequence, &end_of_subsequence);
			printSubsequence(array_for_subsequence, start_of_subsequence, end_of_subsequence);

		}
		if (option == 1)
		{
			printf("Enter the dimension of Pascal Triangle: ");
			scanf("%d", &triangle_dimension);
			PrintingPascalTriangle(triangle_dimension);
		}

	}

	return 0;
}