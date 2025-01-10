/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#include "HashTable.h"

typedef struct SpellingSuggestion SpellingSuggestion;

struct SpellingSuggestion {
	char* originalWord;
	LinkedList* suggestions;
	SpellingSuggestion* next;
};

int isWordInDictionary(HashTable* dictionaryTable, char* word);
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);

