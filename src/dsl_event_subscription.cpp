#include "dsl_eventbus.h"

namespace dsl
{
    namespace eventbus
    {
        EventSubscription EventSubscription::make_event_subscription(eventbus_callback_type callback, std::string identifier)
        {
            EventSubscription obj;
            obj.callback = callback;
            obj.identifier = identifier;
            obj.run_as_thread = false;
            return obj;
        }

        EventSubscription EventSubscription::make_threaded_event_subscription(eventbus_callback_type callback, std::string identifier)
        {
            EventSubscription obj = EventSubscription::make_event_subscription(callback, identifier);
            obj.run_as_thread = true;
            return obj;
        }

        bool EventSubscription::operator==(const EventSubscription &other) const
        {
            return this->identifier == other.identifier;
        }
    };
};
