#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//Program losujący raporty
void main() {
	int a;
	int proj, chosen;
	int L = 24; // Amount of projects
	int N = 14; // Number of students
	int* list; list = (int*)malloc(N * sizeof(int));

	srand(time(NULL));

	for (int i = 0; i < N; i++)
	{
		do {
			chosen = 1;
			proj = rand() % L + 1;
			for (int j = 0; j < i; j++) //check if project is already generated
				if (list[j] == proj)
					chosen = 0;
			if (chosen == 1) list[i] = proj; // Project number is unique, give it to i'th student
		} while (chosen != 1); // Until generated project is not unique - iterate
	}

	printf("Students number \t Project number\n");
	for (int i = 0; i < N; i++) printf("%3.0d \t %3.0d\n", i+1, list[i]);

	free(list);
}
