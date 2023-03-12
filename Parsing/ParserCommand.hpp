#ifndef PARSERCOMMAND_HPP
#define PARSERCOMMAND_HPP


#include <string>
#include <utility>
#include <memory>

namespace Parsing
{
    enum class Lexeme
    {
        Command,
        DynamicBlockStart,
        DynamicBlockStop,
        EndOfFile
    };

    struct ParserCommand
    {
        ParserCommand(Lexeme lex):
            lexeme{lex},
            payload{nullptr}
        {}

        ParserCommand(Lexeme lex, std::unique_ptr<std::string>& payload_):
            lexeme{lex},
            payload{std::move(payload_)}
        {}

        ~ParserCommand() = default;


        Lexeme lexeme;
        std::unique_ptr<std::string> payload;
    };
}


#endif // PARSERCOMMAND_HPP
