#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/time.h"

#include "esphome/components/display/display.h"

namespace esphome::three_sevenseg {

class THREE_SEVENSEGComponent;

using three_sevenseg_writer_t = display::DisplayWriter<THREE_SEVENSEGComponent>;

class THREE_SEVENSEGComponent final : public PollingComponent {
 public:
  explicit THREE_SEVENSEGComponent();

  void set_writer(three_sevenseg_writer_t &&writer);

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  void display();

  void set_a_pin(GPIOPin *a_pin);
  void set_b_pin(GPIOPin *b_pin);
  void set_c_pin(GPIOPin *c_pin);
  void set_d_pin(GPIOPin *d_pin);
  void set_e_pin(GPIOPin *e_pin);
  void set_f_pin(GPIOPin *f_pin);
  void set_g_pin(GPIOPin *g_pin);
  void set_dp_pin(GPIOPin *dp_pin);
  void set_d1_pin(GPIOPin *d1_pin);
  void set_d2_pin(GPIOPin *d2_pin);
  void set_d3_pin(GPIOPin *d3_pin);

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str);

 protected:
  void clear_display_();
  void set_digit_();

  GPIOPin *a_pin_{nullptr};
  GPIOPin *b_pin_{nullptr};
  GPIOPin *c_pin_{nullptr};
  GPIOPin *d_pin_{nullptr};
  GPIOPin *e_pin_{nullptr};
  GPIOPin *f_pin_{nullptr};
  GPIOPin *g_pin_{nullptr};
  GPIOPin *dp_pin_{nullptr};
  GPIOPin *d1_pin_{nullptr};
  GPIOPin *d2_pin_{nullptr};
  GPIOPin *d3_pin_{nullptr};

  uint8_t *buffer_;
  uint16_t buffer_size_{0};
  bool setup_complete_{false};

  optional<three_sevenseg_writer_t> writer_{};
};

}  // namespace esphome::three_sevenseg
