#include "akinator.h"

int main(void)
{
    // system("cd dump/dotfiles/ \nrm * \n");
    // system("cd dump/tree_pictures/ \nrm * \n");
    size_t nPic = 0;

    long text_size = 0;
    char* text = PutText("tree.txt", &text_size);
    //fprintf(stderr, "tree: %s\n", text);
    node *Tree_Root = TakeTreeFromTxt(&text);
    //GuessTheWord(Tree_Root, NULL);
    
    FILE* second_tree = fopen("tree.txt", "w");
    WriteTreeTxt(Tree_Root, second_tree);
    fclose(second_tree);

    TreeDumpFromStringNode(Tree_Root, &nPic);

    char word[15] = {'\0'};
    scanf("%s", word);
    GiveWordDefinition(Tree_Root, word);

    FreeTree(Tree_Root);

}