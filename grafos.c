#include <stdio.h>

void imprimir(int n, int grafo[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

int grau(int n, int grafo[][n], int v)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grafo[v][i] > 0)
        {
            count++;
        }
    }
    return count;
}

void grau_total(int n, int grafo[][n])
{
    for (int i = 0; i < n; i++)
    {
        printf("GRAU %d: %d\n", i + 1, grau(n, grafo, i));
    }
}

int grau_maximo(int n, int grafo[][n])
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp_grau = grau(n, grafo, i);
        if (tmp_grau > max)
        {
            max = tmp_grau;
        }
    }
    return max;
}
int grau_minimo(int n, int grafo[][n])
{
    int min = grau(n, grafo, 0);
    for (int i = 1; i < n; i++)
    {
        int tmp_grau = grau(n, grafo, i);
        if (tmp_grau < min)
        {
            min = tmp_grau;
        }
    }
    return min;
}

void paralelo(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grafo[i][j] > 1 && i != j)
            {
                count++;
                printf("PARALELO: %d\n", i + 1);
            }
        }
    }
    printf("QNT PARALELO: %d\n", count);
}

void loop(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grafo[i][i] > 0)
        {
            count++;
            printf("LOOP: %d\n", i + 1);
        }
    }
    printf("QNT LOOP: %d\n", count);
}

void isolado(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grau(n, grafo, i) == 0)
        {
            count++;
            printf("ISOLADO: %d\n", i + 1);
        }
    }
    printf("QNT ISOLADO: %d\n", count);
}

void regular(int n, int grafo[][n])
{
    if (grau_maximo(n, grafo) == grau_minimo(n, grafo))
    {
        printf("É REGULAR\n");
    }
    else
    {
        printf("NÃO É REGULAR\n");
    }
}

void completo(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grafo[i][j] == 1)
            {
                count++;
            }
        }
    }
    if (count == (n * n - n))
    {
        printf("GRAFO COMPLETO\n");
    }
    else
    {
        printf("GRAFO NÃO E COMPLETO\n");
    }
}

void main()
{
    FILE *file;
    int n, a, o, t1, t2, count = 0;
    char line[10];
    file = fopen("G5.txt", "r");

    fscanf(file, "%d %d %d", &n, &a, &o);

    int grafo[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grafo[i][j] = 0;
        }
    }

    while (fgets(line, sizeof(line), file))
    {
        if (count == 0)
        {
            count++;
            continue;
        }
        sscanf(line, "%d %d", &t1, &t2);
        grafo[t1 - 1][t2 - 1]++;
        if (o != 1)
        {
            grafo[t2 - 1][t1 - 1]++;
        }
    }
    fclose(file);

    printf("------------------\n");
    grau_total(n, grafo);
    printf("------------------\n");
    printf("GRAU MINIMO: %d\n", grau_minimo(n, grafo));
    printf("------------------\n");
    printf("GRAU MAXIMO: %d\n", grau_maximo(n, grafo));
    printf("------------------\n");
    loop(n, grafo);
    printf("------------------\n");
    paralelo(n, grafo);
    printf("------------------\n");
    isolado(n, grafo);
    printf("------------------\n");
    regular(n, grafo);
    printf("------------------\n");
    completo(n, grafo);
    printf("------------------\n");
    imprimir(n, grafo);
}