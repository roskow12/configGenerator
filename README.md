Configuration Generator
=====


Dependencies
-------
* **C++14**
* **OpenSSL:** Optional, for using TLS/Secure sockets
* **[JSON for Modern C++:](https://github.com/nlohmann/json)** This is already included in the repo
* **CMake 3.9 or later**
In Ubuntu 17.10 you can run:
```
sudo apt install cmake make g++ libssl-dev
```


* **Boost 1.66.0 or later:** Boost Beast is used for HTTP and it relies on other parts of boost: ASIO and system. System must be compiled so I'd like to add it with the CMake ExternalProject Module. Advantages here would be avoiding 3rd party sourcing, controlling build flags(LTO, arch, static libs). Disadvantage is deleting source tree deletes boost build.

Right now you must build and install Boost so CMake can find it in the include directories(probably can get away with just building boost:system). [Boost Getting Started](http://www.boost.org/doc/libs/1_66_0/more/getting_started/)



