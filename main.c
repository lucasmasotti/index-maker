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

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    char inputTextFile[] = "text.txt";
    char queryTextFile[] = "query.txt";
    char outPutTextFile[] = "output.txt";

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
            memset(&currentWord[0], 0, sizeof(currentWord));
            currentWordIndex = 0;
        }
        if(currentChar == '\n')
        {
            currentLine++;
        }

    }
    while(currentChar != EOF);

    fclose(inputText);

    //Desenha(tree,1);

    //imprime(tree->info.occurrencesList);
    //pNodoA *nodo = findWord(tree, "resposta");
    //imprime(nodo->info.occurrencesList);

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
            pNodoA *wordNode = findWord(tree, currentQueryWord);
            if(wordNode != NULL) {
                imprime(wordNode->info.occurrencesList);
            }

            memset(&currentQueryWord[0], 0, sizeof(currentQueryWord));
            currentQueryWordIndex = 0;
        }
    }
    while(currentQueryChar != EOF);


    fclose(queryFile);
    fclose(outputFile);
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
