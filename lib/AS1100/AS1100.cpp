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

#include <AS1100.h>
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>

AS1100::AS1100(int sck, int mosi, int latch) : GFXcanvas1(192, 9),
                                            _spi(-1, sck, -1, mosi, 100000, SPI_BITORDER_MSBFIRST, SPI_MODE3),
                                            _latch(latch) {
  pinMode(_latch, OUTPUT);
  digitalWrite(_latch, HIGH);
}

void AS1100::begin() {
  _spi.begin();

  sendCmd(AS1100_REG_CLOCK | 0x02);
  sendCmd(AS1100_REG_CLOCK | 0x00);
  sendCmd(AS1100_REG_DECODE | 0x00);
  sendCmd(AS1100_REG_SCAN | 0x07);
  sendCmd(AS1100_REG_INTENSITY | 0x00);
  sendCmd(AS1100_REG_SHUTDOWN | 0x01);

  display();
}

void AS1100::display() {
  for (int digit = 0; digit < 8; digit++) {
    for (int chip = 0; chip < 32; chip++) {
      uint8_t value = 0;

      if (digit > 1) {
        value |= getPixel(192 - chip * 6 - (digit - 1), 8);
      }

      for (int i = 0; i < 6; i++) {
        value <<= 1;
        value |= getPixel(192 - chip * 6 - (i + 1), 8 - (digit + 1));
      }

      write16(((digit + 1) << 8) | value);
    }

    latch();
  }
}

void AS1100::latch() {
  digitalWrite(_latch, LOW);
  digitalWrite(_latch, HIGH);
}

void AS1100::sendCmd(int data) {
  for (int chip = 0; chip < 32; chip++) {
    write16(data);
  }

  latch();
}

void AS1100::write16(int d) {
  uint8_t buf[2] = {(uint8_t) (d >> 8), (uint8_t) (d & 0xFF)};
  _spi.write(buf, 2);
}
