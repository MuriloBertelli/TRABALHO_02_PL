#include <stdio.h>
#include <stdlib.h>
#include "m.h"

Matriz m;

void printMatrix(int rows, int cols, int **matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

Matriz alocaMatriz(int rows, int cols)
{

    m.rows = rows;
    m.cols = cols;
    m.elementos = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        m.elementos[i] = (int *)malloc(cols * sizeof(int));
    }
    return m;
}

void leMatrixDeArquivo(Matriz *m, const char *nomedoarquivo)
{

    FILE *f;
    f = fopen(nomedoarquivo, "r");

    if (f == 0)
    {
        printf("Desculpe, banco de dados não disponivel\n\n");
        exit(1);
    }

    fscanf(f, "%d %d", &m->rows, &m->cols);
    *m = alocaMatriz(m->rows, m->cols);

    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            fscanf(f, "%d", &m->elementos[i][j]);
        }
    }

    fclose(f);
}

Matriz multiplicaMatrix(const Matriz *m1, const Matriz *m2)
{

    // Verifica
    if (m1->cols != m2->rows)
    {
        printf("Erro: As matrizes não podem ser multiplicadas!!\n\n");
    }

    // multiplica

    Matriz resultado = alocaMatriz(m1->rows, m2->cols);
    for (int i = 0; i < resultado.rows; i++)
    {
        for (int k = 0; k < resultado.cols; j++)
        {

            resultado.elementos[i][j] = 0;
            for (int k = 0; k < m1->cols; k++)
            {
                resultado.elementos[i][j] += m1->elementos[i][k] * m2->elementos[k][j];
            }
        }
    }

    return resultado;
}

void escreveMatrizEmArquivo(const Matriz *m, const char *nomearquivo)
{

    FILE *f;
    f = fopen(nomearquivo, "w");
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            fprintf(f, "%d ", m->elementos[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void liberaMatriz(Matriz *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->elementos[i]);
    }
    free(m->elementos);
}

int main()
{

    Matriz A, B, C;

    // Le matrizes de A e B do arquivo
    leMatrixDeArquivo(&A, "matrizA.txt");
    leMatrixDeArquivo(&B, "matrizB.txt");

    // alocar memoria para C

    C = alocaMatriz(A.rows, B.cols);

    // Multiplicação das matrizes

    C = multiplicaMatrix(&A, &B);

    // Impressão das matrizes  A, B e C

    printf("Matriz A:\n");
    printMatrix(&A);
    printf("Matriz B:\n");
    printMatrix(&B);
    printf("Matriz C (Resultado):\n");
    printMatrix(&C);

    // escrita da matriz C em um arquivo.
    escreveMatrizEmArquivo(&C, "matrizC.txt");

    // libera memoria

    liberaMatriz(&A);
    liberaMatriz(&B);
    liberaMatriz(&C);
}