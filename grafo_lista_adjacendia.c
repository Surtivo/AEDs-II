#include <stdio.h>
#include <stdlib.h>
#define TAM 5

typedef struct grafo_lista_adjacendia{
    int valor;
    struct grafo_lista_adjacendia *prox;
    
}Lista_adj;

void inicializa_grafo (Lista_adj **grafo){
    for (int i=0; i<TAM; i++){
        grafo[i] = NULL;
    }
}

void insere_grafo (Lista_adj **grafo, int indice, int valor){
    
    Lista_adj *novo = malloc(sizeof(Lista_adj));
    Lista_adj *ant = grafo[indice];
    
    while (ant->prox != NULL){
        ant = ant->prox;
    }
    
    novo->valor = valor;
    novo->prox = NULL;
    ant->prox = novo;

}

void print_grafo (Lista_adj **grafo){

    for(int i=0; i<TAM; i++){
        Lista_adj *atual = grafo[i];

        if(atual == NULL){
            printf("[%d]:\t\n", i+1);
        }else{
            printf("[%d]:\t", i+1);  
            atual = atual->prox;  
            while(atual != NULL){
                printf("%d\t", atual->valor);  
                atual = atual->prox; 
            }
            printf("\n");
        }
        
    }
}

int grau_max (Lista_adj **grafo, int indice){
    Lista_adj *ant = grafo[indice];
    ant = ant->prox;
    int count = 0;
    while(ant != NULL){
        count++;
        ant = ant->prox;
    }
    return count;
}

int main (){

    FILE *file;
    int n, a, o, t1, t2, count = 0;
    char line[10];
    file = fopen("G1.txt", "r");

    fscanf(file, "%d %d %d", &n, &a, &o);

    Lista_adj *grafo [TAM];
    for (int i = 0; i < TAM; i++){
        grafo[i] = malloc(sizeof(Lista_adj));
        grafo[i]->valor = i;
        grafo[i]->prox = NULL;
    }

    if(o != 0){
        while (fgets(line, sizeof(line), file)){
        if (count == 0){
            count++;
            continue;
        }
        sscanf(line, "%d %d", &t1, &t2);
        insere_grafo(grafo, t1-1, t2);
        insere_grafo(grafo, t2-1, t1);
        }
    }else{
        while (fgets(line, sizeof(line), file)){
        if (count == 0){
            count++;
            continue;
        }
        sscanf(line, "%d %d", &t1, &t2);
        insere_grafo(grafo, t1-1, t2);
        }
    }
    
    fclose(file);
    
    print_grafo(grafo);
    printf("\n\n");
    int indice = 2;
    printf("Grau indice %d: %d\n", indice, grau_max(grafo, indice-1));

    return 0;
}