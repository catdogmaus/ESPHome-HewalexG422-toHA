# esphome-hewalex-g422
 

## Supported devices

* HEWALEX G422

## Schematics

```
                RS485-TTL (3.3V)
┌──────────┐                ┌─────────┐
│        10│<----- B- ----->│         │
│ G422    9│<----- A+------>│ ESP32/  │
│         ││                  ESP8266 │<-- 3.3V
│          │                │         │<-- GND
└──────────┘                └─────────┘


## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://smaksimowicz/esphome-hewalex-g422@main
```

or just use the `esp32-example.yaml` as proof of concept:

```bash
# Install esphome
pip3 install esphome

# Clone this external component
git clone https://github.com/smaksimowicz/esphome-hewalex-g422.git
cd esphome-hewalex-g422

# Create a secrets.yaml containing some setup specific secrets
cat > secrets.yaml <<EOF
wifi_ssid: MY_WIFI_SSID
wifi_password: MY_WIFI_PASSWORD

mqtt_host: MY_MQTT_HOST
mqtt_username: MY_MQTT_USERNAME
mqtt_password: MY_MQTT_PASSWORD
EOF

# Validate the configuration, create a binary, upload it, and start logs
# If you use a esp8266 run the esp8266-examle.yaml
esphome run esp32-example.yaml

```

## Example response all sensors enabled
```bash
[23:46:04][D][uart_debug:114]: >>> 69:02:01:84:00:00:0C:F6:02:00:01:00:40:80:00:32:64:00:BD:B2
[23:46:04][D][sensor:094]: 'T1 (Collectors temp)': Sending state 21.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'T2 (Tank bottom temp)': Sending state 24.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'T3 (Air separator temp)': Sending state 27.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'T4 (Tank top temp)': Sending state 43.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'T5 (Boiler outlet temp)': Sending state 0.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'T6 ()': Sending state 0.00000 °C with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'Collector Power (W)': Sending state 0.00000 W with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Consumption (W)': Sending state 0.00000 W with 0 decimals of accuracy
[23:46:04][D][uart_debug:114]: <<< 69:01:02:84:00:00:3E:0D:01:00:02:00:50:80:00:32:64:00:21:90:01:61:01:00:67:C7:00:00:00:00:00:00:00:00:00:00:00:00:17:07:10:06:16:38:13:00:15:00:18:00:1B:00:2B:00:00:00:00:00:00:00:00:00:00:00:00:00:F0:00:B2:93
[23:46:04][D][uart_debug:114]: >>> 69:02:01:84:00:00:0C:F6:02:00:01:00:40:80:00:32:96:00:C8:11
[23:46:04][D][sensor:094]: 'Collector Active (1/0)': Sending state 0.00000  with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Flow Rate (l/min)': Sending state 0.00000 l/min with 2 decimals of accuracy
[23:46:04][D][sensor:094]: 'Collector Pump (P) ON (1/0)': Sending state 0.00000  with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Boiler Pump (K) ON (1/0)': Sending state 0.00000  with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Circulation Pump (C) ON (1/0)': Sending state 0.00000  with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Collector Pump Speed (0-15)': Sending state 0.00000  with 0 decimals of accuracy
[23:46:04][D][sensor:094]: 'Total Energy (kWh)': Sending state 0.00000 kWh with 2 decimals of accuracy
[23:46:04][D][uart_debug:114]: <<< 69:01:02:84:00:00:3E:0D:01:00:02:00:50:80:00:32:96:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:04:00:0A:00:0A:00:01:00:01:00:00:00:E7:FF:0A:00:1E:00:01:00:01:00:00:00:01:00:01:00:00:00:00:45
[23:46:04][D][uart_debug:114]: >>> 69:02:01:84:00:00:0C:F6:02:00:01:00:40:80:00:32:C8:00:E5:A1
[23:46:04][D][uart_debug:114]: <<< 69:01:02:84:00:00:3E:0D:01:00:02:00:50:80:00:32:C8:00:01:00:01:00:01:00:00:00:08:00:05:00:55:00:29:00:28:00:30:00:4B:00:00:00:00:00:DC:05:01:00:5A:00:00:00:01:00:00:00:00:00:00:00:50:00:28:00:06:00:00:00:8F:1B
```

## Protocol

 

## Known issues

None.

## Goodies

 

## Debugging

If this component doesn't work out of the box for your device please update your configuration to enable the debug output of the UART component and increase the log level to the see outgoing and incoming serial traffic:

```
logger:
  level: DEBUG

uart:
  id: uart_0
  baud_rate: 9600
  tx_pin: GPIO4
  rx_pin: GPIO5
  debug:
    direction: BOTH
```

## References

 
