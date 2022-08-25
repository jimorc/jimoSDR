#include "device.h"

namespace soapy
{
    device::device(const SoapySDR::Kwargs& kwargs) : _properties(kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    device::device(device&& dev) : _properties(dev._properties)
    {
        _device = dev._device;
        dev._device = nullptr;
    }

    device::~device() noexcept
    {
        if (_device != nullptr)
        {
            SoapySDR::Device::unmake(_device);
            _device = nullptr;
        }
    }

    const std::string device::operator[](const std::string& key) const
    { 
        if(_properties.find(key) != _properties.cend())
        {
            return _properties.at(key);
        }
        else
        {
            return "not found";
        }
    }

    const std::string device::driver_key() const
    {
        return _device->getDriverKey();
    }

    const std::string device::hardware_key() const
    {
        return _device->getHardwareKey();
    }

    const std::map<std::string, std::string> device::hardware_info() const
    {
        return _device->getHardwareInfo();
    }

    const std::string device::frontend_mapping(const direction dir) const
    {
        return _device->getFrontendMapping(static_cast<int>(dir));
    }

    size_t device::number_of_channels(const direction dir) const
    {
        return _device->getNumChannels(static_cast<int>(dir));
    }

    std::map<std::string, std::string> device::channel_info(const direction dir, 
                const size_t channel) const
    {
        return _device->getChannelInfo(static_cast<int>(dir), channel);
    }

    bool device::full_duplex(const direction dir, const size_t channel) const
    {
        return _device->getFullDuplex(static_cast<int>(dir), channel);
    }

    const std::vector<std::string> device::stream_formats(const direction dir,
                const size_t channel) const
    {
        return _device->getStreamFormats(static_cast<int>(dir), channel);
    }

    const std::tuple<std::string, double> device::native_stream_format(
                const direction dir, const size_t channel) const
    {
        double fullScale;
        auto format = _device->getNativeStreamFormat(static_cast<int>(dir), channel,
            fullScale);
        return std::make_tuple(format, fullScale);
    }
}