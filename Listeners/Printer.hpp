#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "../Analize/Analizer.hpp"
#include <iostream>

namespace Listeners
{

    template <class Stream>
    void printBlock(std::shared_ptr<Data::Block> block, Stream& stream)
    {
        stream<<"bulk: ";

        for(auto& v:(*block))
        {
            stream<<(*v);
            stream<<", ";
        }
    }

    struct Printer: public Analize::AnalizerListener
    {
        Printer()=default;
        ~Printer()=default;

        void newBlockreceived(std::shared_ptr<Data::Block> block) override
        {
            printBlock(block, std::cout);
        }
    };


}
#endif // PRINTER_HPP
