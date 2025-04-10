#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

class BTNode;

using ActionFactoryFunc = std::function<std::shared_ptr<BTNode>()>;

std::unordered_map<std::string, ActionFactoryFunc>& getActionFactory();

class ActionRegistrar {
public:
    ActionRegistrar(const std::string& name, ActionFactoryFunc func);
};

#define REGISTER_ACTION(ClassName) \
    static ActionRegistrar _reg_##ClassName(#ClassName, []() { \
        return std::make_shared<ClassName>(); \
    })
