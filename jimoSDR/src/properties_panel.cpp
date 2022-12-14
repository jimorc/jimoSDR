#include "properties_panel.h"
#include "MainForm.h"

using namespace xtd::forms;

namespace jimo_sdr
{
    properties_panel::properties_panel(MainForm& f, device_properties& deviceProps, GuiNotifier& notifier)
        : _main_form(f), m_deviceProps(deviceProps), m_sourcePanel(m_deviceProps, notifier)
    {
        auto_scroll(true);
        auto_size_mode(auto_size_mode::grow_and_shrink);
        anchor(anchor_styles::top | anchor_styles::bottom | anchor_styles::left);
        m_sourcePanel.sourceChanged += xtd::event_handler(*this, &properties_panel::OnSourceChanged);
        *this << m_sourcePanel;

    }

    void properties_panel::source(const std::string& src) noexcept
    {
        _source_button.text(src);
    }

    void properties_panel::OnSourceChanged(xtd::object& sender, const xtd::event_args& e)
    {
        xtd::event_handler handler = sourceChanged;
        if (!handler.is_empty())
        {
            handler.invoke(sender, e);
        }
    }
}