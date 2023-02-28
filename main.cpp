#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "winbgi2.h"

int main()
{
	graphics(800, 600);

	int i, j, k, l = 6, n = 100;
	double b = 5, a = -5;

	double x[6], y[6];
	double xi[6][100], yi[6][100];
	double xk[100] = { 0 }, yk[100] = { 0 };
	char osx[2] = "x", osy[2] = "y", tytul1[21] = "Wezly interpolacyjne", tytul2[15] = "Skladowe_wzoru", tytul3[6] = "Wynik";

	for (i = 0; i < l; i++) {
		x[i] = a + ((b - a) /((double)l - 1)) * i;
		y[i] = pow(x[i],2.);
		for (j = 0; j < n; j++)
		{
			xi[i][j] = a + ((b-a) / ((double)n - 1.0)) * j;
			if(i == 0) xk[j] = a + ((b - a) / ((double)n - 1.0)) * j;
			printf("%lf\n", xi[i][j]);
		}
	}


	chart(x, y, l, osx, osy, tytul1);
	wait();

	for (k = 0; k < l; k++) {
		for (i = 0; i < n; i++)
		{
			yi[k][i] = 1;
			for (j = 0; j < l; j++)
			{
				if (k == j)
					continue;

				yi[k][i] *= (xi[k][i] - x[j]) / (x[k] - x[j]);
			}
			yi[k][i] = y[k] * yi[k][i];
		}
	}
	for (i = 0; i < n; i++)
		printf("%lf, %lf\n", xi[0][i], yi[0][i]);


	for (k = 0; k < l; k++) {
		chart(xi[k], yi[k], n, osx, osy, tytul2);
		wait();
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < l; j++)
			yk[i] += yi[j][i];

	chart(xk, yk, n, osx, osy, tytul3);

	for (i = 0; i < l; i++) circle(x[i], y[i], 12);
	for (i = 0; i < n; i++) circle(xk[i], yk[i], 4);

	wait();

    return 0;
}
