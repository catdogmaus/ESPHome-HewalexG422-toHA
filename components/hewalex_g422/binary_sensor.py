import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_CONNECTIVITY,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

from . import CONF_HEWALEG_G422_ID, HewalexG422
 

DEPENDENCIES = ["hewalex_g422"]

CODEOWNERS = ["@smaksimowicz"]

 

BINARY_SENSORS = [
 
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HEWALEG_G422_ID): cv.use_id(HewalexG422),
        
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_HEWALEG_G422_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
