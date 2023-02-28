#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //linux sleep()
// #include<windows.h> sleep()
#define FILENAME "/home/earlymor/VSCODE/c/XUPT_management/INFO.txt"
#define SIZE 1000
typedef struct Member {
    char name[30];        // 会员姓名
    unsigned int grade;   // 会员卡等级
    unsigned int order;   // 会员编号
    char telenumber[12];  // 预留手机号
    int balance;          // 余额
    unsigned int score;   // 积分
    float permissions;    // 折扣

} Member;

struct Member people[SIZE];
int num = 0;
typedef struct Node {
    struct Member data;
    struct Node* next;
} Node;

void data_add(Node* head);      // 增加数据
void data_delete(Node* head);   // 删除数据
Node* data_find(Node* head);    // 查找数据
void data_modify(Node* head);   // 修改数据
void data_sort(Node* head);     // 数据排序
void data_print(Node* head);    // 打印数据
void data_save(Node* head);     // 保存数据
void data_account(Node* head);  // 统计数据
void show_single(Node* p);      // 显示单条数据
void menu();                    // 菜单
Node* IO_ReadInfo();            // 读取文件

int main() {
    Node* head = IO_ReadInfo();  // 读取文件
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
void show_single(Node* p) {
    printf("会员卡等级\t会员编号\t会员姓名\t预留手机号\t余额\t积分\t折扣\n");
    printf("%5d\t\t%08d\t%-16s\t%-11s\t %d\t %d\t%.1f\n", p->data.grade,
           p->data.order, p->data.name, p->data.telenumber, p->data.balance,
           p->data.score, p->data.permissions);
}
void data_add(Node* head) {  // 增加数据
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
    printf("请输入折扣：\n");
    scanf("%f", &s->data.permissions);
    getchar();
}

void data_delete(Node* head) {  // 删除数据
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
Node* data_find(Node* head) {  // 查找数据
    int n;
    printf("请输入要查找的会员序号:\n");
    scanf("%d", &n);
    getchar();
    Node* p = head;
    while (p->next && p->data.order != n) {
        p = p->next;
    }
    if (p->data.order == n) {
        show_single(p);
        printf("按回车键退出");
        getchar();
        return p;
    } else {
        printf("序号不存在\n");
        sleep(2);
        return NULL;
    }
}
void data_print(Node* head) {  // 打印数据
    printf("会员卡等级\t会员编号\t会员姓名\t预留手机号\t余额\t积分\t折扣\n");
    Node* p = head;
    p = p->next;
    while (p) {
        printf("%5d\t\t%08d\t%-16s\t%-11s\t %d\t %d\t %.1f\n", p->data.grade,
               p->data.order, p->data.name, p->data.telenumber, p->data.balance,
               p->data.score, p->data.permissions);
        p = p->next;
    }
    printf("按回车键键退出");
    getchar();
}
void data_save(Node* head) {  // 保存数据
    FILE* fp;
    if ((fp = fopen(FILENAME, "wb")) == NULL) {
        printf("不能打开文件!\n");
        return;
    } else {
        Node* p = head;
        p = p->next;
        while (p) {
            fprintf(fp, "%s %d %d %s %d %d %f\n", p->data.name, p->data.grade,
                    p->data.order, p->data.telenumber, p->data.balance,
                    p->data.score, p->data.permissions);
            p = p->next;
        }
    }
    fclose(fp);
    printf("保存成功");
}

void data_account(Node* head) {  // 统计数据
}
void data_modify(Node* head) {  // 修改数据
    system("clear");
    Node* p;
    int n, key = 1, key2 = 1;
    if ((p = data_find(head)) == NULL) {
        return;
    } else {
        while (key) {
            key2=1;
            printf("--------------------请选择要修改的数据------------\n");
            printf("- 1.会员姓名                                     -\n");
            printf("- 2.会员卡等级                                   -\n");
            printf("- 3.预留手机号                                   -\n");
            printf("- 4.余额                                         -\n");
            printf("- 5.积分                                         -\n");
            printf("- 6.折扣                                         -\n");
            printf("- 0.退出                                         -\n");
            printf("--------------------------------------------------\n");
            scanf("%d", &n);
            getchar();
            switch (n) {
                case 1:
                    printf("将会员姓名修改为：\n");
                    scanf("%s", &p->data.name);

                    break;
                case 2:
                    printf("将会员卡等级修改为：\n");
                    scanf("%d", &p->data.grade);

                    break;
                case 3:
                    printf("将预留手机号修改为：\n");
                    scanf("%s", &p->data.telenumber);

                    break;
                case 4:
                    printf("将余额修改为：\n");
                    scanf("%d", &p->data.balance);

                    break;
                case 5:
                    printf("将积分修改为：\n");
                    scanf("%d", &p->data.score);

                    break;
                case 6:
                    printf("将折扣修改为：\n");
                    scanf("%f", &p->data.permissions);

                    break;
                case 0:
                    return;
                default:
                    printf("无此选项,请重新选择");
                    break;
            }
            while (key2) {
                fflush(stdin);
                getchar();
                show_single(p);
                printf("是否继续修改:(Y or N)\n");
                char ch;
                scanf("%c", &ch);
                if (ch == 'N' || ch == 'n') {
                    key = 0;
                    key2 = 0;
                } else if (ch == 'Y' || ch == 'y' || ch == '\n') {
                    system("clear");
                    key2 = 0;
                } else
                    printf("无此选项,请重新选择");
            }
        }
    }
}
void data_sort(Node* head) {  // 排序数据
}
Node* IO_ReadInfo() {  // 读取文件
    FILE* fp;
    int i;
    Node *head, *p = (Node*)malloc(sizeof(Node));
    head = p;
    if ((fp = fopen(FILENAME, "r")) == NULL) {
        printf("不能打开文件!\n");
        return head;
    } else {
        while (!feof(fp)) {
            Node man;
            int end = fscanf(fp, "%s %d %d %s %d %d %f", &man.data.name,
                             &man.data.grade, &man.data.order,
                             &man.data.telenumber, &man.data.balance,
                             &man.data.score, &man.data.permissions);
            man.next = NULL;
            if (end != -1) {
                Node* s = (Node*)malloc(sizeof(Node));
                *s = man;
                p->next = s;
                p = s;
            }
        }
    }
    fclose(fp);
    return head;
}