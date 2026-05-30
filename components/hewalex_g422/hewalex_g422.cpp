#include "hewalex_g422.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace hewalex_g422 {

static const uint8_t MAX_NO_RESPONSE_COUNT = 5;
static const char *const TAG = "hewalex_g422";

void HewalexG422::setup() { 
   current_data_package_ = 1;
}

void HewalexG422::loop() {
    const uint32_t now = millis();
    if (now - this->last_byte_ > this->rx_timeout_) {
      if (!this->rx_buffer_.empty()) {
        ESP_LOGVV(TAG, "Buffer cleared due to timeout: %s",
                  format_hex_pretty(&this->rx_buffer_.front(), this->rx_buffer_.size()).c_str());
        this->rx_buffer_.clear();
      }
      this->last_byte_ = now;
    }

    while (this->available()) {
      uint8_t byte;
      this->read_byte(&byte);
      if (this->parse_g422_response_byte_(byte)) {
        this->last_byte_ = now;
      } else {
        if (!this->rx_buffer_.empty()) {
          ESP_LOGVV(TAG, "Buffer cleared due to reset: %s",
                    format_hex_pretty(&this->rx_buffer_.front(), this->rx_buffer_.size()).c_str());
          this->rx_buffer_.clear();
        }
      }
    }
}

