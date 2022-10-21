#include "SourcePanel.h"
#include "ReceiverAction.h"
#include "RadioReceiver.h"
#include "GotReceiversEventArgs.h"
#include "GotDeviceDriverKeyEventArgs.h"
#include "exceptions.h"


using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    SourcePanel::SourcePanel(device_properties& deviceProps, GuiNotifier& notifier) 
        : m_notifier(notifier), m_deviceProps(deviceProps)
    {
        width(300);
        m_panelLabel.text("    Source");
        m_panelLabel.dock(dock_style::top);
        m_notifier.gotReceivers += xtd::event_handler(*this, &SourcePanel::GotReceivers);
        m_notifier.gotDriverKey += xtd::event_handler(*this, &SourcePanel::GotDriverKey);

        m_sources.drop_down_style(combo_box_style::drop_down_list);
        m_sources.dock(dock_style::top);
        m_sources.items().push_back("None");
        m_sources.drop_down += xtd::event_handler(*this, &SourcePanel::SourcesDropDown);
        m_sources.selected_value_changed += xtd::event_handler(*this, &SourcePanel::SourceValueChanged);

        m_sampleRatesLabel.text("Sample Rate: ");
        m_sampleRatesLabel.text_align(content_alignment::middle_right);
        m_sampleRatesLabel.dock(dock_style::left);
        m_sampleRatesLabel.width(150);

        m_sampleRates.dock(dock_style::right);
        m_sampleRates.width(150);

        m_sampleRatesPanel << m_sampleRatesLabel << m_sampleRates;

        m_spaceLabel1.dock(dock_style::top);
        m_spaceLabel2.dock(dock_style::top);

        m_groupBoxPanel.dock(dock_style::top);
        m_groupBoxPanel << m_spaceLabel1 << m_sources << m_spaceLabel2 << m_sampleRatesPanel;
        m_groupBoxPanel.back_color(drawing::color::pink);

        m_groupBoxPanel.control_layout_style(m_sources, {20, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_spaceLabel1, { 3, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_sampleRatesPanel, {20, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_spaceLabel2, { 3, size_type::absolute, true});

        *this << m_panelLabel << m_groupBoxPanel;
    }

    void SourcePanel::SourcesDropDown(xtd::object& sender, const xtd::event_args& e)
    {
            GetReceivers();
    }

    void SourcePanel::GetReceivers()
    {
        ReceiverAction getReceivers({ ReceiverTask::getReceivers,
            std::bind(&GuiNotifier::NotifyGotReceivers, &m_notifier, _1), nullptr} );
        RadioReceiver::GetInstance().QueueTask(getReceivers);
    }

    void SourcePanel::GotReceivers(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const GotReceiversEventArgs&>(e);
        m_devices = args.Devices();
        if (m_devices.cbegin() == m_devices.cend())
        {
            message_dialog msgDialog;
            msgDialog.buttons(message_dialog_buttons::ok_cancel);
            std::string message("There are no SDRs attached.\nAttach one, then click OK\n"
                + std::string("or click Cancel so you can close jimoSDR."));
            msgDialog.message(message);
            msgDialog.text("No SDRs Found");
            auto result = msgDialog.show_dialog(*this);
            if (result == dialog_result::ok)
            {
                GetReceivers();
            }
        }
        else
        {
            m_sources.items().clear();
            for (auto device : m_devices)
            {
                ReceiverAction getDriverKey({ ReceiverTask::getDriverKey,
                    std::bind(&GuiNotifier::NotifyGotDeviceDriverKey, &m_notifier, _1), device} );
                RadioReceiver::GetInstance().QueueTask(getDriverKey);
            }
       }
    }

    void SourcePanel::GotDriverKey(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const GotDeviceDriverKeyEventArgs&>(e);
        auto key = args.DriverKey();
        m_sources.items().push_back(key);
        // If there is only one device, we select it now. No point in waiting for the user
        // to select it.
        if (m_devices.size() == 1)
        {
            m_sources.selected_index(0);
        }
    }

    void SourcePanel::SourceValueChanged(xtd::object& sender, const xtd::event_args& e)
    {
        auto index = m_sources.selected_index();
        m_deviceProps.device(m_devices[index]);
    }
}