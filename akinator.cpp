#include "akinator.h"

node* MakeStringNode(char* string, node* child_left, node* child_right)
{
    node* node_ptr = (node*)calloc(1, sizeof(node));
    node_ptr->data = string;  

    node_ptr->child_left = child_left;
    node_ptr->child_right = child_right;

    return node_ptr;
}

void MakeGraphStringNode(node* node, FILE* newGraph)
{
    if (node == NULL)
    {
        fprintf(stderr, "node is null!!!\n");
        return;
    }    
    if(node->data == NULL)
    {
        fprintf(stderr, "data is null\n");
        return;
    }
    fprintf(newGraph, "node%p [shape=Mrecord; label = \" {%p"
                      "| data = %s | left = %p | right = %p }\"];\n\t", 
                       node, node, (char*)(node->data), node->child_left, node->child_right);

    if (node->child_left)
    {
        MakeGraphStringNode(node->child_left, newGraph);
    }
    if (node->child_right)
    {
        MakeGraphStringNode(node->child_right, newGraph);
    }
}

void  TreeDumpFromStringNode(node* root, size_t* nPic)
{
    *(nPic) +=1;

    char graphName[128];
    sprintf(graphName, "dump/dotfiles/%lu.dot", *nPic);
    FILE* newGraph = fopen(graphName, "w");
    fprintf(newGraph, "digraph G\n\t" "{\n\t");

    MakeGraphStringNode(root, newGraph);
    fprintf(newGraph, "\n\t");
    MakeEdgeToChildren(root, newGraph);
    fprintf(newGraph, "}");
    fclose(newGraph);

    char pictureName[128];
    sprintf(pictureName, "dump/tree_pictures/%lu.png\n", *nPic);

    char buffer[512] = {'\0'};
    sprintf(buffer, "dot -Tpng %s -o %s\n", graphName, pictureName);

    system(buffer);
}

int CheckTheAnswer(char* answer)
{
    for (size_t i = 0; i < strlen(answer); i++)
    {
        answer[i] = tolower(answer[i]);
    }
    
    if (strcmp(answer, "yes") == 0 || strcmp(answer, "y") == 0 
    ||  strcmp(answer,  "да") == 0 || strcmp(answer, "д") == 0)
    {
        return 1;
    }
    if (strcmp(answer,  "no") == 0 || strcmp(answer, "n") == 0 
    ||  strcmp(answer, "нет") == 0 || strcmp(answer, "y") == 0)
    {
        return -1;
    }

    return 0;
}

void GuessTheWord(node* root, node* parent)
{
    printf("%s?\n", (char*)(root->data));
    char answer[32] = {'\0'};//make const
    scanf("%s", answer);
    if (CheckTheAnswer(answer) == right_way)
    {
        if(root->child_right) 
        {
            GuessTheWord(root->child_right, root);
        }
        else    
        {
            printf("I am very smart\n");
            return;
        }
    }
    if (CheckTheAnswer(answer) == left_way)
    {
        if(root->child_left) 
        {
            GuessTheWord(root->child_left, root);
        }
        else    
        {
            AddQuestion(parent, root);
        }
    }
    if (CheckTheAnswer == 0)
    {
        fprintf(stderr, "Syntax error\n");
        return;
    }
    
}

void AddQuestion(node* root, node* left_answer)
{
    printf("Enter the question: ");
    char* question = (char*)calloc(Max_String_For_Node, sizeof(char));
    ClearBuffer();
    scanf("%[^\n]", question);

    printf("Enter the answer: ");
    char* answer = (char*)calloc(Max_String_For_Node, sizeof(char));
    ClearBuffer();
    scanf("%[^\n]", answer);
    ClearBuffer();

    node* right_answer = MakeStringNode(answer, NULL, NULL);
    if (root == NULL)
    {
        node* new_left_answer = MakeStringNode((char*)(left_answer->data), NULL, NULL);
        left_answer->data = question;
        left_answer->child_left = new_left_answer;
        left_answer->child_right = right_answer;

        return;
    }
    else
    {
        if (WhichChild(root, left_answer) == left_way)
        {
            root->child_left = MakeStringNode(question, left_answer, right_answer);
            return; 
        }
        if (WhichChild(root, left_answer) == right_way)
        {
            root->child_right = MakeStringNode(question, left_answer, right_answer); 
            return;
        }
    }
    fprintf(stderr, "Something is getting wrong!!!\n"
                    "We don't know what it is!!!\n");
}

char WhichChild(node* root, node* child)
{
    if (child == root->child_left)
        return left_way;
    if  (child == root->child_right)
        return right_way;
    return 0;
}

void ClearBuffer(void)
{
    int c = getchar();
    while (c != '\n')
    {
        c = getchar();
    }
    return;
}


void WriteTreeTxt(node* root, FILE* tree_file)
{
    if (root == NULL)
    {
        fprintf(tree_file, "root is null!!!\n");
        return;
    }

    fprintf(tree_file, "{");
    fprintf(tree_file, "%s", (char*)(root->data));
    if (root->child_left)
    {
        WriteTreeTxt(root->child_left, tree_file);
    }
    else
    {
        fprintf(tree_file, "{*}");
    }
    if (root->child_right)
    {
        WriteTreeTxt(root->child_right, tree_file);
    }
    else
    {
        fprintf(tree_file, "{*}");
    }
    fprintf(tree_file, "}");
}

