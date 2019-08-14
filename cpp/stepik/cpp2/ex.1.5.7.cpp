// typedef ComplexFunction
typedef int* (*ReturnFunc)(char const*);
typedef int (*ArgFunc)(double);
typedef ReturnFunc (*ComplexFunction)(int, ArgFunc);

int main() {}
