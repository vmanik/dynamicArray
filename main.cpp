#include <iostream>

using namespace std;

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int

struct node {
    uint16 ele;
    uint16 pos;
    struct node *next;
};

struct node *head = NULL;
uint32 head_size = 0;
const uint32 head_max_size = 32;
const uint16 not_valid_ele = 0xff;

enum InsertStatus{
    FAILURE = -1,
    SUCCESS = 0,
};

InsertStatus insertElement(struct node **head, uint16 ele, uint16 pos) {
    struct node *temp = NULL;
    struct node *ptemp = NULL;
    uint16 cnt = 0;
    uint8 flag = 0;

    if (pos > head_max_size){
        printf("\n Fail in insertion of ele:%d pos %d > head_max : %d", ele, pos, head_max_size);
        return FAILURE;
    }

    if (*head == NULL) {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->ele = ele;
        temp->pos = pos;
        temp->next = NULL;
        head_size = pos+1;
        *head = temp;
    }
    else {
        struct node *cur = *head;
        struct node *prev = NULL;

        while ((cur != NULL) && (pos > cur->pos)) {
            prev = cur;
            cur = cur->next;
        }

        if (cur != NULL && (cur->pos == pos)) {
            cur->ele = ele;
            return SUCCESS;
        }

        temp = (struct node *)malloc(sizeof(struct node));
        temp->ele = ele;
        temp->pos = pos;
        temp->next = NULL;

        temp->next = prev->next;
        prev->next = temp;

        if(cur == NULL)
        {
            head_size = temp->pos + 1;
        }
    }

    return SUCCESS;
}

enum deleteStatus {
    DEL_FAILURE = -1,
    DEL_SUCCESS = 0,
};

deleteStatus deleteEle(struct node **head, uint16 pos)
{
    if ((pos > head_size) || (head_size == 0)) {
        printf("\n deleteEle failure out of bounds pos:%d > size:%d", pos, head_size);
        return DEL_FAILURE;
    }

    struct node *cur = *head;
    struct node *prev = NULL;

    //check the head
    if(cur->pos == pos) {
        printf("\n Found head pos:%d ele:%d", pos, cur->ele);
        prev = cur;
        *head = cur->next;
        delete(prev);
        return DEL_SUCCESS;
    }

    while((cur != NULL) && (pos > cur->pos)) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL && (cur->pos == pos)) {
        printf("\n Found pos:%d ele:%d", pos, cur->ele);
        prev->next = cur->next;
        delete(cur);

        //Recalculate size if prev is the last node.
        if(prev->next == NULL){
            head_size = prev->pos + 1;
        }

        return DEL_SUCCESS;
    }

    printf("\n Not Found pos:%d", pos);
    return DEL_FAILURE;
}



void printNode(struct node **head){
    struct node *cur = *head;
    //uint16 node_cnt = 0;

    printf("\n printing elements and pos in the list size: %d", head_size);

    while (cur != NULL){

      /* while (node_cnt < cur->pos){
            printf("\n index:%d val:%d",node_cnt, not_valid_ele);
            node_cnt++;
       } */
       printf("\n index:%d val:%d",cur->pos, cur->ele);
       //node_cnt = cur->pos + 1;
       cur = cur->next;
    }

}

int main()
{
    cout << "Hello world!" << endl;

    printNode(&head);

    (void) insertElement(&head, 21, 0);
    printNode(&head);

    (void) insertElement(&head, 23, 2);
    printNode(&head);

    (void) insertElement(&head, 25, 4);
    printNode(&head);

    (void) insertElement(&head, 29, 2);
    printNode(&head);

    (void) insertElement(&head, 54, 1);
    printNode(&head);

    (void) insertElement(&head, 56, -1);
    printNode(&head);

    (void) insertElement(&head, 69, 0);
    printNode(&head);

    (void) deleteEle(&head, 1);
    printNode(&head);

    (void) deleteEle(&head, 6);
    printNode(&head);

    (void) deleteEle(&head, 0);
    printNode(&head);


    (void) deleteEle(&head, -2);
    printNode(&head);


    (void) deleteEle(&head, 4);
    printNode(&head);


    return 0;
}
