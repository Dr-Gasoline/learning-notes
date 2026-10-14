# 从 C 语言转向 Java：基础语法与常用功能指南

> 适用对象：已经掌握 C 语言基本语法，希望快速建立 Java 编程能力的学习者。  
> 本文按“要完成的功能”划分板块，并重点说明 Java 与 C 的对应关系和差异。

---

## 1. 建立整体认识

### 1.1 C 与 Java 的主要差异

| 方面 | C | Java |
| --- | --- | --- |
| 编程方式 | 以过程式编程为主 | 以面向对象编程为主 |
| 程序组织 | 函数、源文件、头文件 | 类、包、方法 |
| 编译结果 | 通常直接生成本地机器码 | 生成字节码，由 JVM 运行 |
| 内存管理 | 可使用 `malloc`、`free` 手动管理 | 对象由垃圾回收器自动管理 |
| 指针 | 支持指针及指针运算 | 使用引用，不支持普通指针运算 |
| 字符串 | 通常使用字符数组 | 使用 `String` 类 |
| 数组 | 通常不记录长度 | 数组对象自带 `length` |
| 泛型容器 | 通常自行实现或使用第三方库 | 标准库提供 `List`、`Set`、`Map` 等 |

从 C 转向 Java 时，最重要的思维变化是：

1. Java 代码必须写在类中。
2. C 中的“函数”在 Java 中称为“方法”。
3. 数组、字符串以及自定义类型的实例都是对象。
4. 使用对象引用代替指针，但不能进行地址运算。
5. Java 会自动回收不再使用的对象，通常不需要手动释放内存。

### 1.2 最小 Java 程序

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, Java!");
    }
}
```

将文件保存为 `Main.java`，类名必须与文件名一致：

```bash
javac Main.java
java Main
```

- `javac Main.java`：将源代码编译为 `Main.class` 字节码文件。
- `java Main`：由 JVM 运行 `Main` 类。
- 程序入口固定为 `public static void main(String[] args)`。
- Java 严格区分大小写，例如 `String` 不能写成 `string`。

---

## 2. 输出信息

### 2.1 普通输出

```java
System.out.print("Hello");       // 输出后不换行
System.out.println("Java");     // 输出后换行
```

对应 C 中的：

```c
printf("Hello");
printf("Java\n");
```

### 2.2 格式化输出

Java 的 `printf` 与 C 的 `printf` 用法接近：

```java
String name = "Alice";
int age = 20;
double score = 92.5;

System.out.printf("姓名：%s，年龄：%d，成绩：%.1f%n", name, age, score);
```

常用格式符：

| 格式符 | 含义 | 示例 |
| --- | --- | --- |
| `%d` | 十进制整数 | `System.out.printf("%d", 10);` |
| `%f` | 浮点数 | `System.out.printf("%.2f", 3.14159);` |
| `%c` | 字符 | `System.out.printf("%c", 'A');` |
| `%s` | 字符串或对象 | `System.out.printf("%s", "Java");` |
| `%x` | 十六进制整数 | `System.out.printf("%x", 255);` |
| `%n` | 与平台匹配的换行符 | `System.out.printf("OK%n");` |

---

## 3. 输入数据

### 3.1 使用 `Scanner` 读取控制台输入

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int age = scanner.nextInt();
        double height = scanner.nextDouble();
        String word = scanner.next();

        System.out.println(age);
        System.out.println(height);
        System.out.println(word);

        scanner.close();
    }
}
```

常用输入方法：

| 方法 | 读取内容 |
| --- | --- |
| `nextInt()` | `int` 整数 |
| `nextLong()` | `long` 整数 |
| `nextDouble()` | `double` 浮点数 |
| `next()` | 一个不含空白字符的单词 |
| `nextLine()` | 一整行文本 |
| `hasNextInt()` | 判断下一个输入是否为 `int` |

### 3.2 `nextInt()` 与 `nextLine()` 连用的陷阱

`nextInt()` 读取数字后会留下行末换行符，紧接着调用 `nextLine()` 时，可能读到空字符串：

```java
Scanner scanner = new Scanner(System.in);

int age = scanner.nextInt();
scanner.nextLine();              // 消耗数字后的换行符
String name = scanner.nextLine();
```

### 3.3 竞赛或大规模输入

