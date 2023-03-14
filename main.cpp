#include <iostream>
#include "Parsing/Parser.hpp"
#include "Analize/Analizer.hpp"

using namespace std;



int main()
{
    Analize::Analizer analyzer{5};
    Parsing::Parser parser{analyzer};


//    auto printer = std::make_shared<Analize::Printer>();

//    analyzer.addListener(printer);



//    parser.parse();

    cout << "Hello World!" << endl;
    return 0;
}
