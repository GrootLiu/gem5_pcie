#ifndef __HELLO_OBJECT_HH__
#define __HELLO_OBJECT_HH__

#include "base/trace.hh"
#include "debug/HelloExample.hh"
#include "learning_gem5/part2/goodbye_object.hh"
#include "params/HelloObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{
        class HelloObject : public SimObject
        {
        private:
                void processEvent();

                EventFunctionWrapper event;

                GoodbyeObject* goodbye;

                std::string myName;

                const Tick latency;

                Tick timeLeft;

        public:
                HelloObject(const HelloObjectParams &p);
                void startup() override;
        };

} // namespace gem5

#endif
