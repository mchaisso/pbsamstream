template <typename T>
void StoreValue(std::string &valueStr, T &value)
{
    std::stringstream strm(valueStr);
    if (!(strm >> value)) {
        std::cout << "Error parsing " << valueStr << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

template <typename T_Value>
bool KeywordValuePair<T_Value>::Parse(std::string &kvPair, const char *key, T_Value &result)
{
    std::string kvKey, kvValue;
    SplitSAMKeyValuePair(kvPair, kvKey, kvValue);
    if (kvKey != key) {
        return false;
    } else {
        std::stringstream strm(kvValue);
        if (!(kvValue >> result)) {
            return false;
        } else {
            return true;
        }
    }
}

template <typename T_Value>
bool KeywordValuePair<T_Value>::Store(std::string &valueStr, T_Value &value)
{
    return (std::stringstream(valueStr) >> value);
}
