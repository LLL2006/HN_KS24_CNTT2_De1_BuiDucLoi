//
// Created by Thang Loi on 7/16/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[50];
    int priority;
    char deadline[50];
} Task;

typedef struct TaskNode {
    Task task;
    struct TaskNode *next;
} TaskNode;

typedef struct CompleteTaskNode {
    Task task;
    struct CompleteTaskNode *next;
    struct CompleteTaskNode *prev;
} CompleteTaskNode;

TaskNode *TaskList = NULL;
CompleteTaskNode *CompleteTaskList = NULL;

void addTask() {
    TaskNode* newTask = (TaskNode*)malloc(sizeof(TaskNode));
    printf("Moi nhap ID nhiem vu: ");
    scanf("%d", &newTask->task.id);
    printf("Moi nhap ten nhiem vu: ");
    getchar();
    fgets(newTask->task.title, sizeof(newTask->task.title), stdin);
    newTask->task.title[strcspn(newTask->task.title, "\n")] = '\0';
    printf("Moi nhap han cuoi: ");
    fgets(newTask->task.deadline, sizeof(newTask->task.deadline), stdin);
    newTask->task.deadline[strcspn(newTask->task.deadline, "\n")] = '\0';
    printf("Moi nhap muc do uu tien(1->3, 1 la cao nhat): ");
    scanf("%d", &newTask->task.priority);


    newTask->next = NULL;

    if(TaskList == NULL) {
        TaskList = newTask;
    } else {
        TaskNode* temp = TaskList;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
}

void displayTasks() {
    printf("Danh sach nhiem vu dang co: ");
    if(TaskList == NULL) {
        printf("Khong co nhiem vu nao");
    } else {
        TaskNode* temp = TaskList;
        while(temp != NULL) {
            printf("ID: %d | Ten: %s | Do uu tien: %d | Han cuoi: %s\n", temp->task.id, temp->task.title, temp->task.priority, temp->task.deadline);
            temp = temp->next;
        }
    }
    printf("\n");
    printf("Danh sach nhiem vu da hoan thanh: ");
    if(CompleteTaskList == NULL) {
        printf("Khong co nhiem vu nao");
    } else {
        CompleteTaskNode* temp = CompleteTaskList;
        while(temp != NULL) {
            printf("ID: %d | Ten: %s | Do uu tien: %d | Han cuoi: %s\n", temp->task.id, temp->task.title, temp->task.priority, temp->task.deadline);
            temp = temp->next;
        }
    }
}

void deleteTask() {
    int id;
    printf("Nhap ID nhiem vu can xoa: ");
    scanf("%d", &id);
    TaskNode* temp = TaskList;
    TaskNode* prev = NULL;

    while(temp != NULL && temp->task.id != id) {
        prev = temp;
        temp = temp->next;
    }

    while(temp == NULL) {
        printf("Khong tim thay nhiem vu");
        return;
    }

    if(prev == NULL) {
        TaskList = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Da xoa nhiem vu");
}

void updateTask() {
    int id;
    printf("Nhap ID nhiem vu can cap nhat: ");
    scanf("%d", &id);
    TaskNode* temp = TaskList;

    while (temp != NULL && temp->task.id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay nhiem vu");
        return;
    }

    printf("Nhap ten nhiem vu moi: ");
    getchar();
    fgets(temp->task.title, sizeof(temp->task.title), stdin);
    temp->task.title[strcspn(temp->task.title, "\n")] = '\0';
    printf("Nhap han cuoi moi: ");
    fgets(temp->task.deadline, sizeof(temp->task.deadline), stdin);
    temp->task.deadline[strcspn(temp->task.deadline, "\n")] = '\0';
    printf("Nhap do uu tien moi(1->3, 1 la cao nhat): ");
    scanf("%d", &temp->task.priority);
    printf("Cap nhat thanh cong");
}

void markAsComplete() {
    int id;
    printf("Nhap ID nhiem vu da hoan thanh: ");
    scanf("%d", &id);
    TaskNode* temp = TaskList;
    TaskNode* prev = NULL;

    while (temp != NULL && temp->task.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay nhiem vu");
        return;
    }

    if (prev == NULL) {
        TaskList = temp->next;
    } else {
        prev->next = temp->next;
    }

    CompleteTaskNode* newTask = (CompleteTaskNode*)malloc(sizeof(CompleteTaskNode));
    newTask->task = temp->task;
    newTask->prev = NULL;
    newTask->next = CompleteTaskList;

    if(CompleteTaskList != NULL) {
        CompleteTaskList->prev = newTask;
    }
    CompleteTaskList = newTask;

    free(temp);
    printf("Da danh dau nhiem vu");
}

void sortTasks() {
    if (!TaskList || TaskList != NULL) {
        return;
    }
    for (TaskNode* i = TaskList; i != NULL; i = i->next) {
        for(TaskNode* j = i->next; j != NULL; j = j->next) {
            if(i->task.priority > j->task.priority) {
                Task temp = i->task;
                i->task = j->task;
                j->task = temp;
            }
        }
    }

    printf("Da sap xep nhiem vu theo do uu tien giam dan");
}

void searchTaskByTitle() {
    char keyword[50];

    printf("Nhap tu khoa can tim: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    TaskNode* temp = TaskList;

    while(temp != NULL) {
        if(strstr(temp->task.title, keyword) != NULL) {
            printf("ID: %d | Ten: %s | Do uu tien: %d | Han cuoi: %s\n", temp->task.id, temp->task.title, temp->task.priority, temp->task.deadline);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found) {
        printf("Khong tim thay nhiem vu");
        return;
    }
}
int main() {
    int choice;
    while(1) {
        printf("\n\nTASK MANAGER\n");
        printf("1. Them nhiem vu\n");
        printf("2. Hien thi nhiem vu\n");
        printf("3. Xoa nhiem vu\n");
        printf("4. Cap nhat thong tin nhiem vu\n");
        printf("5. Danh dau nhiem vu hoan thanh\n");
        printf("6. Sap xep nhiem vu\n");
        printf("7. Tim kiem nhiem vu\n");
        printf("8. Thoat chuong trinh\n");
        printf("Chon chuc nang (1-8): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                updateTask();
                break;
            case 5:
                markAsComplete();
                break;
            case 6:
                sortTasks();
                break;
            case 7:
                searchTaskByTitle();
                break;
            case 8: 
                printf("Thoat chuong trinh\n");
                exit(0);
            default:
                printf("Lua chon khong hop le\n");
        }
    }
    return 0;
}