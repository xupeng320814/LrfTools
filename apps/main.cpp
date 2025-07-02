#include "Lt_time.h"
#include "Lt_class.h"
#include <iostream>

Lt_class Func1()
{
	Lt_class lt;
	return lt;
}

Lt_class& Func2(Lt_class& lt)
{
	return lt;
}

int main()
{
	std::cout << Lt_time_GetMs() << std::endl;
	Lt_class lt = Lt_time_DuringMs_t(Func1);
	Lt_class& lt2 = Lt_time_DuringMs_t(Func2, lt);
	return 0;
}

/*
Lt_class()				// Func1里创建局部对象A
					// 函数返回局部变量/临时对象：
					//	有移动构造（T(T&&)）优先用移动，因为右值可以被“安全地夺取资源”。
					//	没有移动构造就退化为拷贝（T(const T&)）。
Lt_class(Lt_class&&)		// return时A->B，局部A被move到外部B（传递到 ret）
~Lt_class()			// A析构（已move，成员跟B共享）
Func1 Run During:0 ms
Lt_class(Lt_class&&)		// ret move到 main 里的lt（B->C）
~Lt_class() // ret(B)析构
Lt_class(const Lt_class&)	// 调用Func2(lt): 返回lt引用，但封装ret时调用一次拷贝（main的lt->D）
Func2 Run During:0 ms
Lt_class(Lt_class&&)		// ret move到main的lt2（D->E），理论上如果是引用应无此操作，实际由auto、RVO失效特性混杂导致
~Lt_class()			// ret(E)销毁
~Lt_class()			// main里的lt2析构
~Lt_class()			// main里的lt析构
*/

/*
* //Release
Lt_class()
Lt_class(Lt_class&& other)
~Lt_class()
Func1 Run During:0 ms
Lt_class(const Lt_class& other)
Func2 Run During:0 ms
~Lt_class()
~Lt_class()
*/