`Scanner` 简单但速度相对较慢。数据量较大时，可使用 `BufferedReader`：

```java
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in));

        int n = Integer.parseInt(reader.readLine());
        String[] parts = reader.readLine().split("\\s+");
        int a = Integer.parseInt(parts[0]);
        int b = Integer.parseInt(parts[1]);

        System.out.println(n + a + b);
    }
}
```

---

## 4. 保存数据：变量、常量与基本类型

### 4.1 声明变量

Java 的基本声明方式与 C 相似：

```java
int count = 10;
double price = 19.9;
char grade = 'A';
boolean passed = true;
```

变量必须先声明再使用，局部变量在读取前必须显式初始化。

### 4.2 常用基本类型

| 类型 | 位数 | 典型用途 | 示例 |
| --- | ---: | --- | --- |
| `byte` | 8 | 小范围整数、原始字节 | `byte b = 100;` |
| `short` | 16 | 较小范围整数 | `short s = 1000;` |
| `int` | 32 | 常用整数 | `int n = 100000;` |
| `long` | 64 | 大整数 | `long x = 10_000_000_000L;` |
| `float` | 32 | 单精度浮点数 | `float f = 3.14F;` |
| `double` | 64 | 常用浮点数 | `double d = 3.14;` |
| `char` | 16 | UTF-16 代码单元 | `char c = '中';` |
| `boolean` | 未规定固定存储位数 | 逻辑值 | `boolean ok = true;` |

注意：

- Java 各整数类型的位数固定，不随操作系统变化。
- `long` 字面量通常加 `L`，`float` 字面量必须加 `F`。
- `boolean` 只能取 `true` 或 `false`，不能用整数 `0`、`1` 代替。
- `char` 使用单引号，`String` 使用双引号。

### 4.3 声明常量

C 中常使用 `const`，Java 使用 `final`：

```java
final double PI = 3.1415926;
```

类级常量通常同时使用 `static final`：

```java
public class Circle {
    public static final double PI = 3.1415926;
}
```

### 4.4 类型转换

小范围类型可以自动转换为大范围类型：

```java
int a = 10;
double b = a;       // 自动转换为 10.0
```

大范围类型转为小范围类型时必须强制转换：

```java
double x = 3.8;
int y = (int) x;    // y 为 3，直接截去小数部分
```

强制转换可能造成溢出或精度损失：

```java
int n = 130;
byte b = (byte) n;  // 溢出，结果不是 130
```

### 4.5 包装类型

每个基本类型都有对应的包装类：

| 基本类型 | 包装类 |
| --- | --- |
| `byte` | `Byte` |
| `short` | `Short` |
| `int` | `Integer` |
| `long` | `Long` |
| `float` | `Float` |
| `double` | `Double` |
| `char` | `Character` |
| `boolean` | `Boolean` |

集合不能直接使用基本类型，因此要写 `List<Integer>`，不能写 `List<int>`。

Java 通常会自动完成基本类型与包装类之间的转换：

```java
Integer boxed = 10;  // 自动装箱
int value = boxed;   // 自动拆箱
```

---

## 5. 进行运算

### 5.1 算术运算

```java
int a = 7;
int b = 3;

System.out.println(a + b);  // 10
System.out.println(a - b);  // 4
System.out.println(a * b);  // 21
System.out.println(a / b);  // 2：整数除法
System.out.println(a % b);  // 1
```

若希望得到浮点结果，至少一个操作数应为浮点类型：

```java
double result = (double) a / b;  // 2.333...
```

### 5.2 自增、自减和复合赋值

```java
int x = 5;
x++;
--x;
x += 3;
x *= 2;
```

其行为与 C 基本一致，但复杂表达式中不建议混用多次自增、自减。

### 5.3 比较与逻辑运算

```java
boolean r1 = a > b;
boolean r2 = a == b;
boolean r3 = a != b;
boolean r4 = (a > 0) && (b > 0);
boolean r5 = (a > 0) || (b > 0);
boolean r6 = !r1;
```

`&&` 和 `||` 具有短路特性：能够确定结果后，不再计算右侧表达式。

### 5.4 位运算

Java 仍支持常见位运算：

```java
int x = 0b1100;
int y = 0b1010;

int and = x & y;
int or  = x | y;
int xor = x ^ y;
int not = ~x;
int left = x << 1;
int right = x >> 1;       // 算术右移，保留符号
int unsigned = x >>> 1;   // 逻辑右移，高位补 0
```

