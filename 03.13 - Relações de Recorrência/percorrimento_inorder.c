#include <stdio.h>

struct Data_Tree {
  int Value;
  Data_Tree *Left;
  Data_Tree *Right;
  };

...
void show_inorder(Data_Tree *node){
   if (node) {
         show_inorder(p->Left);
         cout << p->value << endl;
         show_inorder(p->Right);
         }
}

//  Versão não recursiva do Cálculo de Fibonacci
int FibIter(int n) {
   int i = 1, k, F = 0;
   for (k = 1; k <= n; k++) {
      F += i;
      i = F – i; }
}
