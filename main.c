#include <stdio.h>
#include <stdlib.h>
typedef struct Member {
    char name[30];        // 会员姓名
    int grade;            // 会员卡等级
    int order;            // 会员编号
    char telenumber[12];  // 预留手机号
    int balance;          // 余额
    int score;            // 积分
    float permissions;    // 权限

} Member;

typedef struct Node {
    struct Member data;
    struct Node* next;
} Node;

void data_add(Node*);  // 增加数据
void data_delete(Node*);  // 删除数据
void data_find(Node*);    // 查找数据
void data_modify(Node*);  // 修改数据
void data_sort(Node*);  // 数据排序
void data_print(Node*);  // 打印数据
void data_save(Node*);  // 保存数据
void data_account(Node*);  // 统计数据
void menu();

// void IO_ReadInfo();			//读取文件

int main() {
    //  IO_ReadInfo();			//读取文件
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    while (1) {
        menu();
        printf("请选择1-8\n");
        int choice;
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:  // 录入会员信息
                data_add(head);
                break;
            case 2:  // 打印会员信息
                data_print(head);
                break;
            case 3:  // 保存会员信息
                data_save(head);
                break;
            case 4:  // 排序会员信息
                data_sort(head);
                break;
            case 5:  // 统计会员人数
                data_account(head);
                break;
            case 6:  // 查找会员信息
                data_find(head);
                break;
            case 7:  // 修改会员信息
                data_modify(head);
                break;
            case 8:  // 删除会员信息
                data_delete(head);
                break;
            case 0:  // 退出系统
                exit(0);
                break;
            default:
                printf("输入格式错误，请重新输入\n");
                sleep(2);
                break;
        }
    }

    return 0;
}
void menu() {
    system("clear");  // 清屏
    printf("##########################################\n");
    printf("#############  影院管理系统  #############\n");
    printf("##########################################\n");
    printf("###  请选择功能：                      ###\n");
    printf("###  1.录入会员信息   2.打印会员信息   ###\n");
    printf("###  3.保存会员信息   4.排序会员信息   ###\n");
    printf("###  5.统计会员人数   6.查找会员信息   ###\n");
    printf("###  7.修改会员信息   8.删除会员信息   ###\n");
    printf("###  0.退出系统                        ###\n");
    printf("##########################################\n");
}
// void IO_ReadInfo(){/*读取file.txt*/
//     FILE *fp;
//     if((fp=fopen("file.txt",'r'))==NULL){
//         printf("无法打开文件");
//     }
//     else {

//     }
// }

void data_add(Node* head) {
    Node* p = head;
    while (p->next) {
        p = p->next;
    }
    Node* s = (Node*)malloc(sizeof(Node));
    s->next = NULL;
    p->next = s;
    printf("请输入会员卡等级：\n");
    scanf("%d", &s->data.grade);
    getchar();
    printf("请输入会员编号：\n");
    scanf("%d", &s->data.order);
    getchar();
    printf("请输入会员姓名：\n");
    scanf("%s", &s->data.name);
    getchar();
    printf("请输入预留手机号：\n");
    scanf("%s", &s->data.telenumber);
    getchar();
    printf("请输入余额：\n");
    scanf("%d", &s->data.balance);
    getchar();
    printf("请输入积分：\n");
    scanf("%d", &s->data.score);
    getchar();
    printf("请输入权限：\n");
    scanf("%f", &s->data.permissions);
    getchar();
}
void data_delete(Node* head) {
    printf("请输入要删除的会员序号：\n");
    int n;
    scanf("%d", &n);
    getchar();
    Node* p = head;
    Node* s = p;
    while (p->next && p->data.order != n) {
        s = p;
        p = p->next;
    }
    if (p->data.order == n) {
        s->next = p->next;
        free(p);
        printf("已删除\n");
        sleep(2);
    } else {
        printf("序号不存在\n");
        sleep(2);
    }
}
void data_find(Node* head) {}
void data_change(Node* head) {}
void data_print(Node* head) {
    printf("会员卡等级\t会员编号\t会员姓名\t预留手机号\t余额\t积分\t权限\n");
    Node* p = head;
    p = p->next;
    while (p) {
        printf("%5d\t\t%08d\t%-8s\t%-11s\t %d\t %d\t%.1f\n", p->data.grade,
               p->data.order, p->data.name, p->data.telenumber, p->data.balance,
               p->data.score, p->data.permissions);
        p = p->next;
    }
    printf("按任意键退出");
    getchar();
}
void data_save(Node* head) {}

void data_account(Node* head) {}
void data_modify(Node* head) {}
void data_sort(Node* head) {}