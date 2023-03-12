#ifndef STATES_HPP
#define STATES_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"

namespace Analize
{
    struct State
    {
        State() = default;
        ~State() = default;

        virtual  void execute ( std::unique_ptr<Parsing::ParserCommand>&& cmd ) = 0;
    };

    struct StateBase: public State
    {

    };
}

#endif // STATES_HPP
