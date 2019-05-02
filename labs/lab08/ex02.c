#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *v;
    int cap;
    int sz;
} stack;

void init(stack * s) {
    s->cap = 80;
    s->v = malloc(sizeof(int) * s->cap);
    s->sz = 0;
}

void push(stack * s, int e) {
    if (s->sz < s->cap) {
        s->v[s->sz] = e;
        s->sz++;
    }
}

int pop(stack * s) {
    if (s->sz > 0) {
        s->sz--;
        return *(s->v+s->sz);
    }
    return -1;
}

int is_empty(stack * s) {
    return s->sz == 0;
}

void destroy(stack * s) {
    free(s->v);
}

int doTheThing() {
    stack s;
    int slen = 0, i = 0, p;
    char * str = malloc(sizeof(char) * 80);

    scanf("%s", str);
    slen = strlen(str);
    init(&s);

    for (i = 0; i < slen; i++) {
        if (*(str+i) == '(') {
            push(&s, ')');
        } else if (*(str+i) == '[') {
            push(&s, ']');
        } else if (*(str+i) == '{') {
            push(&s, '}');
        } else if ((*(str+i) == ')' || *(str+i) == ']' || *(str+i) == '}') &&
        *(str+i) != (p=pop(&s)) && p != -1) {
            return 0;
        }
    }
    return is_empty(&s);
}

int main() {
    printf("%s\n", doTheThing() ? "yes" : "no");
    return 0;
}

