#ifndef ANALIZER_HPP
#define ANALIZER_HPP

#include <string>
#include <utility>
#include <memory>
#include "../Parsing/ParserCommand.hpp"
#include <list>
#include "../Data/Block.hpp"

#include <iostream>
#include "States.hpp"


namespace Analize
{
    struct AnalizerListener
    {
        virtual void newBlockreceived(std::shared_ptr<Data::Block> block)=0;
        virtual ~AnalizerListener()=default;
    };


    struct Analizer :public StateListener
    {

        Analizer(const std::size_t stBlockSize_):
            stBlockSize(stBlockSize_)
        {
            currentState=std::make_unique<StateBasic>(*this);
        }

        void addListener(std::shared_ptr<AnalizerListener> lisPtr)
        {
            listeners.push_front(lisPtr);
        }

        void execute ( Parsing::ParseCommand cmd )
        {
            auto temp=currentState->executeNewCommand(cmd);
            if(temp)
            {
                currentState=std::move(temp.value());
            }
        }

        void executeNewBlock(std::unique_ptr<Data::Block>& block) override
        {
            executeListeners(block);
        }

        std::size_t getStaticSize() override   {return stBlockSize;}


    private:
        std::unique_ptr<State> currentState;
        const std::size_t stBlockSize;

        std::list<std::weak_ptr<AnalizerListener>> listeners;

        void executeListeners(std::unique_ptr<Data::Block>& block)
        {
            if(block==nullptr){return;}
            std::shared_ptr<Data::Block> temp=std::move(block);

            for(auto it=listeners.begin();it!=listeners.end();)
            {
                auto cur=it;
                it++;

                if(auto sh=(*cur).lock())
                {                    
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
