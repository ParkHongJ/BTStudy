#pragma once
#include <string>
#include <any>
#include <unordered_map>
class Blackboard
{
public:
    template<typename T>
    void Set(const std::string& key, const T& value) {
        data[key] = std::make_any<T>(value);
    }

    template<typename T>
    T Get(const std::string& key) const {
        return std::any_cast<T>(data.at(key));
    }

private:
    std::unordered_map<std::string, std::any> data;
};

