#ifndef STATES_HPP
#define STATES_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"
#include "../Data/Block.hpp"

namespace Analize
{

//    enum class BlockAnalizeStates
//    {
//        Basic=0,
//        StaticBlock,
//        DynamicBloc,
//        Skip
//    };


//    BlockAnalizeStates basicStateHandler(std::unique_ptr<Data::Block>& block, Parsing::ParseCommand& cmd, std::size_t staticBlockSize )
//    {
//        auto& [cmdInfo, payload]=cmd;

//        if(cmdInfo==Parsing::Lexeme::Command)
//        {
//            block=std::make_unique<Data::Block>(3);
//            return BlockAnalizeStates::StaticBlock;
//        }

//        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
//        {
//            block=std::make_unique<Data::Block>();
//            return BlockAnalizeStates::DynamicBloc;
//        }

//        return BlockAnalizeStates::Basic;
//    }

//    struct State
//    {
//        State() = default;
//        ~State() = default;

//        virtual  void execute ( std::unique_ptr<Parsing::ParserCommand>&& cmd ) = 0;
//    };

//    struct StateBase: public State
//    {

//    };
}

#endif // STATES_HPP
