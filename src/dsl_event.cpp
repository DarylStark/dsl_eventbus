#include "dsl_eventbus.h"

namespace dsl
{
    namespace eventbus
    {
        Event Event::make_event(const std::string &event, const EventSubscription &subscription)
        {
            return Event({event, subscription});
        }
    };
};
