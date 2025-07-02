1. CMake的变量作用域分类
CMake的“作用域”与C/C++的语句作用域不同，它按“目录”和“函数”划分，本质是一棵“作用域树”：

A. 目录作用域（Directory Scope）
每一个CMakeLists.txt（即每个目录）都拥有自己的作用域。
当调用add_subdirectory()进入子目录时，会为该子目录创建一个新的作用域，
它初始时复制父目录作用域中的变量的当前值，但之后“变量是拷贝而非引用”
——子目录对变量的修改不影响父目录，反之亦然citation 1。

B. 函数作用域（Function Scope）
每当你写function()时，CMake会创建一个新的临时作用域，其变量也是“值拷贝”自外部。
函数内部修改的变量，默认不会影响调用它的外部作用域。

C. 块作用域（Block Scope）
CMake 3.19+ 支持block()和endblock()明确创建额外局部作用域，行为类似函数作用域。

2. 临时变量和作用域常见误区
变量可见性
在一个CMakeLists.txt文件中声明（例如set(VARI xxx)）的变量，“立刻对当前目录已解析到的所有后续内容（同文件和包含的somename.cmake）可见”。
传递规则
add_subdirectory引入子目录时，变量值会被拷贝到子目录，“相当于快照”，子目录更改不会反作用于父目录。
include一个.cmake文件，会在当前作用域执行，不产生新作用域，变量全局可见。
临时变量
如果你说“临时变量”指的是在某个CMakeLists.txt文件中set(VARI xxx)，它的作用范围确实是当前目录及通过add_subdirectory进入的子目录的“初次快照”。
下层目录有自己的scope，类似子函数值传递。


set(... PARENT_SCOPE) 作用
普通的 set(VAR val) 只在当前作用域（无论是目录作用域、function作用域还是block作用域）生效。
加上 PARENT_SCOPE，变量不会在当前作用域更改，而是“写入到上一层作用域”（即父目录、调用该function的外层，或包裹本block的外层）。
不会进一步递归写到上上层，只影响直接父作用域

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

set(FOO demo1 PARENT_SCOPE) 不是在“本地作用域”设置 FOO，而是直接把 FOO 的新值写回外层作用域。
但本地作用域的FOO（即函数作用域里的变量表）并没有变化！
1> [CMake] inside function: abc

1> [CMake] after demo1 function: demo1
1> [CMake] inside function: demo2
1> [CMake] after demo2 function: demo1

如果你确实想让函数里和外部都同步为新值，你需要两步：
function(demo1)
    set(FOO 函数内部的新值)
    message("inside function: ${FOO}")
    set(FOO ${FOO} PARENT_SCOPE)  # 或 set(FOO 函数内部的新值 PARENT_SCOPE)
endfunction()