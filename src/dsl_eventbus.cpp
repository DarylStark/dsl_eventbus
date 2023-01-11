#include "dsl_eventbus.h"
#include <thread>

namespace dsl
{
    namespace eventbus
    {
        void EventBus::subscribe(const std::string event, EventSubscription subscription)
        {
            __subscriptions[event].push_back(subscription);
        }

        void EventBus::unsubscribe(const std::string event, const std::string &identifier)
        {
            for (const auto &sub : __subscriptions[event])
                if (sub.identifier == identifier)
                    __subscriptions[event].remove(sub);
        }

        void EventBus::unsubscribe_all(const std::string event)
        {
            __subscriptions[event].clear();
        }

        void EventBus::raise(const std::string event)
        {
            // Find the subscriptions for this event
            const auto &subscriptions = __subscriptions[event];

            // Run the callbacks for this subscription
            for (const auto &sub : subscriptions)
            {
                Event e = Event::make_event(event, sub);
                if (sub.run_as_thread)
                { // Start the function in it's own thread
                    std::thread thread(sub.callback, e);
                    thread.detach();
                }
                else
                {
                    sub.callback(e);
                }
            }
        }
    };
};
