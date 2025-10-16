<span class="badge-buymeacoffee">
<a href="https://ko-fi.com/catdog58928" title="Donate to this project using Ko-Fi"><img src="https://img.shields.io/badge/Buy_me_coffee_and_biscuits-donate-yellow.svg?style=for-the-badge&logo=kofi" alt="Buy Me A Coffee donate button" /></a>
</span><br/>

# ESPHome-HewalexG422-toHA
 

## Supported devices

* HEWALEX G422

![Hardware](https://github.com/catdogmaus/ESPHome-HewalexG422-toHA/blob/main/files/sensors.jpg)

## What has changed
I am not coder and this repo exists because original code did not work for me and original owner seems to have abandon it. That means I have only made nessesary changes and probably are not able to maintain it. <br/>
This fork is intended to fix some shortcomings of original script.<br/>

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

Total Energy "fix" is made most part in ESPHome YAML. Reason for that is, I am not sure if it does work exactly same for all users. If your Total Energy output is still not correct it should be easy to correct for everybody. In yaml:
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
You need ESP32 board, some 12V to 5V board and TTL to RS485 (max 3585 module)
Keep in mind that in controller side, between A+ and B+ 120 Ω resistor may be needed but today most TTL boards already have onboard termination resistors. To use them proprly you must refer to your board documetation. Mostly for that you need to solder on specific jumper on your board. When you data cable is short you may not need resistor at all!
![Hardware](https://github.com/catdogmaus/ESPHome-HewalexG422-toHA/blob/main/files/scema.png)

## Issues

In my case - none. 

