#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

int getLength(struct Node *head) {
    int length = 0;
    struct Node *current = head;
    while(current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void display(struct Node *head) {
    struct Node *current = head;
    printf("list: ");
    while(current != NULL) {
        if(current->next == NULL) {
            printf("%d\n", current->value);
        } else {
            printf("%d -> ", current->value);
        }
        current = current->next;
    }
}

struct Node* insert(struct Node *head, int val) {
    printf("inserting node with value %d\n", val);
    struct Node *current = head;
    bool inserted = false;
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = val;
    // if list is empty, insert node as head
    if(current == NULL) {
        current = newNode;
        current->next = NULL;
        current->prev = NULL;
        inserted = true;
        return current;
    }
    while(!inserted && current != NULL) {
        // if on last node, add to end
        if(current->next == NULL && current->value < val) {
            current->next = newNode;
            newNode->next = NULL;
            newNode->prev = current;
            inserted = true;
            return head;
        // if greater, keep looking
        } else if(current->value < val) {
            current = current->next;
        // if less/equal, insert here
        } else {
            // if node is being inserted at beginning
            if(current->prev == NULL) {
                newNode->prev = NULL;
                current->prev = newNode;
                newNode->next = current;
                return newNode;
            // node is being inserted in the middle somewhere
            } else {
                current->prev->next = newNode;
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev = newNode;
                return head;
            }
            inserted = true;
        }
    }
    return head;
}

struct Node* delete(struct Node *head, int val) {
    printf("deleting node with value %d\n", val);
    struct Node *current = head;
    bool deleted = false;
    while(!deleted && current != NULL) {
        // if value is found, delete
        if(current->value == val) {
            // if first in list
            if(current->prev == NULL) {
                current->next->prev = NULL;
                struct Node *temp = current->next;
                free(current);
                return temp;
            // if last in list
            } else if(current->next == NULL) {
                current->prev->next = NULL;
                free(current);
                return head;
            // otherwise
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                return head;
            }
            deleted = true;
        }
        current = current->next;
    }
    return head;
}

int main(void) {
    // initialize head of list
    struct Node *head = NULL;
    
    // manipulate list
    head = insert(head, 1); // edge case: adding first node
    head = insert(head, 3); // edge case: adding to end
    head = insert(head, 7);
    head = insert(head, 4);
    head = insert(head, 2);
    head = insert(head, 1);
    display(head);
    int len = getLength(head);
    printf("current length: %d\n", len);

    head = delete(head, 7); // edge case: deleting from the end
    head = delete(head, 2); 
    head = delete(head, 1); // edge case: deleting from the beginning
    display(head);
    len = getLength(head);
    printf("current length: %d\n", len);
}