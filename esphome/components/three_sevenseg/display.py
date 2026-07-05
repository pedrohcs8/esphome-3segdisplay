import esphome.codegen as cg
from esphome.components import display, spi
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_LAMBDA
from esphome.pins import gpio_output_pin_schema

three_sevenseg_ns = cg.esphome_ns.namespace("three_sevenseg")
THREE_SEVENSEGComponent = three_sevenseg_ns.class_(
    "THREE_SEVENSEGComponent", cg.PollingComponent, spi.SPIDevice
)
THREE_SEVENSEGComponentRef = THREE_SEVENSEGComponent.operator("ref")

CONF_A_PIN = "a_pin"
CONF_B_PIN = "b_pin"
CONF_C_PIN = "c_pin"
CONF_D_PIN = "d_pin"
CONF_E_PIN = "e_pin"
CONF_F_PIN = "f_pin"
CONF_G_PIN = "g_pin"
CONF_DP_PIN = "dp_pin"
CONF_D1_PIN = "d1_pin"
CONF_D2_PIN = "d2_pin"
CONF_D3_PIN = "d3_pin"

CONFIG_SCHEMA = display.BASIC_DISPLAY_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(THREE_SEVENSEGComponent),
        cv.Required(CONF_A_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_B_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_C_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_D_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_E_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_F_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_G_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_DP_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_D1_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_D2_PIN): cv.ensure_schema(gpio_output_pin_schema),
        cv.Required(CONF_D3_PIN): cv.ensure_schema(gpio_output_pin_schema),
    }
).extend(cv.polling_component_schema("25ms"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await display.register_display(var, config)

    pin_a = await cg.gpio_pin_expression(config[CONF_A_PIN])
    cg.add(var.set_a_pin(pin_a))

    pin_b = await cg.gpio_pin_expression(config[CONF_B_PIN])
    cg.add(var.set_b_pin(pin_b))

    pin_c = await cg.gpio_pin_expression(config[CONF_C_PIN])
    cg.add(var.set_c_pin(pin_c))

    pin_d = await cg.gpio_pin_expression(config[CONF_D_PIN])
    cg.add(var.set_d_pin(pin_d))

    pin_e = await cg.gpio_pin_expression(config[CONF_E_PIN])
    cg.add(var.set_e_pin(pin_e))

    pin_f = await cg.gpio_pin_expression(config[CONF_F_PIN])
    cg.add(var.set_f_pin(pin_f))

    pin_g = await cg.gpio_pin_expression(config[CONF_G_PIN])
    cg.add(var.set_g_pin(pin_g))

    pin_dp = await cg.gpio_pin_expression(config[CONF_DP_PIN])
    cg.add(var.set_dp_pin(pin_dp))

    pin_d1 = await cg.gpio_pin_expression(config[CONF_D1_PIN])
    cg.add(var.set_d1_pin(pin_d1))

    pin_d2 = await cg.gpio_pin_expression(config[CONF_D2_PIN])
    cg.add(var.set_d2_pin(pin_d2))

    pin_d3 = await cg.gpio_pin_expression(config[CONF_D3_PIN])
    cg.add(var.set_d3_pin(pin_d3))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(THREE_SEVENSEGComponent, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
