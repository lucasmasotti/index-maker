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
void printWord(char currentWord[MAX_WORLD_SIZE], int *currentWordIndex, int currentLine);

int main()
{
    setlocale(LC_ALL,"");

    pNodoA *arv = NULL;
    int ok;

    FILE *inputText;

    inputText = fopen ("alienista.txt", "r");

    char currentWord[MAX_WORLD_SIZE];
    int currentWordIndex = 0;

    char currentChar;
    int currentLine = 1;

    do
    {
        currentChar = getc(inputText);
        if(!isSeparatorCharacter(currentChar))
        {
            currentWord[currentWordIndex] = currentChar;
            currentWordIndex++;
        }
        else if(isSeparatorCharacter(currentChar) && currentWordIndex > 0)
        {
           //printWord(currentWord, &currentWordIndex, currentLine);

           TipoInfo wordStruct;
           strcpy(wordStruct.word, currentWord);
           arv = InsereAVL(arv, wordStruct, &ok);

        }
        if(currentChar == '\n')
        {
            currentLine++;
        }

    }
    while(currentChar != EOF);
    //printWord(currentWord, &currentWordIndex, currentLine); // Print the last world before EOF

    fclose(inputText);

    Desenha(arv,1);
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

void printWord(char currentWord[MAX_WORLD_SIZE], int *currentWordIndex, int currentLine) {
    currentWord[*currentWordIndex] = '\0';
    printf("\n[%d] %s", currentLine, currentWord);
    memset(&currentWord[0], 0, sizeof(currentWord));
    *currentWordIndex = 0;
}
