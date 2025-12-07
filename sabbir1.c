#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 1000

char* tokens[MAX];
int tokenCount = 0;
int st[MAX], top = -1;

void push(int x){ st[++top] = x; }
int pop(){ return st[top--]; }

int floorDiv(int a, int b){
    if (a*b < 0 && a % b != 0) return (a/b)-1;
    return a/b;
}

// Tokenizer for prefix (handles + - * / ^ and multi-digit integers)
void tokenize(char *exp){
    int len = strlen(exp);
    for(int i=0; i<len; ) {

        if (exp[i]==' '){
            i++;
            continue;
        }

        if (exp[i]=='+' || exp[i]=='*' || exp[i]=='/' || exp[i]=='^'){
            char* t = (char*)malloc(2);
            t[0] = exp[i];
            t[1] = '\0';
            tokens[tokenCount++] = t;
            i++;
        }
        else if (exp[i]=='-'){
            if (i+1 < len && isdigit(exp[i+1])) {
                int start=i;
                i++;
                while(i<len && isdigit(exp[i])) i++;
                char* t = strndup(exp+start, i-start);
                tokens[tokenCount++] = t;
            } else {
                char* t = (char*)malloc(2);
                t[0] = '-';
                t[1] = '\0';
                tokens[tokenCount++] = t;
                i++;
            }
        }
        else if (isdigit(exp[i])){
            int start=i;
            while(i<len && isdigit(exp[i])) i++;
            char* t = strndup(exp+start, i-start);
            tokens[tokenCount++] = t;
        }
        else {
            printf("Invalid char %c\n", exp[i]);
            exit(1);
        }
    }
}

int evaluatePrefix(){
    for(int i = tokenCount-1; i>=0; i--){
        char *t = tokens[i];

        if (isdigit(t[0]) || (t[0]=='-' && strlen(t)>1)){
            push(atoi(t));
        }
        else {
            int v1 = pop();
            int v2 = pop();

            if(strcmp(t, "+")==0) push(v1+v2);
            else if(strcmp(t, "-")==0) push(v1-v2);
            else if(strcmp(t, "*")==0) push(v1*v2);
            else if(strcmp(t, "/")==0) push(floorDiv(v1,v2));
            else if(strcmp(t, "^")==0) push((int)pow(v1,v2));
        }
    }
    return pop();
}

int main(){
    char exp[] = "--/-23-^22*23^-3*^3222//223";

    tokenize(exp);

    int ans = evaluatePrefix();

    printf("Result = %d\n", ans);
    return 0;
}
