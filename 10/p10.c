#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Initializes a Trie node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = 0;
    return node;
}

// Inserts a word into the Trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

// Computes the number of occurrences of a word in the Trie
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current->isEndOfWord;
}

// Deallocates the Trie
void deallocateTrie(struct TrieNode *root) {
    if (root == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Initializes a Trie structure
struct TrieNode* createTrie() {
    return createNode();
}

// Reads words from a file into an array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    int count = 0;
    char word[100]; // Assuming maximum word length is 100
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }

    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];
    
    // Read words from the dictionary file
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; i++) {
        printf("%s\n", inWords[i]);
    }
    
    // Create a Trie and insert all words
    struct TrieNode *root = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    
    // Test the Trie by checking occurrences of some words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    
    // Deallocate the Trie
    deallocateTrie(root);
    
    return 0;
}