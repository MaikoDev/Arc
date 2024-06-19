#include <iostream>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
