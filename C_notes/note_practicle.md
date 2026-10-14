1.宏定义要慎重，不行就写个函数吧，**宏定义参数不要用 执行函数 / 自增 / 自减**，否则隐蔽地执行多次  

    e.g. #define H(x) ((x)<=10 && (x)>=0) 

良好的习惯是：外层加上括号，内层每个(x)也加上括号

2.链表的增删改查一定要注意 **空链表 / 链表头 / 链表尾 / 唯一节点** 的特殊情况，做好特判

3.试图**移动指针**或者**使用指针指向内容**时，首先应确保**指针非空**

4.常用读入函数及其返回值：  
|类型|函数名|返回值|缓冲区末/文件末/剩余为空|匹配失败|
|:---|:---|:---|:---|:---|
|单字符输入|getchar()/getc()/fgetc()|读到的字符|EOF（需用int类型承接，char类型可能非负）|-|
|字符串输入|fgets()|指向录入缓冲区的指针（一般用不到）|NULL|NULL|
|格式化输入|scanf()/sscanf()/fscanf()|成功匹配并赋值的参数数目|EOF|返回成功匹配数（即输入流有非空内容，但与占位符要求格式不匹配，可能返回0）|

5.`qsort` 中比较函数 `cmp` 的写法要点

`qsort` 函数原型：`void qsort(void *_Base, size_t _NumOfElements, size_t _SizeOfElements, int (*_PtFuncCompare)(const void *, const void *))`

比较函数 `cmp` 接收两个 `const void*` 参数，分别指向**待比较的两个数组元素的起始地址**。返回值：**负数** → `a` 排在 `b` 前；**零** → 相等；**正数** → `a` 排在 `b` 后。

不同数组元素类型下，`cmp` 的写法区别如下（核心：**强转后解引用得到的类型必须等于数组元素的类型**）：

| 数组元素类型 | `cmp` 中输入 `a` 和 `b` 的实际类型 | 正确强转写法 | 比较方式 |
| :--- | :--- | :--- | :--- |
| `int` | `const int*` | `*(const int*)a` | 数值相减：`return *(int*)a - *(int*)b;`（注意防溢出，稳妥写法：`return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b);`） |
| `char*`<br>（字符串指针数组） | `const char**`（指向 `char*` 的指针） | `*(const char**)a` | `return strcmp(*(const char**)a, *(const char**)b);` |
| `char[100]`<br>（二维字符数组的行） | `const char (*)[100]`（指向一维数组的指针） | `*(const char (*)[100])a`| `return strcmp(*(const char (*)[100])a, *(const char (*)[100])b);` |
| 结构体 <br>`struct S` | `const struct S*` | `(const struct S*)a` | 访问成员比较：`return ((struct S*)a)->field - ((struct S*)b)->field;` 或 `strcmp(...)` |

6.文件处理语法：

- 打开文件：`FILE *fp = fopen("文件名", "模式");`
  - 模式：`"r"`（只读）、`"w"`（写入，覆盖）、`"a"`（追加）、`"r+"`（读写）、`"w+"`（读写，覆盖）、`"a+"`（读写，追加）
  - 返回值：成功返回文件指针，失败返回 `NULL`
  - 检查返回值：`if (fp == NULL) { perror("fopen"); exit(1); }`

- 关闭文件：`fclose(fp);`


| 操作类型 | 文本模式 |
| :--- | :--- | 
| **字符读取** | `int ch = fgetc(fp);`<br>返回读到的字符（`unsigned char` 转 `int`），文件尾或出错返回 `EOF` | 
| **字符写入** | `fputc(ch, fp);`<br>成功返回写入的字符，失败返回 `EOF` | 
| **行读取** | `char *fgets(char *buf, int size, FILE *fp);`<br>读取到 `size-1` 个字符或换行符或 EOF，末尾自动添加 `'\0'` | 
| **行写入** | `fputs(const char *str, FILE *fp);`<br>写入字符串（不含换行符），成功返回非负，失败返回 `EOF` | 
| **格式化读取** | `fscanf(fp, "格式串", &变量);`<br>返回成功匹配并赋值的参数个数 | 
| **格式化写入** | `fprintf(fp, "格式串", 变量);`<br>返回写入的字符数，失败返回负值 | 


- 判断文件尾（文本）：`feof(fp)` 在**读取操作尝试越过文件尾之后**才返回非零，不能用于提前判断。
- 判断文件尾（二进制 + `fread`）：**直接比较 `fread` 返回值是否小于 `nmemb`**，比 `feof` 更可靠。

- 文件定位：
  - `fseek(FILE *fp, long offset, int whence);`  
    定位文件指针，`whence` 可取 `SEEK_SET`（文件开头）、`SEEK_CUR`（当前位置）、`SEEK_END`（文件末尾）  
    成功返回 `0`，失败返回 `-1`
  - `ftell(FILE *fp);`  
    返回当前文件指针相对于文件开头的偏移量（字节数），失败返回 `-1L`
  - `rewind(FILE *fp);`  
    将文件指针重置到文件开头（相当于 `fseek(fp, 0L, SEEK_SET);`）


