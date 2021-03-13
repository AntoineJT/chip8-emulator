#pragma once
#include <cassert>
#include <unordered_map>

namespace Chip8::Utils
{
    template<typename K, typename V>
    class SimpleBiMap
    {
        std::unordered_map<K, V> m_data;
        std::unordered_map<V, K> m_reverse_data {};
    public:
        SimpleBiMap(std::unordered_map<K, V> data)
        {
            m_data = std::move(data);
            for (const auto& pair : m_data)
            {
                m_reverse_data[pair.second] = pair.first;
            }
            assert(m_data.size() == m_reverse_data.size());
        }

        const std::unordered_map<K, V>& Data()
        {
            return m_data;
        }

        const std::unordered_map<V, K>& ReversedData()
        {
            return m_reverse_data;
        }

        // I will add things like Add or Delete if I need it
        // this implementation is very dumb anyway
    };
}
