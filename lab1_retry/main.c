#include <conio.h>

#include "matrix.h"
#include "element.h"
#include "tests.h"
#include "fieldinfo.h"

void PrintMenu() {
    printf("\n--------------------------Menu--------------------------\n");
    printf("1. Show all matrices\n");
    printf("2. Show a chosen matrix\n");
    printf("3. Create a matrix\n");
    printf("4. Rename a matrix\n");
    printf("5. Matrix addition\n");
    printf("6. Matrix multiplication\n");
    printf("7. Multiplication of a matrix by a scalar\n");
    printf("8. Add a linear combination of rows to the selected row\n");
    printf("--------------------------------------------------------\n\n");
    printf("Enter 'STOP' to finish\n");
    printf("----------Or----------\n");
    printf("Select an action: ");
}

int main() {

    if(AllTests() == -1){
        return -1;
    }
    printf("\nAll tests completed successfully\n");

    int Action;

    MatrixCollection collection;
    collection.Matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.Size = 0;

    while(1) {
        char UserInput[20];

        PrintMenu();
        scanf("%19s", UserInput);
        if (strcmp(UserInput, "STOP") == 0) {

            for (int g = 0; g < collection.Size; g++)
            {
                MatrixFree(&collection.Matrices[g].matrix);
                free(collection.Matrices[g].Name);
            }
            free(collection.Matrices);

            exit(0);
        }

        Action = atoi(UserInput);

        switch(Action){
            case 1:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int i;

                printf("\nNumber of matrices: %zu\n", collection.Size);
                for(i=0; i < collection.Size; i++){
                    printf("\n%d. %s\n", i+1, &collection.Matrices[i].Name);
                    MatrixPrint(&collection.Matrices[i].matrix);
                }

                break;
            }


            case 2:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int Counter=0;
                char name[20];
                Matrix M;
                size_t Size;

                printf("\nNumber of matrices: %zu\n", collection.Size);
                printf("Enter the matrix's name: ");
                scanf("%19s", name);

                FindMatrix(&collection, &M, name, &Counter, &Size);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }

                printf("Matrix %s:\n", name);
                MatrixPrint(&M);

                break;
            }


            case 3:{
                Matrix M;
                char name[20];
                size_t size;
                int Counter=0;
                int option;
                FieldInfo M_FieldInfo;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name);

                printf("\nEnter the size of the matrix (max size is 7): ");
                scanf("%zu", &size);
                if (size > 7){
                    printf("\nError: The max size is 7!\n");
                    break;
                }

                printf("\nWhat type of elements do you want the matrix to have?\n");
                printf("Enter <1> for int or <2> for float: ");
                scanf("%d", &option);

                if(option==1){
                    GetIntFieldInfo(&M_FieldInfo);
                }
                else if(option==2){
                    GetFloatFieldInfo(&M_FieldInfo);
                }
                else{
                    printf("\nError: This type doesn't exist. Please try again.\n");
                    break;
                }

                int IntMax = 0;
                float FloatMax = 0.0;

                printf("\nDo you want to create the matrix automatically or manually?\n");
                printf("Enter <1> for automatic creation or <2> for manual: ");
                scanf("%d", &option);

                if(option==1){
                    printf("\nEnter the max number for random generation: ");
                    if(strcmp( M_FieldInfo.TypeName, "int")==0 ){
                        scanf("%d", &IntMax);
                    }
                    else if(strcmp( M_FieldInfo.TypeName, "float")==0 ){
                        scanf("%f", &FloatMax);
                    }

                    MatrixAutomaticCreation(&collection, &M, name, size, &M_FieldInfo, &Counter, IntMax, FloatMax);
                }
                else if(option==2){
                    MatrixCreation(&collection, &M, name, size, &M_FieldInfo, &Counter);
                }
                else{
                    printf("\nError: This action doesn't exist. Please try again.\n");
                    break;
                }

                if(collection.Size - 1 > 0){
                    if(Counter > 0){
                        printf("\nError: A matrix with this name already exists\n");
                        break;
                    }
                }

                printf("%zu. %s\n", collection.Size, name);
                MatrixPrint(&M);

                break;
            }


            case 4:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                char name1[20];
                char name2[20];
                Matrix M;
                int Counter=0;
                size_t Size;

                printf("\nEnter the name of the matrix you want to rename: ");
                scanf("%19s", name1);


                FindMatrix(&collection, &M, name1, &Counter, &Size);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }

                printf("\nEnter the new name for the matrix %s: ", name1);
                scanf("%19s", name2);

                MatrixRenaming(&collection, name1, name2);

                printf("\nMatrix %s:\n", name2);
                MatrixPrint(&M);

                break;
            }


            case 5:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.Size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for addition\n");
                    break;
                }

                Matrix M_sum, M1, M2;
                char name1[20];
                char name2[20];
                char name3[20];
                int Counter=0;
                size_t Size1;
                size_t Size2;

                printf("\nEnter the first matrix's name: ");
                scanf("%s", name1);
                FindMatrix(&collection, &M1, name1, &Counter, &Size1);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                printf("\nEnter the second matrix's name: ");
                scanf("%s", name2);
                FindMatrix(&collection, &M2, name2, &Counter, &Size2);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                if(Size1 != Size2){
                    printf("\nError: For addition you need matrices to be the same size.\n");
                    break;
                }

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name3);
                FindMatrix(&collection, &M_sum, name3, &Counter, &Size1);
                if(Counter > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                Counter = 0;

                MatrixAddition(&M_sum, &M1, &M2, &Counter, &collection, name3);
                if(Counter > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                Counter = 0;

                printf("\nResult - Matrix %s:\n", name3);
                MatrixPrint(&M_sum);

                break;
            }


            case 6:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.Size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for multiplication\n");
                    break;
                }

                Matrix M_mult, M1, M2;
                char name1[20];
                char name2[20];
                char name3[20];
                int Counter=0;
                size_t Size1;
                size_t Size2;

                printf("\nEnter the first matrix's name: ");
                scanf("%s", name1);
                FindMatrix(&collection, &M1, name1, &Counter, &Size1);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                printf("\nEnter the second matrix's name: ");
                scanf("%s", name2);
                FindMatrix(&collection, &M2, name2, &Counter, &Size2);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                if(Size1 != Size2){
                    printf("\nError: For multiplication you need matrices to be the same size.\n");
                    break;
                }


                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name3);
                FindMatrix(&collection, &M_mult, name3, &Counter, Size1);
                if(Counter > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                Counter = 0;

                MatrixMultiplication(&M_mult, &M1, &M2, &Counter, &collection, name3);
                if(Counter > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                Counter = 0;

                printf("\nResult - Matrix %s:\n", name3);
                MatrixPrint(&M_mult);

                break;
            }


            case 7:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                Matrix M_mult, M1;
                char name1[20];
                char name2[20];
                int Counter=0;
                size_t Size;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name1);
                FindMatrix(&collection, &M1, name1, &Counter, &Size);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name2);
                FindMatrix(&collection, &M_mult, name2, &Counter, &Size);
                if(Counter > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                Counter = 0;

                MatrixMultiplicationByScalar(&M_mult, &M1, &collection, name2);

                printf("\nResult - Matrix %s:\n", name2);
                MatrixPrint(&M_mult);

                break;
            }


            case 8:{
                if(collection.Size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                Matrix M_res, M1;
                char name1[20];
                char name2[20];
                int Counter=0;
                size_t Size;
                int RowNumber;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name1);
                FindMatrix(&collection, &M1, name1, &Counter, &Size);
                if(Counter==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                Counter = 0;

                printf("\nEnter the number of the row: ");
                scanf("%d", &RowNumber);
                if(RowNumber > M1.Size || RowNumber == 0){
                    printf("\nError: This row doesn't exist\n");
                    break;
                }

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name2);
                FindMatrix(&collection, &M_res, name2, &Counter, Size);
                if(Counter > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                Counter = 0;

                MatrixAdditionOfLinearCombination(&M_res, RowNumber, &M1, &collection, name2);

                printf("\nResult - Matrix %s:\n", name2);
                MatrixPrint(&M_res);

                break;
            }


            default:{
                printf("\nError: This action doesn't exist. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}
