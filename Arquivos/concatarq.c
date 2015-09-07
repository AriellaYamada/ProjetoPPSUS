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

int getKey (char *reg) {
	char key[6];
	int i;
	for (i = 1; i < 5; i++) {
		key[i-1] = reg[i];
	}
	key[4] = '\0';
	return atoi(key);
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
	
	//Le o nome do arquivo final a ser gerado
	char file[20];
	//printf("Filename: ");
	scanf("%s", file);

	//Abertura de todos os arquivos
	FILE *final = fopen(file, "w+");
	
	FILE **registers = (FILE **) malloc (n_files * sizeof(FILE *));
	for (i = 0; i < n_files; i++) {
		registers[i] = fopen(filenames[i], "r+");
	}	
	
	int keyLine, keyNext, end = 0;

	do {
		//Le a linha do primeiro arquivo
		char *line = readline(registers[0]);
		if(line != NULL) {
			//Busca a chave da linha
			keyLine = getKey(line);
			//Concatena com todas as linhas de mesmo numero dos outros arquivos
			for (i = 1; i < n_files; i++) {
				//Busca a linha do arquivo ate que a chave seja a mesma
				char *new;
				do {
					new = readline(registers[i]);
					if (new != NULL) 
						keyNext = getKey(new);
				} while (new != NULL && keyNext != keyLine);
				//Caso encontre, concatena
				if (keyNext == keyLine) {
					int size = strlen(new) + strlen(line) + 2;
					line = (char *) realloc (line, size * sizeof(char));
					strcat(line, SEPARATOR);
					strcat(line, new);
					free(new);
				//Caso contrario, volta ao comeco do arquivo e exibe mensagem de erro
				} else {
					fseek(registers[i], 0, SEEK_SET);
					printf("Registro %d do arquivo %s faltando! \n", keyLine, filenames[i]);
				}
			}
			strcat(line, "\n");
			fprintf(final, "%s", line);
			free(line);
		} else {
			end = 1;
		}

	} while (end == 0);

	//Fecha os arquivos
	fclose(final);
	for (i = 0; i < n_files; i++) {
		fclose(registers[i]);
	}
	free(registers);

	return 0;
}
