#include <stdio.h>
#include <stdlib.h>

struct Node{
  int data;
  struct Node *next;
};

void push(struct Node **head_ref, int new_data);

void append(struct Node **head_ref, int new_data);

void insert(struct Node* prev_node, int new_data);

void deleteKey(struct Node **head_ref, int key);

void deleteNode(struct Node **head_ref, int position);

void printLinkedList(struct Node *n);

int main(int argc, char *argv[]){

  struct Node* head = NULL;
  struct Node* second = NULL;
  struct Node* third = NULL;

  head   = (struct Node*)calloc(1,sizeof(struct Node));  
  second = (struct Node*)calloc(1,sizeof(struct Node));
  third  = (struct Node*)calloc(1,sizeof(struct Node));

  head->data = 21;
  head->next = second;

  second->data = 32;
  second->next = third;

  third->data = 37;
  third->next = NULL;

  printLinkedList(head);
  free(head); free(second); free(third);
  return 0;
}

void printLinkedList(struct Node *n) {
  while (n != NULL) {
    printf("%d \n", n->data);
    n = n->next;
  }
}

void push(struct Node **head_ref, int new_data) {
  struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  (*head_ref)    = new_node;
}

void deleteKey(struct Node **head_ref, int key) {
  struct Node *temp = *head_ref, *previous;
  
  if (temp != NULL && temp->data == key) {
    *head_ref = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->data != key) {
    previous = temp;
    temp = temp->next;
  }
  
  if (temp == NULL) return;
  previous->next = temp->next;
  free(temp);
}

void deleteNode(struct Node **head_ref, int position) {
  if (*head_ref == NULL) return;

  struct Node *temp = *head_ref;

  if (position == 0) {
    *head_ref = temp->next;
    free(temp);
    return;
  }
  
  for (int i=0; temp != NULL && i<position-1; i++) temp = temp->next;

  if (temp == NULL || temp->next == NULL) return;

  struct Node *next = temp->next->next;
  free(temp->next);
  temp->next = next;
  
}

void append(struct Node **head_ref, int new_data) {
  struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
  struct Node *last = *head_ref;

  new_node->data = new_data;
  new_node->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = new_node;
  }

  while (last->next != NULL) last = last->next;
  last->next = new_node;
}

void insert(struct Node *prev_node, int new_data) {
  if (prev_node == NULL) {
    printf("The previous node cannot be NULL");
    return;
  }
  
  struct Node *new_node = (struct Node*) calloc(1,sizeof(struct Node));

  new_node->data = new_data;
  new_node->next = prev_node->next;
  prev_node->next = new_node;

}
