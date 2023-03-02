#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //strcmp
#include "wcsys.h"
#define FILENAME "INFO.txt"
#define ACCOUNT "account.txt"
#define SIZE 1000
typedef struct account {
    char user[20];//账号
    char passwd[20];//密码
} account;

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
int login();
void logup();
void data_add(Node* head);         // 增加数据
void data_delete(Node* head);      // 删除数据
Node* data_find(Node* head);       // 查找数据
void data_modify(Node* head);      // 修改数据
void data_sort(Node* head);        // 数据排序
void data_print(Node* head);       // 打印数据
void data_save(Node* head);        // 保存数据
void data_statistics(Node* head);  // 统计数据
void show_single(Node* p);         // 显示单条数据
void menu();                       // 菜单
Node* IO_ReadInfo();               // 读取文件
void welcome();

int main() {
    wcclear();//清屏
    welcome();//登录菜单
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
                data_statistics(head);
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
    wcclear();  // 清屏
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
        printf("按回车键退出\n");
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
    printf("按回车键键退出\n");
    getchar();
}
void data_save(Node* head) {  // 保存数据
    FILE* fp;
    if ((fp = fopen(FILENAME, "w")) == NULL) {
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
    printf("保存成功\n");
}
void data_statistics(Node* head) {  // 统计数据
    Node* p = head->next;
    int grade_1 = 0, grade_2 = 0, grade_3 = 0, b1 = 0, b2 = 0, b3 = 0, s1 = 0,
        s2 = 0, s3 = 0;
    while (p) {
        if (p->data.grade == 1)
            grade_1++;
        if (p->data.grade == 2)
            grade_2++;
        if (p->data.grade == 3)
            grade_3++;
        if (p->data.balance >= 0 && p->data.balance < 500)
            b1++;
        if (p->data.balance >= 500 && p->data.balance < 1000)
            b2++;
        if (p->data.balance >= 1000)
            b3++;
        if (p->data.score >= 0 && p->data.score < 500)
            s1++;
        if (p->data.score >= 500 && p->data.score < 1000)
            s2++;
        if (p->data.score >= 1000)
            s3++;
        p = p->next;
    }
    printf(" --------------------------------------------------  \n");
    printf(" 会员总数  | 一级会员卡 | 二级会员卡 | 三级会员卡  \n");
    printf("%8d   |%10d  |%10d  |%10d        \n", num, grade_1, grade_2,
           grade_3);
    printf(" --------------------------------------------------  \n");
    printf("   区间    |   0-500    |  500-1000  |    >1000       \n");
    printf(" --------------------------------------------------  \n");
    printf("   余额    | %4d       | %4d       | %4d       \n", b1, b2, b3);
    printf(" --------------------------------------------------  \n");
    printf("   积分    | %4d       | %4d       | %4d       \n", s1, s2, s3);
    printf(" --------------------------------------------------  \n");
    getchar();
}
void data_modify(Node* head) {  // 修改数据
    wcclear();
    Node* p;
    int n, key = 1, key2 = 1;
    if ((p = data_find(head)) == NULL) {
        return;
    } else {
        while (key) {
            key2 = 1;
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
                    printf("无此选项,请重新选择\n");
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
                    wcclear();
                    key2 = 0;
                } else
                    printf("无此选项,请重新选择\n");
            }
        }
    }
}
void data_sort(Node* head) {  // 排序数据
    Node *p, *s;
    p = s = head;
    int n;  // 选项
    int cnt = 0;
    p = p->next;
    while (p) {
        people[cnt] = p->data;
        cnt++;  // 数据总数
        p = p->next;
    }
    num = cnt;
    printf("--------------------请选择要排序的数据------------\n");
    printf("- 1.会员姓名                                     -\n");
    printf("- 2.会员卡等级                                   -\n");
    printf("- 3.会员序号                                     -\n");
    printf("- 4.余额                                         -\n");
    printf("- 5.积分                                         -\n");
    printf("- 按其他键退出                                   -\n");
    printf("--------------------------------------------------\n");
    scanf("%d", &n);
    getchar();
    for (int i = 1; i < cnt; i++) {
        for (int j = 0; j < cnt - i; j++) {
            switch (n) {
                case 1:  // 1.会员姓名
                    if (strcmp(people[j].name, people[j + 1].name) > 0) {
                        Member t;
                        t = people[j];
                        people[j] = people[j + 1];
                        people[j + 1] = t;
                    }
                    break;
                case 2:  // 2.会员卡等级
                    if (people[j].grade > people[j + 1].grade) {
                        Member t;
                        t = people[j];
                        people[j] = people[j + 1];
                        people[j + 1] = t;
                    }
                    break;
                case 3:  // 3.会员序号
                    if (people[j].order > people[j + 1].order) {
                        Member t;
                        t = people[j];
                        people[j] = people[j + 1];
                        people[j + 1] = t;
                    }
                    break;
                case 4:  // 4.余额
                    if (people[j].balance > people[j + 1].balance) {
                        Member t;
                        t = people[j];
                        people[j] = people[j + 1];
                        people[j + 1] = t;
                    }
                    break;
                case 5:  // 5.积分
                    if (people[j].score > people[j + 1].score) {
                        Member t;
                        t = people[j];
                        people[j] = people[j + 1];
                        people[j + 1] = t;
                    }
                    break;
                default:  // 退出
                    return;
            }
        }
    }
    s = s->next;
    for (int i = 0; i < cnt; i++) {
        s->data = people[i];
        s = s->next;
    }
}
int login() {
    FILE* fr = fopen(ACCOUNT, "r");
    account writer;
    int m = 0;
    printf("请输入用户名：\n");
    scanf("%s", &writer.user);
    getchar();
    printf("请输入密码：\n");
    scanf("%s", &writer.passwd);
    getchar();
    while (!feof(fr)) {  // 读入用户账号信息
        account save;
        fscanf(fr, "%s %s", &save.user, &save.passwd);
        if (strcmp(writer.user, save.user) == 0)
            m = 2;
        if (strcmp(writer.user, save.user) == 0 &&
            strcmp(writer.passwd, save.passwd) == 0) {
            return 1;
        }
    }
    return m;
}
void logup() {
    FILE* fa = fopen(
        ACCOUNT,
        "a+");  // 以附加方式打开可读/写的文件,
                // 如果没有此文件则会进行创建，然后以附加方式打开可读/写的文件
    FILE* fr = fopen(ACCOUNT, "r");
    account writer;
    printf("请注册用户名\n");
    scanf("%s", &writer.user);
    getchar();
    while (!feof(fr)) {  // 读入用户账号信息
        account save;
        fscanf(fr, "%s %s", &save.user, &save.passwd);
        if (strcmp(writer.user, save.user) == 0) {
            printf("用户已存在@_@\n");
            wcsleep(2);
            return;
        }
    }
    printf("请输入密码\n");
    scanf("%s", &writer.passwd);
    getchar();
    fseek(fa, 0, SEEK_END);  // 定位到文件末尾
    fprintf(fa, "%s %s\n", writer.user, writer.passwd);
    printf("创建成功!^_^\n");
    wcsleep(2);
    fclose(fr);
    fclose(fa);
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
                num++;
            }
        }
    }
    fclose(fp);
    return head;
}
void welcome() {
    wcclear();
    printf("##########################################\n");
    printf("#############  影院管理系统  #############\n");
    printf("##########################################\n");
    printf("## 1.登录                               ##\n");
    printf("## 2.注册                               ##\n");
    printf("##########################################\n");
    printf("##########################################\n");
    int m, n;
    scanf("%d", &n);
    getchar();
    if (n == 1) {  // 登录
        m = login();
        if (1 == m) {
            printf("登录成功^_^\n");
            wcsleep(2);
            return;
        }
        if (2 == m) {
            printf("密码错误@_@\n");
            wcsleep(2);
            welcome();
        }
        if (0 == m) {
            printf("用户不存在@_@\n");
            wcsleep(2);
            welcome();
        }

    } else if (n == 2) {  // 注册
        logup();
        welcome();

    } else {
        printf("输入错误@_@\n");
        wcsleep(2);
        welcome();
    }
}