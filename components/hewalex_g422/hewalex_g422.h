#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace hewalex_g422 {

class HewalexG422 : public uart::UARTDevice, public PollingComponent {
 public:
  void loop() override;
  void dump_config() override;
  void update() override;
  void setup() override;
 
  float get_setup_priority() const override;
  void set_enable_fake_traffic(bool enable_fake_traffic) { enable_fake_traffic_ = enable_fake_traffic; }
  void set_rx_timeout(uint16_t rx_timeout) { rx_timeout_ = rx_timeout; }

  void set_online_status_binary_sensor(binary_sensor::BinarySensor *online_status_binary_sensor) {
    this->online_status_binary_sensor_ = online_status_binary_sensor;
  }
 
  void set_total_energy_kwh_sensor(sensor::Sensor *total_energy_kwh) { total_energy_kwh_ = total_energy_kwh; }
  void set_collector_pump_speed_sensor(sensor::Sensor *collector_pump_speed) { collector_pump_speed_ = collector_pump_speed; }
  void set_circulation_pump_on_sensor(sensor::Sensor *circulation_pump_on) { circulation_pump_on_ = circulation_pump_on; }
  void set_boiler_pump_on_sensor(sensor::Sensor *boiler_pump_on) { boiler_pump_on_ = boiler_pump_on; }
  void set_collector_pump_on_sensor(sensor::Sensor *collector_pump_on) { collector_pump_on_ = collector_pump_on; }
  void set_flow_rate_sensor(sensor::Sensor *flow_rate) { flow_rate_ = flow_rate; }
  void set_collector_active_sensor(sensor::Sensor *collector_active) { collector_active_ = collector_active; }
  void set_collector_power_sensor(sensor::Sensor *collector_power) { collector_power_ = collector_power; } 
  void set_consumption_w_sensor(sensor::Sensor *consumption_w) { consumption_w_ = consumption_w; } 
  void set_temperature_sensor(uint8_t temperature, sensor::Sensor *temperature_sensor) {
    this->temperatures_[temperature].temperature_sensor_ = temperature_sensor;
  }

  void set_device_date_text_sensor(text_sensor::TextSensor *device_date) { this->device_date_text_sensor_ = device_date; }
  void set_device_time_text_sensor(text_sensor::TextSensor *device_time) { this->device_time_text_sensor_ = device_time; }

  // Public getter methods for pump states
  float get_collector_pump_state() const {
    if (this->collector_pump_on_ != nullptr) {
      return this->collector_pump_on_->state;
    }
    return 0;
  }

  float get_boiler_pump_state() const {
    if (this->boiler_pump_on_ != nullptr) {
      return this->boiler_pump_on_->state;
    }
    return 0;
  }

  float get_circulation_pump_state() const {
    if (this->circulation_pump_on_ != nullptr) {
      return this->circulation_pump_on_->state;
    }
    return 0;
  }

  float get_collector_active_state() const {
    if (this->collector_active_ != nullptr) {
      return this->collector_active_->state;
    }
    return 0;
  }

 protected:
  uint16_t getWord(const uint8_t *d);
  float getTemp(const uint8_t *d, float scale);
  
  binary_sensor::BinarySensor *online_status_binary_sensor_{nullptr};
  text_sensor::TextSensor *device_date_text_sensor_{nullptr};
  text_sensor::TextSensor *device_time_text_sensor_{nullptr};

  uint8_t current_data_package_ = 1;
  sensor::Sensor *collector_power_{nullptr};
  sensor::Sensor *consumption_w_{nullptr};
  sensor::Sensor *collector_active_{nullptr};
  sensor::Sensor *flow_rate_{nullptr};
  sensor::Sensor *collector_pump_on_{nullptr};
  sensor::Sensor *boiler_pump_on_{nullptr};
  sensor::Sensor *circulation_pump_on_{nullptr};
  sensor::Sensor *collector_pump_speed_{nullptr};
  sensor::Sensor *total_energy_kwh_{nullptr};

  struct Temperature {
    sensor::Sensor *temperature_sensor_{nullptr};
  } temperatures_[6];

  std::string device_model_{"1.0.0"};
  std::vector<uint8_t> rx_buffer_;
  uint32_t last_byte_{0};
  uint16_t rx_timeout_{150};
  uint8_t no_response_count_{0};
  bool enable_fake_traffic_{false};

  bool parse_g422_response_byte_(uint8_t byte);

  void hex2bin_(const char* src, uint8_t* target);
  int char2int_(char input);
  void HewalexRequest(uint8_t requestID); 
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_device_unavailable_();
  void reset_online_status_tracker_();
  void track_online_status_();
};

}  // namespace hewalex_g422
}  // namespace esphome