Java 没有 C 中无符号整数类型的常规用法，但提供了 `>>>` 和部分无符号辅助方法。

### 5.5 数学功能

```java
int max = Math.max(3, 8);
int min = Math.min(3, 8);
int abs = Math.abs(-5);
double power = Math.pow(2, 3);
double root = Math.sqrt(16);
long rounded = Math.round(3.6);
double random = Math.random();   // [0.0, 1.0)
```

---

## 6. 根据条件选择操作

### 6.1 `if` 语句

```java
if (score >= 90) {
    System.out.println("优秀");
} else if (score >= 60) {
    System.out.println("及格");
} else {
    System.out.println("不及格");
}
```

Java 的条件必须是 `boolean`：

```java
int x = 1;

// if (x) { }        // 错误
if (x != 0) {        // 正确
    System.out.println("x 非零");
}
```

### 6.2 条件运算符

```java
int max = a > b ? a : b;
```

### 6.3 `switch` 语句

传统写法：

```java
switch (day) {
    case 1:
        System.out.println("Monday");
        break;
    case 2:
        System.out.println("Tuesday");
        break;
    default:
        System.out.println("Unknown");
}
```

箭头形式可避免遗漏 `break` 导致的贯穿执行：

```java
switch (day) {
    case 1 -> System.out.println("Monday");
    case 2 -> System.out.println("Tuesday");
    default -> System.out.println("Unknown");
}
```

`switch` 除整数和字符外，还可直接匹配字符串、枚举等类型。

---

## 7. 重复执行操作

### 7.1 `for` 循环

```java
for (int i = 0; i < 5; i++) {
    System.out.println(i);
}
```

写法与 C 基本一致。

### 7.2 `while` 与 `do-while`

```java
int i = 0;
while (i < 5) {
    System.out.println(i);
    i++;
}
```

```java
int j = 0;
do {
    System.out.println(j);
    j++;
} while (j < 5);
```

### 7.3 增强 `for` 循环

遍历数组或集合时，可以使用增强 `for`：

```java
int[] numbers = {10, 20, 30};

for (int number : numbers) {
    System.out.println(number);
}
```

其含义是“依次取出 `numbers` 中的每个元素”。它适合只读遍历，但不便获取下标，也不能通过修改循环变量直接修改基本类型数组中的元素。

### 7.4 `break` 与 `continue`

```java
for (int i = 0; i < 10; i++) {
    if (i == 3) {
        continue;   // 跳过本次循环
    }
    if (i == 8) {
        break;      // 结束整个循环
    }
    System.out.println(i);
}
```

---

## 8. 批量保存同类数据：数组

### 8.1 创建与初始化数组

```java
int[] a = new int[5];            // 5 个元素，默认值均为 0
int[] b = {1, 2, 3, 4, 5};
int[] c = new int[]{1, 2, 3};
```

推荐将方括号写在类型后，即 `int[] a`，而不是 `int a[]`。

### 8.2 访问元素和获取长度

```java
int first = b[0];
b[1] = 20;

for (int i = 0; i < b.length; i++) {
    System.out.println(b[i]);
}
```

Java 会检查数组下标。下标越界会抛出 `ArrayIndexOutOfBoundsException`，不会像 C 那样直接访问未知内存。

### 8.3 二维数组

```java
int[][] matrix = {
    {1, 2, 3},
    {4, 5, 6}
};

System.out.println(matrix[1][2]);  // 6
```

Java 的二维数组本质上是“数组的数组”，因此每一行的长度可以不同：

```java
int[][] jagged = new int[3][];
jagged[0] = new int[2];
jagged[1] = new int[4];
jagged[2] = new int[1];
```

### 8.4 常用数组操作

```java
import java.util.Arrays;

int[] numbers = {5, 2, 8, 1};

Arrays.sort(numbers);                         // 排序
int index = Arrays.binarySearch(numbers, 5);  // 二分查找，使用前应先排序
int[] copy = Arrays.copyOf(numbers, numbers.length);
boolean same = Arrays.equals(numbers, copy);
System.out.println(Arrays.toString(numbers));
```

二维数组可使用 `Arrays.deepToString(matrix)` 转为易读字符串。

---

## 9. 处理文本：字符与字符串

