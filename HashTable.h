/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#include <conio.h>
#include <math.h>
#include "LinkedList.h"

typedef struct HashTableElement HashTableElement;

struct HashTableElement
{
	int key;
	LinkedList* chain;
};

typedef struct HashTable HashTable;

struct HashTable
{
	HashTableElement* hashTable;
	int hashFunction;
	int tableSize;
	int cellsTaken;
	int numOfElements;
};

int constantStringHashFunction(char* str);
int accumulateStringHashFunction(char* str);
int improvedHashFunction(char* str);

int hash(char* str, HashTable* ht);
HashTable* initTable(int tableSize, int hashFunction);
int insert(HashTable* ht, char* str);
int deleteStr(HashTable* ht, char* str);
int search(HashTable* ht, char* str);

void printHT(HashTable* ht); // <- Assistance Function