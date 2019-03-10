#pragma once

#include <gmock/gmock.h>
#include "ISampleImpl.h"

namespace Sample {

class SampleImplMock : public Sample::ISampleImpl
{
public:
    MOCK_METHOD0(setup, void());
    MOCK_METHOD0(teardown, void());
    MOCK_METHOD0(operate, void());
    MOCK_CONST_METHOD0(isErrorOccurred, bool());
};

} // namespace Sample