### 9.1 `char` 与 `String`

```java
char letter = 'A';
String text = "Hello";
```

- `char` 表示一个 UTF-16 代码单元。
- `String` 是类，不是字符数组。
- Java 字符串对象不可变：对字符串进行修改会产生新字符串。

### 9.2 常用字符串操作

```java
String s = "Hello Java";

int length = s.length();
char first = s.charAt(0);
String part = s.substring(0, 5);  // [0, 5)，结果为 "Hello"
boolean contains = s.contains("Java");
boolean starts = s.startsWith("Hello");
int position = s.indexOf("Java");
String upper = s.toUpperCase();
String replaced = s.replace("Java", "World");
String trimmed = s.trim();
String[] words = s.split("\\s+");
```

### 9.3 比较字符串

比较字符串内容必须使用 `equals`：

```java
String a = new String("Java");
String b = new String("Java");

System.out.println(a.equals(b));  // true：内容相同
System.out.println(a == b);       // false：引用通常不同
```

- `==` 比较两个引用是否指向同一个对象。
- `equals()` 比较对象的逻辑内容；字符串类已经实现了内容比较。
- 忽略大小写可使用 `a.equalsIgnoreCase(b)`。

为避免变量可能为 `null` 时出现异常，可以将确定非空的字符串放在前面：

```java
if ("yes".equals(answer)) {
    System.out.println("确认");
}
```

### 9.4 高效拼接字符串

少量拼接可直接使用 `+`：

```java
String message = "Hello, " + name;
```

循环中大量拼接应使用 `StringBuilder`：

```java
StringBuilder builder = new StringBuilder();

for (int i = 0; i < 5; i++) {
    builder.append(i).append(' ');
}

String result = builder.toString();
```

常用方法包括 `append`、`insert`、`delete`、`reverse` 和 `toString`。

---

## 10. 封装重复操作：方法

### 10.1 定义和调用方法

C 中的函数在 Java 中称为方法，且必须属于某个类：

```java
public class Main {
    static int add(int a, int b) {
        return a + b;
    }

    public static void main(String[] args) {
        int result = add(3, 5);
        System.out.println(result);
    }
}
```

基本格式：

```java
访问修饰符 static 返回类型 方法名(参数列表) {
    // 方法体
}
```

暂时可以这样理解 `static`：`main` 是静态方法，它可以直接调用同一个类中的其他静态方法；调用普通实例方法则需要先创建对象。

### 10.2 无返回值方法

```java
static void greet(String name) {
    System.out.println("Hello, " + name);
}
```

`void` 表示不返回结果。

### 10.3 方法重载

同一个类中可以存在同名但参数列表不同的方法：

```java
static int max(int a, int b) {
    return a > b ? a : b;
}

static double max(double a, double b) {
    return a > b ? a : b;
}
```

只有返回类型不同不能构成重载。

### 10.4 参数传递

Java 永远采用值传递：

- 传入基本类型时，复制的是数值。
- 传入对象或数组时，复制的是引用的值；方法能够借助该引用修改对象内容，但不能改变调用者变量本身所保存的引用。

```java
static void changeNumber(int x) {
    x = 100;
}

static void changeArray(int[] array) {
    array[0] = 100;
}
```

调用后，前者不会改变外部整数变量，后者会改变外部数组的第一个元素。

### 10.5 可变参数

```java
static int sum(int... numbers) {
    int result = 0;
    for (int number : numbers) {
        result += number;
    }
    return result;
}

int total = sum(1, 2, 3, 4);
```

可变参数在方法内部按数组处理，并且必须位于参数列表末尾。

---

## 11. 描述一类事物：类与对象

### 11.1 定义类

```java
class Student {
    String name;
    int age;

    void introduce() {
        System.out.println("我是" + name + "，今年" + age + "岁");
    }
}
```

### 11.2 创建和使用对象

```java
public class Main {
    public static void main(String[] args) {
        Student student = new Student();
        student.name = "Alice";
        student.age = 20;
        student.introduce();
    }
}
```

```java
Student student = new Student();
```

可理解为：创建一个 `Student` 对象，并让引用变量 `student` 指向它。它不同于 C 中在栈上声明一个普通结构体变量的思路。

### 11.3 构造方法

构造方法用于初始化对象，其名称与类名相同，没有返回类型：

