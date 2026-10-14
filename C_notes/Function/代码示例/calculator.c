#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef double DataType;

enum symbol{NUM,OP,EQ,OTHER}; // 符号类型
enum oper{EPT,ADD,MIN,MUL,DIV,LEFT,RIGHT};                                  // 运算类型及优先级
int Pri[] = {-1, 0, 0, 1, 1, 2, 2}; // 运算符优先级
union sym
{
    DataType num;
    enum oper op;
}; // 符号值
enum symbol getSym(union sym *item);
void operate(enum oper op); // 操作运算符
void compute(enum oper op); // 进行运算
void pushNum(DataType num);
DataType popNum();
void pushOp(enum oper op);
enum oper popOp();
enum oper topOp();

enum symbol getSym(union sym *item)
{
    int c, n;
    while ((c = getchar()) != '=')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = getchar())
                n = n * 10 + c - '0';
            ungetc(c, stdin);
            item->num = n;
            return NUM;
        }
        else
            switch (c)
            {
            case '+':
                item->op = ADD;
                return OP;
            case '-':
                item->op = MIN;
                return OP;
            case '*':
                item->op = MUL;
                return OP;
            case '/':
                item->op = DIV;
                return OP;
            case '(':
                item->op = LEFT;
                return OP;
            case ')':
                item->op = RIGHT;
                return OP;
            case ' ':
            case '\t':
            case '\n':
                break;
            default:
                return OTHER;
            }
    }
    return EQ;
}

void compute(enum oper op)
{
    DataType tmp;
    switch (op)
    {
    case ADD:
        pushNum(popNum() + popNum());
        break;
    case MIN:
        tmp = popNum();
        pushNum(popNum() - tmp);
        break;
    case MUL:
        pushNum(popNum() * popNum());
        break;
    case DIV:
        tmp = popNum();
        pushNum(popNum() / tmp);
        break;
    }
}

// 数据栈操作
DataType Num_stack[MAXSIZE]; // 数据栈
int Ntop = -1;               // 数据栈顶指示器，初始为空栈
void error(char s[])
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}
void pushNum(DataType num)
{
    if (Ntop == MAXSIZE - 1)
        error("Data stack is full!");
    Num_stack[++Ntop] = num;
}
DataType popNum()
{
    if (Ntop == -1)
        error("Error in the expression!");
    return Num_stack[Ntop--];
}

// 运算符栈操作
enum oper Op_stack[MAXSIZE]; // 符号栈
int Otop = -1;               // 运算符栈顶指示器，初始为空栈
void pushOp(enum oper op)
{
    if (Otop == MAXSIZE - 1)
        error("Operator stack is full!");
    Op_stack[++Otop] = op;
}
enum oper popOp()
{
    if (Otop != -1)
    {
        return Op_stack[Otop--];
    }
    return EPT;
}
enum oper topOp()
{
    return Op_stack[Otop];
}

void operate(enum oper op)
{
    if (op == LEFT)
    {
        pushOp(op);
    }
    else if (op == RIGHT)
    {
        while (topOp() != LEFT)
        {
            compute(popOp());
        }
        popOp(); // 弹出左括号
    }
    else
    {
        while (Otop >= 0 && topOp() != LEFT && Pri[topOp()] >= Pri[op])
        {
            compute(popOp());
        }
        pushOp(op);
    }
}

int main()
{
    union sym item;
    enum symbol s;
    while ((s = getSym(&item)) != EQ)
    {
        if (s == NUM)
            pushNum(item.num);
        else if (s == OP)
            operate(item.op);
        else
        {
            printf("Error in the expression!\n");
            return 1;
        }
    }
    while (Otop >= 0) // 将栈中所有运算符弹出计算
        compute(popOp());
    if (Ntop == 0) // 输出计算结果
        printf("%.2lf\n", popNum());
    else
        printf("Error in the expression!\n");
    return 0;
}