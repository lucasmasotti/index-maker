#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "structures.h"

#define MAX_WORLD_SIZE 50
char separatorCharacters[]
{
    ' ', '.', ',', ';', ':',
    '?', '!', '-', '(', ')',
    '\n'
};
int numberSeparatorCharacters = 11;


int isSeparatorCharacter(char character);
void printListToFile(FILE *file, PtNo *list);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    if(argc != 4)
    {
        printf("Numero de argumentos invalido. \nSintaxe esperada: texto query saida");
        return 1;
    }

    char inputTextFile[50];
    char queryTextFile[50];
    char outPutTextFile[50];

    strcpy(inputTextFile, argv[1]);
    strcpy(queryTextFile, argv[2]);
    strcpy(outPutTextFile, argv[3]);

    /* Beggining of the tree construction phase */
    pNodoA *tree = NULL;
    int ok;

    FILE *inputText;

    inputText = fopen (inputTextFile, "r");

    if(inputText == NULL)
    {
        printf("Falha ao abrir arquivo de texto.");
        return 1;
    }

    char currentWord[MAX_WORLD_SIZE];
    int currentWordIndex = 0;

    char currentChar;
    int currentLine = 0;

    do
    {
        currentChar = getc(inputText);
        if(!isSeparatorCharacter(currentChar) && currentChar != EOF)
        {
            currentWord[currentWordIndex] = currentChar;
            currentWordIndex++;
        }

        if((isSeparatorCharacter(currentChar) || currentChar == EOF) && currentWordIndex > 0)
        {
            currentWord[currentWordIndex] = '\0';
            TipoInfo wordStruct;
            strcpy(wordStruct.word, currentWord);
            tree = InsereAVL(tree, wordStruct, currentLine, &ok);
            memset(&currentWord[0], 0, sizeof(currentWord)); // erase the currentWord
            currentWordIndex = 0;
        }
        if(currentChar == '\n')
        {
            currentLine++;
        }

    }
    while(currentChar != EOF);

    fclose(inputText);
    /* End of the tree construction phase */

    FILE *queryFile;
    FILE *outputFile;

    queryFile = fopen(queryTextFile, "r");
    if(queryFile == NULL)
    {
        printf("Falha ao abrir arquivo de de consulta.");
        return 1;
    }

    outputFile = fopen(outPutTextFile, "w");
    if(outputFile == NULL)
    {
        printf("Falha ao criar arquivo de saída.");
        return 1;
    }

    char currentQueryWord[MAX_WORLD_SIZE];
    int currentQueryWordIndex = 0;
    char currentQueryChar;

    do
    {
        currentQueryChar = getc(queryFile);
        if(!isSeparatorCharacter(currentQueryChar) && currentQueryChar != EOF)
        {
            currentQueryWord[currentQueryWordIndex] = currentQueryChar;
            currentQueryWordIndex++;
        }

        if(isSeparatorCharacter(currentQueryChar) || currentQueryChar == EOF)
        {
            currentQueryWord[currentQueryWordIndex] = '\0';

            fprintf(outputFile, "[Consulta] %s -> ", currentQueryWord);

            pNodoA *wordNode = findWord(tree, currentQueryWord);
            if(wordNode != NULL)
            {
                fprintf(outputFile, "palavra encontrada nas linhas: ");
                printListToFile(outputFile, wordNode->info.occurrencesList);
            }
            else
            {
                fprintf(outputFile, "palavra não encontrada");
            }

            fprintf(outputFile, "\n");

            memset(&currentQueryWord[0], 0, sizeof(currentQueryWord));
            currentQueryWordIndex = 0;
        }
    }
    while(currentQueryChar != EOF);


    fclose(queryFile);
    fclose(outputFile);
}

void printListToFile(FILE *file, PtNo *list)
{
    PtNo* auxiliarPointer;
    if (list == NULL)
    {
        puts("lista vazia");
    }
    else
    {
        for (auxiliarPointer = list; auxiliarPointer != NULL; auxiliarPointer = auxiliarPointer->prox)
        {
            fprintf(file, "%d, ", auxiliarPointer->info.page);
        }
    }
}

int isSeparatorCharacter(char character)
{
    int i;
    for(i = 0; i < numberSeparatorCharacters; i++)
    {
        if(character == separatorCharacters[i])
        {
            return 1;
        }
    }

    return 0;
}
