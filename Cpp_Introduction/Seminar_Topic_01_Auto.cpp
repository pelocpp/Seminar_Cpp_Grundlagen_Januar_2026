// =====================================================================================
// Auto.cpp // Keyword 'auto'
// =====================================================================================

#include <cstddef>
#include <map>
#include <print>
#include <vector>

namespace Auto_Examples {

    // ----------------------------------------------------------------------

    static void test_01() {


        auto x = 123;

        auto y = 123.345f;   // Type Deduction

















        // type deduction / type inference

        auto a = 1;                  // int
        auto b = 7ul;                // unsigned long
        auto c = 2.0;                // double
        auto d = 2.0f;               // float
        auto e = 'A';                // char

        auto f = "hi";               //  const char*   // Da gab es schon in C: Anfangsadresse

        auto g = true;               // bool

        auto list = { 1, 2, 3 };     // std::initializer_list<int>

        // C++ 14 and above we have std::string_literals
        using namespace std::string_literals;    //  necessary (!)
        auto st = "hello"s;          // std::string, note the s operator

        // C++ 23 and above we have size_t and signed size_t
        // Not yet supported from Visual C++
        // auto k = 1uz;             // size_t
        // auto m = 1z;              // signed size_t
    }

    // ---------------------------------------------------------------------

    static std::map<int, std::string> getFunction() {

        return {};
    }

    static void test_02() {

        auto n{ 123 };                   // n is type of int

        auto result = getFunction();    // result is type of ...

        std::map<int, std::string> result2{
            getFunction()
        };
    }

    // ---------------------------------------------------------------------

    static void test_03() {

        // Dictionary // Binärer Baum // (Schlüssel/Wert) // std::pair<int, std::string>
        std::map<int, std::string> anotherMap{ { 1, "Hello"  } };

        std::map<int, std::string>::iterator it = anotherMap.begin();

        // A) KOPIE B) Typkonvertierung:  const int ==> int
        //std::pair<int, std::string>& entry1 = *it;  // Why this line DOES NOT compile ???

        auto& entry2 = *it;
    }

    // ---------------------------------------------------------------------

    static auto sum(float f1, float f2)
    {
        return f1 + f2;    // 2 Mal Max-Float: Überlauf // UB // Undefined Behaviour
    }

    // Die Breite des int-Datentyps in C/C++ ist implementierungsabhängig
    static auto sum2Creepy(short s1, short s2)
    {
        return s1 + s2;    // 2 Mal Max-Float: Überlauf // UB // Undefined Behaviour
    }

    static auto sum2Real(int i1, int i2)
    {
        return i1 + i2;    // 2 Mal Max-Float: Überlauf // UB // Undefined Behaviour
    }



    // Kann eine CPU mit 16-Bit Werten rechnen // Arithmetik betreiben: +, *,...
    // NEIN.
    // CPU: Rechenregister: Akkumulator (anhäufen)
    // Bit-Breite:  64-Bit Rechner



    static auto foo(bool flag, float f, double d) -> double
    {
        if (flag) {
            return f;
        }
        else {
            return d;
        }
    }

    // type of the ternary ?: expression is the common type
    // of its second and third argument
    // (if both types are the same, you get a reference back)
    static auto moreFoolish(bool flag, float f, double d)
    {
        return (flag) ? f : d;
    }

    static void test_04() {

        auto result = sum(1.0, 2.0);                           // float

        auto value = foo(true, 123, 123.456);                  // double

        auto anotherValue = moreFoolish(true, 123, 123.456);   // double
    }

    // ---------------------------------------------------------------------

    class Contact
    {
        std::string m_name;
        size_t m_number;

    public:
        Contact() : m_name{}, m_number{} {}

        auto getName() const { return m_name; }
        auto getMobileNumber() const { return m_number; }
    };

    // ---------------------------------------------------------------------

    static auto make_planet()
    {
        struct Planet
        {
            std::string name;
            int moons;
            bool rings;
        };

        return Planet{ "Saturn", 82, true };
    }

    static void test_05() {

        // using automatic return type deduction
        auto planet{ make_planet() };
        std::println("{} {} {}", planet.name, planet.moons, planet.rings);

        // using automatic return type deduction & structured binding
        auto [name, num_moons, has_rings] = make_planet();
        std::println("{} {} {}", name, num_moons, has_rings);
    }

    // ---------------------------------------------------------------------

    class Person
    {
    private:
        std::string m_name;   // Vor fremdem Zugriff schützen

    public:
        // c'tor
        Person (const std::string& name) 
            : m_name(name) 
        {}

        // getter
        // go for this style
        const std::string& getName() {
            return m_name; 
        }

        // Hmmm, da wird eine KOPIE zurückgegeben
        std::string getNameAlternate() {
            return m_name;
        }
    };

    void test_loss_of_reference()
    {
        Person hans("Hans");   // STACK 
                               // Wo liegt der Name: Auch auf dem Stack

        const std::string& s = hans.getName();
        // s[0] = 'h';
        char first = s[0];
    }

    void test_loss_of_reference_there_is_more()
    {
        Person hans("Hans");

        auto name2 = hans.getName();

        const auto& name = hans.getName();
       // name[0] = 'h';
    }






    const std::string message{ "This is an important message :)" };

    static const std::string& getMessage()
    {
        return message;
    }

    static void test_06() {

        auto msg1{ getMessage() };
        std::println("Message: {}", msg1);

        // but:
        const auto& msg2{ getMessage() };
        std::println("Message: {}", msg2);

        // Ohhh:
        auto& msg3{ getMessage() };
        std::println("Message: {}", msg3);

        // or:
        decltype(getMessage()) msg4{ getMessage() };
        std::println("Message: {}", msg4);

        // once again 'or':
        decltype(auto) msg5{ getMessage() };
        std::println("Message: {}", msg5);
    }

    // ---------------------------------------------------------------------

    static decltype(auto) getFirstCharacter(const std::string& s)
    {
        return s[0];
    }

    static void test_07()
    {
        auto ch1{ getFirstCharacter(std::string{ "ABC" }) };

        decltype(auto) ch2{ getFirstCharacter(std::string{ "ABC" }) };
    }

    // ---------------------------------------------------------------------

    static int f() { return 0; }

    static void test_08()
    {
        decltype(f()) i{ 1 };                 // i is integer

        std::vector<decltype(f())> v;         // vector<int>, cannot be done with auto
    }

    static int& g(int& i) { return ++i; }

    static void test_09()
    {
        int x{ 10 };

        auto i{ g(x) };      // i gets a copy of f(10) ==> 11

        auto& j{ g(x) };     // j is a reference to x  ==> 12
    }

    // ---------------------------------------------------------------------

    template <typename TReturn, typename T1, typename T2>
    TReturn add1(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename T1, typename T2, typename TReturn>
    TReturn add2(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename TReturn = long, typename T1, typename T2>
    TReturn add3(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    static void test_10()
    {
        // works - specifying all template parameters
        auto result{ add1<long, int, int>(10, 20) };

        // works too - only the return template parameter type needs to be specified
        auto result1{ add1<long>(10, 20) };

        // doesn't work too - return template parameter is at wrong position
        // auto result2{ add2<long>(10, 20) };

        // works too - no template parameter type needs to be specified
        auto result3{ add3(10, 20) };
    }
}

void main_auto()
{
    using namespace Auto_Examples;

    test_loss_of_reference_there_is_more();
   // test_loss_of_reference();
    return;
    

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
