#include "learning_gem5/part2/hello_object.hh"
#include <iostream>

namespace gem5
{
    HelloObject::HelloObject(const HelloObjectParams &params)
        : SimObject(params),
          event([this]
                { processEvent(); },
                name()),
          latency(params.time_to_wait),
          timeLeft(params.number_of_fires),
          myName(params.name),
          goodbye(params.goodbye_object)
    {
        DPRINTF(HelloExample, "Created the Hello Object...\n");
        panic_if(!goodbye, "HelloObject must have a non-null GoodbyeObject");
    }

    void HelloObject::processEvent()
    {
        timeLeft--;
        DPRINTF(HelloExample, "Processing the event! %d time left\n",
                timeLeft);
        if (timeLeft <= 0)
        {
            DPRINTF(HelloExample, "Done!\n");
            printf("111111111111111\n");
            goodbye->sayGoodbye(myName);
        }
        else
        {
            schedule(event, curTick() + latency);
        }

        // DPRINTF(HelloExample, "Event's name is %s\n", event.name());
    }

    void HelloObject::startup()
    {
        schedule(event, latency);
    }
} // namespace gem5
