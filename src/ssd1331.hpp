// ==========================================================================
//
// File      : ssd1331.hpp
// Copyright : kenny.vandoorn@student.hu.nl, 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#pragma once
#include "hwlib.hpp"

// this file contains Doxygen lines
/// @file

/// SSD1331 chip commands
enum class ssd1331 : uint8_t
{
    set_column                  = 0x15, // Set column address
    set_row                     = 0x75, // Set row adress
    contrast_a                  = 0x81, // Set contrast for color A
    contrast_b                  = 0x82, // Set contrast for color B
    contrast_c                  = 0x83, // Set contrast for color C
    master_current              = 0x87, // Master current control
    pre_charge_a                = 0x8A, // Set second pre-charge speed for color A
    pre_charge_b                = 0x8B, // Set second pre-charge speed for color B
    pre_charge_c                = 0x8C, // Set second pre-charge speed for color C
    pre_charge_level            = 0xBB, // Set pre-charge voltage
    vcomh                       = 0xBE, // Set Vcomh voltage
    set_remap                   = 0xA0, // Set re-map & data format
    start_line                  = 0xA1, // Set display start line
    display_offset              = 0xA2, // Set display offset
    normal_display              = 0xA4, // Set display to normal mode
    display_all_on              = 0xA5, // Set entire display ON
    display_all_off             = 0xA6, // Set entire display OFF
    invert_display              = 0xA7, // Invert display
    set_multiplex               = 0xA8, // Set multiplex ratio
    set_master                  = 0xAD, // Set master configuration
    display_off                 = 0xAE, // Display OFF (sleep mode)
    display_on                  = 0xAF, // Normal Brightness Display ON
    power_mode                  = 0xB0, // Power save mode
    pre_charge                  = 0xB1, // Phase 1 and 2 period adjustment
    clock_div                   = 0xB3, // Set display clock divide ratio/oscillator frequency
    deactivate_scrolling        = 0x2E  // Deactivate scrolling
};

// ==========================================================================
//
// ssd1331, accessed by SPI using buffered OLED window
//
// ==========================================================================

/// \brief
/// RGB OLED Display
/// \details
/// This class implements an interface to an 96 x 64 pixel OLED display.
/// The interface is SPI.
/// The driver chip is an SSD1331.
///
/// The interface is buffered: All writes are buffered in memory until flush() is called.
///
/// VDD can only be up to 3.3V.
///
/// See the datasheet here: https://cdn-shop.adafruit.com/datasheets/SSD1331_1.2.pdf
/// 

class ssd1331_spi_dc_cs_res : public hwlib::window
{
private:
    static auto constexpr wsize = hwlib::xy(96, 64);
    static auto constexpr bufsize = ((uint32_t)wsize.x) * ((uint32_t)wsize.y);
    uint16_t buffer[bufsize];
    hwlib::spi_bus &bus;
    hwlib::pin_out &dc;
    hwlib::pin_out &cs;
    hwlib::pin_out &res;

public:

    /// Command only
    void command(ssd1331 c)
    {
        dc.write(0); dc.flush();
        auto t = bus.transaction(cs);
        t.write(static_cast<uint8_t>(c));
        dc.write(1); dc.flush();
    }

    /// Command with one data byte
    void command(ssd1331 c, uint8_t d)
    {
        dc.write(0); dc.flush();
        auto t = bus.transaction(cs);
        t.write(static_cast<uint8_t>(c));
        dc.write(1); dc.flush();
        dc.write(0); dc.flush();
        t.write(d);
        dc.write(1); dc.flush();
    }

    /// Command with two data bytes
    void command(ssd1331 c, uint8_t d0, uint8_t d1)
    {
        dc.write(0); dc.flush();
        auto t = bus.transaction(cs);
        t.write(static_cast<uint8_t>(c));
        dc.write(1); dc.flush();
        dc.write(0); dc.flush();
        t.write(d0);
        dc.write(1); dc.flush();
        dc.write(0); dc.flush();
        t.write(d1);
        dc.write(1); dc.flush();
    }

    /// Create an SSD1331 OLED instance.
    ///
    /// This constructor creates an SSD1331 OLED instance from its interface pins.
    ssd1331_spi_dc_cs_res(
        hwlib::spi_bus &bus,
        hwlib::pin_out &dc,
        hwlib::pin_out &cs,
        hwlib::pin_out &res) : window(
                               wsize,
                               hwlib::white,
                               hwlib::black),

                               bus(bus),
                               dc(dc),
                               cs(cs),
                               res(res)
    {
        // Reset and prepare the OLED for commands
        res.write(0); res.flush();
        hwlib::wait_ms(50);
        res.write(1); res.flush();

        // OLED initialization commands
        command(ssd1331::display_off);
        command(ssd1331::set_remap, 0x74);
        command(ssd1331::set_column, 0x00, 0x5F);
        command(ssd1331::set_row, 0x00, 0x3F);
        command(ssd1331::start_line, 0x0);
        command(ssd1331::display_offset, 0x0);
        command(ssd1331::normal_display);
        command(ssd1331::set_multiplex, 0x3F);
        command(ssd1331::set_master, 0x8E);
        command(ssd1331::power_mode, 0x0B);
        command(ssd1331::pre_charge, 0x31);
        command(ssd1331::clock_div, 0xF0);
        command(ssd1331::pre_charge_a, 0x64);
        command(ssd1331::pre_charge_b, 0x78);
        command(ssd1331::pre_charge_c, 0x64);
        command(ssd1331::pre_charge_level, 0x3A);
        command(ssd1331::vcomh, 0x3E);
        command(ssd1331::master_current, 0x06);
        command(ssd1331::contrast_a, 0x91);
        command(ssd1331::contrast_b, 0x50);
        command(ssd1331::contrast_c, 0x7D);
        command(ssd1331::deactivate_scrolling);
        command(ssd1331::display_on);
    }

    /// Flush the GDDRAM, and write to the OLED display
    void flush()
    {
        auto k = bus.transaction(cs);
        for (unsigned int i = 0; i < bufsize; ++i)
        {
            k.write((buffer[i] >> 8) & 0xFF);
            k.write(buffer[i] & 0xFF);
        }
    }

    /// Fill the buffer with pixels
    void write_implementation(hwlib::xy pos, hwlib::color col)
    {
        buffer[pos.y * wsize.x + pos.x] =
            ((static_cast<uint_fast16_t>(col.blue) & 0x00f8) << 8)
          + ((static_cast<uint_fast16_t>(col.green) & 0x00fc) << 3)
          + ((static_cast<uint_fast16_t>(col.red) & 0x00f8) >> 3);
    }

    /// Clear the screen by writing a color to the whole screen size
    void clear_implementation(hwlib::color col)
    {
        for (int i = 0; i < 96; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                write_implementation(hwlib::xy(i, j), col);
            }
        }
        flush();
    }
}; // class ssd1331_spi_dc_cs_res