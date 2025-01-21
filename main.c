#include <stdio.h>
#include <stdlib.h>
#define TAM 4

typedef struct grafo_lista_adjacendia {
    int valor;
    struct grafo_lista_adjacendia *prox;

} Lista_adj;

void inicializa_grafo (Lista_adj **grafo) {
    for (int i=0; i<TAM; i++) {
        grafo[i] = NULL;
    }
}

void insere_grafo (Lista_adj **grafo, int indice, int valor) {

    Lista_adj *novo = malloc(sizeof(Lista_adj));
    Lista_adj *ant = grafo[indice];

    while (ant->prox != NULL) {
        ant = ant->prox;
    }

    novo->valor = valor;
    novo->prox = NULL;
    ant->prox = novo;

}

void print_grafo (Lista_adj **grafo) {

    for(int i=0; i<TAM; i++) {
        Lista_adj *atual = grafo[i];

        if(atual == NULL) {
            printf("[%d]:\t\n", i+1);
        } else {
            printf("[%d]:\t", i+1);
            atual = atual->prox;
            while(atual != NULL) {
                printf("%d\t", atual->valor);
                atual = atual->prox;
            }
            printf("\n");
        }

    }
}

int grau_saida (Lista_adj **grafo, int indice) {
    Lista_adj *ant = grafo[indice];
    ant = ant->prox;
    int count = 0;
    while(ant != NULL) {
        count++;
        ant = ant->prox;
    }
    return count;
}

int grau_entrada(Lista_adj **grafo, int indice)
{
    Lista_adj *ant;
    int count = 0;
    for(int i=0; i<TAM-1; i++) {
        ant = grafo[i];
        ant = ant->prox;
        while(ant != NULL) {
            if(ant->valor == indice)
                count++;
            ant = ant->prox;
        }
    }
    return count;
}

void verticeIsoladoDir (Lista_adj **grafo) {
    for(int i=1; i<=TAM; i++) {
        if((grau_entrada (grafo, i)) == 0 && (grau_saida(grafo, i-1)) == 0)
            printf("Vertice [%d] e isolado\n", i);
    }
    printf("\n");
}

void verticeIsoladoNDir (Lista_adj **grafo) {
    for(int i=1; i<=TAM; i++) {
        if((grau_saida(grafo, i-1)) == 0)
            printf("Vertice [%d] e isolado\n", i);
    }
    printf("\n");
}

void grafo_regular_Ndir (Lista_adj **grafo) {
    int aux = grau_saida(grafo, 0);
    int aux2 = 0;
    for(int i=1; i<TAM; i++) {
        if(grau_saida(grafo, i)!=aux) {
            aux2 = i;
            break;
        }
    }
    if(grau_saida(grafo, aux2)!=aux) {
        printf("Grafo nao e regular\n");
    } else {
        printf("Grafo e regular\n");
    }
}

void grafo_regular_dir (Lista_adj **grafo) {
    int aux = grau_saida(grafo, 0);
    int aux2 = grau_entrada(grafo, 0);
    int aux3 = 0;
    for(int i=1; i<TAM; i++) {
        if((grau_saida(grafo, i)!=aux) || (grau_entrada(grafo, i)!=aux2)!=aux2) {
            aux3 = i;
            break;
        }
    }
    if((grau_saida(grafo, aux3)!=aux) || (grau_entrada(grafo, aux3)!=aux2)!=aux) {
        printf("Grafo nao e regular\n");
    } else {
        printf("Grafo e regular\n");
    }
}

void grafo_completo_Ndir (Lista_adj **grafo) {
    Lista_adj *ant;
    int count = 0;
    ant = grafo[0];
    ant = ant->prox;
    for(int i=2; i<=TAM; i++) {
        if(ant->valor == i)
            count++;
        ant = ant->prox;
    }
    if(count == TAM-1)
        printf("Grafo e completo\n");
}

void printvet (int *vet, int tam)
{
    for (int i=0; i<(tam); i++)
        printf("%d\t", vet[i]);
    printf("\n\n");
}

void printvetchar (char *vet, int tam)
{
    for (int i=0; i<(tam); i++)
        printf("%c\t", vet[i]);
    printf("\n\n");
}

PrintPath(Lista_adj **grafo, int beg, int end, int ant[]) {
    if(beg == end)
        printf("%d ", beg+1);
    else if (ant[end-1] == -1)
        printf("Nao existe caminho de %d ate %d", beg+1, end);
    else {
        PrintPath(grafo, beg, ant[end-1], ant);
        printf("%d ", end);
    }
}

void BFS (Lista_adj **grafo, int beg, int end) {    //Funciona, mas tem seus problemas;
    int fila[TAM+1];
    int dist[TAM];
    int ant[TAM];
    char color[TAM];
    int aux = 0;
    int aux2;
    int aux3 = 1;

    for(int u=0; u<TAM; u++) {
        color[u] = 'b';
        dist[u] = -1;
        ant[u] = -1;
        fila[u] = -64;
    }
    fila[TAM+1] = -64;
    color[beg] = 'c';
    dist[beg] = 0;
    ant[beg] = -1;
    fila[aux] = beg;

    Lista_adj *aux_grafo = grafo[beg];
    aux_grafo = aux_grafo->prox;

    //return;

    while( aux < aux3) {
        aux2 = fila[aux++];
        //printf("aux2 = %d\n\n", aux2);
        while(aux_grafo != NULL) {
            if(color[aux_grafo->valor-1] == 'b') {
                color[aux_grafo->valor-1] = 'c';
                dist[aux_grafo->valor-1] = dist[aux2]+1;
                ant[aux_grafo->valor-1] = aux2;
                fila[aux3++] = aux_grafo->valor;
            }
            //printf("%d\n\n", aux_grafo->valor);
            aux_grafo = aux_grafo->prox;
        }
        //printf("aux = %d\n\n", aux);
        color[aux2] = 'p';
        aux_grafo = grafo[aux-1]->prox;
    }
    PrintPath(grafo, beg, end, ant);
}

int main () {

    FILE *file;
    int n, a, o, t1, t2, count = 0;
    char line[10];
    file = fopen("G6.txt", "r");

    fscanf(file, "%d %d %d", &n, &a, &o);

    Lista_adj *grafo [TAM];
    for (int i = 0; i < TAM; i++) {
        grafo[i] = malloc(sizeof(Lista_adj));
        grafo[i]->valor = i;
        grafo[i]->prox = NULL;
    }

    if(o == 0) {
        while (fgets(line, sizeof(line), file)) {
            if (count == 0) {
                count++;
                continue;
            }
            sscanf(line, "%d %d", &t1, &t2);
            insere_grafo(grafo, t1-1, t2);
            insere_grafo(grafo, t2-1, t1);
        }
    } else {
        while (fgets(line, sizeof(line), file)) {
            if (count == 0) {
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
    int indice = 4;
    if(o==0) {
        printf("Grau indice de saida %d: %d\n", indice, grau_saida(grafo, indice-1));
        verticeIsoladoNDir(grafo);
        grafo_regular_Ndir(grafo);
        //grafo_completo_Ndir(grafo);
    } else {
        printf("Grau indice de saida %d: %d\n", indice, grau_saida(grafo, indice-1));
        printf("Grau indice de entrada %d: %d\n", indice, grau_entrada(grafo, indice));
        verticeIsoladoDir(grafo);
        grafo_regular_dir(grafo);
    }


    BFS(grafo, indice-3, 4);
    printf("\n");
    //remove_no(grafo, indice-1);
    //printf("\n\n");
    //print_grafo(grafo);


    return 0;
}
