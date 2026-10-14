#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}
// 中缀表达式转后缀表达式（字符串数组）
void infix_to_postfix(const char *infix, char **postfix, int *len) {
    char op_stack[1000];
    int top = -1;
    int i = 0;
    int idx = 0;
    int n = strlen(infix);
    while (i < n) {
        if (isdigit(infix[i])) {
            // 读取一个数字
            char num_str[20];
            int j = 0;
            while (i < n && isdigit(infix[i])) {
                num_str[j++] = infix[i++];
            }
            num_str[j] = '\0';
            postfix[idx] = (char*)malloc(strlen(num_str)+1);
            strcpy(postfix[idx], num_str);
            idx++;
        } else if (infix[i] == '(') {
            op_stack[++top] = '(';
            i++;
        } else if (infix[i] == ')') {
            while (top >= 0 && op_stack[top] != '(') {
                char op_str[2] = {op_stack[top--], '\0'};
                postfix[idx] = (char*)malloc(2);
                strcpy(postfix[idx], op_str);
                idx++;
            }
            top--; // 弹出 '('
            i++;
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (top >= 0 && op_stack[top] != '(' && priority(op_stack[top]) >= priority(infix[i])) {
                char op_str[2] = {op_stack[top--], '\0'};
                postfix[idx] = (char*)malloc(2);
                strcpy(postfix[idx], op_str);
                idx++;
            }
            op_stack[++top] = infix[i];
            i++;
        } else { // 空格等忽略
            i++;
        }
    }
    while (top >= 0) {
        char op_str[2] = {op_stack[top--], '\0'};
        postfix[idx] = (char*)malloc(2);
        strcpy(postfix[idx], op_str);
        idx++;
    }
    *len = idx;
}