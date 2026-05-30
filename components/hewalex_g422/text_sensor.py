# components/hewalex_g422/text_sensor.py
"""Text sensors for Hewalex G422."""

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor

from . import CONF_HEWALEG_G422_ID, HewalexG422
from .const import (
    CONF_DEVICE_DATE,
    CONF_DEVICE_TIME,
)

TYPES = {
    CONF_DEVICE_DATE: text_sensor.text_sensor_schema(
        icon="mdi:calendar",
    ).extend(),
    CONF_DEVICE_TIME: text_sensor.text_sensor_schema(
        icon="mdi:clock",
    ).extend(),
}

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HEWALEG_G422_ID): cv.use_id(HewalexG422),
        cv.Optional(CONF_DEVICE_DATE): TYPES[CONF_DEVICE_DATE],
        cv.Optional(CONF_DEVICE_TIME): TYPES[CONF_DEVICE_TIME],
    }
)


async def to_code(config):
    """Code generation for Hewalex G422 text sensors."""
    hub = await cg.get_variable(config[CONF_HEWALEG_G422_ID])
    if CONF_DEVICE_DATE in config:
        sens = await text_sensor.new_text_sensor(config[CONF_DEVICE_DATE])
        cg.add(hub.set_device_date_text_sensor(sens))
    if CONF_DEVICE_TIME in config:
        sens = await text_sensor.new_text_sensor(config[CONF_DEVICE_TIME])
        cg.add(hub.set_device_time_text_sensor(sens))
