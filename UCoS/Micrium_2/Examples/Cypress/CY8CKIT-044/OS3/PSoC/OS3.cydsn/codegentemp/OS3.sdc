# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\edulu.DESKTOP-961TG4K\Documents\PSoC Creator\Micrium\Examples\Cypress\CY8CKIT-044\OS3\PSoC\OS3.cydsn\OS3.cyprj
# Date: Wed, 20 Feb 2019 18:52:03 GMT
#set_units -time ns
create_clock -name {Clock_PWM(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_8}] [get_pins {ClockBlock/ff_div_9}] [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {I2C_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {ADC_intClock(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_7}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_PWM} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {I2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {Clock_Temp} -source [get_pins {ClockBlock/hfclk}] -edges {1 241 481} [list [get_pins {ClockBlock/udb_div_0}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\edulu.DESKTOP-961TG4K\Documents\PSoC Creator\Micrium\Examples\Cypress\CY8CKIT-044\OS3\PSoC\OS3.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\edulu.DESKTOP-961TG4K\Documents\PSoC Creator\Micrium\Examples\Cypress\CY8CKIT-044\OS3\PSoC\OS3.cydsn\OS3.cyprj
# Date: Wed, 20 Feb 2019 18:52:00 GMT
