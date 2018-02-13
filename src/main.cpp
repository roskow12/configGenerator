//
// Copyright (c) 2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, fast
//
//------------------------------------------------------------------------------

#include <http_worker.hpp>
#include <boost/asio.hpp>
#include <cstdio>

// int main(int argc, char* argv[])
int main()
{
    try
    {
        // // Check command line arguments.
        // if (argc != 6)
        // {
        //     std::cerr << "Usage: http_server_fast <address> <port> <doc_root> <num_workers> {spin|block}\n";
        //     std::cerr << "  For IPv4, try:\n";
        //     std::cerr << "    http_server_fast 0.0.0.0 80 . 100 block\n";
        //     std::cerr << "  For IPv6, try:\n";
        //     std::cerr << "    http_server_fast 0::0 80 . 100 block\n";
        //     return EXIT_FAILURE;
        // }

        auto const address = boost::asio::ip::make_address("0.0.0.0");
        unsigned short port = static_cast<unsigned short>(std::atoi("8080"));
        std::string doc_root = ".";
        int num_workers = 2;
        bool spin = true;

        printf("Using ip: %s port: %d doc_root: %s num_workers: %d %s\n\n",
            address.to_string().c_str(), port, doc_root.c_str(), num_workers, spin ? "spin":"block");

        // auto const address = boost::asio::ip::make_address(argv[1]);
        // unsigned short port = static_cast<unsigned short>(std::atoi(argv[2]));
        // std::string doc_root = argv[3];
        // int num_workers = std::atoi(argv[4]);
        // bool spin = (std::strcmp(argv[5], "spin") == 0);

        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {address, port}};

        std::list<http_worker> workers;
        for (int i = 0; i < num_workers; ++i)
        {
            workers.emplace_back(acceptor, doc_root);
            workers.back().start();
        }

        if (spin)
          for (;;) ioc.poll();
        else
          ioc.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}