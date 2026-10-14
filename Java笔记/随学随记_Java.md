# 一、Class里发生了什么？

## 1. 访问权限
| 修饰符         | 可访问范围         |
| ----------- | ------------- |
| `public`    | 其他类通常都可以访问    |
| `private`   | 只有当前类内部可以访问   |
| `protected` | 同包类和子类可以访问    |
| 不写          | 只有同一个包中的类可以访问 |


## 2. 构造方法
一个特殊的方法，在class内用于构建新个体。  
通常声明为`public`，无返回值，要求方法名与类名相同。  
`e.g.`  
- 定义
```java
class Student {
    String name;
    int age;

    //构建方法
    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }
}
```
- 创建
```java
Student student = new Student("Alice", 20);
//类型名  变量名       构造方法
```


## 3. 成员 / 方法 的类型
- **声明static ：**   
***静态成员 / 方法***：成员属于**类**，而不是某个对象，引用时不需要创建对象
- **不声明static ：**  
***非静态成员 / 方法***：成员属于**对象**，每个对象各有各的，互不冲突，使用时必须针对具体的对象

`e.g.`
```java
class Dog {
    // 静态成员：整个 Dog 类共享一份
    static int count = 0;

    // 非静态成员：每个 Dog 对象各有一份
    String name;

    Dog(String name) {
        this.name = name;
        count++;
    }

    // 非静态方法：必须通过具体对象调用
    void bark() {
        System.out.println(name + "：汪汪！");
    }

    // 静态方法：可以直接通过类名调用
    static void showCount() {
        System.out.println("狗的数量：" + count);
    }
}

public class Main {
    public static void main(String[] args) {
        Dog dog1 = new Dog("旺财");
        Dog dog2 = new Dog("小黑");

        dog1.bark();          // 旺财：汪汪！
        dog2.bark();          // 小黑：汪汪！

        Dog.showCount();      // 狗的数量：2
    }
}
```

## 4. class Main 里的 主程序 Main

```java
public class Main{
    public static void main(String[] args){//固定写法
        //主执行程序
    }
}
```

## 5. 子类继承、接口和多态

### 5.1 继承（`extends`）

继承表示“子类是一种父类”，用于复用父类的属性和方法。

```java
class Animal {
    private int age;
    private int price;

    public Animal(int age, int price){
        this.age = age;
        this.price = price;
    }

    public void speak() {
        System.out.println("动物叫");
    }
}
//创建子类
class Dog extends Animal {
    //子类的新属性
    private String type;

    //构造方法
    public Dog(int age, int price, String type) {
        super(age, price);    // 调用 Animal 的构造函数
        this.type = type;
    }

    //重写父类方法
    @Override   
    public void speak() {
        System.out.println("汪汪");
    }

    //创建子类的新方法
    public void fetch() {
        System.out.println("捡球");
    }
}
```

使用：

```java
Dog dog = new Dog(age, price, type);

dog.speak();  // 调用 Dog 重写后的方法
dog.fetch();  // 调用 Dog 自己的方法
```

要点：

- 一个类只能直接继承一个父类。
- 子类可以直接使用父类的 `public`、`protected` 成员，`private` 成员不能被子类直接访问；
- 子类可以重写父类方法，使用 `@Override` 标记；
-  `super` 关键字用于调用父类中对子类可见的的成员或方法。  
如： 
    - 构造函数中通过`super(……)`调用父类的构造方法,且必须写在第一行；
    - 无论子类中父类的方法是否重写，成员是否同名重新赋值，子类总中可以通过`super.method()`、`super.item`调用父类的方法和成员。Btw，`private`依然无法访问。

---

### 5.2 接口（`interface` 与 `implements`）

接口表示一种能力或功能规范，规定实现类必须提供哪些方法。  

声明接口
```java
interface Speakable {
    void speak();
}
```

接入并实现接口：

```java
class Dog implements Speakable {
    @Override
    public void speak() {
        System.out.println("汪汪");
    }
}
```

使用：

```java
Speakable animal = new Dog();
animal.speak();
```

要点：

- 接口中的普通方法通常只有声明，没有具体实现；
- 一个接口内可以声明多个方法，但在逻辑和工程上要恰当；
- 实现类必须实现这些方法，并且方法必须是 `public`；
- 接口主要描述“能做什么”，不负责描述对象的具体身份；
- 一个类可以实现多个接口。

```java
class Robot implements Speakable, Runnable {
    // 实现多个接口
}
```
- 另外需要注意，当同时使用继承和接口构建一个新的类型时，声明格式如下：

```java
class Dog extends Animal implements Runnable {  //要求先继承后接口
    //继承、重写、新建、实现接口……
}
```

---

### 5.3 多态调用

多态指：**父类或接口类型的引用，可以指向子类或实现类对象；调用同名方法时，实际执行对象对应的版本。**  

#### 5.3.1. 父类继承

