#include "tests.h"

int AllTests(){
    int Response = 0;

    MatrixCollection collection;
    collection.Matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.Size = 0;

    int Counter = 0;

    Matrix M1;
    FieldInfo M_FieldInfo;
    GetIntFieldInfo(&M_FieldInfo);

    char name1[1] = "a";
    size_t size1 = 2;
    int MaxNumberInt = 5;
    float MaxNumberFloat = 5.5;

    //Проверка добавления 1 матрицы
    MatrixAutomaticCreation(&collection, &M1, name1, size1, &M_FieldInfo, &Counter, MaxNumberInt, MaxNumberFloat);

    if(collection.Size != 1){
        printf("\nError in MatrixAutomaticCreation: couldn't add a matrix to the collection\n");
        Response = -1;
    }
    //Проверка нахождения 1 существующей матрицы в коллекции
    Counter = 0;
    FindMatrix(&collection, &M1, name1, &Counter, &size1);
    if(Counter == 0){
        printf("\nError in FindMatrix: couldn't find the matrix to the collection\n");
        Response = -1;
    }


    Matrix M2;
    char name2[1] = "b";
    size_t size2 = 2;

    //Проверка добавления 2 матрицы
    Counter = 0;
    MatrixAutomaticCreation(&collection, &M2, name2, size2, &M_FieldInfo, &Counter, MaxNumberInt, MaxNumberFloat);
    if(collection.Size != 2 ){
        printf("\nError in MatrixAutomaticCreation: couldn't add a matrix to the collection\n");
        Response = -1;
    }
    //Проверка нахождения 2 существующей матрицы в коллекции
    Counter = 0;
    FindMatrix(&collection, &M2, name2, &Counter, &size2);
    if(Counter == 0){
        printf("\nError in FindMatrix: couldn't find the matrix to the collection\n");
        Response = -1;
    }



    //Проверка нахождения несуществующей матрицы
    char NonExistingName[1] = "c";
    Counter = 0;
    FindMatrix(&collection, &M1, NonExistingName, &Counter, &size1);
    if(Counter > 0){
        printf("\nError in FindMatrix: found a matrix that doesn't exist\n");
        Response = -1;
    }


    //Проверка переименовывания матрицы
    char NewName[1] = "d";
    Counter = 0;
    MatrixRenaming(&collection, name1, NewName);
    FindMatrix(&collection, &M1, NewName, &Counter, &size1);
    if(Counter == 0){
        printf("\nError in MatrixRenaming: couldn't rename a matrix\n");
        Response = -1;
    }


    //Проверка нахождения уже заменённого имени
    Counter = 0;
    FindMatrix(&collection, &M1, name1, &Counter, &size1);
    if(Counter > 0){
        printf("\nError in MatrixRenaming: found a name that's no longer in use\n");
        Response = -1;
    }
    MatrixRenaming(&collection, NewName, name1);//возвращаем старое имя для удобства


    //Проверка сложения матриц
    Matrix M_sum;
    size_t size3 = 2;
    char name3[3] = "sum";
    int i, j;
    MatrixAddition(&M_sum, &M1, &M2, &Counter, &collection, name3);
    for(i=0; i < 2; i++){
        for(j=0; j < 2; j++){
            if(M_sum.Data + i*M_sum.Size + j == NULL){
                printf("\nError in MatrixAddition: incorrect sum of elements\n");
                Response = -1;
                break;
            }
        }
    }


    //Проверка добавления матрицы сложения в коллекцию
    Counter = 0;
    FindMatrix(&collection, &M_sum, name3, &Counter, &size3);
    if(Counter == 0){
        printf("\nError in MatrixAddition: couldn't add the matrix to the collection\n");
        Response = -1;
    }


    //Проверка умножения матриц
    Matrix M_product;
    size_t size4 = 2;
    char name4[7] = "product";
    MatrixMultiplication(&M_product, &M1, &M2, &Counter, &collection, name4);
    for(i=0; i < 2; i++){
        for(j=0; j < 2; j++){
            if(M_product.Data + i*M_product.Size + j == NULL){
                printf("\nError in MatrixMultiplication: incorrect product of elements\n");
                Response = -1;
                break;
            }
        }
    }


    //Проверка добавления матрицы умножения в коллекцию
    Counter = 0;
    FindMatrix(&collection, &M_product, name4, &Counter, &size4);
    if(Counter == 0){
        printf("\nError in MatrixMultiplication: couldn't add the matrix to the collection\n");
        Response = -1;
    }


    //Проверка умножения матрицы на число
    /*Matrix M_result1;
    size_t size5 = 2;
    char name5[7] = "result1";
    void *Multiplier = malloc(sizeof(int*));
    *(int*)Multiplier = 5;
    MatrixMultiplicationByScalar(&M_result1, &M1, &collection, name5);
    for(i=0; i < 2; i++){
        for(j=0; j < 2; j++){
            if(M_result1.Data + i*M_result1.Size + j == NULL){
                printf("\nError in MatrixMultiplicationByScalar: incorrect product of elements\n");
                Response = -1;
                break;
            }
        }
    }


    //Проверка добавления матрицы умножения на число в коллекцию
    Counter = 0;
    FindMatrix(&collection, &M_result1, name5, &Counter, &size5);
    if(Counter == 0){
        printf("\nError in MatrixMultiplicationByScalar: couldn't add the matrix to the collection\n");
        Response = -1;
    }*/


    //Проверка добавления к строке матрицы линейной комбинации других строк
    Matrix M_result2;
    size_t size6 = 2;
    char name6[7] = "result2";
    int RowNumber = 2;
    MatrixAdditionOfLinearCombination(&M_result2, RowNumber, &M1, &collection, name6);
    for(i=0; i < 2; i++){
        for(j=0; j < 2; j++){
            if(M_result2.Data + i*M_result2.Size + j == NULL){
                printf("\nError in MatrixMultiplicationByScalar: incorrect product of elements\n");
                Response = -1;
                break;
            }
        }
    }


    //Проверка добавления новой матрицы в коллекцию
    Counter = 0;
    FindMatrix(&collection, &M_result2, name6, &Counter, &size6);
    if(Counter == 0){
        printf("\nError in MatrixAdditionOfLinearCombination: couldn't add the matrix to the collection\n");
        Response = -1;
    }




    for (int k = 0; k < collection.Size; k++)
    {
        MatrixFree(&collection.Matrices[k].matrix);
    }
    collection.Size = 0;
    free(collection.Matrices);

    MatrixFree(&M1);
    MatrixFree(&M2);
    MatrixFree(&M_sum);
    MatrixFree(&M_product);
    //MatrixFree(&M_result1);
    MatrixFree(&M_result2);


    return Response;
}