typedef unsigned char uchar_t;
typedef const unsigned char cuchar_t;
typedef int* pint_t;
typedef char** ppchar_t;
typedef char (*pchararray_t)[5];  // pointer to array of 5 char
typedef int* pintarr_t[7];        // array of 7 pointer to int
typedef int* (*pintparr_t)[7];    // pointer to array of 7 pointer to int
typedef int* pintarrarr[8][7];    // array of 8 of array of 7 pointer to int

int main() {}
