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
    Stack undoStack;
    Stack redoStack;
    undoStack.top = -1;
    redoStack.top = -1;

    char command[20];

    

    while (1) {
        printf("TEXT EDITOR\n");
    printf("1. INSERT x: them ky tu x vao cuoi van ban
");
    printf("2. UNDO: hoan tac thao tac gan nhat (xaa ky tu cuoi)
");
    printf("3. REDO: phuc hoi thao tac vua undo
");
    printf("4. HIEN THI: in van ban hien tai");
    printf("5. THOAT: ket thuc chuong trinh");
        printf("\nNhap lenh: ");
        scanf("%s", command);

        switch(command) {
            case 1:
                char x;
                scanf(" %c", &x);
                int len = strlen(text);
                text[len] = x;
                text[len+1] = '\0';

                Operation op = {'I', x};
                push(&undoStack, op);

                redoStack.top = -1;

                break;
            case 2:
                if (!isEmpty(&undoStack)) {
                Operation lastOp = pop(&undoStack);
                int len = strlen(text);
                if (len > 0) {
                    text[len-1] = '\0';
                }
                push(&redoStack, lastOp);
            } else {
                printf("Khong co thao tac đe hoan tac!\n");
            }

                break;
            case 3:
                if (!isEmpty(&redoStack)) {
                Operation redoOp = pop(&redoStack);
                int len = strlen(text);
                text[len] = redoOp.value;
                text[len+1] = '\0';
                push(&undoStack, redoOp);
            } else {
                printf("Khong co thao tac de phuc hoi!\n");
            }
                break;
            case 4:
                char temp[10];
            scanf("%s", temp);
            printf("Van ban hien tai: %s\n", text);
                break;
            case 5:
                 printf("Da thoat chuong trinh.\n");
                exit(0);
            default:
                printf("Lua chon khong hop le\n");
        }
    }
    return 0;
}
