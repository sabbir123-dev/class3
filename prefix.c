#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
int stack[100];
int top = -1;

void push(int x)
{
  stack[++top] = x;
}
int pop()
{

  return stack[top--];
}

int prefixEval(char *exp)
{
  int len = strlen(exp);
  for (int i = len - 1; i >= 0; i--)
  {
    char ch = exp[i];

    if (isdigit(ch))
    {
      push(ch - '0');
    }
    else if (ch == ' ')
    {
      continue;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
    {

      int v1 = pop();
      int v2 = pop();

      switch (ch)
      {
      case '+':
        push(v1 + v2);
        break;
      case '-':
        push(v1 - v2);
        break;
      case '*':
        push(v1 * v2);
        break;
      case '/':if (v2 == 0)
        {
          printf("Error");
        }
        else
        {
          push(v1 / v2);
          break;
        }
      
      case '^':
        push(pow(v1, v2));
        break;
      }
    }
    else{
      printf("Invalid-->%c\n",ch);
    }
  }
  return pop();
}
int main()
{

  char exp[] = "-*93/*24-32";
  printf("Result -->%d", prefixEval(exp));
  return 0;
}