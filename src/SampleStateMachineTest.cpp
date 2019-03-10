#include "SampleStateMachine.h"
#include "SampleImplMock.h"
#include <gtest/gtest.h>
#include <iostream>

using ::testing::AnyNumber;
using ::testing::InSequence;
using ::testing::Return;

using STM = Sample::SampleStateMachine;

namespace Sample {

class SampleStateMachineTest : public testing::Test
{
protected:
    SampleImplMock m_mock;
};

TEST_F(SampleStateMachineTest, Started)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
//    std::cout << stm.GetStateName() << std::endl;
}

TEST_F(SampleStateMachineTest, Operated)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
        // Operated
        EXPECT_CALL(m_mock, operate()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
    stm.PerformEvent(STM::Event::Operated);
}

TEST_F(SampleStateMachineTest, Stopped)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
        // Stopped
        EXPECT_CALL(m_mock, teardown()).Times(1);
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
    stm.PerformEvent(STM::Event::Stopped);
}

TEST_F(SampleStateMachineTest, ErrorOccurred)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
        // ErrorOccurred
        EXPECT_CALL(m_mock, teardown()).Times(1);
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
    stm.PerformEvent(STM::Event::ErrorOccurred);
}

TEST_F(SampleStateMachineTest, StartedWhileErrorOccured)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(true));
        EXPECT_CALL(m_mock, teardown()).Times(1);
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
}

TEST_F(SampleStateMachineTest, OperatedWhileErrorOccured)
{
    {
        InSequence seq;

        // Started
        EXPECT_CALL(m_mock, setup()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(false));
        // Operated
        EXPECT_CALL(m_mock, operate()).Times(1);
        EXPECT_CALL(m_mock, isErrorOccurred())
                .Times(1).WillOnce(Return(true));
        EXPECT_CALL(m_mock, teardown()).Times(1);
    }

    STM stm(&m_mock);
    stm.PerformEvent(STM::Event::Started);
    stm.PerformEvent(STM::Event::Operated);
}

} // namespace Sample
