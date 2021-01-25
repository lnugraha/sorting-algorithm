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

bool _reFlow(NODE *root, int entryNdx){


}

bool _deleteMid(NODE *root, int entryNdx, NODE *subtreePtr){
  int dltNdx; int rightNdx; bool underflow;
  if (subtreePtr->firstPtr == NULL){
    dltNdx = subtreePtr->numEntries - 1;
    root->entries[entryNdx].dataPtr = subtreePtr->entries[dltNdx].dataPtr;
    --subtreePtr->numEntries;
    underflow = subtreePtr->numEntries < MIN_ENTRIES;
  } else {
    rightNdx = subtreePtr->numEntries - 1;
    underflow = _deleteMid(root, entryNdx, 
        subtreePtr->entries[rightNdx].rightPtr);
    if (underflow) underflow = _reFlow(subtreePtr, rightNdx);
  }
  return underflow;
}


bool _borrowLeft(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _borrowRight(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _combine(NODE *root, int entryNdx, NODE *leftTree, NODE *rightTree);
void _destroy(NODE *root);

BTREE* BTree_Create(int (*compare)(void *arg1, void *arg2) ){

}

void BTree_Traverse(BTREE *tree, void (*process)(void *dataPtr)){
  if (tree->root) _travese(tree->root, process);
}

BTREE* BTree_Destroy(BTREE *tree);
void BTree_Insert(BTREE *tree, void *dataInPtr);

bool BTree_Delete(BTREE *tree, void *dltKey){
  bool success; NODE *dltPtr;
  if (!tree->root) return false;
  _delete(tree, tree->root, dltKey, &success);
  if (success){
    (tree->count)--;
    if (tree->root->numEntries == 0){
      dltPtr = tree->root;
      tree->root = tree->root->firstPtr;
      free(dltPtr);
    } // end-if
  } // end-if success
  return success;
}

void *BTree_Search(BTREE *tree, void *dataPtr){
  if (tree->root){
    return _search(tree, dataPtr, tree->root);
  } else {
    return NULL;
  }
}

bool BTree_Empty(BTREE *tree){

}

bool BTree_Full(BTREE *tree){

}

int BTree_Count(BTREE *tree){

}

int main(int argc, char *argv[]){




  return 0;
}

void _travese(NODE *root, void (*process)(void *dataPtr) ){
  int scanCount = 0; NODE *ptr;
  ptr = root->firstPtr;
  while (scanCount <= root->numEntries){
    if (ptr) _travese(root, process);

    if (scanCount < root->numEntries){
      process = (root->entries[scanCount].dataPtr);
      ptr = root->entries[scanCount].rightPtr;
    }
    scanCount++;
  } // end while
}

void *_search(BTREE *tree, void *targetPtr, NODE *root){
  int entryNo; 
  if (!root) return NULL;

  if (tree->compare(targetPtr, root->entries[0].dataPtr) < 0){
    return _search(tree, targetPtr, root->firstPtr);
  }
  
  entryNo = root->numEntries - 1;

  while (tree->compare(targetPtr, root->entries[entryNo].dataPtr) == 0)
    entryNo--;

  if (tree->compare(targetPtr, root->entries[entryNo].dataPtr) == 0)
    return (root->entries[entryNo].dataPtr);
  
  A
  return (_search(tree, targetPtr, root->entries[entryNo].rightPtr));
}
