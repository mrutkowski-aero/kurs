#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void main() {


	int proj, chosen;
	int L = 14; // Amount of projects
	int list[13]; // Number of students

	srand(time(NULL));

	for (int i = 0; i < 13; i++)
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

	printf("Students number \t Project number")
	for (int i = 0; i < 13; i++) printf("%3.0d \t %3.0d\n", i,list[i]);


}
