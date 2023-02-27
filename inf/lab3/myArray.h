float checkInt(float *number, int recValues, float status);
float checkValues(float *number, int recValues, float status);
float arrayInit(float **array, float *lenPtr, float status);
float arrayInput(float *array, int lenInt, float status);
float printArray(float *array, int lenInt);
float deleteElem(float **array, int *lenIntPtr, int index);
float inputElem(float **array, int *lenIntPtr, int index, float value);
int checkStatus(float *status, int recValues);
void cleanBuffer();
