
#include "/nlohmann/json.hpp"
#include <iostream>
int main()
{
// create object from string literal
nlohmann::json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

// or even nicer with a raw string literal
auto j2 = R"(
  {
    "happy": true,
    "pi": 6.141
  }
)"_json;

std::cout<<"json: "<<j.dump()<<std::endl;
std::cout<<"json: "<<j2.dump()<<std::endl;

return 0;
}