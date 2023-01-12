#ifndef __DSL_EVENTBUS_H__
#define __DSL_EVENTBUS_H__

#include <string>
#include <unordered_map>
#include <functional>
#include <list>
#include <dsl_types_event.h>

namespace dsl
{
    namespace eventbus
    {
        class EventBus;
        struct EventSubscription;
        struct Event;

        // Typedef for the callback method
        typedef std::function<void(const Event &)> eventbus_callback_type;

        // Class to define a Entity Subscription
        struct EventSubscription : public dsl::types::Subscription<eventbus_callback_type>
        {
            // Factory methods for this class
            static EventSubscription make_event_subscription(eventbus_callback_type callback, std::string identifier);
            static EventSubscription make_threaded_event_subscription(eventbus_callback_type callback, std::string identifier);

            // Operators
            bool operator==(const EventSubscription &other) const;
        };

        class EventBus
        {
        private:
            std::unordered_map<std::string, std::list<EventSubscription>> __subscriptions;

        public:
            void subscribe(const std::string event, EventSubscription function);
            void unsubscribe(const std::string event, const std::string &identifier);
            void unsubscribe_all(const std::string event);
            void raise(const std::string event);
        };

        // A instance of the Event will be sent to the callback when a event
        // happens
        struct Event : public dsl::types::Event<std::string, EventSubscription>
        {
            // Factory methods
            static Event make_event(const std::string &event, const EventSubscription &subscription);
        };
    };
};

#endif /* __DSL_EVENTBUS_H__ */