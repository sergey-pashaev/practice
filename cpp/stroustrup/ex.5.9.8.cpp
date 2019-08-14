#include <iostream>

using namespace std;

int ArrayIndexIteration(int days[]) {
    int sum = 0;
    for (int i = 0; i < 12; ++i) {
        sum += days[i];
    }

    return sum;
}

int PointerIteration(int days[]) {
    int sum = 0;
    for (int* p = days; p < days + 12; ++p) {
        sum += *p;
    }

    return sum;
}

int main() {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    ArrayIndexIteration(days);

    cout << endl;

    PointerIteration(days);
}

// g++

/* -O1

  ArrayIndexIteration(int*):
  lea rdx, [rdi+48]
  mov eax, 0
.L2:
  add eax, DWORD PTR [rdi]
  add rdi, 4
  cmp rdi, rdx
  jne .L2
  rep ret
PointerIteration(int*):
  lea rdx, [rdi+48]
  cmp rdi, rdx
  jnb .L7
  mov eax, 0
.L6:
  add eax, DWORD PTR [rdi]
  add rdi, 4
  cmp rdi, rdx
  jne .L6
  rep ret
.L7:
  mov eax, 0
  ret
*/

/* -O2
   ArrayIndexIteration(int*):
  lea rdx, [rdi+48]
  xor eax, eax
.L2:
  add eax, DWORD PTR [rdi]
  add rdi, 4
  cmp rdi, rdx
  jne .L2
  rep ret
PointerIteration(int*):
  lea rdx, [rdi+48]
  xor eax, eax
.L6:
  add eax, DWORD PTR [rdi]
  add rdi, 4
  cmp rdi, rdx
  jne .L6
  rep ret
*/

/* -O3
   ArrayIndexIteration(int*):
  mov eax, DWORD PTR [rdi+4]
  add eax, DWORD PTR [rdi]
  add eax, DWORD PTR [rdi+8]
  add eax, DWORD PTR [rdi+12]
  add eax, DWORD PTR [rdi+16]
  add eax, DWORD PTR [rdi+20]
  add eax, DWORD PTR [rdi+24]
  add eax, DWORD PTR [rdi+28]
  add eax, DWORD PTR [rdi+32]
  add eax, DWORD PTR [rdi+36]
  add eax, DWORD PTR [rdi+40]
  add eax, DWORD PTR [rdi+44]
  ret
PointerIteration(int*):
  mov eax, DWORD PTR [rdi+4]
  add eax, DWORD PTR [rdi]
  add eax, DWORD PTR [rdi+8]
  add eax, DWORD PTR [rdi+12]
  add eax, DWORD PTR [rdi+16]
  add eax, DWORD PTR [rdi+20]
  add eax, DWORD PTR [rdi+24]
  add eax, DWORD PTR [rdi+28]
  add eax, DWORD PTR [rdi+32]
  add eax, DWORD PTR [rdi+36]
  add eax, DWORD PTR [rdi+40]
  add eax, DWORD PTR [rdi+44]
  ret
*/