```java
class Student {
    String name;
    int age;

    Student(String name, int age) {
        this.name = name;
        this.age = age;
    }
}
```

调用方式：

```java
Student student = new Student("Alice", 20);
```

`this` 表示当前对象。这里用它区分成员变量 `this.name` 与参数 `name`。

如果显式定义了任意构造方法，编译器就不会再自动提供无参数构造方法。

### 11.4 封装

通常将字段声明为 `private`，通过方法控制访问：

```java
class Student {
    private String name;
    private int age;

    public Student(String name, int age) {
        this.name = name;
        setAge(age);
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        if (age < 0) {
            throw new IllegalArgumentException("年龄不能为负数");
        }
        this.age = age;
    }
}
```

常见访问修饰符：

| 修饰符 | 主要可见范围 |
| --- | --- |
| `private` | 当前类内部 |
| 不写修饰符 | 同一个包内 |
| `protected` | 同一个包以及子类 |
| `public` | 所有可访问该类的位置 |

### 11.5 静态成员与实例成员

```java
class Counter {
    static int total = 0;  // 所有对象共享
    int value = 0;         // 每个对象各自拥有

    void increase() {
        value++;
        total++;
    }
}
```

- 实例成员属于某个对象，通过 `对象.成员` 访问。
- 静态成员属于类，通过 `类名.成员` 访问。

---

## 12. 复用和扩展类型：继承、接口与多态

以下内容可以直接作为 `.md` 笔记：

# 继承、接口与多态

## 1. 继承：复用和扩展父类

```java
class Animal {
    private String name;

    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void eat() {
        System.out.println("动物吃东西");
    }

    public void speak() {
        System.out.println("动物发出声音");
    }
}
```

```java
class Dog extends Animal {
    public Dog(String name) {
        super(name);    // 调用父类构造函数
    }

    @Override
    public void speak() {
        System.out.println(getName() + "：汪汪！");
    }

    public void fetch() {
        System.out.println("狗正在捡球");
    }
}
```

调用：

```java
Dog dog = new Dog("旺财");

dog.eat();      // 调用继承自 Animal 的方法
dog.speak();    // 调用 Dog 重写后的方法
dog.fetch();    // 调用 Dog 自己的方法
```

要点：

* `extends` 表示继承；
* `super(...)` 调用父类构造函数；
* `@Override` 表示重写父类方法；
* 构造函数不会被继承，也不能被重写。

---

## 2. 子类访问父类成员

```java
class Animal {
    private String name;
    protected int age;
    public void eat() {
        System.out.println("吃东西");
    }
}
```

```java
class Dog extends Animal {
    public void test() {
        // name = "旺财";  // 错误：private 不能直接访问
        age = 2;          // 正确：protected
        eat();            // 正确：public
    }
}
```

| 修饰符         | 子类访问情况  |
| ----------- | ------- |
| `private`   | 不能直接访问  |
| 默认权限        | 同包时可以访问 |
| `protected` | 子类可以访问  |
| `public`    | 可以访问    |

访问父类的私有变量，应使用父类提供的 `public` 或 `protected` 方法，例如：

```java
System.out.println(getName());
```

---

## 3. 多态：父类引用指向子类对象

```java
Animal animal = new Dog("小黑");

animal.speak();   // 实际执行 Dog.speak()
animal.eat();     // 可以调用 Animal 中的方法
// animal.fetch(); // 错误：Animal 类型中没有 fetch
```

这里：

```text
Animal：声明类型
Dog：实际对象类型
```

规则：

* 声明类型决定“能调用哪些方法”；
* 实际对象类型决定“重写方法执行哪个版本”。

需要调用子类特有方法时：

```java
if (animal instanceof Dog) {
    Dog dog = (Dog) animal;
    dog.fetch();
}
```

---

## 4. `this` 与 `super`

```java
class Dog extends Animal {
    @Override
    public void speak() {
        super.speak();                  // 调用父类版本
        System.out.println("狗叫");
    }
}
```

```text
this.method()   当前对象的方法，可能执行子类重写版本
super.method()  明确调用父类版本
```

如果子类重写了方法，想保留父类行为，可以使用：

```java
super.speak();
```

---

## 5. 父类内部调用方法也具有多态性

```java
class Animal {
    public void act() {
        speak();
    }

    public void speak() {
        System.out.println("动物叫");
    }
}
```

