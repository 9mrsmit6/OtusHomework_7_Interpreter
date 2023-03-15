#include "Analizer.hpp"

namespace Analize
{

    BlockAnalizeStates Analizer::handlerBasic( Parsing::ParseCommand& cmd)
    {

        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {
            block=std::make_unique<Data::Block>(stBlockSize);
            return BlockAnalizeStates::StaticBlock;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            block=std::make_unique<Data::Block>();
            return BlockAnalizeStates::DynamicBloc;
        }

        return BlockAnalizeStates::Basic;

    }


    BlockAnalizeStates Analizer::handlerStaticBlock( Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {
            block->push(std::move(payload));
            return BlockAnalizeStates::StaticBlock;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            executeListeners();
            block=std::make_unique<Data::Block>();
            return BlockAnalizeStates::DynamicBloc;
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            executeListeners();
            return BlockAnalizeStates::Basic;
        }

        return BlockAnalizeStates::StaticBlock;
    }


    BlockAnalizeStates Analizer::handlerDynamicBlock( Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {
            block->push(std::move(payload));
            return BlockAnalizeStates::DynamicBloc;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            return BlockAnalizeStates::Skip;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
        {
            executeListeners();
            return BlockAnalizeStates::Basic;
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            executeListeners();
            return BlockAnalizeStates::Basic;
        }

        return BlockAnalizeStates::DynamicBloc;

    }


    BlockAnalizeStates Analizer::handlerSkip( Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
        {
            return BlockAnalizeStates::DynamicBloc;
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            executeListeners();
            return BlockAnalizeStates::Basic;
        }

        return BlockAnalizeStates::Skip;
    }

}
