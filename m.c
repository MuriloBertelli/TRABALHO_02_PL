#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int **elementos;
    int rows;
    int cols;

} Matriz;

// Matriz m;

void printMatrix(Matriz *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%d  ", m->elementos[i][j]);
        }
        printf("\n");
    }
}

Matriz alocaMatriz(int rows, int cols)
{

    Matriz m;
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
        printf("Desculpe, banco de dados não disponivel %s\n\n", nomedoarquivo);
        exit(1);
    }

    // Le as dimensoes da matriz
    int rows, cols;
    if (fscanf(f, "%d %d", &rows, &cols) != 2)
    {
        printf("Erro na leitura das dimensoes da matriz no arquivo %s\n", nomedoarquivo);
        exit(1);
    }

    // aloca a matriz na dimensao lida
    *m = alocaMatriz(rows, cols);

    // le os elementos da matriz
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            if (fscanf(f, "%d", &m->elementos[i][j]) != 1)
            {
                printf("Erro na leitura dos elementos da matriz no arquivo %s", nomedoarquivo);
            }
        }
    }
    fclose(f);
}

int ehpossivel(const Matriz *m1, const Matriz *m2)
{
    return (m1->cols == m2->rows);
}

Matriz multiplicaMatrix(const Matriz *m1, const Matriz *m2)
{

    // Verifica
    if (!ehpossivel(m1, m2))
    {
        printf("Erro: As matrizes nao podem ser multiplicadas!!\n\n");
        exit(1);
    }

    // multiplica

    Matriz resultado = alocaMatriz(m1->rows, m2->cols);
    for (int i = 0; i < resultado.rows; i++)
    {
        for (int j = 0; j < resultado.cols; j++)
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