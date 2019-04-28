#pragma once
#include <map>
#include <memory>

namespace PicoC
{
    namespace Representation
    {
        template<typename T>
        class LookupTable
        {
        private:
            std::map<std::string, T> _LookupTable;
        public:
            void Add(const std::string name, T value);
            const bool Find(const std::string name, T& value);
        };
        template<typename T>
        inline void LookupTable<T>::Add(const std::string name, T value)
        {
            _LookupTable.insert(std::pair<std::string, T>(name, value));
        }
        template<typename T>
        inline const bool LookupTable<T>::Find(const std::string name, T & value)
        {
            if (_LookupTable.find(name) != _LookupTable.end())
            {
                value = _LookupTable[name];
                return true;
            }
            return false;
        }
    }
}