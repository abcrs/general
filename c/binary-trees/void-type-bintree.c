#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem 3, Part 1
   A void pointer is used to allow for arbitrary data types */
typedef struct BSTCell *bstnode;
struct bstnode {
  void *data;
  struct bstnode *ltree;
  struct bstnode *rtree;
};

/* Problem 3, Parts 2/3/4\
   The comparison, equality, and print functions have void* as
   their parameter now */
typedef int (*BSTCmp) (void* i, void* j);
typedef int (*BSTeq) (void* i, void* j);
typedef void (*TreePrint) (void* i);

/* Problem 3, Part 1
   The newNode is passed a void* that will have value, to match the
   structure of the BSTCell */
struct bstnode* newNode (void* value) {
  struct bstnode *n;
  n = malloc(sizeof(bstnode));

  n->data = value;
  n->ltree = NULL;
  n->rtree = NULL;

  return n;
}

/* Problem 3, Part 2
   As before, the member function has equality and comparison functions
   passed to it. The value now comes from a void* instead of something else */
int member(struct bstnode *node, void* value, BSTCmp eq, BSTCmp comp){
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

/* Problem 3, Part 3
   Like member, insert has a void* that contains the new value */
struct bstnode* insert (struct bstnode *node, void* value, BSTCmp eq, BSTCmp comp) {
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

/* Problem 3, Part 4
   printtree is unchanged from previous problems */
void printtree (struct bstnode *node, TreePrint p) {
  if (node->ltree != NULL) {
    printtree(node->ltree, p);
  }
  p(node->data);
  if (node->rtree != NULL) {
    printtree(node->rtree, p);
  }
}


/* Problem 3, Parts 2/3/4
   To match the function declarations, all of the comparison, equality,
   and print functions are passed void* as parameters.
   Each function must also cast the parameter into the relevant
   data type to perform the function required */
int intLss(void* a, void* b) { return *(int*)a < *(int*)b; }

int intEq(void* a, void* b) { return *(int*)a == *(int*)b; }

void printInt(void* a) { printf("%d ", *(int*)a); }

int strLss(void* a, void* b) {
  if (strcmp((char*)a, (char*)b) < 0) {
    return 1;
  }
  return 0;
}

int strEq(void* a, void* b) {
  if (strcmp((char*)a,(char*)b) == 0) {
    return 1;
  }
  return 0;
}

void printStr(void* a) { printf("%s ", (char*)a); }

/* Problem 3 Test:
   This data type is a char* that contains an alphabet character,
   followed by a numerical character. It is sorted first
   alphabetically, but then reverse numerically. */
int seatLss(void* a, void* b) {
  char* c;
  char* d;
  c = (char*)a;
  d = (char*)b;
  if (c[0] == d[0]) {
    if (c[1] > d[1]) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else if (c[0] < d[0]) {
    return 1;
  }
  else {
    return 0;
  }
}

int seatEq(void* a, void* b) {
  if (strcmp((char*)a,(char*)b) == 0) {
    return 1;
  }
  return 0;
}

int main() {
  struct bstnode *root;
  void *n;
  void *test;
  int i = 10;
  n = &i;
  root = newNode(n);
  int j = 11;
  n = &j;
  insert(root,n,intEq,intLss);
  int k = 8;
  n = &k;
  insert(root,n,intEq,intLss);
  int l = 12;
  n = &l;
  insert(root,n,intEq,intLss);
  int m = 12;
  n = &m;
  insert(root,n,intEq,intLss);
  int o = 14;
  n = &o;
  insert(root,n,intEq,intLss);
  int p = 9;
  n = &p;
  insert(root,n,intEq,intLss);
  int q = 3;
  n = &q;
  insert(root,n,intEq,intLss);
  int r = 1;
  n = &r;
  insert(root,n,intEq,intLss);
  int s = 4;
  n = &s;
  insert(root,n,intEq,intLss);
  int t = 16;
  n = &t;
  insert(root,n,intEq,intLss);
  printf("An Integer Tree: \n");
  printtree(root,printInt);
  printf("\n");
  printf("Is 1 in the Tree?:  ");
  int t1 = 1;
  test = &t1;
  if (member(root, test, intEq, intLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
  printf("Is 2 in the Tree?:  ");
  int t2 = 2;
  test = &t2;
  if (member(root, test, intEq, intLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
  printf("Is 20 in the Tree?:  ");
  int t3 = 20;
  test = &t3;
  if (member(root, test, intEq, intLss) == 1) {
    printf("Yup!\n");
  }
  else {
    printf("Not found.\n");
  }

  struct bstnode *strt;
  void *st;
  char* one = "Heidi";
  st = one;
  strt = newNode(st);
  char* two = "Carl";
  st = two;
  insert(strt,st,strEq,strLss);
  char* three = "Matt";
  st = three;
  insert(strt,st,strEq,strLss);
  char* four = "Gretchen";
  st = four;
  insert(strt,st,strEq,strLss);
  char* five = "Larry";
  st = five;
  insert(strt,st,strEq,strLss);
  char* six = "Betty";
  st = six;
  insert(strt,st,strEq,strLss);
  char* seven = "Quincy";
  st = seven;
  insert(strt,st,strEq,strLss);
  char* eight = "Fatima";
  st = eight;
  insert(strt,st,strEq,strLss);
  char* nine = "Eric";
  st = nine;
  insert(strt,st,strEq,strLss);
  printf("\nA String Tree:\n");
  printtree(strt,printStr);
  printf("\n");
  printf("Is Betty in the String Tree?:  ");
  char* test1 = "Betty";
  test = test1;
  if (member(strt,test,strEq,strLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
  printf("Is Jake in the String Tree?:  ");
  char* test2 = "Jake";
  test = test2;
  if (member(strt,test,strEq,strLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
  printf("\n");

  struct bstnode *seat;
  void *se;
  char* c1 = "c1";
  se = c1;
  seat = newNode(se);
  char* a1 = "a1";
  se = a1;
  insert(seat,se,seatEq,seatLss);
  char* a2 = "a2";
  se = a2;
  insert(seat,se,seatEq,seatLss);
  char* c2 = "c2";
  se = c2;
  insert(seat,se,seatEq,seatLss);
  char* d3 = "d3";
  se = d3;
  insert(seat,se,seatEq,seatLss);
  char* e9 = "e9";
  se = e9;
  insert(seat,se,seatEq,seatLss);
  char* b2 = "b2";
  se = b2;
  insert(seat,se,seatEq,seatLss);
  char* a3 = "a3";
  se = a3;
  insert(seat,se,seatEq,seatLss);
  char* f1 = "f1";
  se = f1;
  insert(seat,se,seatEq,seatLss);
  char* e1 = "e1";
  se = e1;
  insert(seat,se,seatEq,seatLss);
  printf("An Alpha-Numeric Tree - \n");
  printf("Sorted alphabetically, and then reverse numerically:\n");
  printtree(seat,printStr);
  printf("\n");
  printf("Is f1 in the Alpha-Numeric Tree?:  ");
  char* tt1 = "f1";
  test = tt1;
  if (member(seat,test,seatEq,seatLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
  printf("Is f2 in the Alpha-Numeric Tree?:  ");
  char* tt2 = "f2";
  test = tt2;
  if (member(seat,test,seatEq,seatLss) == 1) {
    printf("It is!\n");
  }
  else {
    printf("Not found.\n");
  }
}
