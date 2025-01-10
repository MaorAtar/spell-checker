/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#include "WordSpellingChecker.h"

/*==============================Part 4=============================*/
/*===========================Exrecise 10===========================*/
int isWordInDictionary(HashTable* dictionaryTable, char* word)
/* Function to check if a given word is in the dictionary */
{
	if (search(dictionaryTable, word) == 1)
		return 1;
	return 0;
}
/*===========================Exrecise 11===========================*/
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word)
/* First method to correct the misspelled words */
{
	LinkedList* correctedList = NULL;
	char tempFirstWord[128], tempSecondWord[128];
	const int wordSize = strlen(word); 
	int firstWordIndex, secondWordIndex, j;
	for (int i = 1; i - 1 < wordSize; i++) {
		j = i;
		firstWordIndex = 0;
		secondWordIndex = 0;
		while (firstWordIndex < i) {
			tempFirstWord[firstWordIndex] = word[firstWordIndex];
			firstWordIndex++;
		}
		tempFirstWord[firstWordIndex] = '\0';
		while (j < wordSize) {
			tempSecondWord[secondWordIndex] = word[j];
			secondWordIndex++;
			j++;
		}
		tempSecondWord[secondWordIndex] = '\0';
		if (isWordInDictionary(dictionaryTable, tempFirstWord) == 1 && isWordInDictionary(dictionaryTable, tempSecondWord) == 1) {
			tempFirstWord[firstWordIndex] = ' ';
			firstWordIndex++;
			tempFirstWord[firstWordIndex] = '\0';
			strcat_s(tempFirstWord, 64, tempSecondWord);
			correctedList = addToEND(correctedList, tempFirstWord);
		}
	}
	return correctedList;
}
/*===========================Exrecise 12===========================*/
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word)
/* Second method to correct the misspelled words */
{
	LinkedList* correctedList = NULL;
	char tempWord[128];
	strcpy_s(tempWord, 64, word);
	char tempChar, charToReplace;
	for (int i = 0; i < strlen(word); i++) {
		tempChar = tempWord[i];
		charToReplace = 'a';
		while(charToReplace != '{') {
			tempWord[i] = charToReplace;
			if (charToReplace != tempChar && isWordInDictionary(dictionaryTable, tempWord) == 1) {
				correctedList = addToEND(correctedList, tempWord);
			}
			charToReplace++;
		}
		tempWord[i] = tempChar;
	}
	return correctedList;
}
/*===========================Exrecise 13===========================*/
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word)
/* Third method to correct the misspelled words */
{
	LinkedList* correctedList = NULL;
	char tempWord[128];
	const int wordSize = strlen(word);
	int k;
	for (int i = 0; i < wordSize; i++) {
		k = 0;
		for (int j = 0; j < wordSize; j++) {
			if (j != i) {
				tempWord[k] = word[j];
				k++;
			}
			tempWord[k] = '\0';
		}
		if (isWordInDictionary(dictionaryTable, tempWord) == 1) {
			correctedList = addToEND(correctedList, tempWord);
		}
	}
	return correctedList;
}
/*===========================Exrecise 14===========================*/
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word)
/* Fourth method to correct the misspelled words */
{
	LinkedList* correctedList = NULL;
	char tempWord[128], charToReplace;
	const int wordSize = strlen(word);
	int firstWordIndex, secondWordIndex;
	for (int i = 0; i <= wordSize; i++) {
		charToReplace = 'a';
		while(charToReplace != '{') {
			firstWordIndex = 0;
			secondWordIndex = 0;
			while (firstWordIndex < i) {
				tempWord[firstWordIndex] = word[secondWordIndex];
				firstWordIndex++;
				secondWordIndex++;
			}
			tempWord[firstWordIndex] = charToReplace;
			firstWordIndex++;
			while (secondWordIndex < wordSize) {
				tempWord[firstWordIndex] = word[secondWordIndex];
				firstWordIndex++;
				secondWordIndex++;
			}
			tempWord[firstWordIndex] = '\0';
			if (isWordInDictionary(dictionaryTable, tempWord) == 1) {
				correctedList = addToEND(correctedList, tempWord);
			}
			charToReplace++;
		}
	}
	return correctedList;
}
/*===========================Exrecise 15===========================*/
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word)
/* Fifth method to correct the misspelled words */
{
	LinkedList* correctedList = NULL;
	char tempWord[128], tempChar;
	const int wordSize = strlen(word);
	for (int i = 0; i < wordSize; i++) {
		strcpy_s(tempWord, 64, word);
		tempChar = tempWord[i];
		tempWord[i] = word[i + 1];
		tempWord[i + 1] = tempChar;
		if (isWordInDictionary(dictionaryTable, tempWord) == 1) {
			correctedList = addToEND(correctedList, tempWord);
		}
	}
	return correctedList;
}
/*===========================Exrecise 16===========================*/
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word)
/* Function to return a list that contains all the suggestions for correction the words */
{
	LinkedList* correctedList = NULL, *temp = NULL;
	temp = addSpaceCheck(dictionaryTable, word);
	if (temp != NULL) correctedList = temp;

	temp = replaceCharacterCheck(dictionaryTable, word);
	while (temp != NULL) {
		if (!isInList(correctedList, temp->data)) {
			correctedList = addToEND(correctedList, temp->data);
		}
		temp = temp->next;
	}
	temp = deleteCharacterCheck(dictionaryTable, word);
	while (temp != NULL) {
		if (!isInList(correctedList, temp->data)) {
			correctedList = addToEND(correctedList, temp->data);
		}
		temp = temp->next;
	}
	temp = addCharacterCheck(dictionaryTable, word);
	while (temp != NULL) {
		if (!isInList(correctedList, temp->data)) {
			correctedList = addToEND(correctedList, temp->data);
		}
		temp = temp->next;
	}
	temp = switchAdjacentCharacterCheck(dictionaryTable, word);
	while (temp != NULL) {
		if (!isInList(correctedList, temp->data)) {
			correctedList = addToEND(correctedList, temp->data);
		}
		temp = temp->next;
	}
	FreeList(temp);
	return correctedList;
}