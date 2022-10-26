#pragma once

#include "SoapySDR/Device.hpp"
#include "SoapySDR/Constants.h"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "types.h"

namespace sdr
{
    class Device
    {
        public:
            enum class direction
            {
                rx = SOAPY_SDR_RX,
                tx = SOAPY_SDR_TX
            };

            Device() = delete;
            Device(const SoapySDR::Kwargs& kwargs);
            Device(const Device&) = delete;
            Device(Device&&) = delete;
            ~Device() noexcept; 
            Device& operator=(const Device&) = delete;
            Device&& operator=(Device&&) = delete;
            const std::string operator[](const std::string& key) const;
            operator std::map<std::string, std::string>() { return _properties; }
            const std::string GetDriverKey() const;
            const std::string GetHardwareKey() const;
            const std::map<std::string, std::string> GetHardwareInfo() const;
            const std::string GetFrontendMapping(const direction dir) const;
            size_t GetNumberOfChannels(const direction dir) const;
            std::map<std::string, std::string> GetChannelInfo(const direction dir, 
                const size_t channel) const;
            bool GetFullDuplex(const direction dir, const size_t channel) const;
            const std::vector<std::string> GetStreamFormats(const direction dir,
                const size_t channel) const;
            const std::tuple<std::string, double> GetNativeStreamFormat(
                const direction dir, const size_t channel) const;
            std::vector<sdr_arg_info> GetStreamArgsInfo(const direction dir,
                const size_t channel) const;
            double GetCenterFrequency(const direction dir, const size_t channel) const;
            void SetCenterFrequency(const direction dir, const size_t channel, const double frequency);
            double sample_rate(const direction dir, const size_t channel) const;
            void sample_rate(const direction dir, const size_t channel,
                const double rate);
            std::vector<double> sample_rates(const direction dir,
                const size_t channel) const;
            std::vector<std::string> gpio_banks() const;
            std::vector<std::string> register_interfaces() const;
        private:
            std::map<std::string, std::string> _properties;
            SoapySDR::Device* _device;
    };
}