```java
class Cat extends Animal {
    @Override
    public void speak() {
        System.out.println("喵喵");
    }
}

class Dog extends Animal {
    @Override
    public void speak() {
        System.out.println("汪汪");
    }
}
```

```java
Animal dog = new Dog();
Animal cat = new Cat();

dog.speak();  // 汪汪
cat.speak();  // 喵喵
```

虽然调用形式相同：

```java
animal.speak();
```

但会根据实际对象执行不同的实现。

也可以将多态用于方法参数：

```java
public static void makeSound(Animal animal) {
    animal.speak();
}
```

```java
makeSound(new Dog());
makeSound(new Cat());
```

方法本身不需要区分传入的是狗还是猫。

注意：

```java
Animal animal = new Dog();
Dog dog = new Dog();

// animal.fetch();  // 错误：Animal 类型中没有 fetch 方法
dog.fetch();    //正确：dog 是 Dog 类对象，具有其中特有的方法
```

***声明类型决定“可以调用哪些方法”，实际对象类型（new的对象）决定“重写方法执行哪个版本”。***

如果声明为父类，要调用子类特有的方法，需进行类型强转：

```java
if (animal instanceof Dog) {
    Dog dog = (Dog) animal;
    dog.fetch();
}
```

#### 5.3.2. 接口调用
多态调用，类型转换等实现语法同上，不再赘述。  
区别在于接口只针对若干个特定的方法，也只对这些方法有多态的特性。

---

### 5.4 继承与接口的异同

| 对比 | 继承 | 接口 |
|---|---|---|
| 表达关系 | “是什么” | “能做什么” |
| 主要作用 | 复用属性和已有方法 | 规定统一的功能规范 |
| 是否能有具体实现 | 可以 | 普通方法通常没有，`default` 方法可以有 |
| 是否能有普通对象属性 | 可以 | 不能，接口字段默认是常量 |
| 构造函数 | 可以有 | 不能有 |
| 数量限制 | 只能继承一个父类 | 可以实现多个接口 |
| 是否支持多态 | 支持 | 支持 |

- 两者的共同点——多态：

```java
Animal animal = new Dog();
Speakable object = new Dog();
```

都可以使用父类型或接口类型统一调用方法，并根据实际对象执行不同实现。

### 5.5 抽象类（abstract）
抽象类是一种不能直接创建实例的父类，既可以保存子类共有的属性和方法，也可以规定子类必须实现的抽象方法。
```java
abstract class AnimalBase {
    protected String name;

    //有构造方法但不能创建实例
    public AnimalBase(String name) {
        this.name = name;
    }

    // 普通方法：子类可以直接使用
    public void eat() {
        System.out.println(name + "正在吃东西");
    }

    // 抽象方法：子类必须实现
    public abstract void speak();
}

class DogBase extends AnimalBase {
    public DogBase(String name) {
        super(name);
    }

    @Override
    public void speak() {
        System.out.println(name + "：汪汪");
    }
}
```
使用时不能直接创建抽象类对象，但可以用抽象类引用指向具体子类对象：
```java
// AnimalBase animal = new AnimalBase("动物");  // 错误

AnimalBase animal = new DogBase("旺财");
animal.eat();
animal.speak();
```
要点：
- 抽象类可以有成员变量、构造方法和普通方法；
- 抽象方法只有声明，没有方法体，具体子类必须实现；
- 如果子类没有实现全部抽象方法，子类也必须声明为 abstract；
- 抽象类作为父类时，使用方式与普通父类基本相同，只是不能直接创建抽象类实例；
- 可以将抽象类理解为“融合了接口特性的父类”。

# 二、常用函数

## 1. 输入输出

### 1.1. 输入：

#### 1.1.1. 输入基础：使用 `Scanner` 读取控制台输入

```java
import java.util.Scanner; //引入扫描库

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); //创建扫描类
        //实际输入方法
        int age = scanner.nextInt();
        double height = scanner.nextDouble();
        String word = scanner.next();

        scanner.close();
    }
}
```

- 常用输入方法：

    | 方法 | 读取内容 |
    | --- | --- |
    | `nextInt()` | `int` 整数 |
    | `nextLong()` | `long` 整数 |
    | `nextDouble()` | `double` 浮点数 |
    | `next()` | 一个不含空白字符的单词 |
    | `nextLine()` | 一整行文本 |
    | `hasNextInt()` | 判断下一个输入是否为 `int` |

- **注意：** `nextInt()` 与 `nextLine()` 连用时，`nextInt()` 读取数字后会留下行末换行符，紧接着调用 `nextLine()` 时，可能读到空字符串：
    ```java
    Scanner scanner = new Scanner(System.in);

    int age = scanner.nextInt();
    scanner.nextLine();              // 消耗数字后的换行符
    String name = scanner.nextLine();
    ```

### 1.2. 输出：
- 普通输出

```java
System.out.print("Hello");       // 输出后不换行
System.out.println("Java");     // 输出后换行
```

- 格式化输出

    Java 的 `printf` 与 C 的 `printf` 用法接近


