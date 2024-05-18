#include <iostream>

const char* strShell(const char* str1, const char* str2) {
    return strstr(str1, str2);
}

const char* strImitate(const char* str1, const char* str2) {
    char* cp = (char*)str1;
    char* s1, * s2;

    if (!*str2)
        return((char*)str1);

    while (*cp)
    {
        s1 = cp;
        s2 = (char*)str2;

        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;

        if (!*s2)
            return(cp);

        cp++;
    }

    return(NULL);
}

char string1[255];
char string2[255];

void inputChar() {
    std::cout << "Input first str: ";
    std::cin >> string1;
    std::cout << "Input second str: ";
    std::cin >> string2;
}

void print() {
    std::cout << "First str: " << string1 << "\n";
    std::cout << "Second str: " << string2 << "\n";
}

int main()
{
    inputChar();
    print();
    std::cout << "-----------------\n";
    std::cout<<"result of strstr(): "<< strShell(string1, string2) << "\n";
    std::cout << "result of imitation: " << strImitate(string1, string2);

    std::cin;
}
