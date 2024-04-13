#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order;
};

struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

struct HashType {
    struct ListNode** array;
    int size;
};

struct ListNode* newListNode(struct RecordType data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Compute the hash function
int hash(int x, int hashSize) {
    return x % hashSize;
}

int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);

		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType* hashTable, struct RecordType data) {
    int index = hash(data.id, hashTable->size);
    struct ListNode* newNode = newListNode(data);
    newNode->next = hashTable->array[index];
    hashTable->array[index] = newNode;
}

void displayRecordsInHash(struct HashType *hashTable) {
    printf("\nHash Table:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct ListNode* node = hashTable->array[i];
        if (node != NULL) {
            printf("Index %d -> ", i);
            while (node != NULL) {
                printf("%d %c %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    const int hashSz = 10;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType hashTable;
    hashTable.size = hashSz;
    hashTable.array = (struct ListNode**)malloc(hashSz * sizeof(struct ListNode*));
    for (int i = 0; i < hashSz; ++i) {
        hashTable.array[i] = NULL;
    }

    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, pRecords[i]);
    }

    displayRecordsInHash(&hashTable);

for (int i = 0; i < hashTable.size; ++i) {
    struct ListNode* current = hashTable.array[i];
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}
    free(hashTable.array);
    free(pRecords);

    return 0;
}