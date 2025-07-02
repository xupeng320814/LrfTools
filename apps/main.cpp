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
Lt_class()				// Func1�ﴴ���ֲ�����A
					// �������ؾֲ�����/��ʱ����
					//	���ƶ����죨T(T&&)���������ƶ�����Ϊ��ֵ���Ա�����ȫ�ض�ȡ��Դ����
					//	û���ƶ�������˻�Ϊ������T(const T&)����
Lt_class(Lt_class&&)		// returnʱA->B���ֲ�A��move���ⲿB�����ݵ� ret��
~Lt_class()			// A��������move����Ա��B����
Func1 Run During:0 ms
Lt_class(Lt_class&&)		// ret move�� main ���lt��B->C��
~Lt_class() // ret(B)����
Lt_class(const Lt_class&)	// ����Func2(lt): ����lt���ã�����װretʱ����һ�ο�����main��lt->D��
Func2 Run During:0 ms
Lt_class(Lt_class&&)		// ret move��main��lt2��D->E�������������������Ӧ�޴˲�����ʵ����auto��RVOʧЧ���Ի��ӵ���
~Lt_class()			// ret(E)����
~Lt_class()			// main���lt2����
~Lt_class()			// main���lt����
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