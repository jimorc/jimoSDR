#include <xtd/xtd>
#include "GuiNotifier.h"

using namespace std::placeholders;

namespace jimo_sdr
{
    GuiNotifier::GuiNotifier(xtd::forms::control& synchronizer) : m_synchronizer(synchronizer) {}

    void GuiNotifier::OnGotReceivers(const std::vector<std::any>& args)
    {
        auto devices = any_cast<sdr::devices>(args[0]);
        GotReceiversEventArgs e(devices);
        gotReceivers.invoke(*this, e);
    }

    void GuiNotifier::OnGotDeviceDriverKey(const std::vector<std::any>& args)
    {
        auto key = any_cast<std::string>(args[0]);
        GotDeviceDriverKeyEventArgs e(key);
        gotDriverKey.invoke(*this, e);
    }

    void GuiNotifier::OnGotSampleRates(const std::vector<std::any>& args)
    {
        auto rates = any_cast<std::vector<double>>(args[0]);
        GotSampleRatesEventArgs e(rates);
        gotSampleRates.invoke(*this, e);
    }

    void GuiNotifier::OnGotCurrentSampleRate(const std::vector<std::any>& args)
    {
        auto rate = any_cast<double>(args[0]);
        GotCurrentSampleRateEventArgs e(rate);
        gotCurrentSampleRate.invoke(*this, e);
    }

    void GuiNotifier::NotifyGotReceivers(const std::any devices)
    {
        std::vector<std::any> args;
        args.push_back(devices);
        m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotReceivers }, args);
    }

    void GuiNotifier::NotifyGotDeviceDriverKey(const std::any key)
    {
        std::vector<std::any> args;
        args.push_back(key);
        m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotDeviceDriverKey }, args);
    }

    void GuiNotifier::NotifyGotSampleRates(const std::any rates)
    {
        std::vector<std::any> args;
        args.push_back(rates);
        m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotSampleRates }, args);
    }

    void GuiNotifier::NotifyGotCurrentSampleRate(const std::any rate)
    {
        std::vector<std::any> args;
        args.push_back(rate);
        m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotCurrentSampleRate }, args);
    }
}