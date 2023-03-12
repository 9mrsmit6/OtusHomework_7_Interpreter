#include <iostream>
#include "Parsing/Parser.hpp"
#include "Analize/Analizer.hpp"

using namespace std;



int main()
{
    Analize::Analizer analyzer;
    Parsing::Parser parser(analyzer);

    parser.parse();

    cout << "Hello World!" << endl;
    return 0;
}