```java
class Dog extends Animal {
    @Override
    public void speak() {
        System.out.println("狗叫");
    }
}
```

```java
Animal animal = new Dog();
animal.act();
```

执行过程：

```text
Animal.act()
    ↓
调用 speak()
    ↓
实际对象是 Dog
    ↓
执行 Dog.speak()
```

输出：

```text
狗叫
```

普通实例方法调用会根据实际对象类型动态选择重写版本。

---

## 6. 接口：规定一种能力

```java
interface Flyable {
    void fly();
}
```

实现接口：

```java
class Bird implements Flyable {
    @Override
    public void fly() {
        System.out.println("鸟正在飞");
    }
}
```

调用：

```java
Flyable flyable = new Bird();
flyable.fly();
```

要点：

* `implements` 表示实现接口；
* 实现类必须实现接口中的方法；
* 接口引用只能调用接口中声明的方法；
* 一个类只能继承一个父类，但可以实现多个接口。

```java
class Robot implements Flyable, Runnable {
    // 同时实现多个接口
}
```

---

## 7. 一句话总结

```text
继承：复用父类代码
重写：子类修改父类行为
多态：父类引用指向子类对象
接口：规定类必须具备的能力
super：调用父类成员
this：调用当前对象成员
```


---

## 13. 动态保存数据：常用集合

数组长度固定；元素数量会变化时，通常使用集合框架。

### 13.1 `List`：有序、可重复

```java
import java.util.ArrayList;
import java.util.List;

List<String> names = new ArrayList<>();
names.add("Alice");
names.add("Bob");
names.add("Alice");

String first = names.get(0);
names.set(1, "Carol");
names.remove("Alice");      // 删除第一个匹配项
int size = names.size();

for (String name : names) {
    System.out.println(name);
}
```

注意数组使用 `.length`，字符串使用 `.length()`，集合使用 `.size()`。

### 13.2 `Set`：元素不重复

```java
import java.util.HashSet;
import java.util.Set;

Set<Integer> numbers = new HashSet<>();
numbers.add(10);
numbers.add(20);
numbers.add(10);             // 不会重复加入

boolean exists = numbers.contains(20);
numbers.remove(10);
```

`HashSet` 不保证遍历顺序。

### 13.3 `Map`：键值映射

```java
import java.util.HashMap;
import java.util.Map;

Map<String, Integer> scores = new HashMap<>();
scores.put("Alice", 95);
scores.put("Bob", 88);

int aliceScore = scores.get("Alice");
int defaultScore = scores.getOrDefault("Carol", 0);
boolean exists = scores.containsKey("Bob");

for (Map.Entry<String, Integer> entry : scores.entrySet()) {
    System.out.println(entry.getKey() + ": " + entry.getValue());
}
```

每个键唯一；对同一键再次调用 `put` 会覆盖旧值。

### 13.4 集合的常见选择

| 需求 | 常用类型 |
| --- | --- |
| 按下标保存一组可重复元素 | `ArrayList` |
| 高频在两端添加或删除 | `ArrayDeque` |
| 保证元素不重复 | `HashSet` |
| 建立键到值的映射 | `HashMap` |
| 自动按自然顺序排序 | `TreeSet`、`TreeMap` |

### 13.5 排序

```java
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

List<Integer> numbers = new ArrayList<>(List.of(5, 2, 8, 1));
numbers.sort(Comparator.naturalOrder());  // 升序
numbers.sort(Comparator.reverseOrder());  // 降序
```

按对象的某个字段排序：

```java
students.sort(Comparator.comparingInt(Student::getAge));
```

---

## 14. 表示“没有对象”：`null`

引用变量可以取 `null`，表示没有指向任何对象：

```java
String name = null;
```

不能通过 `null` 调用方法：

```java
// name.length();  // 抛出 NullPointerException
```

使用前可以判断：

```java
if (name != null) {
    System.out.println(name.length());
}
```

基本类型不能取 `null`，包装类型可以：

```java
int a = 0;
Integer b = null;
```

对值为 `null` 的包装类型进行自动拆箱也会抛出 `NullPointerException`。

---

## 15. 处理错误：异常

### 15.1 捕获异常

