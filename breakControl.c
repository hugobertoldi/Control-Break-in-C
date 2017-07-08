#include <stdio.h>
#include <stdlib.h>

struct dataType
{
	char state[30];
	int city;
	int tax;
};

typedef struct dataType strDataType;

void menu();
void appendFile(FILE **fileTaxes);
void readFile(FILE **fileTaxes);
void appendData(FILE **fileTaxes);
void showData(FILE **fileTaxes);
void closeFile(FILE **fileTaxes);

int main ()
{
	menu();
	
	return 0;
}

void menu()
{
	FILE *fileTaxes;
	char op;
	
	do
	{
		printf("#1> Ingresar provincia, localidad e impuesto\n");
		printf("#2> Visualizar por pantalla los datos del archivo\n");
		printf("#0> Salir del programa\n");
		printf("#>> Cual opcion desea elegir? ");
		fflush(stdin);
		scanf("%c", &op);
		
		system("cls");
		
		switch (op)
		{
			case '1':
				appendFile(&fileTaxes);
				appendData(&fileTaxes);
				closeFile(&fileTaxes);
				printf("\n");
				break;
			
			case '2':
				readFile(&fileTaxes);
				showData(&fileTaxes);
				closeFile(&fileTaxes);
				printf("\n");
				break;
		}
		
	} while (op != '0' || op != '0');
}

void appendFile(FILE **fileTaxes)
{
	*fileTaxes = fopen("fileTaxes.dat", "ab");
}

void readFile(FILE **fileTaxes)
{
	*fileTaxes = fopen("fileTaxes.dat", "rb");
}

void appendData(FILE **fileTaxes)
{
	strDataType strStates;
	
	printf("Ingrese la provincia: ");
	fflush(stdin);
	scanf("%[^\n]", strStates.state);
	
	printf("Ingrese la localidad: ");
	fflush(stdin);
	scanf("%i", &strStates.city);
	
	printf("Ingrese los impuestos totales: ");
	fflush(stdin);
	scanf("%i", &strStates.tax);
	
	fwrite(&strStates, sizeof(strDataType), 1, *fileTaxes);
}

void showData(FILE **fileTaxes)
{
	strDataType strStates;
	
	printf ("%-20s %-20s %-10s\n\n", "Provincia", "Localidad", "Impuesto");
	
	while (fread(&strStates, sizeof(strDataType), 1, *fileTaxes))
	{
		printf ("%-20s %-20i %-10i\n", strStates.state, strStates.city, strStates.tax);
	}
}

void closeFile (FILE **fileTaxes)
{
	fclose (*fileTaxes);
}
