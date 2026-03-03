/**
* MIT License
 *
 * Copyright (c) 2026 Adam Kuczyński
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SPIDevice.h>

constexpr uint16_t AS1100_REG_NOOP        = 0x0000; // no operation
constexpr uint16_t AS1100_REG_DECODE      = 0x0900; // decode mode (0x00 = binary, 0xFF = BCD)
constexpr uint16_t AS1100_REG_INTENSITY   = 0x0A00; // brightness 0x00-0x0F, 0x00 is the brightest
constexpr uint16_t AS1100_REG_SCAN        = 0x0B00; // scan limit (0x07 = all 8 digits)
constexpr uint16_t AS1100_REG_SHUTDOWN    = 0x0C00; // 0x0C00 = off, 0x0C01 = on
constexpr uint16_t AS1100_REG_TEST        = 0x0F00; // 0x0F00 = normal, 0x0F01 = test (all LEDs on)
constexpr uint16_t AS1100_REG_CLOCK       = 0x0E00; // AS1100 only: clock mode (not in MAX7219)

class AS1100 : public GFXcanvas1 {
public:
  AS1100(int sck, int mosi, int latch);

  void begin();
  void display();

private:
  void latch();
  void sendCmd(int cmdData);
  void write16(int d);

  Adafruit_SPIDevice _spi;
  int _latch = 0;
};