```java
try {
    int number = Integer.parseInt("abc");
    System.out.println(number);
} catch (NumberFormatException e) {
    System.out.println("输入不是合法整数");
} finally {
    System.out.println("无论是否出错都会执行");
}
```

### 15.2 主动抛出异常

```java
static double divide(double a, double b) {
    if (b == 0) {
        throw new IllegalArgumentException("除数不能为 0");
    }
    return a / b;
}
```

### 15.3 `throws`

方法暂不处理某些异常时，可以在声明中使用 `throws`：

```java
static String readFirstLine(String path) throws java.io.IOException {
    return java.nio.file.Files.readAllLines(
            java.nio.file.Path.of(path)).get(0);
}
```

不要用空的 `catch` 块静默吞掉异常；至少应提供提示，或者将异常继续抛给调用者。

---

## 16. 读写文件

### 16.1 一次性读取和写入文本

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args) throws IOException {
        Path path = Path.of("data.txt");

        Files.writeString(path, "Hello, Java!\n");
        String content = Files.readString(path);

        System.out.println(content);
    }
}
```

### 16.2 按行读取

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = Files.newBufferedReader(Path.of("data.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
    }
}
```

`try (...)` 称为 try-with-resources。代码块结束时，文件等资源会被自动关闭，作用类似于避免忘记调用 C 中的 `fclose`。

---

## 17. 拆分和组织程序：包与导入

### 17.1 `package`

包用于组织类并避免重名。例如：

```java
package com.example.app;

public class Student {
}
```

源文件通常放在与包名对应的目录中：

```text
com/example/app/Student.java
```

### 17.2 `import`

使用其他包中的类时，可以导入：

```java
import java.util.ArrayList;
import java.util.List;
```

`java.lang` 包会被自动导入，因此 `String`、`System`、`Math` 等无需手动导入。

Java 的 `import` 主要用于简化类名书写，不等同于 C 预处理器的 `#include` 文本包含。

---

## 18. 常用类型转换与工具

### 18.1 字符串与数字互转

```java
int a = Integer.parseInt("123");
long b = Long.parseLong("123456789");
double c = Double.parseDouble("3.14");

String s1 = String.valueOf(123);
String s2 = Integer.toString(123);
```

### 18.2 字符判断和转换

```java
char c = 'A';

boolean digit = Character.isDigit(c);
boolean letter = Character.isLetter(c);
char lower = Character.toLowerCase(c);
```

### 18.3 随机数

```java
import java.util.Random;

Random random = new Random();
int value = random.nextInt(10);  // 0～9
double probability = random.nextDouble();
```

### 18.4 当前时间

```java
import java.time.LocalDate;
import java.time.LocalDateTime;

LocalDate today = LocalDate.now();
LocalDateTime now = LocalDateTime.now();
```

---

## 19. C 程序改写为 Java 的完整示例

目标：输入若干整数，计算总和、平均值与最大值。

### 19.1 C 语言版本

```c
#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int numbers[n];
    int sum = 0;
    int max;

    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
        sum += numbers[i];

        if (i == 0 || numbers[i] > max) {
            max = numbers[i];
        }
    }

    double average = (double) sum / n;
    printf("sum = %d\n", sum);
    printf("average = %.2f\n", average);
    printf("max = %d\n", max);

    return 0;
}
```

### 19.2 Java 版本

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int[] numbers = new int[n];
        int sum = 0;
        int max = Integer.MIN_VALUE;

        for (int i = 0; i < n; i++) {
            numbers[i] = scanner.nextInt();
            sum += numbers[i];
            max = Math.max(max, numbers[i]);
        }

        double average = (double) sum / n;
        System.out.printf("sum = %d%n", sum);
        System.out.printf("average = %.2f%n", average);
        System.out.printf("max = %d%n", max);

        scanner.close();
    }
}
```

对应关系：

| 功能 | C | Java |
| --- | --- | --- |
| 引入功能 | `#include <stdio.h>` | `import java.util.Scanner;` |
| 读取整数 | `scanf("%d", &n)` | `scanner.nextInt()` |
| 动态长度数组 | 部分标准/编译器支持变长数组，或手动分配 | `new int[n]` |
| 输出 | `printf` | `System.out.printf` |
| 求最大值 | 手动比较 | `Math.max` |
| 数组越界检查 | 通常没有 | 运行时自动检查 |

---

## 20. 从 C 转向 Java 时最常见的错误

