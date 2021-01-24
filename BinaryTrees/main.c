#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
  void *dataPtr;
  struct node *left;
  struct node *right;
} NODE;

typedef struct {
  int count;
  int (*compare) (void *arg1, void *arg2);
  NODE *root;
} BST_TREE;


NODE* _insert(BST_TREE *tree, NODE *root, NODE *newPtr);
NODE* _delete(BST_TREE *tree, NODE *root, void *dataPtr, bool *success);
void* _retrieve(BST_TREE *tree, void *dataPtr, NODE *root);
void _traverse(NODE *root, void (*process)(void *dataPtr));
void _destroy(NODE *root);


BST_TREE* BST_Create( int (*compare)(void *arg1, void *arg2) ){
  BST_TREE *tree;
  tree = (BST_TREE*)calloc(1, sizeof(BST_TREE));
  if (tree){
    tree->root = NULL;
    tree->count = 0;
    tree->compare = compare;
  }
  return tree;
}

BST_TREE* BST_Destroy( BST_TREE *tree ){
  if (tree) _destroy (tree->root);
  free(tree);
  return NULL;
}

bool BST_Insert (BST_TREE* tree, void *dataPtr){
  NODE *newPtr;
  newPtr = (NODE*) malloc(sizeof(NODE));
  if (!newPtr) return false;
  newPtr->right = NULL;
  newPtr->left = NULL;
  newPtr->dataPtr = dataPtr;

  if (tree->count == 0){
    tree->root = newPtr;
  }else{
    _insert(tree, tree->root, newPtr);
  }
  (tree->count)++;
  return true;
}

bool BST_Delete (BST_TREE* tree, void *dltKey){
  bool success; NODE *newRoot;
  newRoot = _delete(tree, tree->root, dltKey, &success);
  if (success){
    tree->root = newRoot;
    (tree->count)--;
    if (tree->count == 0) tree->root = NULL;
  }
  return success;
}

void* BST_Retrieve (BST_TREE *tree, void *keyPtr){
  if (tree->root){
    return _retrieve(tree, keyPtr, tree->root);
  } else {
    return NULL;
  }
}

void BST_Traverse (BST_TREE *tree, void (*process)(void *dataPtr)){
  _traverse(tree->root, process);
  return;
}

bool BST_Empty (BST_TREE *tree){
  return (tree->count == 0);
}

bool BST_Full (BST_TREE *tree){
  NODE *newPtr;
  newPtr = (NODE*)malloc( sizeof(*(tree->root)) );
  if (newPtr){
    free(newPtr);
    return false;
  } else {
    return true;
  }
}

bool BST_Count (BST_TREE *tree){
  return (tree->count);
}
int main(int argc, char *argv[]){


  return 0;
}

NODE* _insert(BST_TREE *tree, NODE *root, NODE *newPtr){
  if (!root) return  newPtr;
  if (tree->compare(newPtr->dataPtr, root->dataPtr) < 0){
    root->left = _insert(tree, root->left, newPtr);
    return root;
  } else {
    root->right = _insert(tree, root->right, newPtr);
    return root;
  }
  return root;
}

NODE* _delete(BST_TREE *tree, NODE *root, void *dataPtr, bool *success){
  NODE *dltPtr; NODE *exchPtr; NODE *newRoot; void *holdPtr;
  
  if (!root){
    *success = false;
    return NULL;
  }

  if (tree->compare(dataPtr, root->dataPtr)<0){
    root->left = _delete(tree, root->left, dataPtr, success);
  } else if (tree->compare(dataPtr, root->dataPtr)>0) {
    root->right = _delete(tree, root->right, dataPtr, success);
  } else {
    dltPtr = root;
    if (!root->left){
      free(root->dataPtr);
      newRoot = root->right;
      free(dltPtr);
      *success = true;
      return newRoot;
    } else {
      if (!root->right){
        newRoot = root->left;
        free(dltPtr);
        *success = true;
        return newRoot;
      } else {
        exchPtr = root->left;
        while (exchPtr->right) exchPtr = exchPtr->right;
        
        holdPtr = root->dataPtr;
        root->dataPtr = exchPtr->dataPtr;
        exchPtr->dataPtr = holdPtr;
        root->left = _delete(tree, root->left, exchPtr->dataPtr, success);
      }
    } // node found
  }
  return root;
}

void* _retrieve(BST_TREE *tree, void *dataPtr, NODE *root){
  if (root){
    if (tree->compare(dataPtr, root->dataPtr)<0){
      return _retrieve(tree, dataPtr, root->left);
    } else if (tree->compare(dataPtr, root->dataPtr)>0){
      return _retrieve(tree, dataPtr, root->right);
    } else {
      return root->dataPtr;
    }
  } else {
    return NULL;
  }

}

void _traverse(NODE *root, void (*process)(void *dataPtr)){
  if (root){
    _traverse(root->left, process);
    process(root->dataPtr);
    _traverse(root->right, process);
  }
}

void _destroy(NODE *root){
  if (root){
    _destroy(root->left);
    free(root->dataPtr);
    _destroy(root->right);
    free(root);
  }
}

