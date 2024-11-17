#include "tree.h"

int main()
{
    system("cd dotfiles/\nrm * \n");
    system("cd tree_pictures/\nrm * \n");
    //system("rm -i *\n");
    //system("cd ../\n");
    size_t nPic = 0;
    node* Tree_Root = MakeLongIntNode(666999, NULL, NULL);

    node* new_node = MakeLongIntNode(667000, NULL, NULL);
    InsertLongIntNode(new_node, Tree_Root);
    TreeDumpFromLongIntNode(Tree_Root, &nPic);

    node* node_2 = MakeLongIntNode(999999, NULL, NULL);
    InsertLongIntNode(node_2, Tree_Root);
    TreeDumpFromLongIntNode(Tree_Root, &nPic);

    node* node_3 = MakeLongIntNode(1, NULL, NULL);
    InsertLongIntNode(node_3, Tree_Root);
    TreeDumpFromLongIntNode(Tree_Root, &nPic);

    node* node_4 = MakeLongIntNode(2, NULL, NULL);
    InsertLongIntNode(node_4, Tree_Root);
    TreeDumpFromLongIntNode(Tree_Root, &nPic);

    node* node_5 = MakeLongIntNode(-2, NULL, NULL);
    InsertLongIntNode(node_5, Tree_Root);
    TreeDumpFromLongIntNode(Tree_Root, &nPic);
    

    FreeTree(Tree_Root);
}