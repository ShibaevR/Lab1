#ifndef LAB1_RETRY_MATRIX_H
#define LAB1_RETRY_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "fieldinfo.h"

typedef struct{
    void **Data;              //Указатель на элементы матрицы
    size_t Size;              //Размер матрицы
    FieldInfo TypeInfo;      //Тип элементов матрицы
} Matrix;

typedef struct{
    char Name[20];
    Matrix *matrix;
} NamedMatrix;

typedef struct{
    NamedMatrix *Matrices;
    size_t Size;
} MatrixCollection;  //Массив указателей на матрицы


void MatrixPrint(Matrix **A);

void FindMatrix(MatrixCollection *collection, Matrix **A, char *name, int *Counter, size_t *Size); //1 and 2

void MatrixCreation(MatrixCollection *collection, Matrix **A, char *name, size_t A_size, FieldInfo *ElementType, int *Counter);      //3

void MatrixAutomaticCreation(MatrixCollection *collection, Matrix **A, char *name, size_t A_size, FieldInfo *ElementType, int *Counter, int MaxNumberInt, float MaxNumberFloat);

void MatrixRenaming(MatrixCollection *collection, char *name1, char *name2); //4

void MatrixAddition(Matrix **M_sum, Matrix **M1, Matrix **M2, int *Counter, MatrixCollection *collection, char *name);  //5

void MatrixMultiplication(Matrix **M_product, Matrix **M1, Matrix **M2, int *Counter, MatrixCollection *collection, char *name);  //6

void MatrixMultiplicationByScalar(Matrix **M_product, Matrix **M1, MatrixCollection *collection, char *name);  //7

void MatrixAdditionOfLinearCombination(Matrix **M_result, int RowNumber, Matrix **M1, MatrixCollection *collection, char *name);  //8

void MatrixFree(Matrix **M);


#endif //LAB1_RETRY_MATRIX_H

