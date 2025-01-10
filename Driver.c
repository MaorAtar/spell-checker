/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

int parseWordsToTable(char* path, HashTable* ht);
SpellingSuggestion* spellingCheck(char* text);
/*========================Assistance Functions======================*/
int isInSuggestion(SpellingSuggestion* head, char* word);
SpellingSuggestion* addSuggestionToEND(SpellingSuggestion* head, char* word, HashTable* dictionaryTable);
void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions);
SpellingSuggestion* BuildSuggestionNode(char* word, HashTable* dictionaryTable);

int main()
{	
	char* text = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* spellingSuggestions = spellingCheck(text);
	printSpellingSuggestions(spellingSuggestions);

	return 0;
}
/*==============================Part 3=============================*/
/*============================Exrecise 9===========================*/
int parseWordsToTable(char* path, HashTable* ht)
/* Function to read the dictonary file, and insert the dictonary words into the Hash Table */
{
	FILE* pfile = fopen(path, "r");
	if (pfile == NULL) {
		printf("ERROR - Couldn't open file properly\n");
		return 0;
	}
	char line[128];
	fscanf(pfile, "%s", line);

	while (!feof(pfile)) {
		if (line == NULL) {
			return 0;
		}
		insert(ht, line);
		fscanf(pfile, "%s", line);

	}
	insert(ht, line);
	fclose(pfile);
	return 1;
}
/*==============================Part 5=============================*/
/*===========================Exrecise 17===========================*/
SpellingSuggestion* spellingCheck(char* text)
/* Function to return a list of misspelled words and a suggestions for correction the words */
{
	SpellingSuggestion* suggestionsList = NULL;
	HashTable* dictionaryTable = initTable(6000, 3);
	char* path = "C:/Users/maora/OneDrive/Desktop/Assignment 4 - Maor Atar, Guy Ezra/dictionary.txt";
	int insertDictionary = parseWordsToTable(path, dictionaryTable);
	if (insertDictionary == 0) return suggestionsList;
	const int textSize = strlen(text);
	char tempWord[128];
	int k = 0;
	for (int i = 0; i <= textSize; i++) {
		if (text[i] != ' ' && i < textSize) {
			tempWord[k] = text[i];
			k++;
		}
		else {
			tempWord[k] = '\0';
			if (!isWordInDictionary(dictionaryTable, tempWord)) {
				if (tempWord != NULL && strlen(tempWord) != 0 && !isInSuggestion(suggestionsList, tempWord)) {
					suggestionsList = addSuggestionToEND(suggestionsList, tempWord, dictionaryTable);
				}
			}
			k = 0;
		}
	}
	return suggestionsList;
}
/*========================Assistance Function=======================*/
int isInSuggestion(SpellingSuggestion* list, char* word)
/* Assistance Function to check if a given word is in the suggestion list */
{
	SpellingSuggestion* suggestionsList = list;
	int flag = 0;
	while (flag == 0 && suggestionsList != NULL) {
		if (strcmp(word, suggestionsList->originalWord) == 0) {
			flag = 1;
		}
		suggestionsList = suggestionsList->next;
	}
	return flag;
}
/*========================Assistance Function=======================*/
SpellingSuggestion* addSuggestionToEND(SpellingSuggestion* list, char* word, HashTable* dictionaryTable)
/* Assistance Function to add a new element into the tail of the list  */
{
	if (list == NULL) {
		return  BuildSuggestionNode(word, dictionaryTable);
	}
	SpellingSuggestion* suggestionsList = list;
	while (suggestionsList->next != NULL) {
		suggestionsList = suggestionsList->next;
	}
	suggestionsList->next = BuildSuggestionNode(word, dictionaryTable);
	return list;
}
/*========================Assistance Function=======================*/
void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions)
/* Assistance Function to print the Spelling Suggestion List */
{
	SpellingSuggestion* temp = spellingSuggestions;
	while (temp != NULL) {
		printf(" The word \"%s\" was misspelled.", temp->originalWord);
		if (temp->suggestions == NULL) {
			printf(" No suggestions found for this word.\n");
		}
		else {
			printf(" Did you mean:\n");
			PrintList(temp->suggestions);
		}
		temp = temp->next;
		if (temp != NULL) {
			printf(",");
		}
	}
}
/*========================Assistance Function=======================*/
SpellingSuggestion* BuildSuggestionNode(char* word, HashTable* dictionaryTable)
/* Assistance Function to create a Spelling Suggestion Linked List */
{
	SpellingSuggestion* newSuggestionsList = NULL;
	newSuggestionsList = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
	newSuggestionsList->originalWord = (char*)malloc(128 * sizeof(char));
	strcpy_s(newSuggestionsList->originalWord, 64, word);
	newSuggestionsList->next = NULL;
	newSuggestionsList->suggestions = getWordSuggestions(dictionaryTable, word);
	return newSuggestionsList;
}