#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

#include <boost/array.hpp>
#include <boost/fiber/fiber.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

int main(int argc, char* argv[])
{
    namespace ios = boost::iostreams;
    /*{
        std::ofstream file("hello.z", std::ios_base::out | std::ios_base::binary);
        ios::filtering_streambuf<ios::output> out;
        out.push(ios::zlib_compressor());
        out.push(file);
        boost::iostreams::copy(std::cin, out);
    }*/
    {
        std::ifstream ifile("hello.z", std::ios_base::in | std::ios_base::binary);
        std::ofstream ofile("hello.uz", std::ios_base::out | std::ios_base::binary);
        ios::filtering_streambuf<ios::output> out;
        out.push(ios::zlib_decompressor());
        out.push(ofile);
        boost::iostreams::copy(ifile, out);
    }
}
