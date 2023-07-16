import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
 
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_EMPTY,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_EMPTY, 
    UNIT_PERCENT,
    UNIT_WATT ,
    UNIT_KILOWATT_HOURS ,
 
)

from . import CONF_HEWALEG_G422_ID, HewalexG422

DEPENDENCIES = ["hewalex_g422"]

CODEOWNERS = ["@smaksimowicz"]

 

CONF_TEMPERATURE_1 = "temperature_1"
CONF_TEMPERATURE_2 = "temperature_2"
CONF_TEMPERATURE_3 = "temperature_3"
CONF_TEMPERATURE_4 = "temperature_4"
CONF_TEMPERATURE_5 = "temperature_5"
CONF_TEMPERATURE_6 = "temperature_6"
 
 
CONF_COLLECTOR_POWER = "collector_power"
CONF_CONSUPTION_W = "consumption_w"
CONF_COLLECTOR_ACTIVE = "collector_active"
CONF_FLOW_RATE = "flow_rate"
CONF_COLLECTOR_PUMP_ON = "collector_pump_on"
CONF_BOILER_PUMP_ON =  "boiler_pump_on"
CONF_CIRCULATION_PUMP_ON = "circulation_pump_on"
CONF_COLLECTOR_PUMP_SPEED = "collector_pump_speed"
CONF_TOTAL_ENERGY_KWH =  "total_energy_kwh"
 
ICON_TEMPERATURE = "mdi:temperature-celsius"
ICON_SOLAR_POWER = "mdi:solar-power" 
 
TEMPERATURES = [
    CONF_TEMPERATURE_1,
    CONF_TEMPERATURE_2,
    CONF_TEMPERATURE_3,
    CONF_TEMPERATURE_4,
    CONF_TEMPERATURE_5,
    CONF_TEMPERATURE_6,
]

SENSORS = [
    CONF_COLLECTOR_POWER,
    CONF_CONSUPTION_W,
    CONF_COLLECTOR_ACTIVE,
    CONF_FLOW_RATE,
    CONF_COLLECTOR_PUMP_ON,
    CONF_BOILER_PUMP_ON,
    CONF_CIRCULATION_PUMP_ON,
    CONF_COLLECTOR_PUMP_SPEED,
    CONF_TOTAL_ENERGY_KWH,
]

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HEWALEG_G422_ID): cv.use_id(HewalexG422),
        cv.Optional(CONF_TEMPERATURE_1): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TEMPERATURE_2): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TEMPERATURE_3): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TEMPERATURE_4): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TEMPERATURE_5): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TEMPERATURE_6): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_TEMPERATURE,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_COLLECTOR_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT ,
            icon=ICON_SOLAR_POWER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
         cv.Optional(CONF_CONSUPTION_W): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT ,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_COLLECTOR_ACTIVE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_FLOW_RATE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
         cv.Optional(CONF_COLLECTOR_PUMP_ON): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
         cv.Optional(CONF_BOILER_PUMP_ON): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
         cv.Optional(CONF_CIRCULATION_PUMP_ON): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),  
        cv.Optional(CONF_COLLECTOR_PUMP_SPEED): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
        cv.Optional(CONF_TOTAL_ENERGY_KWH): sensor.sensor_schema(
            unit_of_measurement=UNIT_KILOWATT_HOURS ,
            icon=ICON_EMPTY,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_ENERGY,
            state_class=STATE_CLASS_MEASUREMENT,
        ), 
 
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_HEWALEG_G422_ID])
    for i, key in enumerate(TEMPERATURES):
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(hub.set_temperature_sensor(i, sens))
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
