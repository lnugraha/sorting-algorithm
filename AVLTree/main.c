#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LH +1
#define EH 0
#define RH -1

typedef struct node{
  void *dataPtr;
  struct node* left;
  int bal;
  struct node* right;
} NODE;

typedef struct{
  int count;
  int (*compare)(void *arg1, void *arg2);
  NODE *root;
} AVL_TREE;

NODE* _insert(AVL_TREE *tree, NODE *root, NODE *newPtr, bool *taller){
  if (!root){
    root = newPtr;
    *taller = true;
    return root;
  }
  
  if (tree->compare(newPtr->dataPtr, root->dataPtr) < 0){
    root->left = _insert(tree, root->left, newPtr, taller);
    if (*taller)
      switch (root->bal){
        case LH:
          root = insLeftBal(root, taller); break;
        case EH:
          root->bal = LH; break;
        case RH:
          root->bal = EH; *taller = false; break;
      } // end switch
    return root;
  } else {
    root->right = _insert(tree, root->right, newPtr, taller);
    if (*taller)
      switch (root->bal){
        case LH:
          root->bal = EH; *taller = false; break;
        case EH:
          root->bal = RH; break;
        case RH:
          root = insRightBal(root, taller); break;
      } // end-switch
    return root;
  } // end-if
  return root;
}

NODE* _delete(AVL_TREE *tree, NODE *root, void *dltKey, bool *shorter, bool *success){
  NODE *dltPtr; NODE *exchPtr; NODE *newRoot;
  if(!root){
    *shorter = false; *success = false; return NULL;
  }

  if (tree->compare(dltKey, root->dataPtr) < 0){
    root->left = _delete(tree, root->left, dltKey, shorter, success);
    if (*shorter) root = dltRightBal(root, shorter);
  } else if (tree->compare(dltKey, root->dataPtr) > 0){
    root->right = _delete(tree, root->right, dltKey, shorter, success);
    if (*shorter) root = dltLeftBal(root, shorter);
  } else {
    dltPtr = root;
    if (!root->right){
      newRoot = root->left; *success = true; *shorter = true; 
      free(dltPtr); return newRoot;
    } else {
      if (!root->left){
        newRoot = root->right; *success = true; *shorter = true;
        free(dltPtr); return newRoot;
      } else { // delete nodes that have 2 sub trees
        exchPtr = root->left;
        while (exchPtr->right) exchPtr = exchPtr->right;
        root->dataPtr = exchPtr->dataPtr;
        root->left = _delete(tree,root->left,exchPtr->dataPtr,shorter,success);
        if (*shorter) root = dltRightBal(root, shorter);
      } // end if !root->left

    } // end if !root->right
  }
  return root;
}

void* _retrieve(AVL_TREE *tree, void *keyPtr, NODE *root){
  if (root){
    if (tree->compare(keyPtr, root->dataPtr) <0 ){
      return _retrieve(tree, keyPtr, root->left);
    } else if(tree->compare(keyPtr, root->dataPtr) >0 ){
      return _retrieve(tree, keyPtr, root->right);
    } else {
      return root->dataPtr;
    }
  } else {
    return NULL;
  }
}

void* _traversal(NODE *root, void (*process)(void* dataPtr)){
  if (root){
    _traversal(root->left, process);
    process(root->dataPtr);
    _traversal(root->left, process);
  }
}

void* _destroy(NODE *root){
  if (root){
    _destroy(root->left);
    free(root->dataPtr);
    _destroy(root->right);
    free(root);
  } 
}

NODE* rotateLeft(NODE *root){
  NODE *tempPtr;
  tempPtr = root->right;
  root->right = tempPtr->left;
  tempPtr->left = root;
  return tempPtr;
}

NODE* rotateRight(NODE *root){
  NODE *tempPtr;
  tempPtr = root->left;
  root->left = tempPtr->right;
  tempPtr->right = root;
  return tempPtr;
}

