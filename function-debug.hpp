
// create string containing function debug information including arguments
// information
// information for arguments is passed in using a map of strings
// the first string is the variable name and the second is the value
// converted to string
std::string function_debug(const char* function_string, std::map<const std::string, const std::string> arguments)
{
    std::string ret(function_string);
    ret << "(";
    std::map<const std::string, const std::string>::const_iterator{arguments.begin()};
    for(; it != arguments.end(); ++ it)
    {
        ret << it->first << "=" << it->second;
        if(it != arguments.end() - 1) ret << ",";
    }
    ret << ")";
    return ret;
}
