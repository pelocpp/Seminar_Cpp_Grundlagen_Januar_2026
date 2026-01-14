
#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <string>
#include <vector>

// TODO: Das mit dem 'int' besser machen 

template <typename ... TArgs>    // TArgs: type pack
auto addierer(TArgs ... args)    //  args: values pack
{
    // "auspacken": Initializer List
    std::initializer_list<int> list = { args ... };   // auspacken

    int sum{};

    std::for_each(
        list.begin(), 
        list.end(),
        [&](int value) {
            sum = sum + value;
        }
    );

    return sum;
}

template <typename T, typename ... TArgs>
T addiererImproved(T first, TArgs ... args)
{
    // "auspacken": Initializer List
    std::initializer_list<int> list = { args ... };   // auspacken

    T sum{ 0 };

    std::for_each(
        list.begin(),
        list.end(),
        [&](int value) {
            sum = sum + value;
        }
    );

    return sum;
}


template <typename ... TArgs>    // TArgs: type pack
auto addiererFolding(TArgs ... args)    //  args: values pack
{
    int sum{};

    //    (... op pack)
    sum = (... +  args);

    return sum;
}

// C++ 20
auto addiererFoldingVeryModern(auto ... args) 
{
    int sum{};

    sum = (... + args);

    return sum;
}


auto subtrahiererFolding(auto ... args)
{
    int result{};

    // (1 - 2) - 3 = -4
    // 1 - (2 - 3) = +2 

    result = (args - ...);

    return result;
}

void printer(auto ... args)
{
    // (((init op pack1) op pack2) op ...) op packN
    // init: Wahlfreies Objekt

    // ((std::cout << 1) << 2) << 3;

    (std::cout << ... << args);
}

void main_variadic_templates_01()
{
    // Aufruf:
    // Es wird eine flexible Menge an Parametern "eingepackt"
    int sum = addierer(1, 2, 3, 4, 5, 6, 7, 8);

    sum = addiererImproved(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    sum = addiererFolding(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    sum = addiererFoldingVeryModern(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    int result = subtrahiererFolding(1, 2, 3);

    printer(1, 2, 3, 4, 5, 6, 7, 8);
}

void main_variadic_templates()
{
    main_variadic_templates_01();
}
