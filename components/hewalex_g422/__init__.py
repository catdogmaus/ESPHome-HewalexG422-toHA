import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@smaksimowicz"]

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["binary_sensor", "sensor", "switch", "text_sensor"]
MULTI_CONF = True

CONF_HEWALEG_G422_ID = "hewalex_g422_id"
CONF_ENABLE_FAKE_TRAFFIC = "enable_fake_traffic"
CONF_RX_TIMEOUT = "rx_timeout"


hewalex_g422_ns = cg.esphome_ns.namespace("hewalex_g422")
HewalexG422= hewalex_g422_ns.class_("HewalexG422", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(HewalexG422),
            cv.Optional(CONF_ENABLE_FAKE_TRAFFIC, default=False): cv.boolean,
            cv.Optional(CONF_RX_TIMEOUT, default="150ms"): cv.positive_time_period_milliseconds,
        }
    )
    .extend(cv.polling_component_schema("2s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_enable_fake_traffic(config[CONF_ENABLE_FAKE_TRAFFIC]))
    cg.add(var.set_rx_timeout(config[CONF_RX_TIMEOUT]))
