#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParserCommand.hpp"
#include <memory>
#include <iostream>
#include <utility>

namespace Parsing
{
    template<class A>
    struct Parser
    {
        Parser(A& analyzer_):
            analyzer{analyzer_}
        {}

        void parse()
        {

            while(true)
            {
                if(std::cin.eof())
                {
                    analyzer.execute(     std::make_unique<ParserCommand>(  Lexeme::EndOfFile ));
                    return;
                }

                auto s=std::make_unique<std::string>();
                std::getline(std::cin, *s);

                testSimpleCmd(*s, "{", Lexeme::DynamicBlockStart);
                testSimpleCmd(*s, "}", Lexeme::DynamicBlockStop);

                analyzer.execute(     std::make_unique<ParserCommand>(  Lexeme::Command, s ));

            }

        }
    private:
        A& analyzer;

        void testSimpleCmd(const std::string& input, const std::string l, const Lexeme cmd)
        {
            if(input==l)
            {
                analyzer.execute(     std::make_unique<ParserCommand>(  cmd ));
            }
        }
    };
}

#endif // PARSER_HPP
