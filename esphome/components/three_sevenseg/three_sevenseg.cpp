#include "three_sevenseg.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome::three_sevenseg {

static const char *const TAG = "three_sevenseg";

static const uint8_t THREE_SEVENSEG_UNKNOWN_CHAR = 0b11111111;

const uint8_t THREE_SEVENSEG_ASCII_TO_RAW[128] PROGMEM = {
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x00
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x01
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x02
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x03
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x04
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x05
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x06
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x07
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x08
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x09
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0A
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0B
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0C
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0D
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0E
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x0F
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x10
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x11
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x12
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x13
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x14
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x15
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x16
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x17
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x18
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x19
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1A
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1B
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1C
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1D
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1E
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x1F
    0b00000000,                   // ' ', ord 0x20
    0b10110000,                   // '!', ord 0x21
    0b00100010,                   // '"', ord 0x22
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '#', ord 0x23
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '$', ord 0x24
    0b01001001,                   // '%', ord 0x25
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '&', ord 0x26
    0b00000010,                   // ''', ord 0x27
    0b01001110,                   // '(', ord 0x28
    0b01111000,                   // ')', ord 0x29
    0b01000000,                   // '*', ord 0x2A
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '+', ord 0x2B
    0b00010000,                   // ',', ord 0x2C
    0b00000001,                   // '-', ord 0x2D
    0b10000000,                   // '.', ord 0x2E
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '/', ord 0x2F
    0b10000001,                   // '0', ord 0x30
    0b00110000,                   // '1', ord 0x31
    0b01101101,                   // '2', ord 0x32
    0b01111001,                   // '3', ord 0x33
    0b00110011,                   // '4', ord 0x34
    0b01011011,                   // '5', ord 0x35
    0b01011111,                   // '6', ord 0x36
    0b01110000,                   // '7', ord 0x37
    0b01111111,                   // '8', ord 0x38
    0b01111011,                   // '9', ord 0x39
    0b01001000,                   // ':', ord 0x3A
    0b01011000,                   // ';', ord 0x3B
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '<', ord 0x3C
    0b00001001,                   // '=', ord 0x3D
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '>', ord 0x3E
    0b01100101,                   // '?', ord 0x3F
    0b01101111,                   // '@', ord 0x40
    0b01110111,                   // 'A', ord 0x41
    0b00011111,                   // 'B', ord 0x42
    0b01001110,                   // 'C', ord 0x43
    0b00111101,                   // 'D', ord 0x44
    0b01001111,                   // 'E', ord 0x45
    0b01000111,                   // 'F', ord 0x46
    0b01011110,                   // 'G', ord 0x47
    0b00110111,                   // 'H', ord 0x48
    0b00110000,                   // 'I', ord 0x49
    0b00111100,                   // 'J', ord 0x4A
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'K', ord 0x4B
    0b00001110,                   // 'L', ord 0x4C
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'M', ord 0x4D
    0b00010101,                   // 'N', ord 0x4E
    0b01111110,                   // 'O', ord 0x4F
    0b01100111,                   // 'P', ord 0x50
    0b11111110,                   // 'Q', ord 0x51
    0b00000101,                   // 'R', ord 0x52
    0b01011011,                   // 'S', ord 0x53
    0b00000111,                   // 'T', ord 0x54
    0b00111110,                   // 'U', ord 0x55
    0b00111110,                   // 'V', ord 0x56
    0b00111111,                   // 'W', ord 0x57
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'X', ord 0x58
    0b00100111,                   // 'Y', ord 0x59
    0b01101101,                   // 'Z', ord 0x5A
    0b01001110,                   // '[', ord 0x5B
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '\', ord 0x5C
    0b01111000,                   // ']', ord 0x5D
    THREE_SEVENSEG_UNKNOWN_CHAR,  // '^', ord 0x5E
    0b00001000,                   // '_', ord 0x5F
    0b00100000,                   // '`', ord 0x60
    0b01110111,                   // 'a', ord 0x61
    0b00011111,                   // 'b', ord 0x62
    0b00001101,                   // 'c', ord 0x63
    0b00111101,                   // 'd', ord 0x64
    0b01001111,                   // 'e', ord 0x65
    0b01000111,                   // 'f', ord 0x66
    0b01011110,                   // 'g', ord 0x67
    0b00010111,                   // 'h', ord 0x68
    0b00010000,                   // 'i', ord 0x69
    0b00111100,                   // 'j', ord 0x6A
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'k', ord 0x6B
    0b00001110,                   // 'l', ord 0x6C
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'm', ord 0x6D
    0b00010101,                   // 'n', ord 0x6E
    0b00011101,                   // 'o', ord 0x6F
    0b01100111,                   // 'p', ord 0x70
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'q', ord 0x71
    0b00000101,                   // 'r', ord 0x72
    0b01011011,                   // 's', ord 0x73
    0b00000111,                   // 't', ord 0x74
    0b00011100,                   // 'u', ord 0x75
    0b00011100,                   // 'v', ord 0x76
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'w', ord 0x77
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'x', ord 0x78
    0b00100111,                   // 'y', ord 0x79
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 'z', ord 0x7A
    0b00110001,                   // '{', ord 0x7B
    0b00000110,                   // '|', ord 0x7C
    0b00000111,                   // '}', ord 0x7D
    0b01100011,                   // '~', ord 0x7E (degree symbol)
    THREE_SEVENSEG_UNKNOWN_CHAR,  // 0x7F
};

