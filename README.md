# ESPHome-HewalexG422-toHA
 

## Supported devices

* HEWALEX G422

## What has changed

Tis fork is intended to fix some shortcomings of original script.<br/>

Hewalex documenation tells specifically that uart baud rate must be 38400! This is fixed as well in software as in sample yaml.<br/>
Fixed "Total Energy" output. In my case it did originally show some crazy -490000 kWh.<br/>
Fixed consumption. In my case it did not show any consumption when idle. This obviously can not be true.<br/>
Removed non working "Circulation pump switch" that referred to non existing GPIO.<br/>
Renamed sensors to more understandable/intuitive names.<br/>
Changed to (in my opinion) more pleasing icons.<br/>
Added "Today's Energy" for HA statistics. This uses ESPHome built in mechanism so its output is dependent of correct Total Energy numbers.<br/>
Added "Today's Consuption".<br/>
Added mutch more understandable hardware instructions.

## Total Energy

Total Energy "fix" is made in ESPHome YAML. Reason for that is, I am not sure if it does work exactly same for all users. If your Total Energy output is still not correct it should be easy to correct for everybody. In yaml:
```
  - platform: template
    name: "Collector Total Energy Adjusted" # Output actual energy
    device_class: energy
    state_class: total_increasing
    id: total_energy
    lambda: |-
      return id(total_energy_kwh).state + 6553.6;
    unit_of_measurement: "kWh"
```
calculate and change the number added to lambda .state 

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://catdogmaus/ESPHome-HewalexG422-toHA@main
```
or just use the `esp32-example.yaml` 

## Hardware 



## Issues

In my case - none. 

