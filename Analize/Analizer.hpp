#ifndef ANALIZER_HPP
#define ANALIZER_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"


namespace Analize
{


    enum class BlockAnalizeStates
    {
        Basic=0,
        StaticBlock,
        DynamicBloc
    };

    struct AnalizerListener
    {
        virtual void newBlockreceived()=0;
    };

    struct Analizer
    {

        Analizer(const std::size_t stBlockSize_):
            stBlockSize(stBlockSize_)
        {}

        void execute ( Parsing::ParseCommand cmd )
        {

            auto& [cmdInfo, payload]=cmd;

            switch(currentState)
            {
                case BlockAnalizeStates::Basic:
                    if(cmdInfo==Parsing::Lexeme::Command)
                    {
                        currentState=BlockAnalizeStates::StaticBlock;
                    }

                    if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
                    {
                        currentState=BlockAnalizeStates::DynamicBloc;
                    }

                    break;
                case BlockAnalizeStates::StaticBlock:
                    break;
                case BlockAnalizeStates::DynamicBloc:
                    break;
                default:
                    currentState=BlockAnalizeStates::Basic;
                    break;
            }
        }

    private:
        BlockAnalizeStates currentState{BlockAnalizeStates::Basic};
        const std::size_t stBlockSize;

    };
}

#endif // ANALIZER_HPP
