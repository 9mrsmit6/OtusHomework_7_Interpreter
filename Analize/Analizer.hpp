#ifndef ANALIZER_HPP
#define ANALIZER_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"


namespace Analize
{
    struct Analizer
    {
        void execute ( std::unique_ptr<Parsing::ParserCommand>&& cmd )
        {

        }
    };
}

#endif // ANALIZER_HPP
