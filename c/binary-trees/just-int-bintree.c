#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem 1, Parts 2/3/4
   pointers to functions that will be established later */
typedef int (*BSTCmp) (int i, int j);
typedef int (*BSTeq) (int i, int j);
typedef void (*TreePrint) (int i);

/* Problem 1, Part 1
   A struct is created with a pointer that will handle the BSTNodes */
typedef struct BSTCell *bstnode;
struct bstnode {
  int data;
  struct bstnode *ltree;
  struct bstnode *rtree;
};

/* Problem 1, Part 1
   The newNode function mallocs space for a node, and then adds the passed in
   value to the node's data field. It sets the left and right trees to NULL */
struct bstnode* newNode (int value) {
  struct bstnode *n;
  n = malloc(sizeof(bstnode));

  n->data = value;
  n->ltree = NULL;
  n->rtree = NULL;

  return n;
}

/* Problem 1, Part 2
   The member function looks through the tree until it finds either a NULL node
   or the matching value. It uses the properties of a BST to search more quickly,
   so that it does not need to check each node. */
int member(struct bstnode *node, int value, BSTCmp eq, BSTCmp comp){
  if (node == NULL) {
    return 0;
  }
  else if (eq(node->data,value) == 1) {
    return 1;
  }
  else if (comp(node->data, value) == 0) {
    return member(node->ltree, value, eq, comp);
  }
  else {
    return member(node->rtree, value, eq, comp);
  }
}

/* Problem 1, Part 3
   The insert function determines where the new integer value passed in belongs
   by checking the value at each node until it locates the correct location.
   A comparison and equality function are passed in, which will increase
   adaptability in later problems. */
struct bstnode* insert (struct bstnode *node, int value, BSTCmp eq, BSTCmp comp) {
  if (eq(node->data,value) == 1) {
    return node;
  }
  else if (comp(node->data, value) == 0) {
    if (node->ltree == NULL) {
      node->ltree = newNode(value);
      return node;
    }
    else {
      return insert(node->ltree, value, eq, comp);
    }
  }
  else {
    if (node->rtree == NULL) {
      node->rtree = newNode(value);
      return node;
    }
    else {
      return insert(node->rtree, value, eq, comp);
    }
  }
}

/* Problem 1, Part 4
   An inorder traversal checks the left branch first, then prints the
   current node's value, and then checks the right branch.
   A print function is used for adaptability in later problems */
void printtree (struct bstnode *node, TreePrint p) {
  if (node->ltree != NULL) {
    printtree(node->ltree, p);
  }
  p(node->data);
  if (node->rtree != NULL) {
    printtree(node->rtree, p);
  }
}

/* Problem 1, Parts 2/3
   The functions to handle equality and comparison for integers just return
   the value expected by integer comparison */
int intLss(int a, int b) { return a < b; }

int intEq(int a, int b) { return a == b; }

/* Problem 1, Part 4
   Printing an integer is simple with printf */
void printInt(int a) { printf("%d ",a); }

int main() {
/* A BST is created and values are added. It is printed in order, and then
   a few values are tested if they are in the tree */
  struct bstnode *root;
  root = newNode(10);
  insert(root,11,intEq,intLss);
  insert(root,8,intEq,intLss);
  insert(root,12,intEq,intLss);
  insert(root,14,intEq,intLss);
  insert(root,9,intEq,intLss);
  insert(root,3,intEq,intLss);
  insert(root,1,intEq,intLss);
  insert(root,4,intEq,intLss);
  insert(root,16,intEq,intLss);
  printf("A tree is created, printed, and tested: \n");
  printtree(root,printInt);
  printf("\n");
  printf("Is 1 in the Tree?:  ");
  if (member(root, 1, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 2 in the Tree?:  ");
  if (member(root, 2, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 20 in the Tree?:  ");
  if (member(root, 20, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("\n");

/* A single node tree is created, printed, and tested. */
  root = newNode(2);
  printf("A tree with one node is created, printed, and tested: ");
  printtree(root,printInt);
  printf("\n");
  printf("Is 1 in the Tree?:  ");
  if (member(root, 1, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }printf("Is 5 in the Tree?:  ");
  if (member(root, 2, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 20 in the Tree?:  ");
  if (member(root, 20, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("\n");

/* Numbers are added to the tree in numerical order.
   It is then printed and tested. */
  root = newNode(1);
  insert(root,2,intEq,intLss);
  insert(root,3,intEq,intLss);
  insert(root,4,intEq,intLss);
  insert(root,5,intEq,intLss);
  insert(root,6,intEq,intLss);
  insert(root,7,intEq,intLss);
  insert(root,8,intEq,intLss);
  insert(root,9,intEq,intLss);
  insert(root,10,intEq,intLss);
  printf("A tree is created, numbers are added in numerical order.\n");
  printf("Then it is printed and tested\n");
  printtree(root,printInt);
  printf("\n");
  printf("Is 1 in the Tree?:  ");
  if (member(root, 1, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 2 in the Tree?:  ");
  if (member(root, 2, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 20 in the Tree?:  ");
  if (member(root, 20, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("\n");

/* Numbers are added to the tree in reverse numerical order.
   It is then printed and tested. */
  root = newNode(10);
  insert(root,9,intEq,intLss);
  insert(root,8,intEq,intLss);
  insert(root,7,intEq,intLss);
  insert(root,6,intEq,intLss);
  insert(root,5,intEq,intLss);
  insert(root,4,intEq,intLss);
  insert(root,3,intEq,intLss);
  insert(root,2,intEq,intLss);
  insert(root,1,intEq,intLss);
  printf("A tree is created, numbers are added in reverse numerical order.\n");
  printf("Then it is printed and tested\n");
  printtree(root,printInt);
  printf("\n");
  printf("Is 1 in the Tree?:  ");
  if (member(root, 1, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 2 in the Tree?:  ");
  if (member(root, 2, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("Is 20 in the Tree?:  ");
  if (member(root, 20, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Nah.\n");
  }
  printf("\n");

/* An uneven amount of numbers is added to the tree.
   It is then printed and tested. */
   root = newNode(15);
   insert(root,13,intEq,intLss);
   insert(root,7,intEq,intLss);
   insert(root,12,intEq,intLss);
   insert(root,18,intEq,intLss);
   insert(root,11,intEq,intLss);
   insert(root,2,intEq,intLss);
   insert(root,4,intEq,intLss);
   insert(root,20,intEq,intLss);
   printf("A tree is created with an uneven number of nodes.\n");
   printf("Then it is printed and tested.\n");
   printtree(root,printInt);
   printf("\n");
   printf("Is 1 in the Tree?:  ");
   if (member(root, 1, intEq, intLss) == 1) {
     printf("Yup!\n");
   }
   else {
     printf("Nah.\n");
   }
   printf("Is 2 in the Tree?:  ");
   if (member(root, 2, intEq, intLss) == 1) {
     printf("Yup!\n");
   }
   else {
     printf("Nah.\n");
   }
   printf("Is 20 in the Tree?:  ");
   if (member(root, 20, intEq, intLss) == 1) {
     printf("Yup!\n");
   }
   else {
     printf("Nah.\n");
   }
}
