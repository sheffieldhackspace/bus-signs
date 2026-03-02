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

class AS1100 : public GFXcanvas1 {
public:
  AS1100(int sck, int mosi, int cs);

  void begin();
  void display();

  void setIntensity(int level, int chip); // sets intensity of one or all chips (-1 default)
  void setIndividualIntensity(int chips[]); // provide an array of intensities, one per chip

private:
  void load();
  void write16(int d);
  void writeDigit(int digit, uint8_t d); // used by display()
  void sendCmd(int cmdData);

  Adafruit_SPIDevice _spi;
  int _loadPin = 0;
  int _clkPin = 0;
  int _dataPin = 0;
};
