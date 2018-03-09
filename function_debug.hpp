
#include <map>
#include <string>
#include <cstdarg>


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

/*
   std::string operator<<(std::string& l, const char r[])
{
    return l + std::string(r);
}
*/

std::string operator<<(std::string& l, const char* const r)
{
    return l + std::string(r);
}

std::string operator<<(const std::string& l, const std::string& r)
{
    return l + r;
}

/*
template <typename T>
std::string argument_convert(const T& t)
{
    std::ostringstream os;
    os << t;
    return os;
}
*/

// create string containing function debug information including arguments
// information
// information for arguments is passed in using a map of strings
// the first string is the variable name and the second is the value
// converted to string
std::string function_debug_arguments(const char* function_string, std::map<const std::string, const std::string> arguments)
{
    std::string ret(function_string);
    //ret << "(");
    ret << std::string("(");
    std::map<const std::string, const std::string>::const_iterator it{arguments.begin()};
    for(; it != arguments.end(); ++ it)
    {
        ret << it->first << std::string("=") << it->second;
        if(it != --arguments.end()) ret << std::string(", ");
        //if(!is_last(it, arguments)) ret + std::string(",");
    }
    ret << ")";
    return ret;
}

// all arguments have to be of type string
// which isn't a significant improvement over the map method
// however it is a slightly more convenient syntax
// instead of organizing arguments into pairs of name and values
// the function takes a continual list of strings, and these should
// be formatted into names and values format
// count is the number of arguments, however twice that number of
// strings must be provided
std::string function_debug_arguments(const char* function_string, const int count, ...)
{
    va_list vargs;
    va_start(vargs, count);

    std::ostringstream os;
    os << function_string;
    os << "(";
    for(int i{0}; i < count; ++ i)
    {
        os << va_arg(vargs, std::string) << "=" << va_arg(vargs, std::string);
        if(i < count - 1) os << ", ";
    }
    os << ")";
    
    va_end(vargs);
    return os.str();
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
        ret << it->first << std::string("=") << it->second;
        if(it != --locals.end()) ret << std::string(", ");
        //if(!is_last(it, locals)) ret + std::string(",");
    }
    return ret;
}
