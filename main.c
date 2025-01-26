#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TAM 8

//Numera��o do tabuleiro est� invertida. e2 ser� na verdade e7 (com base no tabuleiro do beecrowd);

//Definindo os movimentos do cavalo
int movimentos[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

//Fun��o de compara��o para a fila de prioridade (min-heap)
int comparar(const void *a, const void *b) {
    const int *linhaA = a;
    const int *linhaB = b;
    return linhaA[0] - linhaB[0];
}

//Fun��o que converte o caractere da posi��o inicial/final para coordenadas do tabuleiro
void converter_posicao(char *pos, int *x, int *y) {
    *x = pos[1] - '1';  //1 deve virar 0;
    *y = pos[0] - 'a';  //a deve virar 0;
}

//Fun��o Dijkstra para encontrar o menor caminho
int dijkstra(char *pos_inicial, char *pos_final, int n, int tabuleiro[n][n]) {
    int piaux_x, piaux_y, pfaux_x, pfaux_y;

    //Converte as posi��es iniciais e finais para coordenadas
    converter_posicao(pos_inicial, &piaux_x, &piaux_y);
    converter_posicao(pos_final, &pfaux_x, &pfaux_y);

    int fila[(n*n)] [3];    //Fila para guardar a dist�ncia, a posi��o com base na letra (eixo x) e a posi��o com base no n�mero (eixo y);
    int fila_tam = 0;
    int i, j;

    //Inicializa a dist�ncia como infinita e a fila;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            tabuleiro[i][j] = INT_MAX;
        }
    }
    //print_matriz(n, n, tabuleiro);

    tabuleiro[piaux_x][piaux_y] = 0;
    fila[fila_tam] [0] = 0;
    fila[fila_tam] [1] = piaux_x;
    fila[fila_tam] [2] = piaux_y;
    fila_tam++;

    while(fila_tam > 0){
        //Ordena a fila (menor dist�ncia vem primeiro);
        qsort(fila, fila_tam, sizeof(fila[0]), comparar);

        //Pega o n� com a menor dist�ncia
        int dist_atual = fila[0][0];
        int x = fila[0][1];     //Posi��o das letras (eixo x);
        int y = fila[0][2];     //Posi��o dos n�meros (eixo y);

        //Remove o primeiro elemento da fila passando o pr�ximo valor para o anterior ([0][0] se torna [1][0]);
        for (i = 1; i < fila_tam; i++) {
            fila[i - 1][0] = fila[i][0];
            fila[i - 1][1] = fila[i][1];
            fila[i - 1][2] = fila[i][2];
        }
        fila_tam--;

        //Se chegou ao destino, retorna a dist�ncia;
        if (x == pfaux_x && y == pfaux_y) {
            return dist_atual;
        }

        //Vamos explorar todos os movimentos poss�veis;
        for(i = 0; i < 8; i++){
            //Faz o movimento para uma dire��o;
            int mx = x + movimentos[i][0];  //Movimento no eixo x;
            int my = y + movimentos[i][1];  //Movimento no eixo y;

            if(mx >= 0 && mx < n && my >= 0 && my < n){   //Verifica se ainda estamos dentro do tauleiro;
                int nova_distancia = dist_atual+1;
                if(nova_distancia < tabuleiro[mx][my]){
                    tabuleiro[mx][my] = nova_distancia;   //Atualiza a dist�ncia quando ela for menor;

                    fila[fila_tam][0] = nova_distancia;
                    fila[fila_tam][1] = mx;
                    fila[fila_tam][2] = my;
                    fila_tam++;
                }
            }
        }
    }

    return -1;  //Retorna -1 se n�o houver caminho
}

int main() {
    char pos_inicial[3], pos_final[3];
    int tabuleiro[TAM][TAM];

    // L� casos at� o final do arquivo (EOF)
    while (scanf("%s %s", pos_inicial, pos_final) != EOF) {
        int caminho_minimo = dijkstra(pos_inicial, pos_final, TAM, tabuleiro);
        printf("To get from %s to %s takes %d knight moves.\n", pos_inicial, pos_final, caminho_minimo);
    }

    return 0;
}
