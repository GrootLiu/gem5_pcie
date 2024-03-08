#ifndef __GOODBYE_OBJECT_HH
#define __GOODBYE_OBJECT_HH

#include <string>

#include "base/trace.hh"
#include "debug/GoodBye.hh"
#include "params/GoodbyeObject.hh"
#include "sim/sim_exit.hh"
#include "sim/sim_object.hh"

namespace gem5
{
        class GoodbyeObject : public SimObject
        {
        private:
                void processEvent();

                void fillBuffer();

                EventFunctionWrapper event;

                float bandWidth;

                char* buffer;

                int bufferSize;

                std::string message;

                int bufferUsed;
        public:
                GoodbyeObject(const GoodbyeObjectParams &p);

                ~GoodbyeObject();

                void sayGoodbye(std::string name);
        };

} // namespace gem5

#endif