bool HewalexG422::parse_g422_response_byte_(uint8_t byte) {
  size_t at = this->rx_buffer_.size();
  this->rx_buffer_.push_back(byte);
  const uint8_t *raw = &this->rx_buffer_[0];

  if (at == 0) {
    if (raw[0] != 0x69) {
      ESP_LOGW(TAG, "Invalid header: 0x%02X", raw[0]);
      // return false to reset buffer
      return false;
    }
    ESP_LOGVV(TAG, "buffer at %d", at);
    return true;
  }

  if (at < 69) {      
    return true;
  }
    
  if (70 != 8 + raw[6]) {
    ESP_LOGI(TAG, "ERROR: Reported packet size does not match response length");
    return false;
  }
 
  uint8_t fncID = raw[12];
  if (fncID != 0x50) {
    ESP_LOGI(TAG, "ERROR: Protocol error, data not consistent");
    return false;
  }

  // Valid packet parsed successfully, reset online status counters
  this->reset_online_status_tracker_();

  uint8_t startReg = raw[16];
  uint16_t pump_states = 0; 
  for (uint8_t iPacketPos = 0; iPacketPos < raw[15]; iPacketPos++) {
     if (iPacketPos % 2 == 0) {
         uint8_t iReg = iPacketPos + startReg;

         // Ensure safe memory access checks on variable-sized inputs
         if (18 + iPacketPos + 1 >= this->rx_buffer_.size()) {
             ESP_LOGW(TAG, "Parsing skipped: buffer index out of bounds");
             break;
         }

         switch (iReg) {
          case 120: // Date (Retrieves Year, Month, Day)
               if (18 + iPacketPos + 2 < this->rx_buffer_.size()) {
                   if (this->device_date_text_sensor_ != nullptr) {
                       char date_str[16];
                       // Formats to YYYY-MM-DD by prefixing "20" to the year byte
                       sprintf(date_str, "20%02d-%02d-%02d", raw[18+iPacketPos], raw[18+iPacketPos+1], raw[18+iPacketPos+2]);
                       this->publish_state_(this->device_date_text_sensor_, std::string(date_str));
                   }
               }
          break;
          case 124: // Time (Retrieves Hour, Minute)
               if (18 + iPacketPos + 2 < this->rx_buffer_.size()) {
                   if (this->device_time_text_sensor_ != nullptr) {
                       char time_str[16];
                       // Changed from "%02d:%02d:%02d" to "%02d:%02d" (Drops the seconds byte)
                       sprintf(time_str, "%02d:%02d", raw[18+iPacketPos], raw[18+iPacketPos+1]);
                       this->publish_state_(this->device_time_text_sensor_, std::string(time_str));
                   }
               }
          break;
          case 128: //T1
               this->publish_state_(this->temperatures_[0].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 130: //T2
               this->publish_state_(this->temperatures_[1].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 132: //T3
               this->publish_state_(this->temperatures_[2].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 134: //T4
               this->publish_state_(this->temperatures_[3].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 136: //T5
               this->publish_state_(this->temperatures_[4].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 138: //T6
               this->publish_state_(this->temperatures_[5].temperature_sensor_, this->getTemp(&raw[18+iPacketPos], 1.0f));
          break;
          case 144: //CollectorPower
               this->publish_state_(this->collector_power_, this->getWord(&raw[18+iPacketPos]));
          break;
          case 148: //Consumption
               this->publish_state_(this->consumption_w_, 0.1f * this->getWord(&raw[18+iPacketPos]));
          break;
          case 150: //Collector Active
               this->publish_state_(this->collector_active_, this->getWord(&raw[18+iPacketPos]));
          break;
          case 152: //FlowRate
               this->publish_state_(this->flow_rate_, 0.1f * this->getWord(&raw[18+iPacketPos]));
          break;
          case 154: //CollectorPumpON BoilerPumpON CirculationPumpOn
               pump_states = this->getWord(&raw[18+iPacketPos]);
               this->publish_state_(this->collector_pump_on_, (pump_states & 1));
               this->publish_state_(this->boiler_pump_on_, (pump_states & 2) >> 1);           
               this->publish_state_(this->circulation_pump_on_, (pump_states & 4) >> 2);
          break;
          case 156:  //CollectorPumpSpeed
               this->publish_state_(this->collector_pump_speed_, this->getWord(&raw[18+iPacketPos]));
          break;
          case 166:  //TotalEnergy
               this->publish_state_(this->total_energy_kwh_, 0.1f * this->getWord(&raw[18+iPacketPos]));
          break;
         }
     }
  }
  
  if (current_data_package_ < 3) {
     current_data_package_ += 1;
     HewalexRequest(current_data_package_);
  } else {
     current_data_package_ = 1;
  }
  // return false to reset buffer
  return false;
}

void HewalexG422::hex2bin_(const char* src, uint8_t* target) {
  while (*src && src[1]) {
    *(target++) = char2int_(*src) * 16 + char2int_(src[1]);
    src += 2;
  }
}

int HewalexG422::char2int_(char input) {
  if (input >= '0' && input <= '9')
    return input - '0';
  if (input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if (input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  return 0;
}

uint16_t HewalexG422::getWord(const uint8_t *d) {
  return ((uint16_t)d[1] << 8) | d[0];
}

float HewalexG422::getTemp(const uint8_t *d, float scale) {
  int16_t word = this->getWord(d);
  if (word & 0x8000)
    word = word - 0x10000;
  return word * scale;
}

void HewalexG422::HewalexRequest(uint8_t requestID) {
  uint8_t tx_buffer[20];
  switch (requestID) {
   case 1: //Requesting bytes 100-149
    hex2bin_("6902018400000cf602000100408000326400bdb2", tx_buffer);
    this->write_array(tx_buffer, 20); // request 50 registers from 100
    this->flush();
    break;
  case 2: //Requesting bytes 150-199
    hex2bin_("6902018400000cf602000100408000329600c811", tx_buffer);
    this->write_array(tx_buffer, 20); // request 50 registers from 150
    this->flush();
    break;
  case 3: //Requesting bytes 200-249
    hex2bin_("6902018400000cf60200010040800032c800e5a1", tx_buffer);
    this->write_array(tx_buffer, 20); // request 50 registers from 200
    this->flush();
    break;
  }
}

void HewalexG422::update() {
  this->track_online_status_();

  current_data_package_ = 1;
  HewalexRequest(1);
}

void HewalexG422::dump_config() {
  ESP_LOGCONFIG(TAG, "Hewalex_G422:");
  ESP_LOGCONFIG(TAG, "  RX timeout: %d ms", this->rx_timeout_);
  ESP_LOGCONFIG(TAG, "  Fake traffic enabled: %s", YESNO(this->enable_fake_traffic_));
  
  LOG_SENSOR("", "T1", this->temperatures_[0].temperature_sensor_);
  LOG_SENSOR("", "T2", this->temperatures_[1].temperature_sensor_);
  LOG_SENSOR("", "T3", this->temperatures_[2].temperature_sensor_);
  LOG_SENSOR("", "T4", this->temperatures_[3].temperature_sensor_);
  LOG_SENSOR("", "T5", this->temperatures_[4].temperature_sensor_);
  LOG_SENSOR("", "T6", this->temperatures_[5].temperature_sensor_);
 
  LOG_SENSOR("", "collector_power_", this->collector_power_);
  LOG_SENSOR("", "consumption_w_", this->consumption_w_);
  LOG_SENSOR("", "collector_active_", this->collector_active_);
  LOG_SENSOR("", "flow_rate_", this->flow_rate_);
  LOG_SENSOR("", "collector_pump_on_", this->collector_pump_on_);
  LOG_SENSOR("", "boiler_pump_on_", this->boiler_pump_on_);
  LOG_SENSOR("", "circulation_pump_on_", this->circulation_pump_on_);
  LOG_SENSOR("", "collector_pump_speed_", this->collector_pump_speed_);
  LOG_SENSOR("", "total_energy_kwh_", this->total_energy_kwh_);

  this->check_uart_settings(38400);
}

void HewalexG422::track_online_status_() {
  if (this->no_response_count_ < MAX_NO_RESPONSE_COUNT) {
    this->no_response_count_++;
  }
  if (this->no_response_count_ == MAX_NO_RESPONSE_COUNT) {
    this->publish_device_unavailable_();
    this->no_response_count_++;
  }
}

void HewalexG422::reset_online_status_tracker_() {
  this->no_response_count_ = 0;
  this->publish_state_(this->online_status_binary_sensor_, true);
}

void HewalexG422::publish_device_unavailable_() {
  this->publish_state_(this->online_status_binary_sensor_, false);

  this->publish_state_(this->collector_power_, NAN);
  this->publish_state_(this->consumption_w_, NAN);
  this->publish_state_(this->collector_active_, NAN);
  this->publish_state_(this->flow_rate_, NAN);
  this->publish_state_(this->collector_pump_on_, NAN);
  this->publish_state_(this->boiler_pump_on_, NAN);
  this->publish_state_(this->circulation_pump_on_, NAN);
  this->publish_state_(this->collector_pump_speed_, NAN);
  this->publish_state_(this->total_energy_kwh_, NAN);

  for (auto &temperature : this->temperatures_) {
    this->publish_state_(temperature.temperature_sensor_, NAN);
  }
}

float HewalexG422::get_setup_priority() const {
  return setup_priority::BUS - 1.0f;
}

void HewalexG422::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;
  binary_sensor->publish_state(state);
}

void HewalexG422::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;
  sensor->publish_state(value);
}

void HewalexG422::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;
  text_sensor->publish_state(state);
}

}  // namespace hewalex_g422
}  // namespace esphome