float THREE_SEVENSEGComponent::get_setup_priority() const { return setup_priority::PROCESSOR; }

void THREE_SEVENSEGComponent::set_writer(three_sevenseg_writer_t &&writer) { this->writer_ = writer; }
void THREE_SEVENSEGComponent::set_a_pin(GPIOPin *a_pin) { this->a_pin_ = a_pin; }
void THREE_SEVENSEGComponent::set_b_pin(GPIOPin *b_pin) { this->b_pin_ = b_pin; }
void THREE_SEVENSEGComponent::set_c_pin(GPIOPin *c_pin) { this->c_pin_ = c_pin; }
void THREE_SEVENSEGComponent::set_d_pin(GPIOPin *d_pin) { this->d_pin_ = d_pin; }
void THREE_SEVENSEGComponent::set_e_pin(GPIOPin *e_pin) { this->e_pin_ = e_pin; }
void THREE_SEVENSEGComponent::set_f_pin(GPIOPin *f_pin) { this->f_pin_ = f_pin; }
void THREE_SEVENSEGComponent::set_g_pin(GPIOPin *g_pin) { this->g_pin_ = g_pin; }
void THREE_SEVENSEGComponent::set_dp_pin(GPIOPin *dp_pin) { this->dp_pin_ = dp_pin; }
void THREE_SEVENSEGComponent::set_d1_pin(GPIOPin *d1_pin) { this->d1_pin_ = d1_pin; }
void THREE_SEVENSEGComponent::set_d2_pin(GPIOPin *d2_pin) { this->d2_pin_ = d2_pin; }
void THREE_SEVENSEGComponent::set_d3_pin(GPIOPin *d3_pin) { this->d3_pin_ = d3_pin; }

void THREE_SEVENSEGComponent::setup() {
  ESP_LOGCONFIG(TAG, "Iniciando Display 3 Segmentos!");

  this->a_pin_->setup();
  this->a_pin_->digital_write(true);

  this->b_pin_->setup();
  this->b_pin_->digital_write(true);

  this->c_pin_->setup();
  this->c_pin_->digital_write(true);

  this->d_pin_->setup();
  this->d_pin_->digital_write(true);

  this->e_pin_->setup();
  this->e_pin_->digital_write(true);

  this->f_pin_->setup();
  this->f_pin_->digital_write(true);

  this->g_pin_->setup();
  this->g_pin_->digital_write(true);

  this->dp_pin_->setup();
  this->dp_pin_->digital_write(true);

  // TODO: Put this on Low again.

  this->d1_pin_->setup();
  this->d1_pin_->digital_write(false);

  this->d2_pin_->setup();
  this->d2_pin_->digital_write(false);

  this->d3_pin_->setup();
  this->d3_pin_->digital_write(false);

  this->buffer_ = new uint8_t[3];
  this->buffer_size_ = sizeof(this->buffer_);

  ESP_LOGCONFIG(TAG, "Terminei sabosta");
}

