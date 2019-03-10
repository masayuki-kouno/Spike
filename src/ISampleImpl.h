#pragma once

namespace Sample {

class ISampleImpl
{
public:
    virtual ~ISampleImpl() = default;
    virtual void setup() = 0;
    virtual void teardown() = 0;
    virtual void operate() = 0;
    virtual bool isErrorOccurred() const = 0;
};
} // namespace Sample
