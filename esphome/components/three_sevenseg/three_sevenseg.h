#pragma once

#include "esphome/core/component.h"
#include "esphome/components/gpio/output/gpio_binary_output.h"
#include "esphome/core/time.h"

#include "esphome/components/display/display.h"

namespace esphome::three_sevenseg {

class THREE_SEVENSEGComponent;

using three_sevenseg_writer_t = display::DisplayWriter<THREE_SEVENSEGComponent>;

class THREE_SEVENSEGComponent final : public PollingComponent {
 public:
  void set_writer(three_sevenseg_writer_t &&writer);

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  void display();

  void set_a_pin(gpio::GPIOBinaryOutput *a_pin);
  void set_b_pin(gpio::GPIOBinaryOutput *b_pin);
  void set_c_pin(gpio::GPIOBinaryOutput *c_pin);
  void set_d_pin(gpio::GPIOBinaryOutput *d_pin);
  void set_e_pin(gpio::GPIOBinaryOutput *e_pin);
  void set_f_pin(gpio::GPIOBinaryOutput *f_pin);
  void set_g_pin(gpio::GPIOBinaryOutput *g_pin);
  void set_dp_pin(gpio::GPIOBinaryOutput *dp_pin);
  void set_d1_pin(gpio::GPIOBinaryOutput *d1_pin);
  void set_d2_pin(gpio::GPIOBinaryOutput *d2_pin);
  void set_d3_pin(gpio::GPIOBinaryOutput *d3_pin);

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str);

 protected:
  void clear_display_();
  void set_digit_();

  gpio::GPIOBinaryOutput *a_pin_{nullptr};
  gpio::GPIOBinaryOutput *b_pin_{nullptr};
  gpio::GPIOBinaryOutput *c_pin_{nullptr};
  gpio::GPIOBinaryOutput *d_pin_{nullptr};
  gpio::GPIOBinaryOutput *e_pin_{nullptr};
  gpio::GPIOBinaryOutput *f_pin_{nullptr};
  gpio::GPIOBinaryOutput *g_pin_{nullptr};
  gpio::GPIOBinaryOutput *dp_pin_{nullptr};
  gpio::GPIOBinaryOutput *d1_pin_{nullptr};
  gpio::GPIOBinaryOutput *d2_pin_{nullptr};
  gpio::GPIOBinaryOutput *d3_pin_{nullptr};

  uint8_t *buffer_;
  uint16_t buffer_size_{0};

  optional<three_sevenseg_writer_t> writer_{};
};

}  // namespace esphome::three_sevenseg
