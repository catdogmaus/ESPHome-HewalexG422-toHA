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
  
  void set_temperature_sensor(uint8_t temperature, sensor::Sensor *temperature_sensor) {
    this->temperatures_[temperature].temperature_sensor_ = temperature_sensor;
  }

 protected:
  uint16_t getWord(uint8_t *d);
  float getTemp(uint8_t * d, float scale);
  binary_sensor::BinarySensor *online_status_binary_sensor_;
  uint8_t current_data_package_ = 1;
  sensor::Sensor *temperature_t1_;
  sensor::Sensor *temperature_t2_;
  sensor::Sensor *temperature_t3_;
  sensor::Sensor *temperature_t4_;
  sensor::Sensor *temperature_t5_;
  sensor::Sensor *temperature_t6_;

 
  struct Temperature {
    sensor::Sensor *temperature_sensor_{nullptr};
  } temperatures_[6];
 

  std::string device_model_{"1.0.0"};
  std::vector<uint8_t> rx_buffer_;
  uint32_t last_byte_{0};
  uint16_t rx_timeout_{150};
  uint8_t no_response_count_{0};
  bool enable_fake_traffic_;

 
  bool parse_g422_responce_byte_(uint8_t byte);

  void hex2bin_(const char* src, char* target);
  int char2int_(char input);
  void HewalexRequest(uint8_t requestID); 
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_device_unavailable_();
  void reset_online_status_tracker_();
  void track_online_status_();
 
 
};

}  // namespace jbd_bms
}  // namespace esphome
