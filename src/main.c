/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"

#include "timer.h"
#include "led.h"

#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// Declare and initialize the temperature array
int temperature[] = {10, 55, 40, 22, 30, 42, 30, 36, 31, 26};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  trace_puts("Chuong Trinh Dieu Khien Quat Gio!");
  trace_puts("Nhiet do > 32 tien hanh bat quat gio, Nhiet do < 32 tat quat gio!");


  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  timer_start();

  blink_led_init();

  uint32_t seconds = 0;

  // Infinite loop
  while (1)
    {
      //blink_led_on();
      timer_sleep(seconds == 0 ? TIMER_FREQUENCY_HZ : BLINK_ON_TICKS);

      //blink_led_off();
      timer_sleep(BLINK_OFF_TICKS);

      ++seconds;
      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);

      // Print the current temperature
      trace_printf("Temperature: %d\n", temperature[seconds % 10]);

      // Check if the current temperature is above 30
      if (temperature[seconds % 10] > 32) {
        blink_led_on(); // Turn on the LED
        trace_puts("BAT QUAT GIO, LED XANH BAT!");
      } else {
        blink_led_off(); // Turn off the LED
        trace_puts("TAT QUAT GIO, LED XANH TAT!");
      }
    }
}

#pragma GCC diagnostic pop
