#ifndef LAB1_RETRY_FIELDINFO_H
#define LAB1_RETRY_FIELDINFO_H

#include <stdlib.h>
#include <stddef.h>

#include "element.h"

typedef void (*ElementAddition)(void *sum, void *a, void *b);
typedef void (*ElementMultiplication)(void *product, void *a, void *b);
typedef void (*ElementPrint)(void *a);


typedef struct{
    char *TypeName;                               //Название типа элемента
    size_t ElementSize;                           //Размер 1 элемента

    ElementAddition M_Addition;                  //Сумма элементов матрицы
    ElementMultiplication M_Multiplication;      //Произведение элементов матрицы
    ElementPrint M_Print;                        //Вывод элементов матрицы
}FieldInfo;

void GetIntFieldInfo(FieldInfo *ElementType);
void GetFloatFieldInfo(FieldInfo *ElementType);


#endif //LAB1_RETRY_FIELDINFO_H
