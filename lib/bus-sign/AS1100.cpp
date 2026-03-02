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

AS1100::AS1100(int sck, int mosi, int cs) : GFXcanvas1(192, 9),
                                            _spi(-1, sck, -1, mosi, 100000, SPI_BITORDER_MSBFIRST, SPI_MODE3),
                                            _loadPin(cs) {
  pinMode(_loadPin, OUTPUT);
  digitalWrite(_loadPin, HIGH);
}

void AS1100::begin() {
  _spi.begin();

  sendCmd(0x0E00 + (2 & 3)); // set clock to internal
  sendCmd(0x0E00 + (0 & 3)); // set clock to external
  sendCmd(0x0900); // set binary mode
  sendCmd(0x0B07); // 7 means 8 blocks of 8 pixels

  setIntensity(2, -1); // start low.
  sendCmd(0x0C01); // 0x0C01 - display on, 0x0C00 - display off

  display();
}

void AS1100::load() {
  digitalWrite(_loadPin, LOW);
  digitalWrite(_loadPin, HIGH);
}

void AS1100::writeDigit(int digit, uint8_t d) {
  // d=d & 0xFF;	// mask off trash
  int dd = (digit + 1) << 8;
  write16(0x0000 | dd | d);
}

void AS1100::write16(int d) {
  uint8_t buf[2] = {(uint8_t) (d >> 8), (uint8_t) (d & 0xFF)};
  _spi.write(buf, 2);
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

      writeDigit(digit, value);
    }

    load();
  }
}

/**
 * @brief Sets the intensity of one AS1100 chip (character) or ALL chips if chip=-1.
 * Note: you cannot set the intensity of individual LEDs.
 *
 * if chipNum is -1 (default) sets ALL chips to same intensity level
 * level can be 0..16
 * levels outside this range are ignored.
 *
 * The range of level is 0-32. `begin()` sets the initial intensity to 5.
 */
void AS1100::setIntensity(int level, int chipNum = -1) {
  // panel only supports 16 intensity levels
  // if chipNum>-1 only affects that chip
  if (level < 0 && level > 15)
    return; // ignore
  if (chipNum == -1) // set all chips
  {
    for (int c = 0; c < 32; c++)
      write16(0x0A00 + level); // the chip whose brightness needs setting
    load();
    return;
  }

  // we are setting one chip use no-op to push past chips not to be changed

  if (chipNum > 0) {
    for (int c = 0; c < chipNum - 1; c++)
      write16(0); // NO OP
    write16(0x0A00 + level); // the chip whose brightness needs setting
    load();
  }
}

/**
 * @brief Sets all the chips' intensities with one function.
 *
 * Chips is an array of intensity levels in chip order
 * i.e chips[0] is the first chip.
 *
 * This allows you to set the intensity of each character in one go. You provide an array of intensity values.
 *
 * Note that the code does not check if the length of chips is correct
 */

void AS1100::setIndividualIntensity(int chips[]) {
  // chip[s is an array of intensity values, one per chip
  for (int i = 32 - 1; i >= 0; i--)
    write16(0x0A00 + (chips[i] & 15));
  load();
}

void AS1100::sendCmd(int data) {
  for (int chip = 0; chip < 32; chip++) {
    write16(data);
  }

  load();
}
