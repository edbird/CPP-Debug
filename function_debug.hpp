
#include <map>
#include <string>


#if DEBUG_MESSAGE_DISABLE
#else
    #define DEBUG_MESSAGE_ENABLE 1
#endif

#define DEBUG_MESSAGE_OUTPUT std::cerr
void DEBUG_MESSAGE(const std::string& message)
{
    #if DEBUG_MESSAGE_ENABLE
        DEBUG_MESSAGE_OUTPUT << message;
        DEBUG_MESSAGE_OUTPUT << std::endl;
    #endif
}

/*
// is last function
// https://stackoverflow.com/questions/3516196/testing-whether-an-iterator-points-to-the-last-item

template <typename Iter>
Iter next(Iter iter)
{
    return ++ iter;
}

template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont)
{
    return (iter != cont.end()) && (next(iter) == cont.end());
}
*/

std::string operator<<(std::string& l, const std::string& r)
{
    return l += r;
}

// create string containing function debug information including arguments
// information
// information for arguments is passed in using a map of strings
// the first string is the variable name and the second is the value
// converted to string
std::string function_debug_arguments(const char* function_string, std::map<const std::string, const std::string> arguments)
{
    std::string ret(function_string);
    //ret << "(");
    ret << "(";
    std::map<const std::string, const std::string>::const_iterator it{arguments.begin()};
    for(; it != arguments.end(); ++ it)
    {
        ret << it->first << "=" << it->second;
        if(it != --arguments.end()) ret << ", ");
        //if(!is_last(it, arguments)) ret + std::string(",");
    }
    ret << ")";
    return ret;
}

// create string containing function debug information including local
// variables
std::string function_debug_locals(const char* function_string, std::map<const std::string, const std::string> locals)
{
    std::string ret(function_string);
    ret << ": Local vars: ";
    std::map<const std::string, const std::string>::const_iterator it{locals.begin()};
    for(; it != locals.end(); ++ it)
    {
        ret << it->first << "=" << it->second;
        if(it != --locals.end()) ret << ", ");
        //if(!is_last(it, locals)) ret + std::string(",");
    }
    return ret;
}
