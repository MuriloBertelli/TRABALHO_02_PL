#ifndef MATRIZES_H
#define MATRIZES_H

typedef struct
{
    int **elementos;
    int rows;
    int cols;

} Matriz;

Matriz alocaMatriz(int rows, int cols);
void leMatrixDeArquivo(Matriz *m, const char *nomedoarquivo);
Matriz multiplicaMatrix(const Matriz *m1, const Matriz *m2);
void escreveMatrizEmArquivo(const Matriz *m, const char *nomearquivo);
void liberaMatriz(Matriz *m);
void printMatrix(Matriz *m);
int ehpossivel(const Matriz *m1, const Matriz *m2);

#endif
