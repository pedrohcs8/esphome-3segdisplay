#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"

#include "esphome/components/display/display.h"

namespace esphome::three_sevenseg {

class THREE_SEVENSEGComponent;

using three_sevenseg_writer_t = display::DisplayWriter<THREE_SEVENSEGComponent>;

class THREE_SEVENSEGComponent final : public PollingComponent, public Trigger<> {
 public:
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

  /// Evaluate the printf-format and print the result at the given position.
  uint8_t printf(uint8_t pos, const char *format, ...) __attribute__((format(printf, 3, 4)));
  /// Evaluate the printf-format and print the result at position 0.
  uint8_t printf(const char *format, ...) __attribute__((format(printf, 2, 3)));

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str);
  /// Print `str` at position 0.
  uint8_t print(const char *str);
  /// Print `str` at position 0.
  uint8_t print(std::string str);

  uint8_t switchDisplay(int display, float temp, float hum);

 protected:
  void clear_display_();
  void set_digit_(uint8_t digit, uint8_t value, bool dp);

  uint8_t printTempHum(float tempHum);
  uint8_t printECO2TVOC(float eco2TVOC);

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
