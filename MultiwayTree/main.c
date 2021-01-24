#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ORDER = 5;
const int MIN_ENTRIES = (((ORDER+1)/2)-1);

struct node;
typedef struct{
  void *dataPtr;
  struct node *rightPtr;
} ENTRY;

typedef struct node{
  struct node *firstPtr;
  int numEntries;
  ENTRY entries[ORDER-1];
} NODE;

typedef struct{
  int count;
  NODE *root;
  int (*compare)(void *arg1, void *arg2);
} BTREE;

void *_search(BTREE *tree, void *targetPtr, NODE *root);
int _searchNode(BTREE *tree, NODE *nodePtr, void *target);
bool _delete(BTREE *tree, NODE *root, void *dltKeyPtr, bool *success);
bool _insert(BTREE *tree, NODE *root, void *dltKeyPtr, bool *success);
void _travese(NODE *root, void (*process)(void *dataPtr) );
void _splitNode(NODE *root, int entryNdx, int compResult, ENTRY *upEntry);

void _insertEntry(NODE *root, int entryNdx, ENTRY upEntry);
bool _deleteEntry(NODE *node, int entryNdx);
bool _deleteMid(NODE *node, int entryNdx, NODE *leftPtr);
bool _reFlow(NODE *root, int entryNdx);

bool _borrowLeft(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _borrowRight(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _combine(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _destroy(NODE *root);

BTREE* BTree_Create(int (*compare)(void *arg1, void *arg2) );
void BTree_Traverse(BTREE *tree, void (*process)(void *dataPtr));
BTREE* BTree_Destroy(BTREE *tree);
void BTree_Insert(BTREE *tree, void *dataInPtr);
bool BTree_Delete(BTREE *tree, void *dltKey);
void *BTree_Search(BTREE *tree, void *dataPtr);
bool BTree_Empty(BTREE *tree);
bool BTree_Full(BTREE *tree);
int BTree_Count(BTREE *tree);

int main(int argc, char *argv[]){




  return 0;
}
