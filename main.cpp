#include "akinator.h"

int main(void)
{
    size_t nPic = 0;

    long text_size = 0;
    char* text = PutText("tree.txt", &text_size);
    node *Tree_Root = TakeTreeFromTxt(&text);
    
    FILE* second_tree = fopen("tree.txt", "w");
    WriteTreeTxt(Tree_Root, second_tree);
    fclose(second_tree);

    TreeDumpFromStringNode(Tree_Root, &nPic);
    
    char word_1[15] = {'\0'};
    printf("Enter the 1 word:\t");
    scanf("%s", word_1);
    GiveWordDefinition(Tree_Root, word_1);

    char word_2[15] = {'\0'};
    printf("Enter the 2 word:\t");
    scanf("%s", word_2);
    GiveWordDefinition(Tree_Root, word_2);

    GiveTheDifference(Tree_Root, word_1, word_2);

    FreeTree(Tree_Root);

}