#include "matrix.h"

void MatrixPrint(Matrix **A){
    int i, j;
    printf("\n");
    for (i=0; i < (**A).Size; i++){
        printf("   ");
        for (j=0; j < (**A).Size; j++) {
            (**A).TypeInfo.M_Print((Matrix*)(**A).Data + (i * (**A).Size) + j);
        }
        printf("\n");
    }
    printf("\n");
}


void FindMatrix(MatrixCollection *collection, Matrix **A, char *name, int *Counter, size_t *Size){
    int i;

    for(i=0; i < (*collection).Size; i++){
        if (strcmp((*collection).Matrices[i].Name, name)==0){
            (*Counter)++;
            *A = (*collection).Matrices[i].matrix;
            *Size = (**A).Size;
            break;
        }
    }
}


void MatrixCreation(MatrixCollection *collection, Matrix **A, char *name, size_t A_size, FieldInfo *ElementType, int *Counter){

    int AddMemory = 100;
    int i, j;

    for(i=0; i < (*collection).Size; i++){
        if (strcmp((*collection).Matrices[i].Name, name)==0){
            (*Counter)++;
            return;
        }
    }

    *A = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**A).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*A && (**A).Data){
        for (i=0; i < A_size; i++){

            (**A).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));

            for (j=0; j < A_size; j++){
                printf("\nEnter element in row %d column %d:", i+1, j+1);
                if (strcmp( (*ElementType).TypeName, "int")==0){
                    scanf("%d", ( (Matrix *)(**A).Data + (i*A_size) + j));
                }
                else if(strcmp( (*ElementType).TypeName, "float")==0){
                    scanf("%f", ( (Matrix *)(**A).Data + (i*A_size) + j));
                }
            }
        }
    }
    else{
        printf("\nError in MatrixCreation: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (**A).Size = A_size;
    (**A).TypeInfo = *ElementType;

    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixCreation: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *A;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;


}


void MatrixAutomaticCreation(MatrixCollection *collection, Matrix **A, char *name, size_t A_size, FieldInfo *ElementType, int *Counter, int MaxNumberInt, float MaxNumberFloat){

    int AddMemory = 100;
    int i, j;

    srand((unsigned int)time(NULL));
    int RandomInt;
    float RandomFloat;
    int k;

    for(i=0; i < (*collection).Size; i++){
        if (strcmp((*collection).Matrices[i].Name, name)==0){
            (*Counter)++;
            return;
        }
    }


    *A = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**A).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*A && (**A).Data){
        for (i=0; i < A_size; i++){

            (**A).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));

            for (j=0; j < A_size; j++){

                void *TemporaryResult = malloc( sizeof((**A).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixAutomaticCreation: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                if (strcmp( (*ElementType).TypeName, "int")==0 ){
                    for (k=0; k < 5; k++){
                        RandomInt = rand()/(RAND_MAX/MaxNumberInt);
                    }
                    *(int*)TemporaryResult = RandomInt;
                }
                else if (strcmp( (*ElementType).TypeName, "float")==0 ){
                    for (k=0; k < 5; k++){
                        RandomFloat = (float)rand()/((float)RAND_MAX/MaxNumberFloat);
                    }
                    *(float*)TemporaryResult = RandomFloat;
                }

                memcpy( (Matrix*)(**A).Data + i*A_size + j, TemporaryResult, sizeof((**A).TypeInfo.ElementSize));

                free(TemporaryResult);
            }
        }
    }
    else{
        printf("\nError in MatrixAutomaticCreation: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (**A).Size = A_size;
    (**A).TypeInfo = *ElementType;


    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixAutomaticCreation: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *A;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;

}


void MatrixRenaming(MatrixCollection *collection, char *name1, char *name2){
    int i;

    for(i=0; i < (*collection).Size; i++){
        if (strcmp((*collection).Matrices[i].Name, name1)==0){
            strncpy( (*collection).Matrices[i].Name, name2, sizeof((*collection).Matrices[i].Name));
            break;
        }
    }
}


void MatrixAddition(Matrix **M_Sum, Matrix **M1, Matrix **M2, int *Counter,
                    MatrixCollection *collection, char *name){

    int i, j;

    if(strcmp( (**M1).TypeInfo.TypeName, (**M2).TypeInfo.TypeName) != 0){
        (*Counter)++;
        return;
    }


    int AddMemory = 100;//A_size;

    *M_Sum = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**M_Sum).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*M_Sum && (**M_Sum).Data){

        (**M_Sum).Size = (**M1).Size;
        (**M_Sum).TypeInfo = (**M1).TypeInfo;

        for (i=0; i < (**M1).Size; i++){
            (**M_Sum).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));
            for (j=0; j < (**M1).Size; j++){

                void *TemporaryResult = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_Sum).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixAddition: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *Element1 = (Matrix*)(**M1).Data + i*(**M1).Size + j;
                void *Element2 = (Matrix*)(**M2).Data + i*(**M2).Size + j;

                (**M_Sum).TypeInfo.M_Addition(TemporaryResult, Element1, Element2);
                memcpy( (Matrix*)(**M_Sum).Data + i*(**M_Sum).Size + j, TemporaryResult, sizeof((**M_Sum).TypeInfo.ElementSize));

                free(TemporaryResult);
            }
        }
    }
    else{
        printf("\nError in MatrixAddition: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixAddition: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *M_Sum;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;

}


void MatrixMultiplication(Matrix **M_product, Matrix **M1, Matrix **M2, int *Counter,
                          MatrixCollection *collection, char *name){

    int i, j;

    if(strcmp( (**M1).TypeInfo.TypeName, (**M2).TypeInfo.TypeName) != 0){
        (*Counter)++;
        return;
    }


    int AddMemory = 100;//A_size;

    *M_product = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**M_product).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*M_product && (**M_product).Data){

        (**M_product).Size = (**M1).Size;
        (**M_product).TypeInfo = (**M1).TypeInfo;

        for (i=0; i < (**M1).Size; i++){
            (**M_product).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));
            for (j=0; j < (**M1).Size; j++){

                void *TemporaryResult = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_product).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixMultiplication: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *Element1 = (Matrix*)(**M1).Data + i*(**M1).Size + j;
                void *Element2 = (Matrix*)(**M2).Data + i*(**M2).Size + j;

                (**M_product).TypeInfo.M_Multiplication(TemporaryResult, Element1, Element2);
                memcpy( (Matrix*)(**M_product).Data + i*(**M_product).Size + j, TemporaryResult, sizeof((**M_product).TypeInfo.ElementSize));

                free(TemporaryResult);
            }
        }
    }
    else{
        printf("\nError in MatrixMultiplication: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixMultiplication: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *M_product;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;

}


void MatrixMultiplicationByScalar(Matrix **M_product, Matrix **M1, MatrixCollection *collection, char *name){

    int i, j;
    int AddMemory = 100;//A_size;

    printf("\nEnter the scalar of the same type as the matrix's elements: ");

    void *Multiplier = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M1).TypeInfo.ElementSize));
    if(Multiplier == NULL){
        printf("\nError in MatrixMultiplicationByScalar: Couldn't allocate memory space for Multiplier\n");
        exit(-1);
    }

    int IntScalar;
    float FloatScalar;

    if (strcmp( (**M1).TypeInfo.TypeName, "int")==0 ){
        scanf("%d", &IntScalar);
        *(int*)Multiplier = IntScalar;
    }
    else if (strcmp( (**M1).TypeInfo.TypeName, "float")==0 ){
        scanf("%f", &FloatScalar);
        *(float*)Multiplier = FloatScalar;
    }


    *M_product = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**M_product).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*M_product && (**M_product).Data){

        (**M_product).Size = (**M1).Size;
        (**M_product).TypeInfo = (**M1).TypeInfo;

        for (i=0; i < (**M1).Size; i++){
            (**M_product).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));
            for (j=0; j < (**M1).Size; j++){

                void *TemporaryResult = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_product).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixMultiplicationByScalar: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *Element = (Matrix*)(**M1).Data + i*(**M1).Size + j;

                (**M_product).TypeInfo.M_Multiplication(TemporaryResult, Element, Multiplier);
                memcpy( (Matrix*)(**M_product).Data + i*(**M_product).Size + j, TemporaryResult, sizeof((**M_product).TypeInfo.ElementSize));

                free(TemporaryResult);
            }
        }
    }
    else{
        printf("\nError in MatrixMultiplicationByScalar: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixMultiplicationByScalar: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *M_product;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;

}


void MatrixAdditionOfLinearCombination(Matrix **M_result, int RowNumber, Matrix **M1, MatrixCollection *collection, char *name){

    int i, j;

    srand((unsigned int)time(NULL));
    int RandomInt;
    float RandomFloat;
    int k;

    int LinearCombinationInt[(**M1).Size];
    float LinearCombinationFloat[(**M1).Size];

    for(i=0; i < (**M1).Size; i++){
        LinearCombinationInt[i] = 0;
    }
    for(i=0; i < (**M1).Size; i++){
        LinearCombinationFloat[i] = 0.0;
    }

    int AddMemory = 100;//A_size;

    *M_result = (Matrix *) malloc(AddMemory * AddMemory * sizeof(Matrix*));
    (**M_result).Data = malloc(AddMemory * AddMemory * sizeof(Matrix*));

    if(*M_result && (**M_result).Data){

        (**M_result).Size = (**M1).Size;
        (**M_result).TypeInfo = (**M1).TypeInfo;

        for (i=0; i < (**M1).Size; i++){

            if (strcmp( (**M1).TypeInfo.TypeName, "int")==0 ){
                for (k=0; k < 10; k++){
                    RandomInt = rand()/(RAND_MAX/10);
                }
            }
            else if (strcmp( (**M1).TypeInfo.TypeName, "float")==0 ){
                for (k=0; k < 10; k++){
                    RandomFloat = (float)rand()/((float)RAND_MAX/10.0);
                }
            }

            (**M_result).Data[i] = malloc(AddMemory * AddMemory * sizeof(Matrix*));
            for (j=0; j < (**M1).Size; j++){

                void *Multiplier = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_result).TypeInfo.ElementSize));
                if(Multiplier == NULL){
                    printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for Multiplier\n");
                    exit(-1);
                }

                if (strcmp( (**M1).TypeInfo.TypeName, "int")==0 ){
                    *(int*)Multiplier = RandomInt;
                }
                else if (strcmp( (**M1).TypeInfo.TypeName, "float")==0 ){
                    *(float*)Multiplier = RandomFloat;
                }

                void *TemporaryResult = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_result).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *Element = (Matrix*)(**M1).Data + i*(**M1).Size + j;
                (**M_result).TypeInfo.M_Multiplication(TemporaryResult, Element, Multiplier);

                if (strcmp( (**M1).TypeInfo.TypeName, "int")==0 ){
                    LinearCombinationInt[j] += *(int*)TemporaryResult;
                }
                else if (strcmp( (**M1).TypeInfo.TypeName, "float")==0 ){
                    LinearCombinationFloat[j] += *(float*)TemporaryResult;
                }

                memcpy( (Matrix*)(**M_result).Data + i*(**M_result).Size + j, (Matrix*)(**M1).Data + i*(**M_result).Size + j, sizeof((**M_result).TypeInfo.ElementSize));

                free(TemporaryResult);
                free(Multiplier);
            }
        }
    }
    else{
        printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }


    for (i=0; i < (**M1).Size; i++){
        for (j=0; j < (**M1).Size; j++){
            if(i+1 == RowNumber){

                void *TemporaryResult = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_result).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *Result = malloc((**M1).Size * AddMemory * AddMemory * sizeof((**M_result).TypeInfo.ElementSize));
                if(TemporaryResult == NULL){
                    printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                if (strcmp( (**M1).TypeInfo.TypeName, "int")==0 ){
                    *(int*)TemporaryResult = LinearCombinationInt[j];
                }
                else if (strcmp( (**M1).TypeInfo.TypeName, "float")==0 ){
                    *(float*)TemporaryResult = LinearCombinationFloat[j];
                }

                void *Element = (Matrix*)(**M1).Data + i*(**M1).Size + j;
                (**M_result).TypeInfo.M_Addition(Result, Element, TemporaryResult);

                memcpy( (Matrix*)(**M_result).Data + i*(**M_result).Size + j, Result, sizeof((**M_result).TypeInfo.ElementSize));

                free(TemporaryResult);
                free(Result);
            }
        }
    }



    (*collection).Matrices = realloc( (*collection).Matrices, ( (*collection).Size + 1) * AddMemory * AddMemory * sizeof(NamedMatrix));

    if((*collection).Matrices==NULL){
        printf("\nError in MatrixAdditionOfLinearCombination: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    (*collection).Matrices[(*collection).Size].matrix = *M_result;
    strncpy( (*collection).Matrices[(*collection).Size].Name, name, sizeof((*collection).Matrices[(*collection).Size].Name));
    (*collection).Size++;

}


void MatrixFree(Matrix **M){
    (**M).Data = NULL;
    (**M).Size = 0;
    (**M).TypeInfo.ElementSize = 0;
}