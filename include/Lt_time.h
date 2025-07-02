#pragma once
#include <cstdint>
#include <chrono>
#include <utility>

extern uint64_t Lt_time_GetMs();

template<typename F, typename... Args>
auto Lt_time_DuringMs(F&& f, const char* name, Args&&... args)
{
        using namespace std::chrono;
        auto __begin = steady_clock::now();

        //std::forward<F>, 根据F的推导, 把f“正确地”转发出来（保留左值/右值/const等所有属性）
        //触发的是移动构造？
        auto ret = std::forward<F>(f)(std::forward<Args>(args)...);
        auto __end = steady_clock::now();

        std::cout << name << " Run During:"
                << duration_cast<milliseconds>(__end - __begin).count()
                << " ms" << std::endl;
        return ret;
}

#define Lt_time_DuringMs_t(Func, ...) \
    Lt_time_DuringMs(Func, #Func, __VA_ARGS__)