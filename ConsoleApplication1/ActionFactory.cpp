#include "ActionFactory.h"

std::unordered_map<std::string, ActionFactoryFunc>& getActionFactory() {
    static std::unordered_map<std::string, ActionFactoryFunc> instance;
    return instance;
}

ActionRegistrar::ActionRegistrar(const std::string& name, ActionFactoryFunc func) {
    getActionFactory()[name] = func;
}
