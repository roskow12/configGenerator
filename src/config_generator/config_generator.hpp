#include <json.hpp>
#include <iostream>


using json = nlohmann::json;


namespace config_generator {

    bool process_post_request(std::string const& body)
    {
        std::cout << body << "\n";
        json request_object = json::parse(body);

        std::cout << request_object << "\n";
        std::cout << request_object << "\n";
        return true;
    }
}