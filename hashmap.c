#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the key-value pair
typedef struct HashNode {
    char key[100];       // Key can be a string
    int value;           // Value can be an integer
    struct HashNode* next; // Pointer to the next node in case of collision
} HashNode;

// Define the hashmap structure with an array of linked lists
#define TABLE_SIZE 10
typedef struct HashMap {
    HashNode* table[TABLE_SIZE]; // Array of linked lists
} HashMap;

// Hash function to calculate the index from the key
unsigned int hash(char* key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue << 5) + *key++; // Simple hash function
    }
    return hashValue % TABLE_SIZE; // Ensure it's within bounds
}

// Function to create a new key-value pair
HashNode* createNode(char* key, int value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Insert a key-value pair into the hashmap
void insert(HashMap* hashmap, char* key, int value) {
    unsigned int index = hash(key); // Get the index using the hash function
    HashNode* newNode = createNode(key, value);
    
    if (hashmap->table[index] == NULL) {
        hashmap->table[index] = newNode; // No collision, just insert
    } else {
        // Handle collision by chaining (linked list)
        HashNode* current = hashmap->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Search for a key in the hashmap
int search(HashMap* hashmap, char* key) {
    unsigned int index = hash(key);
    HashNode* current = hashmap->table[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Found the key, return the value
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Delete a key-value pair from the hashmap
void delete(HashMap* hashmap, char* key) {
    unsigned int index = hash(key);
    HashNode* current = hashmap->table[index];
    HashNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashmap->table[index] = current->next; // Remove the first node
            } else {
                prev->next = current->next; // Remove from the linked list
            }
            free(current); // Free memory
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Initialize the hashmap
void initHashMap(HashMap* hashmap) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashmap->table[i] = NULL;
    }
}

int main() {
    HashMap hashmap;
    initHashMap(&hashmap);

    insert(&hashmap, "apple", 1);
    insert(&hashmap, "banana", 2);
    insert(&hashmap, "cherry", 3);

    printf("apple: %d\n", search(&hashmap, "apple"));
    printf("banana: %d\n", search(&hashmap, "banana"));
    printf("cherry: %d\n", search(&hashmap, "cherry"));

    delete(&hashmap, "banana");
    printf("banana after deletion: %d\n", search(&hashmap, "banana"));

    return 0;
}
