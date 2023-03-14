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
//        AnalizerListener()=default;
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



    template <BlockAnalizeStates in, BlockAnalizeStates base>
    concept TypeSelector = (in==base);


    struct Analizer
    {

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
                    handler<BlockAnalizeStates::Basic> (cmd);
                    break;

                case BlockAnalizeStates::StaticBlock:
//                    handler<BlockAnalizeStates::StaticBlock> (cmd);
                    break;

                case BlockAnalizeStates::DynamicBloc:
//                    handler<BlockAnalizeStates::DynamicBloc> (cmd);
                    break;

                default:
//                    currentState=BlockAnalizeStates::Basic;
                    break;
            }
        }


    private:
        std::unique_ptr<Data::Block> block;
        BlockAnalizeStates currentState{BlockAnalizeStates::Basic};
        const std::size_t stBlockSize;

        template<BlockAnalizeStates current>
        BlockAnalizeStates handler( Parsing::ParseCommand& cmd) requires TypeSelector <current,BlockAnalizeStates::Basic>;

        std::list<std::weak_ptr<AnalizerListener>> listeners;

        void executeListeners()
        {
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
