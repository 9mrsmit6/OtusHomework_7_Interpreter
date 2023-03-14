#include "Analizer.hpp"

namespace Analize
{


    template <BlockAnalizeStates in, BlockAnalizeStates base>
    concept TypeSelector = (in==base);


//    template<BlockAnalizeStates current>
//    BlockAnalizeStates handler( Parsing::ParseCommand& cmd);

//     requires TypeSelector <current,BlockAnalizeStates::Basic>

    template<BlockAnalizeStates current>
    BlockAnalizeStates Analizer::handler( Parsing::ParseCommand& cmd) requires TypeSelector <current,BlockAnalizeStates::Basic>
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

//    template<>
//    BlockAnalizeStates Analizer::handler<BlockAnalizeStates::StaticBlock>( Parsing::ParseCommand& cmd)
//    {
//        auto& [cmdInfo, payload]=cmd;

//        if(cmdInfo==Parsing::Lexeme::Command)
//        {
//            block->push(std::move(payload));
//            return BlockAnalizeStates::StaticBlock;
//        }

//        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
//        {
//            executeListeners();
//            block=std::make_unique<Data::Block>();
//            return BlockAnalizeStates::DynamicBloc;
//        }

//        if(cmdInfo==Parsing::Lexeme::EndOfFile)
//        {
//            executeListeners();
//            return BlockAnalizeStates::Basic;
//        }

//        return BlockAnalizeStates::StaticBlock;
//    }

//    template<>
//    BlockAnalizeStates Analizer::handler<BlockAnalizeStates::DynamicBloc>( Parsing::ParseCommand& cmd)
//    {
//        auto& [cmdInfo, payload]=cmd;

//        if(cmdInfo==Parsing::Lexeme::Command)
//        {
//            block->push(std::move(payload));
//            return BlockAnalizeStates::DynamicBloc;
//        }

//        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
//        {
//            return BlockAnalizeStates::Skip;
//        }

//        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
//        {
//            executeListeners();
//            return BlockAnalizeStates::Basic;
//        }

//        if(cmdInfo==Parsing::Lexeme::EndOfFile)
//        {
//            executeListeners();
//            return BlockAnalizeStates::Basic;
//        }

//        return BlockAnalizeStates::DynamicBloc;

//    }

//    template<>
//    BlockAnalizeStates Analizer::handler<BlockAnalizeStates::Skip>( Parsing::ParseCommand& cmd)
//    {
//        auto& [cmdInfo, payload]=cmd;

//        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
//        {
//            return BlockAnalizeStates::DynamicBloc;
//        }

//        if(cmdInfo==Parsing::Lexeme::EndOfFile)
//        {
//            executeListeners();
//            return BlockAnalizeStates::Basic;
//        }

//        return BlockAnalizeStates::Skip;
//    }

}