void THREE_SEVENSEGComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Teste foda?");

  LOG_UPDATE_INTERVAL(this);
}

// update
void THREE_SEVENSEGComponent::update() {
  if (this->writer_.has_value())
    (*this->writer_)(*this);
  this->display();
}

// display
void THREE_SEVENSEGComponent::display() {
  for (uint8_t i = 0; i < 3; i++) {
    this->set_digit_(i, this->buffer_[i], false);
  }
}

void THREE_SEVENSEGComponent::set_digit_(uint8_t digit, uint8_t ch, bool dot) {
  uint8_t segments = 0;
  // concat to printable ASCII characters
  if (ch < 128) {
    segments = THREE_SEVENSEG_ASCII_TO_RAW[ch];
  } else {
    segments = 128;
  }
  segments = THREE_SEVENSEG_ASCII_TO_RAW[ch];

  // write binary representation of the segments
  this->clear_display_();

  uint8_t ct = 0;
  GPIOPin *pins[3] = {this->d1_pin_, this->d2_pin_, this->d3_pin_};

  for (GPIOPin *pin : pins) {
    pin->digital_write(ct == digit);
    ct++;
  }

  this->dp_pin_->digital_write((segments & 0b10000000) || dot);
  this->a_pin_->digital_write(segments & 0b01000000);
  this->b_pin_->digital_write(segments & 0b00100000);
  this->c_pin_->digital_write(segments & 0b00010000);
  this->d_pin_->digital_write(segments & 0b00001000);
  this->e_pin_->digital_write(segments & 0b00000100);
  this->f_pin_->digital_write(segments & 0b00000010);
  this->g_pin_->digital_write(segments & 0b00000001);

  delay(5);
};

void THREE_SEVENSEGComponent::clear_display_() {
  this->a_pin_->digital_write(true);
  this->b_pin_->digital_write(true);
  this->c_pin_->digital_write(true);
  this->d_pin_->digital_write(true);
  this->e_pin_->digital_write(true);
  this->f_pin_->digital_write(true);
  this->g_pin_->digital_write(true);
  this->dp_pin_->digital_write(true);

  delay(10);
}

// print functions
uint8_t THREE_SEVENSEGComponent::print(uint8_t start_pos, const char *str) {
  uint8_t pos = start_pos;
  std::string input = std::string(str);
  for (unsigned char c : input) {
    uint8_t data = THREE_SEVENSEG_UNKNOWN_CHAR;
    if (c >= 0 && c <= 127)
      data = THREE_SEVENSEG_ASCII_TO_RAW[c];
    if (c == '.') {
      if (pos != start_pos && pos > 0 && this->buffer_[pos - 1] ^ 0b10000000)
        this->buffer_[pos - 1] |= 0b10000000;
    } else {
      if (pos >= 3) {
        break;
      }

      this->buffer_[pos] = data;
    }
    pos++;
  }
  return pos - start_pos;
}

uint8_t THREE_SEVENSEGComponent::print(const char *str) { return this->print(0, str); }

uint8_t THREE_SEVENSEGComponent::print(std::string str) { return this->print(0, str.c_str()); }

uint8_t THREE_SEVENSEGComponent::printf(uint8_t pos, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[64];
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  va_end(arg);
  if (ret > 0)
    return this->print(pos, buffer);
  return 0;
}

uint8_t THREE_SEVENSEGComponent::printf(const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[64];
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  va_end(arg);
  if (ret > 0)
    return this->print(buffer);
  return 0;
}

uint8_t THREE_SEVENSEGComponent::strftime(uint8_t pos, const char *format, ESPTime time) {
  char buffer[64];
  size_t ret = time.strftime(buffer, sizeof(buffer), format);
  if (ret > 0)
    return this->print(pos, buffer);
  return 0;
}

uint8_t THREE_SEVENSEGComponent::strftime(const char *format, ESPTime time) { return this->strftime(0, format, time); }

}  // namespace esphome::three_sevenseg
// namespace esphome::three_sevenseg
