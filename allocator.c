#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int start;
    int end;
    int mID;
    struct node* next;
} node;

typedef struct {
    char* data; // the data we are going to allocate.
    node* head;
    int size;
} Allocator;

Allocator* allocatorCreate(int n) {
    Allocator* new_allocator = (Allocator*)malloc(sizeof(Allocator));
    new_allocator->data = malloc(n);
    new_allocator->head = NULL;
    new_allocator->size = n;
    return new_allocator;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int start = 0;
    node* prev = NULL;
    node* cur = obj->head;

    while (cur != NULL) {
        if (start + size - 1 < cur->start) {
            // Found a suitable gap
            break;
        }
        start = cur->end + 1;
        prev = cur;
        cur = cur->next;
    }

    if (start + size - 1 >= obj->size) {
        // Not enough memory
        return -1;
    }

    // Create a new node for the allocated block
    node* new_node = malloc(sizeof(node));
    new_node->start = start;
    new_node->end = start + size - 1;
    new_node->mID = mID;
    new_node->next = cur;

    if (prev == NULL) {
        // Inserting at the head
        obj->head = new_node;
    } else {
        prev->next = new_node;
    }

    return start;
}

int allocatorFreeMid(Allocator* obj, int mID) {
    node* prev = NULL;
    node* cur = obj->head;
    int freed_size = 0;

    while (cur != NULL) {
        if (cur->mID == mID) {
            // Remove this node
            if (prev == NULL) {
                obj->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            freed_size += cur->end - cur->start + 1;
            node* temp = cur;
            cur = cur->next;
            free(temp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return freed_size;
}

void allocatorFree(Allocator* obj) {
    node* cur = obj->head;
    while (cur != NULL) {
        node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(obj->data);
    free(obj);
}

// Test cases for the Allocator functions
int main() {
    // Test case 1: Create an allocator with space for 100 bytes
    Allocator* allocator = allocatorCreate(100);
    if (allocator != NULL) {
        printf("Allocator created successfully with 100 bytes.\n");
    } else {
        printf("Failed to create allocator.\n");
    }

    // Test case 2: Allocate 20 bytes with mID = 1
    int start1 = allocatorAllocate(allocator, 20, 1);
    printf("Allocation result for 20 bytes with mID 1: %d\n", start1);

    // Test case 3: Allocate 30 bytes with mID = 2
    int start2 = allocatorAllocate(allocator, 30, 2);
    printf("Allocation result for 30 bytes with mID 2: %d\n", start2);

    // Test case 4: Attempt to allocate 60 bytes with mID = 3 (expect failure)
    int start3 = allocatorAllocate(allocator, 60, 3);
    printf("Allocation result for 60 bytes with mID 3: %d\n", start3);

    // Test case 5: Free the block with mID = 1
    allocatorFreeMid(allocator, 1);
    printf("Freed memory block with mID 1.\n");

    // Test case 6: Attempt to allocate 10 bytes with mID = 4 (should succeed)
    int start4 = allocatorAllocate(allocator, 10, 4);
    printf("Allocation result for 10 bytes with mID 4: %d\n", start4);

    // Test case 7: Attempt to allocate another 10 bytes with mID = 4
    int start5 = allocatorAllocate(allocator, 10, 4);
    printf("Allocation result for 10 bytes with mID 4: %d\n", start5);

    start1 = allocatorAllocate(allocator, 20, 1);
    printf("Allocation result for 20 bytes with mID 1: %d\n", start1);


    // Test case 8: Free the block with mID = 4
    allocatorFreeMid(allocator, 4);
    printf("Freed memory block with mID 4.\n");

    start1 = allocatorAllocate(allocator, 20, 1);
    printf("Allocation result for 20 bytes with mID 1: %d\n", start1);


    // Test case 9: Free the allocator
    allocatorFree(allocator);
    printf("Allocator freed successfully.\n");

    return 0;
}
