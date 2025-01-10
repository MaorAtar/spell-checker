/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#include "HashTable.h"

/*==============================Part 1=============================*/
/*============================Exrecise 1===========================*/
int constantStringHashFunction(char* str)
/* Hash Function - Returns 3 for each input */
{
	return 3;
}
/*============================Exrecise 2===========================*/
int accumulateStringHashFunction(char* str)
/* Hash Function - Returns the ascii value of a given input*/
{
	int result = 0;
	for (int i = 0; i < strlen(str); i++) {
		result += str[i];
	}
	return result;
}
/*============================Exrecise 3===========================*/
int improvedHashFunction(char* str)
/* Hash Function - Returns the value using the given formula*/
{
	int result = 0, n = strlen(str), power;
	for (int i = 0; i < n; i++) {
		power = pow(31, (n - 1 - i));
		result += str[i] * power;
	}
	return result;
}
/*==============================Part 2=============================*/
/*============================Exrecise 4===========================*/
HashTable* initTable(int tableSize, int hashFunction)
/* Function to create and initialize a new Hash Table */
{
	HashTable* newT = (HashTable*)malloc(sizeof(HashTable));
	newT->tableSize = tableSize;
	newT->hashFunction = hashFunction;
	newT->numOfElements = 0;
	newT->cellsTaken = 0;
	newT->hashTable = (HashTableElement*)calloc(newT->tableSize, sizeof(HashTableElement)); // Using calloc function to initialize the table elements with 0 value
	return newT;
}
/*============================Exrecise 5===========================*/
int hash(char* str, HashTable* ht)
/* Function to calculate the index to store the string in the Hash Table */
{
	int index = 0;
	switch (ht->hashFunction) {
	case 1:
		index = abs(constantStringHashFunction(str)) % ht->tableSize;;
		break;
	case 2:
		index = abs(accumulateStringHashFunction(str)) % ht->tableSize;;
		break;
	case 3:
		index = abs(improvedHashFunction(str)) % ht->tableSize;;
		break;
	}
	return index;
}
/*============================Exrecise 6===========================*/
int insert(HashTable* ht, char* str)
/* Function to insert an element into the Hash Table */
{
	if (str == NULL || search(ht, str) == 1) { return 0; }
	int index = hash(str, ht);
	if (ht->hashTable[index].chain == NULL) {
		ht->cellsTaken += 1;
		ht->numOfElements += 1;
		ht->hashTable[index].chain = addToStart(ht->hashTable[index].chain, str);
		return 1;
	}
	else {
		if (isInList(ht->hashTable[index].chain, str)) {
			return 0;
		}
	}
	ht->hashTable[index].chain = addToStart(ht->hashTable[index].chain, str);
	ht->numOfElements += 1;
	ht->cellsTaken += 1;
	return 1;
}
/*============================Exrecise 7===========================*/
int deleteStr(HashTable* ht, char* str)
/* Function to delete an element from the Hash Table */
{
	if (str == NULL || search(ht, str) == 0) { return 0; }
	for (int i = 0; i < ht->tableSize; i++) {
		if (ht->hashTable[i].chain != NULL) {
			if (isInList(ht->hashTable[i].chain, str)) {
				ht->hashTable[i].chain = DeleteElement(ht->hashTable[i].chain, str);
				ht->cellsTaken -= 1;
				ht->numOfElements -= 1;
				return 1;
			}
		}
	}
	return 0;
}
/*============================Exrecise 8===========================*/
int search(HashTable* ht, char* str)
/* Function to search if a given element appears in the Hash Table */
{
	int index = hash(str, ht);
	if (isInList(ht->hashTable[index].chain, str)) {
		return 1;
	}
	return 0;
}
/*========================Assistance Function=======================*/
void printHT(HashTable* ht)
/* Assistance Function to print the Hash Table */
{
	for (int i = 0; i < ht->tableSize; i++) {
		PrintList(ht->hashTable[i].chain);
	}
	printf("cells taken: %d\n", ht->cellsTaken);
	printf("num of elements: %d\n", ht->numOfElements);
	printf("-----------\n");
}