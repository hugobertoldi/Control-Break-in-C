#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dataType
{
	char state[30];
	int city;
	int tax;
};

typedef struct dataType strDataType;

void openFile(FILE **fileTaxes);
void breakControl(FILE **fileTaxes);
void cleanString(char str[]);
int compareString(char str1[], char str2[]);
void closeFile(FILE **fileTaxes);

int main()
{
	FILE *fileTaxes;
	
	openFile(&fileTaxes);
	breakControl(&fileTaxes);
	closeFile(&fileTaxes);
	
	system("pause");
}

void openFile(FILE **fileTaxes)
{
	*fileTaxes = fopen("fileTaxes.bin", "rb");
	
	if (*fileTaxes == NULL)
	{
		exit(1);
	}
}

void breakControl(FILE **fileTaxes)
{
	strDataType strState;
	
	char breakState[30] = "";
	int breakCity = 0;
	int totalTaxes = 0;
	
	printf ("%-20s %-20s %-10s\n\n", "State", "City", "Total Taxes");
	
	fread(&strState, sizeof(strDataType), 1, *fileTaxes);
	
	while (!feof(*fileTaxes))
	{
		strcpy (breakState, strState.state);
		breakCity = strState.city;
		
		while (compareString(breakState, strState.state) == 1 && !feof(*fileTaxes))
		{
			while (breakCity == strState.city && !feof(*fileTaxes))
			{
				totalTaxes += strState.tax;
				fread(&strState, sizeof(strDataType), 1, *fileTaxes);
			}

			printf ("%-20s %-20i %-10i\n", breakState, breakCity, totalTaxes);
		
			totalTaxes = 0;
		
			breakCity = strState.city;
		}
		
		cleanString(breakState);
	}
}

void cleanString(char str[])
{
	for (int i = 0; i < 30; i++)
	{
		str[i] = '\0';
	}
}

int compareString(char str1[], char str2[])
{
	int aux = 1;
	int lenght;
	
	lenght = strlen(str1);
	
	for (int i = 0; i < lenght; i++)
	{
		if (str1[i] != str2[i])
		{
			aux = 0;
			break;
		}
	}
	
	return aux;
}

void closeFile(FILE **fileTaxes)
{
	fclose(*fileTaxes);
}
