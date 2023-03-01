#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void main() {


	int projekt, wybrany;
	int L = 14;
	int projekty[13];

	srand(time(NULL));          //inicjalizacja generatora

	for (int i = 0; i < 13; i++)
	{
		do {
			wybrany = 1;
			projekt = rand() % L + 1;
			for (int j = 0; j < i; j++)
				if (projekty[j] == projekt) 
					wybrany = 0;
			if (wybrany == 1) projekty[i] = projekt;
		} while (wybrany != 1);
	}


	for (int i = 0; i < 13; i++) printf(" Wylosowana liczba to %d\n", projekty[i]);


}
