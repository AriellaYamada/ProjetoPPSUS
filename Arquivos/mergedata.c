#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEPARATOR ","

//Funcao para ler a linha até encontrar o '\n'
char *readline(FILE *data) {
	int size = 0;
	char c[2];
	char *reg = (char *) malloc ((size + 1) * sizeof(char));
	if (fscanf(data, "%c", c) != EOF) {
		while(strcmp(c, "\n") != 0) {
			reg[size] = c[0];
			size++;
			reg = (char *) realloc (reg, (size + 1) * sizeof(char));
			fscanf(data, "%c", c);
		}
		strcpy(c, "\0");
		reg[size] = c[0];
		return reg;
	}
	return NULL;
}

int main (){

	//Recebe a quantidade de arquivos a serem concatenados
	int n_files;
	scanf("%d", &n_files);

	//Le os arquivos a serem concatenados
	int i;
	char filenames[n_files][20];
	for (i = 0; i < n_files; i++) {
		//printf("File %d: ", i);
		scanf("%s", filenames[i]);
	}
	
/*	//Le o nome do arquivo final a ser gerado
	char file[20];
	//printf("Filename: ");
	scanf("%s", file);
*/
	//Abertura de todos os arquivos
	FILE *final = fopen(filenames[0], "w+");

	fseek(final, 0, SEEK_END);

	FILE *registers;

	for (i = 1; i < n_files; i++) {
		registers = fopen(filenames[i], "r+");
		char *line = readline(registers);;
		while(line != NULL) {
			free(line);
			line = readline(registers);
			strcat(line, "\n");
			fprintf(final, "%s", line);
			//free(line);
		}
		fclose(registers);
	}

	fclose(final);

	return 0;
}
