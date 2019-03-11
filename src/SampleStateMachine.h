#pragma once

#include "ISampleImpl.h"
#include <string>
#include <memory>

namespace Sample {

class SampleStateMachine
{
public:
    enum class Event
    {
        Started = 0,
        Operated,
        Stopped,
        ErrorOccurred
    };

    SampleStateMachine(ISampleImpl* impl);
    ~SampleStateMachine();
    std::string GetStateName() const;
    void PerformEvent(const Event event);

private:
    ISampleImpl* m_sampleImpl;

    struct STMImpl;
    std::unique_ptr<STMImpl> m_stmImpl;

};

} // namespace Sample
