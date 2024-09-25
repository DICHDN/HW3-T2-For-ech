/*
Задание 2
For_each
Реализуйте параллельный вариант оператора for_each.
Функция должна принимать итераторы на начало и конец контейнера и ссылку, обрабатывающую функцию.
При реализации нужно рекурсивно разделить контейнер на несколько блоков и для каждого запустить отдельную задачу,
    применяющую обрабатывающую функцию к части контейнера.
*/


#include <random>
#include <iostream>
#include <vector>
#include <thread>


void parallel_for_each(std::vector<int>::iterator begin, std::vector<int>::iterator end,void (*func)(int&)) 
{
    const size_t size = std::distance(begin, end);
    if (size < 21) 
    { 
        for (; begin != end; ++begin) {
            func(*begin);
        }
        return;
    }
    const size_t mid = size / 2;
    std::thread t1(parallel_for_each, begin, begin + mid, func);
    parallel_for_each(begin + mid, end, func);
    t1.join();
}

void random_int(int& x)
{
    /* вариант на модификацию
    int a = rand() % 100;
    x = a;
    */

    //вариант на чтение
    std::cout << x << " ";
}

int main() 
{
    std::vector<int> v(22, 0);
    for (int x : v) 
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;    
    parallel_for_each(v.begin(), v.end(), random_int);
    std::cout << std::endl;
    return 0;
}