#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

class EventBus
{
public:

    template<typename EventType>
    using Handler = std::function<void(const EventType&)>;

    template<typename EventType>
    void Subscribe(Handler<EventType> handler)
    {
        auto wrapper =
        [handler](const void* eventData)
        {
            handler(*static_cast<const EventType*>(eventData));
        };

        subscribers[typeid(EventType)].push_back(wrapper);
    }

    template<typename EventType>
    void Publish(const EventType& event)
    {
        auto it = subscribers.find(typeid(EventType));

        if(it == subscribers.end())
            return;

        for(auto& handler : it->second)
        {
            handler(&event);
        }
    }

private:

    std::unordered_map
    <
        std::type_index,
        std::vector<std::function<void(const void*)>>
    >
    subscribers;
};