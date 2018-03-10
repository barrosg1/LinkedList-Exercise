/*
 
 Gabriel Barros
 CS 288 2017F Section 101
 HW 02
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* self-referential structure */
struct Node
{
    int item;
    int StdID;
    struct Node *next;
};

struct List
{
    struct Node *head;
    struct Node *tail;
};

struct List SLL_new()
{
    /* construct an empty list */
    struct List list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

int SSL_length(struct List *list)
{
    /* return the number of items in the list */
    struct Node *p;
    
    int n = 0;
    for (p = list->head; p != NULL; p = p->next)
    {
        ++n;
    }
    return n;
}

int SLL_empty(struct List *list)
{
    /* return true if the list contains no items */
    return list->head == NULL;
}

int SLL_pop(struct List *list)
{
    /* remove and return the first item of the list */
    struct Node *node = list->head;
    int item = node->item;
    list->head = node->next;
    if (SLL_empty(list))
    {
        list->tail = NULL;
    }
    free(node);
    return item;
}

void SLL_clear(struct List *list)
{
    /* remove all the items from the list */
    while (!SLL_empty(list))
    {
        SLL_pop(list);
    }
}

void SLL_push(struct List *list, int item, int id)
{
    /*  insert the item at the front of the list */
    struct Node *node = malloc(sizeof(struct Node));
    node->item = item;
    node->StdID = id;
    list->head = node->next;
    list->tail = node;
    list->head = node;
}

void SLL_append(struct List *list, int item, int id)
{
    /* append the item to the end of the list */
    if (SLL_empty(list))
    {
        SLL_push(list, item, id);
    }
    else
    {
        struct Node *node = malloc(sizeof(struct Node));
        node->item = item;
        node->StdID = id;
        node->next = NULL;
        list->tail->next = node;
        list->tail = list->tail->next;
    }
}

int readFromFile(struct List *list, int argc, char*argv[]){
    if (argc < 5)
    {
        printf("Not enough arguments!\n");
        return 1;
    }
    
    /*open file*/
    char e;
    FILE*fp = NULL;
    
    int i=0;
    for (i++; i < argc; i++)
    {
        /*If not opened then print error message*/
        if (!fp)
        {
            printf("File: %s did not open!\n", argv[i]);
            return 0;
        }
        
        fp = fopen(argv[i], "r");
        
        char arr[20];
        int i = 0, id = 0;
        while (fread(&e, 1, 1, fp))
        {
            if (e == ',')
            {
                id = atoi(&arr[0]);
                memset(arr, 0, 20);
                i = 0;
            }
            else if (e == '\n')
            {
                SLL_append(list, atoi(&arr[0]), id);
                i = 0;
                memset(arr, 0, 20);
            }
            else
            {
                arr[i++] = e;
            }
        }
    }
    return 1;
}

void DisplayList(struct List * list){
    struct Node * nod = list->head;
    while (nod != NULL)
    {
        printf("%i %i\n",  nod->StdID, nod->item);
        nod = nod->next;
    }
}

void sortList(struct List * list)
{
    struct Node * nod = list->head;
    if (!nod->next)
    {
        printf("Empty\n");
    }
    struct Node * nod2 = list->head;
    int temp;
    while (nod != NULL)
    {
        nod2 = list->head;
        while (nod2 != NULL)
        {
            if (nod->StdID < nod2->StdID)
            {
                //swap
                temp = nod->item;
                nod->item = nod2->item;
                nod2->item = temp;
                
                // swap stdID again
                temp = nod->StdID;
                nod->StdID = nod2->StdID;
                nod2->StdID = temp;
            }
            nod2 = nod2->next;
        }
        nod = nod->next;
    }
}

void outputFile(int argc, char*argv[], struct List *list)
{
    FILE*fp3 = NULL;
    
    if (argc < 5)
    {
        printf("Not enough arguments!\n");
    }
    else
    {
        fp3 = fopen(argv[4], "w");
        if (!fp3)
        {
            printf("File3 not opened!\n");
        }
        else
        {
            struct Node * nod = list->head;
            int sum = 0;
            int id = nod->StdID;
            int total = 0;
            
            printf("Final grade\n");
            while (nod != NULL)
            {
                
                if (id == nod->StdID)
                {
                    sum += nod->item;
                    total++;
                }
                else
                {
                    sum = sum / total;
                    fprintf(fp3, "%d,", id);
                    fprintf(fp3, "%d\n", sum);
                    
                    //For console output
                    printf("%d,", id);
                    printf("%d\n", sum);
                    total = 1;
                    id = nod->StdID;
                    sum = nod->item;
                }
                
                if (!nod->next)
                {
                    sum = sum / total;
                    fprintf(fp3, "%d,", nod->StdID);
                    fprintf(fp3, "%d\n", sum);
                    
                    //For console output
                    printf("%d,", nod->StdID);
                    printf("%d\n", sum);
                }
                nod = nod->next;
            }
        }
    }
    fclose(fp3);
}
int main(int argc, char * argv[])
{
    struct List list = SLL_new();
    readFromFile(&list, argc, argv);
    sortList(&list);
    DisplayList(&list);
    outputFile(argc, argv, &list);
    printf("\nDONE !\n");
    getchar();
    return 0;
}
