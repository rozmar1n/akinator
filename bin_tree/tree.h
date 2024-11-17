#ifndef  BIN_TREE_H
#define  BIN_TREE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int(*compar_func_t)(void* elem_1, void* elem_2, int MaxLine);
typedef long long int lli; 

struct node
{
    void* data;
    node* child_left;
    node* child_right;
};

node* MakeLongIntNode        (lli data, node* child_left, node* child_right);
void  InsertLongIntNode      (node* leaf, node* root);
void  MakeEdgeToChildren     (node* node, FILE* newGraph);
void  MakeGraphLongIntNode   (node* node, FILE* newGraph);
void  TreeDumpFromLongIntNode(node* root, size_t* nPic);

void FreeTree(node* root);

#endif //BIN_TREE_H