#include <stdio.h>
#include <ctype.h>

int stack[100];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int postfixevaluation(char *exp) {
    int i = 0;
    char ch;

    while ((ch = exp[i++]) != '\0') {

        if (isdigit(ch)) {
            push(ch - '0');
        }
        else if (ch == ' ') {
            continue;
        }
        else {
            int v1 = pop();
            int v2 = pop();

            switch (ch) {
                case '+': push(v2 + v1); break;
                case '-': push(v2 - v1); break;
                case '*': push(v2 * v1); break;
                case '/': push(v2 / v1); break;
            }
        }
    }
    return pop();
}

int main() {
    char expression[] = "53-8*";
    printf("Result : %d", postfixevaluation(expression));
    return 0;
}

