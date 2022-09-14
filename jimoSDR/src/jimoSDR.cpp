#include <sstream>
#include "devices.h"
#include "main_form.h"
#include "exceptions.h"

using namespace jimo_sdr;
using namespace xtd::forms;

soapy::devices soapy_devices;

int main()
{
    main_form form1;
    form1.show();
    try
    {
        form1.show_source_dlg();
        xtd::forms::application::run(form1);
    }
    catch(no_sdrs_exception& e)
    {
        // do nothing. User wants to exit because he has no SDRs
    }
    catch(std::exception& ex)
    {
        message_dialog msg_dlg;
        msg_dlg.buttons(message_dialog_buttons::ok);
        msg_dlg.icon(message_dialog_icon::error);

        std::stringstream ss;
        ss << "jimoSDR has encountered the following error and cannot continue:\n";
        ss << ex.what();
        ss << "\njimoSDR must terminate.";
        msg_dlg.message(ss.str());
    }
    return EXIT_SUCCESS;
}