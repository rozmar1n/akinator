#include "tree.h"

node* MakeLongIntNode    (lli data, node* child_left, node* child_right)
{
    node* node_ptr = (node*)calloc(1, sizeof(node));
    node_ptr->data = calloc(1, sizeof(long long int));
    *((lli*)node_ptr->data) = data;

    node_ptr->child_left = child_left;
    node_ptr->child_right = child_right;

    return node_ptr;
}

void MakeGraphLongIntNode(node* node, FILE* newGraph)
{
    if (node == NULL)
    {
        fprintf(stderr, "node is null!!!\n");
        return;
    }    
    fprintf(newGraph, "node%p [shape=Mrecord; label = \" {%p"
                      "| data = %lld | left = %p | right = %p }\"];\n\t", 
                       node, node, *((lli*)(node->data)), node->child_left, node->child_right);

    if (node->child_left)
    {
        MakeGraphLongIntNode(node->child_left, newGraph);
    }
    if (node->child_right)
    {
        MakeGraphLongIntNode(node->child_right, newGraph);
    }
}
void MakeEdgeToChildren(node* node, FILE* newGraph)
{
    if (node == NULL)
    {
        fprintf(stderr, "node is null!!!\n");
        return;
    }
    if(node->child_left)
    {
        fprintf(newGraph, "node%p -> node%p [color = blue;]\n\t",
                           node, node->child_left);
        MakeEdgeToChildren(node->child_left, newGraph);
    }
    if (node->child_right)
    {
        fprintf(newGraph, "node%p -> node%p [color = red;]\n\t",
                           node, node->child_right);
        MakeEdgeToChildren(node->child_right, newGraph);
    }
}

void  TreeDumpFromLongIntNode   (node* root, size_t* nPic)
{
    *(nPic) +=1;

    char graphName[128];
    sprintf(graphName, "dotfiles/%lu.dot", *nPic);

    FILE* newGraph = fopen(graphName, "w");
    fprintf(newGraph, "digraph G\n\t{\n\t");

    MakeGraphLongIntNode(root, newGraph);
    fprintf(newGraph, "\n\t");
    MakeEdgeToChildren(root, newGraph);

    fprintf(newGraph, "}");
    char buffer[512] = {'\0'};

    char pictureName[128];
    sprintf(pictureName, "tree_pictures/%lu.png", *nPic);

    sprintf(buffer, "dot -Tpng %s -o %s\n", graphName, pictureName);
    fprintf(stderr, "%s", buffer);
    fclose(newGraph);
    system(buffer);
}
void  InsertLongIntNode(node* leaf, node* root)
{
    if (root == NULL)
    {
        fprintf(stderr, "root is null\n");
        return;
    }

    if (*((lli*)(leaf->data)) > *((lli*)(root->data)))
    {
        if (root->child_right)
        {
            InsertLongIntNode(leaf, root->child_right);
            return;
        }
        else
        {
            root->child_right = leaf;
            return;
        }
    }
    else
    {
        if (root->child_left)
        {
            InsertLongIntNode(leaf, root->child_left);
            return;
        }
        else
        {
            root->child_left = leaf;
            return;
        }
    }
}

void FreeTree(node* root)
{
    if (root->child_left)
    {
        FreeTree(root->child_left);
    }
    if (root->child_right)
    {
        FreeTree(root->child_right);
    }
    free(root->data);
    free(root);
}