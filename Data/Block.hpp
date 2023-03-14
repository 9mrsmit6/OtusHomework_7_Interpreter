#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <utility>
#include <memory>
#include<ctime>

namespace Data
{
    struct Block
    {
        Block()
        {
            creationTime=std::time(nullptr);
        }

        Block(const std::size_t N)
        {
            creationTime=std::time(nullptr);
            paylolds.reserve(N);
        }

        void push(std::unique_ptr<std::string>&& payloadPtr)
        {
            paylolds.push_back(std::forward<std::unique_ptr<std::string>>(payloadPtr));
        }

        auto cbegin()
        {
            return paylolds.cbegin();
        }

        auto cend()
        {
            return paylolds.cend();
        }

        std::time_t getCreationTime()
        {
            return creationTime;
        }


        private:
            std::vector<std::unique_ptr<std::string>> paylolds;
            std::time_t creationTime{0};

    };
}

#endif // BLOCK_HPP
