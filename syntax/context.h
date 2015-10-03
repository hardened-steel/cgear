#ifndef CONTEXT_H
#define CONTEXT_H

#include <list>
#include <map>
#include <string>

class ast::context
{
	/*
    std::list<std::multimap<std::string, ast::type>> identifiers;
public:
    context() {
        add_space();
    }
    ~context() {}

    void add_space() {
        std::multimap<std::string, ast::type> new_space;
        identifiers.push_front(std::move(new_space));
    }
    void add_name(const std::string& name, ast::type type) {
        std::multimap<std::string, ast::type>& current_space = identifiers.front();
        current_space.insert(std::pair<std::string, ast::type>(name, type));
    }
    void remove_space() {
        identifiers.pop_front();
    }
    bool find_name(const std::string& name, ast::type type) {
        for(auto it = identifiers.begin(); it != identifiers.end(); it++) {
            std::multimap<std::string, ast::type>& current_space = *it;
            for(auto n = current_space.find(name); n != current_space.end(); n++) {
                if((n->second) == type) return true;
            }
        }
        return false;
    }
    bool find_name(const std::string& name, ast::type* type) {
        for(auto it = identifiers.begin(); it != identifiers.end(); it++) {
            std::multimap<std::string, ast::type>& current_space = *it;
            for(auto n = current_space.find(name); n != current_space.end(); n++) {
                (*type) = n->second;
                return true;
            }
        }
        return false;
    }
    bool find_name(const std::string& name) {
        for(auto it = identifiers.begin(); it != identifiers.end(); it++) {
            std::multimap<std::string, ast::type>& current_space = *it;
            for(auto n = current_space.find(name); n != current_space.end(); n++) {
                return true;
            }
        }
        return false;
    }
    */
};

#endif // CONTEXT_H

