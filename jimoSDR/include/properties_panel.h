#pragma once

#include <xtd/xtd>
#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel();
        private:
            source_panel _source_panel;
    };
}