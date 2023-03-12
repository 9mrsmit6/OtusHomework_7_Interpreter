#include <iostream>
#include "Parsing/ParserCommand.hpp"

using namespace std;



int main()
{
    std::string str{"VAX"};

    auto v=std::make_unique<std::string>("DDD");

    Parsing::ParserCommand testCmd{Parsing::Lexeme::Command};
    Parsing::ParserCommand testCmd2{Parsing::Lexeme::DynamicBlockStart, v};

    cout << "Hello World!" << endl;
    return 0;
}
