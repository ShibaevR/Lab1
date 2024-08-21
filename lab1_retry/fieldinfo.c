#include "fieldinfo.h"

void GetIntFieldInfo(FieldInfo *IntFieldInfo) {
    (*IntFieldInfo).TypeName = "int";
    (*IntFieldInfo).ElementSize = sizeof(int);

    (*IntFieldInfo).M_Addition = IntSum;
    (*IntFieldInfo).M_Multiplication = IntMult;
    (*IntFieldInfo).M_Print = IntPrint;
}


void GetFloatFieldInfo(FieldInfo *FloatFieldInfo) {
    (*FloatFieldInfo).TypeName = "float";
    (*FloatFieldInfo).ElementSize = sizeof(float);

    (*FloatFieldInfo).M_Addition = FloatSum;
    (*FloatFieldInfo).M_Multiplication = FloatMult;
    (*FloatFieldInfo).M_Print = FloatPrint;
}
