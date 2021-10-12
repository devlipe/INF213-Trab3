#include <iostream>

int main(int argc, char const *argv[])
{
    char a = 0;
    char b = ' ';
    char c = 0;
    char d = '\0';

    std::cout << a << "-" << b << "-" << c << "-" << d << std::endl;

    std::cout << (a == b) << " " << (a == c) << (a == c) << std::endl;

    char s = 0;
    for (int i = 0; i < 256; i++)
    {

        std::cout << i << "|" << s << "|" << std::endl;
        s = s + 1;
    }

    return 0;
}
