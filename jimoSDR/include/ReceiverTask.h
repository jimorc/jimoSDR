/// @file receiver_task.h
/// @copyright Copyright © 2022 Jim Orcheson. Licensed under GPL version 3.0

#pragma once

namespace jimo_sdr
{
    enum class ReceiverTask
    {
        getReceivers,           // get all attached receivers
        getDriverKey,           // get device driver key
        getCenterFrequency,     // get center frequency
        setCenterFrequency,     // set center frequency
        getSampleRates,         // get sample rates
        getCurrentSampleRate,   // get the current sample rate
        setSampleRate,          // set the sample rate
    };
}