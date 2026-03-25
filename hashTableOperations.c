#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// define hash table size
#define SIZE 20

// create a data item object to inserted into the hash table
struct DataItem {
    int data;
    int key;
};

// hash array definition returning a pointer to the global hashArray object
struct DataItem* hashArray[SIZE];

// pointer to a dummy object
struct DataItem* dummyItem;

// pointer to item containing data and key
struct DataItem* item;

// hash function created
int hashCode(int key) {

    return key % SIZE;

}

// Search Function for Search Operation
struct DataItem *search(int key) {

    //get the hash
    int hashIndex = hashCode(key);

    // while hashArray cell is not empty
    while(hashArray[hashIndex] != NULL) {

            // Find where the index which matches the hashkey and return it
            if(hashArray[hashIndex]->key == key)

            return hashArray[hashIndex];

        // else go to the next cell
        ++hashIndex;

        //wrap around the table back to index 0
        hashIndex %= SIZE;

    }

    // if no index is found, simply return empty.
    return NULL;

}

// Insert Function for Insert Operation

void insert(int key,int data) {

    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1){

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

// Delete Function for Delete Operation
struct DataItem* delete(struct DataItem* item){
    int key = item->key;
    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL){

        if(hashArray[hashIndex]->key == key){

            struct DataItem* temp = hashArray[hashIndex];

            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            
            return temp;
        }
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}


// Function to Display hash table operations
void display(){
    int i = 0;

        for(i = 0; i<SIZE; i++) {

            if(hashArray[i] != NULL)
                printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);

            else
                printf(" (Nothing Here) ");
        }

    printf("\n");
}

// Main Function. Entry point of programme
int main() {

    // Create a dummy with empty key and data to replace a deleted item and ensure search operation does not break
    dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;

    // inserting data into the hash Table
    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(12, 44);
    insert(14, 32);
    insert(17, 11);
    insert(13, 78);
    insert(37, 97);
    
    // Show inserted data
    display();
    
    //Search for an item with key 37
    item = search(37);

    if(item != NULL){

        printf("Element found: %d\n", item->data);
    }

    else {

        printf("Element not found\n");
    }
        
    delete(item);


    // Searching for the same item again after deleting it to see if it was really deleted.
    item = search(37);

    if(item != NULL){

        printf("Element found: %d\n", item->data);

    }

    else {

        printf("Element not found\n");
    }

// Call display function again after one item has been deleted
    display();
}
