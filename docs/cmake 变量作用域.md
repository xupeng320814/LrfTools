
---

# CMake 变量作用域、PARENT_SCOPE 及 Cache 机制详解

CMake 的变量作用域与 C/C++ 语句块作用域区别较大，其本质是一棵“作用域树”，每个目录（CMakeLists.txt）、函数和 block（3.19+）都形成新的作用域。

---

## 1. 作用域分类

### 1.1 目录作用域（Directory Scope）

- 每个 `CMakeLists.txt`（即每个目录）都有独立作用域。
- 当用 `add_subdirectory()` 进入子目录，会为子目录创建新作用域。
  - 子目录的初始变量“值拷贝”自父目录，**两者后续互不影响**。

> 目录作用域本质上类似于一棵树，每次 add_subdirectory 都是以“父作用域快照”作为新子作用域起点。

---

### 1.2 函数作用域（Function Scope）

- 每次 `function()` 都会新建临时作用域。
  - 作用域初始化时，也是“值拷贝”机制。
  - 函数内部变量的修改，**默认不影响外部作用域**。

---

### 1.3 块作用域（Block Scope）

- CMake 3.19+ 支持 `block()/endblock()`。
  - 与函数机制几乎相同：新建临时作用域，变量只在 block 内部有效。

---

## 2. 变量可见性与传递规则

### 2.1 变量可见性

- `set(VAR xxx)` 声明的变量，对**当前 CMakeLists.txt 及此后的 include 进来的 .cmake 文件**可用。
- `include(xxx.cmake)` 不新建作用域，所有变量和外部“共用”。

---

### 2.2 变量的传递机制

- `add_subdirectory()` 进入子目录时：  
  子目录拿到的是父目录变量的“快照”，此后相互独立。
- 包含层级类似参数值传递，非引用传递。

---

## 3. set(... PARENT_SCOPE) 机制

- 基本 `set(VAR val)`：只在本地作用域生效。
- `set(VAR val PARENT_SCOPE)`：不是在本地作用域设置变量，而是**直接写到上一层作用域**：
  - 目录作用域，则写到父目录；
  - 函数作用域，写到调用这个 function 的外层作用域；
  - block，写到包裹 block 的外层作用域。
- **不会递归传递**，仅影响直接父作用域。

#### 3.1 例子演示

```cmake
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
```

**输出：**
```
before function: abc
inside function: abc
after demo1 function: demo1
inside function: demo2
after demo2 function: demo1
```

**说明：**
- `set(... PARENT_SCOPE)` 时，本地 FOO 没变，但父作用域 FOO 已改变。
- 真正“同步”为新值，需要**先 set(FOO xx) 再 set(FOO xx PARENT_SCOPE)**。

---

## 4. 临时变量与作用范围说明

- `CMakeLists.txt` 或 function/block 内用 set 设置的变量，只在该作用域内生效。
- 下层目录或函数 block 都是“值拷贝”，改动不会影响父层。

---

## 5. CMake Cache 变量

CMake 的 Cache 变量拥有更强大的作用域和生命周期：

### 5.1 基本特点

- **全局可见**：任何目录、函数、块都能访问。
- **持久化**：持久存储在构建目录的 `CMakeCache.txt` 文件中，跨多次 CMake 执行均可用。
- 主要用于**与用户/环境交互**，或保存工程构建开关等。
- 用于 `option`、`ccmake`、`cmake-gui` 配置界面参数持久化。

#### 5.2 普通变量与 Cache 变量区别表

|                 | 普通变量                               | Cache变量                               |
|:----------------|:---------------------------------------|:----------------------------------------|
| 作用域          | 目录/函数/块级，随作用域变化           | **全局**，整个 CMake 项目均可访问       |
| 持久性          | 不持久，仅当前进程/解析时有效           | **持久**，`CMakeCache.txt`中持久储存    |
| 层级可见性      | 当前及 add_subdirectory 继承为快照      | 整理目录、全局和作用域均可获取          |
| 修改规则        | 后 set() 覆盖前 set                    | 除非 FORCE，只第一次 set 有效           |
| 是否暴露        | 不暴露给用户                           | 可在 ccmake/cmake-gui 等界面交互设置    |

#### 5.3 Cache 变量用法示例

```cmake
set(MYFEATURE ON CACHE BOOL "是否启用自定义功能")
```

---

## 6. 总结及实用建议

- CMake 变量是**树状层级作用域**，不同层级变量互为“值拷贝”，避免了隐式联动带来的副作用。
- `PARENT_SCOPE` 做有限一层的作用域写回，可手动管理同步。
- **Cache 变量才是唯一全局+持久性变量袋**，推荐专用于跨不同 CMakeLists.txt、界面选项等场景。
- 善用作用域和 cache，能极大提升大型工程的复杂参数组合和构建可维护性。

---