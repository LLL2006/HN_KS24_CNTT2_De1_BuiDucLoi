#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define MAX_STACK 1000

typedef struct {
    char action;
    char value;
} Operation;

typedef struct {
    Operation data[MAX_STACK];
    int top;
} Stack;

void push(Stack *s, Operation op) {
    if (s->top < MAX_STACK - 1) {
        s->data[++(s->top)] = op;
    }
}

Operation pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    } else {
        Operation empty = {' ', ' '};
        return empty;
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int main() {
    char text[MAX_LEN] = "";
    Stack undoStack, redoStack;
    undoStack.top = -1;
    redoStack.top = -1;
    int choice;

    while (1) {
        printf("\nTEXT EDITOR\n");
        printf("1 INSERT x\n");
        printf("2 UNDO\n");
        printf("3 REDO\n");
        printf("4 HIEN THI\n");
        printf("5 THOAT\n");
        printf("Chon chuc nang 1 5 ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char x;
                printf("Nhap ky tu can them ");
                scanf(" %c", &x);
                int len = strlen(text);
                text[len] = x;
                text[len+1] = '\0';
                Operation op = {'I', x};
                push(&undoStack, op);
                redoStack.top = -1;
                break;
            }
            case 2: {
                if (!isEmpty(&undoStack)) {
                    Operation lastOp = pop(&undoStack);
                    int len = strlen(text);
                    if (len > 0) text[len-1] = '\0';
                    push(&redoStack, lastOp);
                    printf("Hoan tac thanh cong\n");
                } else {
                    printf("Khong co thao tac de hoan tac\n");
                }
                break;
            }
            case 3: {
                if (!isEmpty(&redoStack)) {
                    Operation redoOp = pop(&redoStack);
                    int len = strlen(text);
                    text[len] = redoOp.value;
                    text[len+1] = '\0';
                    push(&undoStack, redoOp);
                    printf("Phuc hoi thanh cong\n");
                } else {
                    printf("Khong co thao tac de phuc hoi\n");
                }
                break;
            }
            case 4: {
                printf("Van ban hien tai %s\n", text);
                break;
            }
            case 5: {
                printf("Da thoat chuong trinh\n");
                exit(0);
            }
            default:
                printf("Lua chon khong hop le vui long chon tu 1 den 5\n");
        }
    }
    return 0;
}
