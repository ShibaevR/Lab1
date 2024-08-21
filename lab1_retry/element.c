#include "element.h"

void IntSum(void* Sum, void* a, void* b) {
    *(int*)Sum = *(int*)a + *(int*)b;
}


void IntMult(void* Product, void* a, void* b) {
    *(int*)Product = (*(int*)a * *(int*)b);
}


void IntPrint(void* Element) {
    printf("%3d ", *(int*)Element);
}



void FloatSum(void* Sum, void* a, void* b){
    *(float*)Sum = *(float*)a + *(float*)b;
}


void FloatMult(void* Product, void* a, void* b){
    *(float*)Product = *(float*)a * *(float*)b;
}


void FloatPrint(void* Element){
    printf("%11f ", *(float*)Element);
}

