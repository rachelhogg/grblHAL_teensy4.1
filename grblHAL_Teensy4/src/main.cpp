/*

  main.ino - startup code for iMXRT1062 processor (on Teensy 4.0 board)

  Part of grblHAL

  Copyright (c) 2020 Terje Io

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,ss
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.

*/

// Double tap reset to enter bootloader mode - select bootloader port for programming
#include "Arduino.h"
#include "grbl/grbllib.h"

void setup ()
{
  Serial.begin(115200);
  // Wait for serial to actually connect before printing
  while (!Serial && millis() < 3000); // wait up to 3 seconds
  delay(100); // small extra buffer

  // Read reset reason BEFORE anything else clears it
  uint32_t resetReason = SRC_SRSR;
  Serial.print("[RESET REASON: 0x");
  Serial.print(resetReason, HEX);
  Serial.print(" = ");
  
  if (resetReason & 0x01) Serial.print("POWER-ON ");
  if (resetReason & 0x02) Serial.print("EXTERNAL-PIN ");
  if (resetReason & 0x04) Serial.print("WATCHDOG ");
  if (resetReason & 0x08) Serial.print("JTAG ");
  if (resetReason & 0x10) Serial.print("SOFTWARE ");
  if (resetReason & 0x20) Serial.print("BROWNOUT ");
  
  Serial.println("]");
  grbl_enter();
}

void loop ()
{
}