node* TakeTreeFromTxt(char** tree_file_buffer)
{
    if (tree_file_buffer == 0)
    {
        fprintf(stderr, "tree_file is null\n");
    }

        if((*tree_file_buffer)[0] == '{')
        {
//fprintf(stderr,"recurs started\n");
            (*tree_file_buffer) += 1;
            char* node_data = (char*)calloc(Max_String_For_Node, sizeof(char));
            int read_symbols = sscanf(*tree_file_buffer, "%[^{}]", node_data);
            if (read_symbols > Max_String_For_Node || read_symbols < 0)
            {
                fprintf(stderr, "it is a very bad thing");
                return NULL;
            }
//fprintf(stderr, "%s\n", node_data);
            
            while ((*tree_file_buffer)[0] !='{' && (*tree_file_buffer)[0] !='\0')
            {
//fprintf(stderr, "skipped symbol: %c\n", (**tree_file_buffer));
                (*tree_file_buffer) += 1;
            }
            if ((*tree_file_buffer)[0] == '}')
            {
                (*tree_file_buffer) += 1;
//fprintf(stderr, "skip }\n");
            }
            
            if (strcmp(node_data, "*") == 0)
            {
//fprintf(stderr, "hmm it is empty node\n");
                free(node_data);
                return NULL;
            }

            while((**tree_file_buffer) == '}')
            {
                (*tree_file_buffer) += 1;
            }
            node* root = MakeStringNode(node_data, NULL, NULL);
            root->child_left = TakeTreeFromTxt(tree_file_buffer);
            root->child_right = TakeTreeFromTxt(tree_file_buffer);
//fprintf(stderr, "recurs end\n");
            return root;
        }
        else
        {
            fprintf(stderr, "AAAAAA What a fuck!!!!\n");
//fprintf(stderr, "symbol after fuck: %c\n", **tree_file_buffer);
            return NULL;
        }
        return NULL;
}

char* PutText(const char *TextFile, long* TextSize)
{
    FILE *OneginText = fopen(TextFile, "r");
    char* buffer = NULL;
    
    if(!OneginText)
    {
        fprintf(stderr, "We cannot open your file!\n");
        return buffer;
    }
    else
    {
        fseek(OneginText, 0, SEEK_END);
        long OneginSize = ftell(OneginText);

        buffer = (char*)calloc(OneginSize + 1, sizeof(char));

        rewind(OneginText);
        fread(buffer, sizeof(char), OneginSize, OneginText);
        fclose(OneginText);
        buffer[OneginSize + 1] = '\0';
        
        *TextSize = OneginSize + 1;
        return buffer;
    }
}

int MakeWayStack(node* root, const char* word, Stack_t* way)
{
    int result = 0;
    if(strcmp((char*)(root->data), word) != 0)
    {
        if (root->child_left)
        {
            //StackPush(way, left_way);
            result = MakeWayStack(root->child_left, word, way);

            if (!result)
            {
                result = MakeWayStack(root->child_right, word, way);
                if(result) StackPush(way, right_way);
                return result;
            }
            StackPush(way, left_way);
            return result;
        }
        return result;
    }
    else
    {
        return 1;
    }
}

void PrintDef(Stack_t *way, double *characteristic_way, node* root)
{
     while(*characteristic_way)
    {

        if ((int)(*characteristic_way) == right_way)
        {       
            printf("%s, ", (char*)(root->data)); 
            root = root->child_right;
        }
        if ((int)(*characteristic_way) == left_way)
        {
            printf("НЕ %s, ", (char*)(root->data)); 
            root = root->child_left;
        }
        StackPop(way, characteristic_way);
    }
    printf("\n");
}

void GiveWordDefinition(node* root, const char* word)
{
    Stack_t way;
    StackCtor(&way, 0);

    MakeWayStack(root, word, &way);
    

    double characteristic_way = 0;
    StackPop(&way, &characteristic_way);
    if ((int)characteristic_way == 0)
    {
        fprintf(stderr, "This word is missing\n");
        return;
    }
    PrintDef(&way, &characteristic_way, root);
    StackDtor(&way);
}

void GiveTheDifference(node* root, const char* word_1, const char* word_2)
{
    Stack_t way_1, way_2;
    StackCtor(&way_1, 0);
    StackCtor(&way_2, 0);
    
    double characteristic_1 = 0,
           characteristic_2 = 0;

    MakeWayStack(root, word_1, &way_1);
    MakeWayStack(root, word_2, &way_2);

    StackPop(&way_1, &characteristic_1);
    
    if ((int)characteristic_1 == 0)
    {
        printf("First word is missing\n");
        return;
    }
    
    StackPop(&way_2, &characteristic_2);
    if ((int)characteristic_2 == 0)
    {
        printf("Second word is missing\n");
        return;
    }

    while ((int)characteristic_1 == (int)characteristic_2)
    {
        if ((int)(characteristic_1) == left_way)
            root = root->child_left;

        if ((int)(characteristic_1) == right_way)
            root = root->child_right;

        StackPop(&way_1, &characteristic_1);
        StackPop(&way_2, &characteristic_2); 
    }
    printf("%s differs from %s in that the first is: ", word_1, word_2);
    PrintDef(&way_1, &characteristic_1, root);
    printf("and the second is: ");
    PrintDef(&way_2, &characteristic_2, root);

    StackDtor(&way_1);
    StackDtor(&way_2);
}