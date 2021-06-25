#include "ssd1331.hpp"
#include "tic_tac_due.hpp"


int main()
{
    hwlib::wait_ms(200);
    namespace target = hwlib::target;

    // SSD1331 --------------------------------------------------------------------------

    auto sck = target::pin_out(target::pins::d13); // SCK - Blauw
    auto sda = target::pin_out(target::pins::d11); // MOSI - Wit
    auto res = target::pin_out(target::pins::d9);  // RES - Oranje
    auto dc = target::pin_out(target::pins::d8);   // DC - Groen
    auto cs = target::pin_out(target::pins::d10);  // CS - Zwar
    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sck, sda, hwlib::pin_in_dummy);
    auto display = ssd1331_spi_dc_cs_res(spi_bus, dc, cs, res);
    display.clear_implementation(hwlib::black);

    // Keypad1 - Player 1 ---------------------------------------------------------------

    auto p1p1 = target::pin_in(target::pins::d21);
    auto p1p2 = target::pin_in(target::pins::d20);
    auto p1p3 = target::pin_in(target::pins::d19);
    auto p1p4 = target::pin_in(target::pins::d18);
    auto p1p5 = target::pin_oc(target::pins::d17);
    auto p1p6 = target::pin_oc(target::pins::d16);
    auto p1p7 = target::pin_oc(target::pins::d15);
    auto p1p8 = target::pin_oc(target::pins::d14);

    auto pinsOC_column_p1 = hwlib::port_in_from_pins_t(p1p1, p1p2, p1p3, p1p4);//input
    auto pinsIN_row_p1 = hwlib::port_oc_from_pins_t(p1p5, p1p6, p1p7, p1p8); //output
    auto key_matrix_p1 = hwlib::matrix_of_switches(pinsIN_row_p1, pinsOC_column_p1);
    auto keypad1 = hwlib::keypad<16>(key_matrix_p1, "123A456B789C*0#D");

    // Keypad2 - Player 2 ---------------------------------------------------------------

    auto p2p1 = target::pin_in(target::pins::d22);
    auto p2p2 = target::pin_in(target::pins::d23);
    auto p2p3 = target::pin_in(target::pins::d24);
    auto p2p4 = target::pin_in(target::pins::d25);
    auto p2p5 = target::pin_oc(target::pins::d26);
    auto p2p6 = target::pin_oc(target::pins::d27);
    auto p2p7 = target::pin_oc(target::pins::d28);
    auto p2p8 = target::pin_oc(target::pins::d29);

    auto pinsOC_column_p2 = hwlib::port_in_from_pins_t(p2p1, p2p2, p2p3, p2p4);//input
    auto pinsIN_row_p2 = hwlib::port_oc_from_pins_t(p2p5, p2p6, p2p7, p2p8);//output
    auto key_matrix_p2 = hwlib::matrix_of_switches(pinsIN_row_p2, pinsOC_column_p2);
    auto keypad2 = hwlib::keypad<16>(key_matrix_p2, "123A456B789C*0#D");

    // Initialize and start the game ----------------------------------------------------

    auto game1 = tic_tac_due(keypad1, keypad2, display);
    game1.start_game();
}