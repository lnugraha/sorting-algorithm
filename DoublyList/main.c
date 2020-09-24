#include <stdio.h>
#include <stdlib.h>

struct Node{
  int data;
  struct Node *next;
  struct Node *prev;
};

void push(struct Node **head_ref, int new_data){
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  new_node->prev = NULL;

  if ((*head_ref) != NULL) (*head_ref)->prev = new_node;
  (*head_ref) = new_node;
}

void insertAfter(struct Node *prev_node, int new_data){
  if (prev_node == NULL) {
    printf("Cannot have NULL previous node");
    return;
  }
  
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

  new_node->data = new_data; 
  new_node->next = prev_node->next; 
  prev_node->next = prev_node->next;
  new_node->prev = prev_node;
  
  if (new_node->next != NULL) new_node->next->prev = new_node;
}

void insertBefore(struct Node **head_ref, struct Node *next_node, int new_data)
{
  if (next_node == NULL) {
    printf("Cannot have NULL next node");
    return;
  }
  
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

  new_node->data = new_data; 
  new_node->prev = next_node->prev;
  next_node->prev = new_node;
  new_node->next = next_node;

  if (new_node->prev != NULL) new_node->prev->next = new_node;
  else (*head_ref) = new_node;
}

void append(struct Node **head_ref, int new_data){
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
  struct Node *last = *head_ref;
  
  new_node->data = new_data;
  new_node->next = NULL;

  if (*head_ref == NULL){
    new_node->prev = NULL;
    *head_ref = new_node;
    return;
  }

  while (last->next != NULL) last = last->next;

  last->next = new_node;
  new_node->prev = last;
  return;
}

void deleteNode(struct Node **head_ref, struct Node *del) {
  if (*head_ref==NULL || del==NULL) return; 
  if (*head_ref==del) *head_ref = del->next; 
  if (del->next != NULL) del->next->prev = del->prev; 
  if (del->prev != NULL) del->prev->next = del->next; 
  free(del);
}

void deleteNodeAtPosition(struct Node **head_ref, int pos) {
  if (*head_ref==NULL || pos<=0) return;

  struct Node* current = *head_ref; int i;
  for (int i=1; current!=NULL && i<pos; ++i) current = current->next; 
  if (current == NULL) return; 
  deleteNode(head_ref, current);
}

void print(struct Node *node){
  struct Node *last;
  printf("Forward Direction\n");
  while (node != NULL) {
    printf(" %d ", node->data);
    last = node;
    node = node->next;
  }

  printf("\nBackward Direction\n");
  while (last != NULL){
    printf(" %d ", last->data);
    last = last->prev;
  }
  printf("\n");
}

int main(int argc, char *argv[]){
  struct Node *head = NULL;
  push(&head, 1);
  push(&head, 2);
  push(&head, 3);

  insertBefore(&head, head->next, 8);
  print(head);

  return 0;
}
