### 函数指针

 如果在程序中定义了一个函数，那么在编译时系统就会为这个函数代码分配一段存储空间，这段存储空间的首地址称为这个函数的地址。而且函数名表示的就是这个地址。既然是地址我们就可以定义一个指针变量来存放，这个指针变量就叫作函数指针变量，简称函数指针。 

定义方式

```c++
int(*p)(int,int);//定义一个指向函数的指针p 前面的int表示返回int类，后面两个int是形参
函数返回值类型 (* 指针变量名) (函数参数列表);

//函数重载时运用
int add(int a,int b)
{
    return a+b;
}
int add()
{
    return 12138;
}
int(*sth)(int,int)=add;
int(*nothing)()=add;

int main()
{
    int(*sth)(int,int)=add;
	int(*nothing)()=add;
    cout<<"有形数："<<(*sth)(10,20)<<endl;
    cout<<"无形参"<<(*nothing)()<<endl;
    return 1;
}
```

### Lambda表达式  匿名函数对象

 lambda 表达式是一种匿名函数，即没有函数名的函数；该匿名函数是由数学中的λ演算而来的。通常情况下，lambda函数的语法定义为：

```c++
[capture] (parameters) mutable ->return-type {statement} 
//capture：捕捉列表-捕捉上下文中变量以使用
//parameters：参数列表-形参-如果不需要参数传递可以连括号一起省略
//mutable：使捕捉对象可更改取消其const常量性质
//return-type：返回类型
//statement：函数体
int main()
{
    int a=1,b=2,c=3;
    auto lam=[=]() mutable->int
    {
        a++;b++; c++;return a+b+c;
    }
    cout<<a+b+c<<endl;
    cout<<lan();
    return 1;
}
```

C++11增加的新特性，项目文件：CONFIG+=C++11		

Qt中配合信号使用非常方便

```c++
    connect(b2,&QPushButton::released,
            // =：将外部所有局部变量、类中所有成员以值传递方式传入
            //mutable:可变的 允许变量被修改
            //this:类中所有成员以值传递方式传入
            //&:引用符号
            [=]() mutable
            {
                b2->setText("已经修改");
                qDebug()<<a;
                a=0;
            }
            );
```