NODE* insLeftBal(NODE *root, bool *taller){
  NODE *rightTree; NODE *leftTree;
  leftTree = root->left;
  switch(leftTree->bal){
    case LH:
      root->bal = EH; // Left hight -- rotate right
      leftTree->bal = EH;
      root = rotateRight(root);
      *taller = false;
      break;
    case EH:
      printf("Error on insLeftBal\n");
      exit(100);
    case RH:
      rightTree = leftTree->right;
      switch(rightTree->bal){
        case LH:
          root->bal = RH; leftTree->bal = EH; break;
        case EH:
          root->bal = EH; leftTree->bal = LH; break;
        case RH:
          root->bal = EH; leftTree->bal = LH; break;
      } // end of switch rightTree
      rightTree->bal = EH;
      root->left = rotateLeft(leftTree); // rotate left
      root = rotateRight(root); // rotate right
      *taller = false;
  }// end switch
  return root;
}

NODE* insRightBal(NODE *root, bool *taller){

}

NODE* dltLeftBal(NODE *root, bool *shorter){

}

NODE* dltRightBal(NODE *root, bool *shorter){
  NODE *rightTree; NODE *leftTree;
  switch (root->bal){
    case LH:
      root->bal = EH; break;
    case EH:
      root->bal = RH; *shorter = false; break;
    case RH:  
      rightTree = root->right;
      if (rightTree->bal == LH){
        leftTree = rightTree->left;
        switch (leftTree->bal){
          case LH:
            rightTree->bal = RH; root->bal = EH; break;
          case EH:
            root->bal= EH; rightTree->bal = EH; break;
          case RH:
            root->bal = LH; rightTree->bal = EH; break;
        } // end-switch
        leftTree->bal = EH;
        // rotate right then left
        root->right = rotateRight(rightTree);
        root = rotateLeft(root);

      } else {
        switch(rightTree->bal){
          case LH:
          case RH:
            root->bal = EH; rightTree->bal = EH; break;
          case EH:
            root->bal = RH; rightTree->bal = LH; *shorter = false; break;
        } // end-switch
        root = rotateLeft(root);
      } // end-if
  } // end-switch
  return root;
}

AVL_TREE* AVL_Create(int (*compare)(void *arg1, void *arg2) ){
  AVL_TREE *tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
  if (tree){
    tree->root = NULL;
    tree->count = 0;
    tree->compare = compare;
  }
  return tree;
}

AVL_TREE* AVL_Destroy(AVL_TREE *tree){
  if (tree) _destroy(tree->root);
  free(tree);
  return NULL;
}

bool AVL_Insert(AVL_TREE *tree, void *dataInPtr){
  NODE *newPtr; bool forTaller;
  newPtr = (NODE*)malloc(sizeof(NODE));
  if (!newPtr) return false;

  newPtr->bal = EH;
  newPtr->right = NULL;
  newPtr->left = NULL;
  newPtr->dataPtr = dataInPtr;

  tree->root = _insert(tree, tree->root, newPtr, &forTaller);
  (tree->count)++;
  return true;
}

bool AVL_Delete(AVL_TREE *tree, void *dltKey){
  bool shorter; bool success; NODE *newRoot;
  newRoot = _delete(tree, tree->root, dltKey, &shorter, &success);
  if (success){
    tree->root = newRoot;
    (tree->count)--;
    return true;
  } else {
    return false;
  }
}

void* AVL_Retrieve(AVL_TREE *tree, void *keyPtr){
  if (tree->root){
    return _retrieve(tree, keyPtr, tree->root);
  } else {
    return NULL;
  }
}

void AVL_Traverse(AVL_TREE *tree, void (*process)(void *dataPtr)){
  _traversal(tree->root, process);
}

int AVL_Count  (AVL_TREE *tree){ return (tree->count); }

bool AVL_Empty (AVL_TREE *tree){ return (tree->count == 0); }

bool AVL_Full  (AVL_TREE *tree){
  NODE *newPtr;
  newPtr = (NODE*)malloc(sizeof(*(tree->root)));
  if (newPtr){
    free(newPtr);
    return false;
  } else {
    return true;  
  }
}

int main(int argc, char *argv[]){



  return 0;
}
