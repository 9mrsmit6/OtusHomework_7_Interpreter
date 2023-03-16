cmake_minimum_required(VERSION 3.5)

project(OtusHomework_7_Interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bulk
    main.cpp
    Parsing/Parser.hpp
    Parsing/ParserCommand.hpp
    Analize/Analizer.hpp
    Data/Block.hpp
    Listeners/Printer.hpp
    Listeners/FilePrinter.hpp
    Analize/States.hpp
)

install(TARGETS bulk
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "bulk")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