### 20.1 用 `==` 比较字符串内容

```java
// 错误思路
if (a == b) {
}

// 正确
if (a.equals(b)) {
}
```

### 20.2 把整数当作布尔值

```java
// if (x) { }       // Java 中不合法
if (x != 0) {
}
```

### 20.3 忘记整数除法

```java
double average1 = sum / count;           // 先做整数除法
double average2 = (double) sum / count;  // 得到浮点结果
```

### 20.4 混淆三种长度写法

```java
array.length;       // 数组属性
string.length();    // String 方法
list.size();        // 集合方法
```

### 20.5 以为 Java 的对象参数是“引用传递”

Java 始终是值传递。传对象时复制的是引用本身，而不是让方法直接控制调用者的引用变量。

### 20.6 忽视 `null`

引用可能为 `null`。在不确定时调用方法，可能触发 `NullPointerException`。

### 20.7 试图手动释放普通对象

Java 没有对应普通对象的 `free`。将引用赋为 `null` 也不等于立即释放对象；对象何时回收由垃圾回收器决定。

### 20.8 一个源文件中放置多个 `public` 顶级类

一个 `.java` 文件最多有一个 `public` 顶级类，文件名必须与该类名相同。其他顶级类可以不写 `public`。

### 20.9 忽略整数溢出

Java 的整数溢出通常不会自动报错：

```java
int x = Integer.MAX_VALUE;
x++;  // 变为 Integer.MIN_VALUE
```

需要检查溢出时，可以使用 `Math.addExact`、`Math.multiplyExact` 等方法。

---

## 21. 常用功能速查表

| 功能 | Java 写法 |
| --- | --- |
| 输出并换行 | `System.out.println(x);` |
| 格式化输出 | `System.out.printf("%d%n", x);` |
| 读取整数 | `scanner.nextInt()` |
| 字符串转整数 | `Integer.parseInt(s)` |
| 整数转字符串 | `String.valueOf(x)` |
| 创建数组 | `int[] a = new int[n];` |
| 数组长度 | `a.length` |
| 字符串长度 | `s.length()` |
| 集合大小 | `list.size()` |
| 比较字符串内容 | `a.equals(b)` |
| 数组排序 | `Arrays.sort(a)` |
| 集合排序 | `list.sort(...)` |
| 数组转可读文本 | `Arrays.toString(a)` |
| 求绝对值 | `Math.abs(x)` |
| 求最大值 | `Math.max(a, b)` |
| 创建动态列表 | `List<Integer> list = new ArrayList<>();` |
| 创建集合 | `Set<Integer> set = new HashSet<>();` |
| 创建映射 | `Map<String, Integer> map = new HashMap<>();` |
| 判断是否为 `null` | `obj == null` |
| 创建对象 | `Type obj = new Type(...);` |

---

## 22. 建议的学习顺序

1. 掌握 Java 程序结构、基本类型、输入输出和运算符。
2. 用 Java 重写熟悉的 C 语言分支、循环和数组练习。
3. 重点掌握 `String`、方法、参数传递和异常信息的阅读。
4. 学习类、对象、构造方法、封装以及 `static`。
5. 掌握 `ArrayList`、`HashSet`、`HashMap` 等常用集合。
6. 再学习继承、接口、多态、泛型、Lambda 表达式和 Stream。

初学阶段不必急于使用复杂框架。先做到能用 Java 独立完成输入、处理、输出以及简单的对象建模，再逐步进入更完整的面向对象设计。

---

## 23. 最小综合模板

下面的模板包含输入、数组、循环、方法和格式化输出，可作为基础练习的起点：

```java
import java.util.Scanner;

public class Main {
    static int sum(int[] numbers) {
        int result = 0;
        for (int number : numbers) {
            result += number;
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int[] numbers = new int[n];

        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = scanner.nextInt();
        }

        int total = sum(numbers);
        double average = n == 0 ? 0.0 : (double) total / n;

        System.out.printf("总和：%d%n", total);
        System.out.printf("平均值：%.2f%n", average);

        scanner.close();
    }
}
```

这份模板的核心执行过程是：

```text
读取数据 → 保存到数组 → 调用方法处理 → 输出结果
```

它与 C 程序的基本流程并无本质差别；Java 主要是在程序组织、类型封装、标准库和内存管理方面采用了不同方式。
