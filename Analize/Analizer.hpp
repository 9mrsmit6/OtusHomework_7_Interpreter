#ifndef ANALIZER_HPP
#define ANALIZER_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"
#include <list>
#include "../Data/Block.hpp"

#include <iostream>


namespace Analize
{

    enum class BlockAnalizeStates
    {
        Basic=0,
        StaticBlock,
        DynamicBloc,
        Skip
    };


    struct AnalizerListener
    {
        virtual void newBlockreceived(std::shared_ptr<Data::Block> block)=0;
        virtual ~AnalizerListener()=default;
    };

    struct Printer: public AnalizerListener
    {
        void newBlockreceived(std::shared_ptr<Data::Block> block) override
        {
            std::cout<<"VAX"<<std::endl;
        }

        Printer()=default;
        ~Printer()=default;

    };


    struct Analizer
    {

        friend class State;

        Analizer(const std::size_t stBlockSize_):
            stBlockSize(stBlockSize_)
        {}

        void addListener(std::shared_ptr<AnalizerListener> lisPtr)
        {
            listeners.push_front(lisPtr);
        }

        void execute ( Parsing::ParseCommand cmd )
        {

            auto& [cmdInfo, payload]=cmd;

            //как от этого избавится???
            switch(currentState)
            {
                case BlockAnalizeStates::Basic:
                    currentState=handlerBasic (cmd);
                    break;

                case BlockAnalizeStates::StaticBlock:
                    currentState=handlerStaticBlock (cmd);
                    break;

                case BlockAnalizeStates::DynamicBloc:
                    currentState=handlerDynamicBlock (cmd);
                    break;

                case BlockAnalizeStates::Skip:
                    currentState=handlerSkip (cmd);
                break;

                default:
                    currentState=BlockAnalizeStates::Basic;
                    break;
            }
        }


    private:
        std::unique_ptr<Data::Block> block;
        BlockAnalizeStates currentState{BlockAnalizeStates::Basic};
        const std::size_t stBlockSize;

        BlockAnalizeStates handlerBasic         ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerStaticBlock   ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerDynamicBlock  ( Parsing::ParseCommand& cmd);
        BlockAnalizeStates handlerSkip          ( Parsing::ParseCommand& cmd);



        std::list<std::weak_ptr<AnalizerListener>> listeners;

        void executeListeners()
        {
            if(block==nullptr){return;}
            for(auto it=listeners.begin();it!=listeners.end();)
            {
                auto cur=it;
                it++;

                if(auto sh=(*cur).lock())
                {
                    std::shared_ptr<Data::Block> temp=std::move(block);
                    (*cur).lock()->newBlockreceived(temp);
                }
                else
                {
                    listeners.erase(cur);
                }
            }
        }



    };
}

#endif // ANALIZER_HPP
