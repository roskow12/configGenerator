#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <json.hpp>
#include <iostream>
#include <cstdint>
// namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

using json = nlohmann::json;

template <typename T>
class PreAllocator
{
private:
    T* memory_ptr;
    std::size_t memory_size;

public:
    typedef std::size_t     size_type;
    typedef T*              pointer;
    typedef T               value_type;

    PreAllocator(T* memory_ptr, std::size_t memory_size) :
        memory_ptr(memory_ptr), memory_size(memory_size) {}

    PreAllocator(const PreAllocator& other) throw() :
        memory_ptr(other.memory_ptr), memory_size(other.memory_size) {};

    template<typename U>
    PreAllocator(const PreAllocator<U>& other) throw() :
        memory_ptr(other.memory_ptr), memory_size(other.memory_size) {}

    template<typename U>
    PreAllocator& operator = (const PreAllocator<U>& other) { return *this; }
    PreAllocator<T>& operator = (const PreAllocator& other) { return *this; }
    ~PreAllocator() {}


    pointer allocate(size_type n, const void* hint = 0) {return memory_ptr;}
    void deallocate(T* ptr, size_type n) {}

    size_type max_size() const {return memory_size;}
};

namespace config_generator {

    using PreAllocatedVector = std::vector<uint8_t, PreAllocator<uint8_t>>;

    bool process_post_request(boost::beast::flat_static_buffer<1024 * 1024> const& body)
    {
        printf("first char: %s, size: %d\n", body.data().data(), body.data().size());
        uint8_t* data = static_cast<uint8_t*>(body.data().data());

        PreAllocatedVector vector_body(PreAllocator<uint8_t>(data, 1024*1024));
        auto begin_it = vector_body.begin();
        auto end_it = vector_body.begin();
        std::advance(end_it, body.data().size());

        // json request_object = json::parse(data, body.data().size());
        json request_object = json::parse(begin_it, end_it);

        for(json::iterator it = request_object.begin(); it != request_object.end(); ++it)
            std::cout << it.key() << " : " << it.value() << "\n";
        return true;
    }
}