#ifndef STATES_HPP
#define STATES_HPP


#include "../Parsing/ParserCommand.hpp"
#include "../Data/Block.hpp"
#include <memory>
#include <utility>
#include <optional>

namespace Analize
{
    struct StateListener
    {
        virtual void executeNewBlock(std::unique_ptr<Data::Block>& block)=0;
        virtual std::size_t getStaticSize()=0;

        StateListener()=default;
        virtual ~StateListener(){};
    };

    struct State
    {
        State(StateListener& analyzer_):
            analyzer(analyzer_)
        {  };

        virtual ~State() {};
        virtual std::optional<std::unique_ptr<State>> executeNewCommand(Parsing::ParseCommand& cmd)=0;

    protected:
        StateListener& analyzer;
    };

    using StateOptPtr=std::optional<std::unique_ptr<State>>;

    struct StateBasic:public State
    {
        StateBasic(StateListener& analyzer_):
            State{analyzer_}
        {  }

        ~StateBasic(){};
        StateOptPtr executeNewCommand(Parsing::ParseCommand& cmd) override;

    };


    struct StateStaticBlock:public State
    {
        StateStaticBlock(StateListener& analyzer_, Parsing::ParseCommand& cmd):
            State{analyzer_},
            block(std::make_unique<Data::Block>(analyzer_.getStaticSize()))
        {
            auto& [cmdInfo, payload]=cmd;
            block->push(std::move(payload));
        }
        ~StateStaticBlock(){};

        StateOptPtr executeNewCommand(Parsing::ParseCommand& cmd) override;


    private:
        std::unique_ptr<Data::Block> block;
    };


    struct StateDynamicBlock:public State
    {
        StateDynamicBlock(StateListener& analyzer_):
            State{analyzer_},
            block{std::make_unique<Data::Block>()}
        {

        }

        StateDynamicBlock(StateListener& analyzer_, std::unique_ptr<Data::Block>& block):
            State{analyzer_},
            block{std::move(block)}
        {

        }
        ~StateDynamicBlock(){};
        StateOptPtr executeNewCommand(Parsing::ParseCommand& cmd) override;

    private:
        std::unique_ptr<Data::Block> block;
    };


    struct StateSkip:public State
    {
        StateSkip(StateListener& analyzer_, std::unique_ptr<Data::Block>& topBlock_):
            State{analyzer_},
            topBlock{std::move(topBlock_)}
        {  }

        ~StateSkip()=default;

        StateOptPtr executeNewCommand(Parsing::ParseCommand& cmd) override;
    private:
        std::size_t skipCnt{1};
        std::unique_ptr<Data::Block> topBlock;

    };






    StateOptPtr StateBasic::executeNewCommand(Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {
            return StateOptPtr{std::make_unique<StateStaticBlock>(this->analyzer, cmd)};
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            return StateOptPtr{std::make_unique<StateDynamicBlock>(this->analyzer)};
        }

        return std::nullopt;
    }


    StateOptPtr StateStaticBlock::executeNewCommand(Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {

            block->push(std::move(payload));

            if(block->getSize()>=this->analyzer.getStaticSize())
            {
                this->analyzer.executeNewBlock(block);
                return StateOptPtr{std::make_unique<StateBasic>(this->analyzer)};
            }
            else
            {
                return std::nullopt;
            }

        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            this->analyzer.executeNewBlock(block);
            return StateOptPtr{std::make_unique<StateDynamicBlock>(this->analyzer)};
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            this->analyzer.executeNewBlock(block);
            return StateOptPtr{std::make_unique<StateBasic>(this->analyzer)};
        }

        return std::nullopt;
    }


    StateOptPtr StateDynamicBlock::executeNewCommand(Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;

        if(cmdInfo==Parsing::Lexeme::Command)
        {
            block->push(std::move(payload));
            return std::nullopt;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            return StateOptPtr{std::make_unique<StateSkip>(this->analyzer, block)};
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
        {
            this->analyzer.executeNewBlock(block);
            return StateOptPtr{std::make_unique<StateBasic>(this->analyzer)};
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            return StateOptPtr{std::make_unique<StateBasic>(this->analyzer)};
        }

        return std::nullopt;
    }


    StateOptPtr StateSkip::executeNewCommand(Parsing::ParseCommand& cmd)
    {
        auto& [cmdInfo, payload]=cmd;


        if(cmdInfo==Parsing::Lexeme::DynamicBlockStart)
        {
            skipCnt++;
            return std::nullopt;
        }

        if(cmdInfo==Parsing::Lexeme::DynamicBlockStop)
        {
            skipCnt--;
            if(skipCnt!=0)
            {
               return std::nullopt;
            }
            return StateOptPtr{std::make_unique<StateDynamicBlock>(this->analyzer, topBlock)};
        }

        if(cmdInfo==Parsing::Lexeme::EndOfFile)
        {
            return StateOptPtr{std::make_unique<StateBasic>(this->analyzer)};
        }

        return std::nullopt;
    }







}

#endif // STATES_HPP
