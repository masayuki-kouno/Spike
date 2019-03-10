#include "SampleStateMachine.h"
#include <regex>
#include <boost/sml.hpp>

namespace sml = boost::sml;

namespace Sample {

namespace { // suppress ODR warning

/// Events
struct Fake {};
struct Started {};
struct Operated {};
struct Stopped {};
struct ErrorOccurred {};

/// Actions
auto setup = [](ISampleImpl* impl) {
    impl->setup();
};
auto teardown = [](ISampleImpl* impl) {
    impl->teardown();
};
auto operate = [](ISampleImpl* impl) {
    impl->operate();
};

/// Guard conditions
auto isErrorOccurred = [](ISampleImpl* impl) {
    return impl->isErrorOccurred();
};

struct Entire
{
    struct Idle {};
    struct Running {};
    auto operator()() const noexcept {
        using namespace sml;
        // clang-format off
        return make_transition_table(
           *state<Idle>    + event<Started>                = state<Running>,
            state<Running> + event<Fake> [isErrorOccurred] = state<Idle>, // lambda transition
            state<Running> + event<Stopped>                = state<Idle>,
            state<Running> + event<ErrorOccurred>          = state<Idle>,
            state<Running> + event<Operated>  / operate,
            state<Running> + sml::on_entry<_> / setup,
            state<Running> + sml::on_exit<_>  / teardown
        );
        // clang-format on
    }
};

} // suppress ODR warning

struct SampleStateMachine::STMImpl
{
    sml::sm<Entire> sm;
    STMImpl(ISampleImpl* impl) : sm(impl) {}
};

SampleStateMachine::SampleStateMachine(ISampleImpl* impl)
    : m_stmImpl(new SampleStateMachine::STMImpl(impl))
{
}

SampleStateMachine::~SampleStateMachine()
{
}

std::string SampleStateMachine::GetStateName() const
{
    const std::string Prefix = "Sample::\\{anonymous\\}::Entire::";
    const std::string Separator = "::";

    std::string stateName;
    m_stmImpl->sm.visit_current_states(
                [&](auto state) { stateName = state.c_str(); });

    const auto shortName = std::regex_replace(stateName, std::regex("\\" + Prefix), "");
    return std::regex_replace(shortName, std::regex("\\" + Separator), "/");
}

void SampleStateMachine::PerformEvent(Event event)
{
    switch (event) {
    case Event::Started:
        m_stmImpl->sm.process_event(Started());
        break;
    case Event::Operated:
        m_stmImpl->sm.process_event(Operated());
        break;
    case Event::Stopped:
        m_stmImpl->sm.process_event(Stopped());
        break;
    case Event::ErrorOccurred:
        m_stmImpl->sm.process_event(ErrorOccurred());
        break;
    default:
        break;
    }
    // boost::sml does not support below transition(lambda)
    //   "src_state + [ guard ] = dst_state"
    // so perform a dummy event and evaluate the guard condition
    m_stmImpl->sm.process_event(Fake());
}

} // namespace Sample
