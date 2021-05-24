#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PI 3.14159265358979323846

struct PizzaOrder {
    float fppd;
    struct PizzaOrder* next;
    char oname[];
};

void sortList(struct PizzaOrder* head);
void printList(struct PizzaOrder* head);
void freeList(struct PizzaOrder* head);


int main (int argc, char* argv[]){
    //open file
    FILE *pfile;
    char buf[64];
    char dbuf1[64];
    char cbuf1[64];
    float dbuf;
    float cbuf;
    float ppd;

    struct PizzaOrder* HEAD = NULL;
    struct PizzaOrder* last = NULL;

    pfile = fopen(argv[1],"r");

    while (1){

        if (pfile == NULL){
            printf("PIZZA FILE IS EMPTY\n");
            break;
        }
	else{
	    fgets(buf,64,pfile);
	}
        //if "DONE"...
        if (strcmp(buf,"DONE\n")==0){
            break;
        }
        //read diameter float
        fgets(dbuf1,64,pfile);
        dbuf = (float) atof(dbuf1);
        //read price float
        fgets(cbuf1,64,pfile);
        cbuf = (float) atof(cbuf1);
        //if cost == 0, ppd = 0
        if (cbuf == 0){
            ppd=0;
        }
        else{
            ppd=(((PI)/4)*(dbuf*dbuf))/(cbuf);
        }

        struct PizzaOrder* new_node = (struct PizzaOrder*) malloc(sizeof(struct PizzaOrder));
        strcpy(new_node->oname,buf);
	strtok(new_node->oname,"\n");
        new_node->fppd = ppd;
        new_node->next = NULL;

        if(HEAD == NULL){
            HEAD = new_node;
            last = new_node;
        }
        else {
            last->next = new_node;
            last = last->next;
        }

    }
    //sort
    sortList(HEAD);
    //print
    printList(HEAD);
    //free
    freeList(HEAD);

    //close file
    fclose(pfile);
    return 0;
}

void sortList(struct PizzaOrder* head){
    char tempname[64];
    float tempppd;
    float maxppd;
    struct PizzaOrder* swap = NULL;
    struct PizzaOrder* trav = head;
    struct PizzaOrder* new_head = head;

    while (new_head->next != NULL){
        maxppd = new_head->fppd;
        swap = new_head;
        trav = new_head->next;
        while (trav!=NULL){
            if (trav->fppd>maxppd){
                maxppd = trav->fppd;
                swap = trav;
            }
            else if (trav->fppd==maxppd){
                if (strcmp(trav->oname,swap->oname)<0){
                    //if second is alphabetically before the prev...
                    swap = trav;
                }
            }
            trav = trav->next;
        }
        strcpy(tempname,new_head->oname);
        tempppd = new_head->fppd;
        strcpy(new_head->oname,swap->oname);
        new_head->fppd = swap->fppd;
        strcpy(swap->oname,tempname);
        swap->fppd = tempppd;
        new_head = new_head->next;
    }
    return;
}

void printList(struct PizzaOrder* head){
    if (head == NULL){
        return;
    }
    struct PizzaOrder* curr = head;
    while (curr!=NULL){
        printf("%s %f\n",curr->oname,curr->fppd);
        curr = curr->next;
    }
    return;
}

void freeList(struct PizzaOrder* head){
    if (head == NULL){
        return;
    }
    struct PizzaOrder* curr = head;
    struct PizzaOrder* prev = NULL;
    while (curr != NULL){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    return;
}
