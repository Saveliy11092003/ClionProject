#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

using namespace std;
//6) с помощью using namespace std можно не писать std::cout
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "RUS");

    //Убедился и проверил 1 и 2 пункты
    cout <<  "Hello world!" << "\n";

    cout << Module1::getMyName() << "\n";
    cout << Module2::getMyName() << "\n";

    using namespace Module1;
    cout << getMyName() << "\n"; // (A)
    //3.1)На экран выведется John, потому что using namespace Module1 позволяет пользоваться getMyName() из namespace Module1,
    //а в этой функции выводится John
    cout << getMyName() << "\n";

    //4) Строки ниже приводят к конфликту имен, так как подключены namespace Module1, namespace Module2, в которых есть функции,
    // с одинаковыми названиями(getMyName())
    //using namespace Module2; // (B)
    //std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)
    //чтобы исправить ошибку нужно указать к какой именно функции хотим обратится, сделать это можно с помощью Module2::getMyName()

    using namespace  Module2; // (B)
    cout << Module2::getMyName() << "\n"; // COMPILATION ERROR (C)

    using Module2::getMyName;
    cout << getMyName() << "\n"; // (D)
    //3.2)На экран выведется James, потому что using Module2::getMyName позволяет пользоваться getMyName() из namespace Module2,
    //а в этой функции выводится James

    using namespace  Module3;
    cout << Module3::getMyName()<< "\n";

}
