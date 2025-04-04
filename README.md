# ESPHome-HewalexG422-toHA
 

## Supported devices

* HEWALEX G422

## What has changed

Tis fork is intended to fix some shortcomings of original script.
Hewalex documenation tells specifically that uart baud rate must be 38400! This is fixed as well in software as in sample yaml.
Fixed "Total Energy" output. In my case it did originally show some crazy -490000 kWh.
Fixed consumption. In my case it did not show any consumption when idle. This obviously can not be true.
Removed non working "Circulation pump switch" that referred to non existing GPIO.
Renamed sensors to more understandable/intuitive names.
Changed to (in my opinion) more pleasing icons.
Added "Today's Energy" for HA statistics.
Added "Today's Consuption".
Added mutch more understandable hardware instructions.

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://catdogmaus/ESPHome-HewalexG422-toHA@main
```
or just use the `esp32-example.yaml` 



## Issues

In my case - none. 

## References

 
