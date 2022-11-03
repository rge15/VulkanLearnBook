#include "config.hpp"


#define VK_NO_EXTENSIONS nullptr
#define VK_NO_LAYERS	 nullptr


using string = std::string;


template <typename T>
using UniqPtr = std::unique_ptr<T>;

template <typename T>
using Vector = std::vector<T>;

template <typename... T>
using Tuple = std::tuple<T...>;

template <typename T, typename V>
using Map = std::map<T,V>;

using JoyID = size_t;

