#include "learning_gem5/part2/goodbye_object.hh"

namespace gem5
{
    GoodbyeObject::GoodbyeObject(const GoodbyeObjectParams &params)
        : SimObject(params),
          event([this]
                { processEvent(); },
                name()),
          bandWidth(params.write_bandwidth),
          bufferSize(params.buffer_size),
          buffer(nullptr),
          bufferUsed(0)
    {
        buffer = new char[bufferSize];
        DPRINTF(GoodBye, "Created the goodbye object\n");
    }

    GoodbyeObject::~GoodbyeObject()
    {
        delete[] buffer;
    }

    void GoodbyeObject::processEvent()
    {
        DPRINTF(GoodBye, "Processing the event\n");
        fillBuffer();
    }

    void GoodbyeObject::sayGoodbye(std::string other_name)
    {
        DPRINTF(GoodBye, "Saying goodbye to %s\n", other_name);

        message = "Goodbye " + other_name + "!";

        fillBuffer();
    }

    void GoodbyeObject::fillBuffer()
    {
        assert(message.length() > 0);

        int bytes_copied = 0;
        for (auto it = message.begin();
             it < message.end() && bufferUsed < bufferSize - 1;
             it++, bufferUsed++, bytes_copied++)
        {
            // Copy the character into the buffer
            buffer[bufferUsed] = *it;
        }

        if (bufferUsed < bufferSize - 1)
        {
            // Wait for the next copy for as long as it would have taken
            DPRINTF(GoodBye, "Scheduling another fillBuffer in %d ticks\n",
                    bandWidth * bytes_copied);
            schedule(event, curTick() + bandWidth * bytes_copied);
        }
        else
        {
            DPRINTF(GoodBye, "Goodbye done copying!\n");
            // Be sure to take into account the time for the last bytes
            exitSimLoop(buffer, 0, curTick() + bandWidth * bytes_copied);
        }
    }
} // namespace gem5
