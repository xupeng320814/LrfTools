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

        //std::forward<F>, ����F���Ƶ�, ��f����ȷ�ء�ת��������������ֵ/��ֵ/const���������ԣ�
        //���������ƶ����죿
        auto ret = std::forward<F>(f)(std::forward<Args>(args)...);
        auto __end = steady_clock::now();

        std::cout << name << " Run During:"
                << duration_cast<milliseconds>(__end - __begin).count()
                << " ms" << std::endl;
        return ret;
}

#define Lt_time_DuringMs_t(Func, ...) \
    Lt_time_DuringMs(Func, #Func, __VA_ARGS__)