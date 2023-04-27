# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Surface\OneDrive\Documents\ECE\ECE 405_406\ECE_406\SPI_Master.cydsn\SPI_Master.cyprj
# Date: Thu, 27 Apr 2023 18:58:44 GMT
#set_units -time ns
create_clock -name {UART_1_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {ADC_Seq_1_intClock(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {SPI_SCBCLK(FFB)} -period 250 -waveform {0 125} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {Clock(FFB)} -period 1520.8333333333333 -waveform {0 760.416666666667} [list [get_pins {ClockBlock/ff_div_7}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFClk} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {UART_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]
create_generated_clock -name {ADC_Seq_1_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {SPI_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 13 25} [list]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 73 147} [list]


# Component constraints for C:\Users\Surface\OneDrive\Documents\ECE\ECE 405_406\ECE_406\SPI_Master.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Surface\OneDrive\Documents\ECE\ECE 405_406\ECE_406\SPI_Master.cydsn\SPI_Master.cyprj
# Date: Thu, 27 Apr 2023 18:58:38 GMT
