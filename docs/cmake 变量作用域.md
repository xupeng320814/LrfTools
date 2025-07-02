1. CMake�ı������������
CMake�ġ���������C/C++�����������ͬ��������Ŀ¼���͡����������֣�������һ�á�������������

A. Ŀ¼������Directory Scope��
ÿһ��CMakeLists.txt����ÿ��Ŀ¼����ӵ���Լ���������
������add_subdirectory()������Ŀ¼ʱ����Ϊ����Ŀ¼����һ���µ�������
����ʼʱ���Ƹ�Ŀ¼�������еı����ĵ�ǰֵ����֮�󡰱����ǿ����������á�
������Ŀ¼�Ա������޸Ĳ�Ӱ�츸Ŀ¼����֮��Ȼcitation 1��

B. ����������Function Scope��
ÿ����дfunction()ʱ��CMake�ᴴ��һ���µ���ʱ�����������Ҳ�ǡ�ֵ���������ⲿ��
�����ڲ��޸ĵı�����Ĭ�ϲ���Ӱ����������ⲿ������

C. ��������Block Scope��
CMake 3.19+ ֧��block()��endblock()��ȷ��������ֲ���������Ϊ���ƺ���������

2. ��ʱ�����������򳣼�����
�����ɼ���
��һ��CMakeLists.txt�ļ�������������set(VARI xxx)���ı����������̶Ե�ǰĿ¼�ѽ����������к������ݣ�ͬ�ļ��Ͱ�����somename.cmake���ɼ�����
���ݹ���
add_subdirectory������Ŀ¼ʱ������ֵ�ᱻ��������Ŀ¼�����൱�ڿ��ա�����Ŀ¼���Ĳ��ᷴ�����ڸ�Ŀ¼��
includeһ��.cmake�ļ������ڵ�ǰ������ִ�У��������������򣬱���ȫ�ֿɼ���
��ʱ����
�����˵����ʱ������ָ������ĳ��CMakeLists.txt�ļ���set(VARI xxx)���������÷�Χȷʵ�ǵ�ǰĿ¼��ͨ��add_subdirectory�������Ŀ¼�ġ����ο��ա���
�²�Ŀ¼���Լ���scope�������Ӻ���ֵ���ݡ�


set(... PARENT_SCOPE) ����
��ͨ�� set(VAR val) ֻ�ڵ�ǰ������������Ŀ¼������function��������block��������Ч��
���� PARENT_SCOPE�����������ڵ�ǰ��������ģ����ǡ�д�뵽��һ�������򡱣�����Ŀ¼�����ø�function����㣬�������block����㣩��
�����һ���ݹ�д�����ϲ㣬ֻӰ��ֱ�Ӹ�������

set(FOO abc)
function(demo1)
    set(FOO demo1 PARENT_SCOPE)
    message("inside function: ${FOO}")
endfunction()

function(demo2)
    set(FOO demo2)
    message("inside function: ${FOO}")
endfunction()

message("before function: ${FOO}")
demo1()
message("after demo1 function: ${FOO}")
demo2()
message("after demo2 function: ${FOO}")

1> [CMake] before function: abc

set(FOO demo1 PARENT_SCOPE) �����ڡ��������������� FOO������ֱ�Ӱ� FOO ����ֵд�����������
�������������FOO����������������ı�������û�б仯��
1> [CMake] inside function: abc

1> [CMake] after demo1 function: demo1
1> [CMake] inside function: demo2
1> [CMake] after demo2 function: demo1

�����ȷʵ���ú�������ⲿ��ͬ��Ϊ��ֵ������Ҫ������
function(demo1)
    set(FOO �����ڲ�����ֵ)
    message("inside function: ${FOO}")
    set(FOO ${FOO} PARENT_SCOPE)  # �� set(FOO �����ڲ�����ֵ PARENT_SCOPE)
endfunction()