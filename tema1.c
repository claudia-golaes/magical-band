/*GOLAES Claudia-311CC*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { 
    char elem;
    struct ListNode *next; 
    struct ListNode *prev; 
} ListNode, *TListNode;

typedef struct {
    TListNode first;
    TListNode last;
} DoubleList, *DList;

typedef struct QueueNode {
    char function[20];
    char operator;
    struct QueueNode* next;
} QueueNode, *TQueueNode;

typedef struct {
    TQueueNode front;
    TQueueNode rear;
} Queue, *TQueue;

// Functie pentru numararea elementelor dintr-o lista
int count(DList list) 
{
    TListNode nodcurent = list->first;
    int nr = 0;
    while (nodcurent != NULL) {
        nodcurent = nodcurent->next;
        nr++;
    }
    return nr;
}

// Functie pentru inserarea unui element intr-o lista dublu inlantuita
void insert(DList list, char val, int poz, int *deget) 
{
    // Un nod nou pentru elementul ce urmeaza a fi inserat
    TListNode nou = (TListNode) malloc(sizeof(ListNode));
    nou->elem = val;

    // Cazul cand lista este goala
    if (list->first == NULL) {
        list->first = nou;
        list->last = nou;
        nou->next = NULL;
        nou->prev = NULL;
        *deget=0;
        return;
    }

    // Cazul cand elementul trebuie inserat la inceputul listei
    if (poz == 0) {
        nou->next = list->first;
        nou->prev = NULL;
        list->first->prev = nou;
        list->first = nou;
        *deget=0;
        return;
    }

    // Cazul cand elementul trebuie inserat la finalul listei
    if (poz == -1 || poz >=count(list)) {
        *deget=count(list);
        nou->prev = list->last;
        nou->next = NULL;
        list->last->next = nou;
        list->last = nou;
        return;
    }

    // Cazul cand elementul trebuie inserat la o pozitie intermediara
    TListNode nodcurent = list->first;
    int i = 0;
    while (nodcurent != NULL && i < poz) {
        nodcurent = nodcurent->next;
        i++;
    }
    
    nou->prev = nodcurent->prev;
    nou->next = nodcurent;
    nodcurent->prev->next = nou;
    nodcurent->prev = nou;
    *deget=poz;
}


// Functie pentru afisarea elementelor dintr-o lista
void print_list(DList list, int deget, FILE *dest) 
{
    TListNode current = list->first;
    int i=0;
    while (current != NULL) {
        if(i==deget) 
        {
            fprintf(dest, "|%c|", current->elem);
        }else{
            fprintf(dest, "%c", current->elem);
        }
        current = current->next;
        i++;
    }
    fprintf(dest,"\n");
}

void move(DList list,  int directie, int *deget) 
{
    // Directia este la dreapta
    if (directie == 1) {
        // Verificare daca exista un element la dreapta
        if (*deget < count(list) - 1) {
            *deget += 1; // Incrementare valoarea pointerului deget
        } else {
            insert(list, '#', -1, deget); // Inserare caracterul '#' la finalul listei
        }
    }
    // Directia este la stanga
    else if (directie == -1) {
        // Verificare daca exista un element la stanga
        if (*deget > 0) {
            *deget -= 1; // Decrementare valoarea pointerului deget
        }
        // Nu exista element la stanga=> nimic
    }
}


//Functiile de baza pentru implementarea cozii
TQueue initQ()
{
    TQueue queue = (TQueue)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void addQ(TQueue queue, char* function, char operator)
{
    TQueueNode nou = (TQueueNode)malloc(sizeof(QueueNode));
    strcpy(nou->function, function);
    nou->operator = operator;
    nou->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = nou;
        queue->rear = nou;
        return;
    }

    queue->rear->next = nou;
    queue->rear = nou;
}

TQueueNode delQ(TQueue queue) 
{
    if (queue->front == NULL)
    {
        return NULL;
    }

    TQueueNode temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    return temp;
}

int emptyQ(TQueue queue)
{
    return queue->front == NULL;
}

//Functie pentru adaugarea comenzii in coada
void addCommand(TQueue queue, char* function, char operator) 
{
    addQ(queue, function, operator);
}

//Functie pentru executarea comenzii
void executeCommand(TQueue queue, DList list, int *deget) {
    TQueueNode nou = (TQueueNode)malloc(sizeof(QueueNode));
    nou=delQ(queue);
    char *command, operator;
    strcpy(command, nou->function);
    operator=nou->operator;
    if (strcmp(command, "INSERT_LEFT") == 0)
    {
        insert(list, operator, *deget, deget);
    }else if (strcmp(command, "INSERT_RIGHT") == 0){
        insert(list, operator, *deget + 1, deget);
    }else if (strcmp(command, "MOVE_LEFT") == 0){
        move(list, -1, deget);
    }else if (strcmp(command, "MOVE_RIGHT") == 0){
        move(list, 1, deget);
    }
}

// Functia main
int main() {
    int deget=0, nr_comenzi, i=0;
    //char operator, command[20];
    TQueue coada_exec;
    coada_exec=initQ();
    DList list = (DList) malloc(sizeof(DoubleList));
    list->first = NULL;
    list->last = NULL;
    // Inseram # in lista
    insert(list, '#', 0, &deget);
    //print_list(list, deget);
    //deschiderea fisierlor
    FILE *dest, *src;
    dest = fopen("tema1.out", "w");
	if (!dest)
	{
		fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
		return 0;
	}
    src = fopen("tema1.in", "r");
	if (!src)
	{
		fprintf(stderr, "Eroare! Nu am putut deschide fisierul sursa!\n");
    	return 0;
	}
    fscanf(src, "%d\n", &nr_comenzi);
    printf("%d\n", nr_comenzi);
    //fgets(command, 20, src);
    while(i<=nr_comenzi)
    {
        char linie[20], *p, *comm, *operator;
        fgets(linie, 20, src);
        linie[strlen(linie)-1]=0;
        comm=strtok(linie, " "); 
        if(strcmp(comm, "EXECUTE")==0)
        {
            executeCommand(coada_exec, list, &deget);
        }else{
            if (strcmp(comm, "INSERT_LEFT") == 0)
            {
                operator=strtok(NULL, " ");
                addCommand(coada_exec, "INSERT_LEFT", operator[0]);
            }else if (strcmp(comm, "INSERT_RIGHT") == 0){
                operator=strtok(NULL, " ");
                addCommand(coada_exec, "INSERT_RIGHT", operator[0]);
            }else if (strcmp(comm, "MOVE_LEFT") == 0){
                addCommand(coada_exec, "MOVE_LEFT", '0');
            }else if (strcmp(comm, "MOVE_RIGHT") == 0){
                addCommand(coada_exec, "MOVE_RIGHT", '0');
            }else if(strcmp(comm, "SHOW")==0)
            {
                print_list(list, deget, dest);
            }
        } 
        i++;
    }
        
    return 0;
}