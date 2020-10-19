#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem 2, Part 1
   A union for StrorIntType */
typedef union StrorIntType {
  int i;
  char* s;
} soivalue;

/* Problem 2, Part 2
   Adapting the bstnode from Problem 1 to use StrorIntType data
   The data is of type soivalue instead of type int */
typedef struct BSTCell *bstnode;
struct bstnode {
  soivalue data;
  struct bstnode *ltree;
  struct bstnode *rtree;
};

/* Problem 2, Parts 3/4/5
   The relation, equality, and print functions are now passed soivalue instead
   of integer values, so the pointers need to be updated */
typedef int (*BSTCmp) (soivalue i, soivalue j);
typedef int (*BSTeq) (soivalue i, soivalue j);
typedef void (*TreePrint) (soivalue i);

/* Problem 2, Part 2
   Implementation of newNode using the StrorIntType value
   The value passed in is the generic soivalue value instead of int */
struct bstnode* newNode (soivalue value) {
  struct bstnode *n;
  n = malloc(sizeof(bstnode));

  n->data = value;
  n->ltree = NULL;
  n->rtree = NULL;

  return n;
}

/* Problem 2, Part 3
   member function using the StrorIntType value
   The int value from the initial member from Problem 1
   is changed to soivalue value to match the data type */
int member(struct bstnode *node, soivalue value, BSTCmp eq, BSTCmp comp){
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

/* Problem 2, Part 4
   insert function using the StrorIntType value */
struct bstnode* insert (struct bstnode *node, soivalue value, BSTCmp eq, BSTCmp comp) {
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

/* Problem 2, Part 5
   printtree function adapted for StrorIntType
   No actual changes occur in this function, but a printStr function must be made */
void printtree (struct bstnode *node, TreePrint p) {
  if (node->ltree != NULL) {
    printtree(node->ltree, p);
  }
  p(node->data);
  if (node->rtree != NULL) {
    printtree(node->rtree, p);
  }
}

/* Problem 2, Parts 3/4/5
   The intLss, intEq, and printInt functions have their parameters changed to
   match the value they are passed (soivalue). To access the integer value,
   the variable has .i added */
int intLss(soivalue a, soivalue b) { return a.i < b.i; }

int intEq(soivalue a, soivalue b) { return a.i == b.i; }

void printInt(soivalue a) { printf("%d ", a.i); }

/* Problem 2, Parts 3/4/5
   strLss and strEq uses strcmp to compare char* strings. The results from
   strcmp are adapted to match what the member and insert functions expect */
int strLss(soivalue a, soivalue b) {
  if (strcmp(a.s, b.s) < 0) {
    return 1;
  }
  return 0;
}

int strEq(soivalue a, soivalue b) {
  if (strcmp(a.s,b.s) == 0) {
    return 1;
  }
  return 0;
}

/* Problem 2, Part 5
   printStr just needs to access the char* aspect of the soivalue, using .s */
void printStr(soivalue a) { printf("%s ", a.s); }

int main() {
/* The boundaries of the BST were tested in Problem 1. This test only tests
   to make sure each function works with integers as it did in Problem 1,
   using the StrorIntType Tree */
  struct bstnode *root;
  soivalue t;
  t.i = 10;
  root = newNode(t);
  t.i = 11;
  insert(root,t,intEq,intLss);
  t.i = 8;
  insert(root,t,intEq,intLss);
  t.i = 12;
  insert(root,t,intEq,intLss);
  t.i = 14;
  insert(root,t,intEq,intLss);
  t.i = 9;
  insert(root,t,intEq,intLss);
  t.i = 3;
  insert(root,t,intEq,intLss);
  t.i = 1;
  insert(root,t,intEq,intLss);
  t.i = 4;
  insert(root,t,intEq,intLss);
  t.i = 16;
  insert(root,t,intEq,intLss);
  printf("An Int Tree:\n");
  printtree(root,printInt);
  printf("\n");
  printf("Is 5 in the Int Tree?:  ");
  t.i = 5;
  if (member(root,t,intEq,intLss) == 1) {
    printf("Yes!\n");
  }
  else {
    printf("Nope.\n");
  }
  printf("Is 4 in the Int Tree?:  ");
  t.i = 4;
  if (member(root,t,intEq,intLss) == 1) {
    printf("Yes!\n");
  }
  else {
    printf("Nope.\n");
  }
  printf("\n");

/* A test creating, adding, and addressing membership of a String version
   of the StrorIntType Tree. Values are added in no particular order */
  struct bstnode *test;
  soivalue c;
  c.s = "Heidi";
  test = newNode(c);
  c.s = "Carl";
  insert(test,c,strEq,strLss);
  c.s = "Matt";
  insert(test,c,strEq,strLss);
  c.s = "Gretchen";
  insert(test,c,strEq,strLss);
  c.s = "Larry";
  insert(test,c,strEq,strLss);
  c.s = "Betty";
  insert(test,c,strEq,strLss);
  c.s = "Quincy";
  insert(test,c,strEq,strLss);
  c.s = "Fatima";
  insert(test,c,strEq,strLss);
  c.s = "Eric";
  insert(test,c,strEq,strLss);
  printf("\nA String Tree:\n");
  printtree(test,printStr);
  printf("\n");
  printf("Is Betty in the String Tree?:  ");
  c.s = "Betty";
  if (member(test,c,strEq,strLss) == 1) {
    printf("Yes!\n");
  }
  else {
    printf("Nope.\n");
  }
  printf("Is Jake in the String Tree?:  ");
  c.s = "Jake";
  if (member(test,c,strEq,strLss) == 1) {
    printf("Yes!\n");
  }
  else {
    printf("Nope.\n");
  }
}
