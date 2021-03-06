
#include<stdio.h>

void createMatrices() {

}


int main()
{
	//DATA
	float A1[10][10] = {
		{ 1.31472369,-0.34238692,0.1557407,0.20604609,-0.06125564,-0.22397492,0.25126706,0.34071726,-0.14834049,-0.42414571 },
		{ 0.40579194,1.47059278,-0.46428832,-0.46816715,-0.11844154,0.17970268,-0.24490488,-0.24571782,0.33082863,-0.44604988 },
		{ -0.37301318,0.45716695,1.34912931,-0.22307702,0.26551679,0.155098,0.00595705,0.31428483,0.08526409,0.03079755 },
		{ 0.41337586,-0.01462435,0.43399325,0.54617139,0.2951999,-0.33738826,0.19907672,-0.25647503,0.04972361,0.27916723 },
		{ 0.13235925,0.30028047,0.17873515,-0.40286822,0.6868726,-0.38100232,0.39090325,0.42926362,0.41719366,0.43401068 },
		{ -0.4024596,-0.35811366,0.25774013,0.32345783,-0.0102356,0.99836405,0.45929143,-0.15001623,-0.21416098,-0.37009379 },
		{ -0.22150178,-0.07823872,0.24313247,0.19482862,-0.0544138,0.45974396,1.04721553,-0.30340475,0.25720023,0.06882366 },
		{ 0.04688152,0.41573553,-0.10777298,-0.18290052,0.14631301,-0.15961427,-0.36137556,0.75108386,0.25372909,-0.03060936 },
		{ 0.45750684,0.29220733,0.15547789,0.45022205,0.20936483,0.08526775,-0.35070599,0.11604468,0.88044585,-0.48809793 },
		{ 0.46488854,0.45949243,-0.32881331,-0.46555392,0.25468668,-0.27618806,-0.24249175,-0.02671115,0.06782164,0.83712264 }
	};


	//CODE
	int i, j, k, order;
	order = 10;

	float A[10][10], c, x[10], sum = 0.0;

	for (int row = 0; row < order; row++) {
		for (int column = 0; column < order; column++) {
			A[row][column] = A1[row][column];
		}
	}

	for (j = 1; j <= order; j++) 
	{
		for (i = 1; i <= order; i++)
		{
			if (i>j)
			{
				c = A[i][j] / A[j][j];
				for (k = 1; k <= order + 1; k++)
				{
					A[i][k] = A[i][k] - c*A[j][k];
				}
			}
		}
	}
	x[order] = A[order][order + 1] / A[order][order];

	for (i = order - 1; i >= 1; i--)
	{
		sum = 0;
		for (j = i + 1; j <= order; j++)
		{
			sum = sum + A[i][j] * x[j];
		}
		x[i] = (A[i][order + 1] - sum) / A[i][i];
	}
	printf("\nThe solution is: \n");
	for (i = 1; i <= order; i++)
	{
		printf("\nx%d=%f\t", i, x[i]);
	}
	getchar();
	getchar();
	return(0);
}