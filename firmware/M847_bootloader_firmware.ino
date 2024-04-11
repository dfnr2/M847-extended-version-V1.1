
// =============================================================================================================
//                                         Bootload programs
//
// Please note the data format. You can use the octal numbers after 0x....
// Please fill in all the numbers even if they are zero
//
// The first number is the initial address to deposit from
// The second number is the EMA address (IF and DF)
// Then the complete program can be written
// The last number is the start address of the program
//
// Example:
// We want a program located at address 200
// The EMA address is 0
// The data to deposit in memory is: 7001, 2300, 5201, 5200
// The startaddress is 200
//
// Should look like this:
// const PROGMEM word Program_01[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200};  //AC
// increment program
//
//
// All Octal values are repesented as HEX numbers, and put as HEX into the MCP23017.
// Due hardware the bits 15, 11, 7 and 3 are zero and just not used.
// Programnumbers are shown in Octal as well... The highest program number is currently 77 (so 7 x 8
// + 7 = 63 programs) Program_00 does not exist, this is used to load the selected default
//
//
// =============================================================================================================

// =============================================================================================================
//                                         Includes
#include <Wire.h> // I2C handler

#define VERSION 1.8

#define KITT_SCAN_DELAY 40

#define r_RUN 8  // PB0
#define r_SW 9   // PB1
#define Dip_1 10 // PB2
#define Dip_2 11 // PB3
#define Dip_3 12 // PB4
#define Dip_4 13 // PB5

#define w_INITIALIZE_H A0 // PC0 for 400nS pulse
#define w_PULSE_LA_H A1   // PC1 for 400nS pulse
#define w_MEM_START A2    // PC2 for 400nS pulse
#define w_STOP A3         // PC3

#define INITIALIZE_BIT 0
#define ADDR_LATCH_BIT 1
#define MEM_START_BIT 2

#define Set_Flip_Flop 2   // PD2
#define Show_Data 3       // PD3
#define Exam 4            // PD4
#define w_LA_ENABLE 5     // PD5
#define w_MS_IR_DISABLE 6 // PD6
#define w_KEY_CONTROL 7   // PD7


// ================================== FROM HERE THE BOOTSTRAPS CAN BE ENTERED
// =================================

// All Octal values are repesented as HEX numbers, and put as HEX into the MCP23017.
// Due hardware the bits 15, 11, 7 and 3 are zero and just not used.
// Programnumbers are shown in Octal as well... The highest program number is currently 77 oct (so
// max 63 programs) Program_00 does not exist, this is used to load the selected default
//
//

// group 0x
// Program 0 does not exist, this is preseved to load a default trough the dip switches
const PROGMEM word os8_server_40[] = {
  0x0017, 0x0000, 0x0017, 0x7240, 0x3017, 0x1045, 0x6416, 0x6411, 0x5024,
  0x6402, 0x6401, 0x5027, 0x6406, 0x7106, 0x7006, 0x7510, 0x5000, 0x7006,
  0x6401, 0x5037, 0x6404, 0x3417, 0x5026, 0x7605, 0x0100, 0x0020
}; // OS8 disk server 40/41

const PROGMEM word rx8_rx01_bootloader[] = {
  0x0024, 0x0000, 0x7126, 0x1060, 0x6751, 0x7201, 0x4053, 0x4053, 0x7104, 0x6755, 0x5054,
  0x6754, 0x7450, 0x7610, 0x5046, 0x1060, 0x7041, 0x1061, 0x3060, 0x5024, 0x6751, 0x4053,
  0x3002, 0x2050, 0x5047, 0x0000, 0x6753, 0x5033, 0x6752, 0x5453, 0x7024, 0x6030, 0x0033
}; // RX8 RX01 bootloader (M8357 RX8E card at 675x)

const PROGMEM word rx28_rx02_bootloader[] = {
  0x0020, 0x0000, 0x1061, 0x1046, 0x0060, 0x3061, 0x7327, 0x1061, 0x6751, 0x7301,
  0x4053, 0x4053, 0x7004, 0x6755, 0x5054, 0x6754, 0x7450, 0x5020, 0x1061, 0x6751,
  0x1061, 0x0046, 0x1032, 0x3060, 0x0360, 0x4053, 0x3002, 0x2050, 0x5047, 0x0000,
  0x6753, 0x5033, 0x6752, 0x5453, 0x0420, 0x0020, 0x0033
}; // RX28 RX02 bootloader (M8357 RX8E card at 675x)

const PROGMEM word rk05_bootloader_mi8_ed_rk8[] = {
  0x0023, 0x0000, 0x6007, 0x6751, 0x6745, 0x5025, 0x7200, 0x6733, 0x5031, 0x0023
}; // RK05 (RK8E) bootloader MI8-ED RK8

const PROGMEM word tu56_td8e_mi8_eh[] = {
  0x7300, 0x0000, 0x1312, 0x4312, 0x4312, 0x6773, 0x5303, 0x6777, 0x3726, 0x2326,
  0x5303, 0x5732, 0x2000, 0x1300, 0x6774, 0x6771, 0x5315, 0x6776, 0x0331, 0x1327,
  0x7640, 0x5315, 0x2321, 0x5712, 0x7354, 0x7756, 0x7747, 0x0077, 0x7400, 0x7300
}; // TU56 (TD8E) MI8-EH

const PROGMEM word tu56_tc08_dectape_mi8_ec[] = {
  0x7554, 0x0000, 0x7600, 0x6774, 0x1374, 0x6766, 0x6771, 0x5360, 0x7240, 0x1354, 0x3773, 0x1354,
  0x3772, 0x1375, 0x6766, 0x5376, 0x7754, 0x7755, 0x0600, 0x0220, 0x6771, 0x5376, 0x7777, 0x7554
}; // TU56 TC08 dec tape MI8-EC

const PROGMEM word tu60_ta8e_caps8[] = {
  0x4000, 0x0000, 0x1237, 0x1206, 0x6704, 0x6706, 0x6703, 0x5204, 0x7264, 0x6702, 0x7610, 0x3211,
  0x3636, 0x1205, 0x6704, 0x6706, 0x6701, 0x5216, 0x7002, 0x7430, 0x1636, 0x7022, 0x3636, 0x7420,
  0x2236, 0x2235, 0x5215, 0x7346, 0x7002, 0x3235, 0x5201, 0x7737, 0x3557, 0x7730, 0x4000
}; //  TU60 (TA8E) CAPS-8 or OS/8 setup cassettes


// group 1x
const PROGMEM word pc04_pc8e_papertape_mi8_ea[] = {
  0x7737, 0x0000, 0x6014, 0x0776, 0x7326, 0x1337, 0x2376, 0x5340, 0x6011, 0x5356, 0x3361, 0x1361,
  0x3371, 0x1345, 0x3357, 0x1345, 0x3367, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510,
  0x5374, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x0000, 0x7737
}; // PC04 PC8E papertape MI8-EA

const PROGMEM word rim_loader_03[] = { 0x7756, 0x0000, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106,
                                       0x7006, 0x7510, 0x5357, 0x7006, 0x6031, 0x5367, 0x6034,
                                       0x7420, 0x3776, 0x3376, 0x5356, 0x7756 }; // RIM loader 03/04

const PROGMEM word bin_loader_03[] = {
  0x7612, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x3212, 0x4260, 0x1300, 0x7750, 0x5237, 0x2212, 0x7040,
  0x5227, 0x1212, 0x7640, 0x5230, 0x1214, 0x0274, 0x1341, 0x7510, 0x2226, 0x7750, 0x5626,
  0x1214, 0x0256, 0x1257, 0x3213, 0x5230, 0x0070, 0x6201, 0x0000, 0x0000, 0x6031, 0x5262,
  0x6036, 0x3214, 0x1214, 0x5660, 0x6011, 0x5270, 0x6016, 0x5265, 0x0300, 0x4343, 0x7041,
  0x1215, 0x7402, 0x6032, 0x6014, 0x6214, 0x1257, 0x3213, 0x7240, 0x7700, 0x1353, 0x1352,
  0x3261, 0x4226, 0x5313, 0x3215, 0x1213, 0x3336, 0x1214, 0x3376, 0x4260, 0x3355, 0x4226,
  0x5275, 0x4343, 0x7420, 0x5336, 0x3216, 0x1376, 0x1355, 0x1215, 0x5315, 0x6201, 0x3616,
  0x2216, 0x7600, 0x5332, 0x0000, 0x1376, 0x7106, 0x7006, 0x7006, 0x1355, 0x5743, 0x5262,
  0x0006, 0x0000, 0x0000, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510, 0x5357,
  0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x7776, 0x5301, 0x7777
}; // BIN LOADER 03/04

const PROGMEM word bin_loader_40[] = {
  0x7612, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x3212, 0x4260, 0x1300, 0x7750, 0x5237, 0x2212, 0x7040,
  0x5227, 0x1212, 0x7640, 0x5230, 0x1214, 0x0274, 0x1341, 0x7510, 0x2226, 0x7750, 0x5626,
  0x1214, 0x0256, 0x1257, 0x3213, 0x5230, 0x0070, 0x6201, 0x0000, 0x0000, 0x6401, 0x5262,
  0x6406, 0x3214, 0x1214, 0x5660, 0x6011, 0x5270, 0x6016, 0x5265, 0x0300, 0x4343, 0x7041,
  0x1215, 0x7402, 0x6402, 0x6014, 0x6214, 0x1257, 0x3213, 0x7240, 0x7700, 0x1353, 0x1352,
  0x3261, 0x4226, 0x5313, 0x3215, 0x1213, 0x3336, 0x1214, 0x3376, 0x4260, 0x3355, 0x4226,
  0x5275, 0x4343, 0x7420, 0x5336, 0x3216, 0x1376, 0x1355, 0x1215, 0x5315, 0x6201, 0x3616,
  0x2216, 0x7600, 0x5332, 0x0000, 0x1376, 0x7106, 0x7006, 0x7006, 0x1355, 0x5743, 0x5262,
  0x0006, 0x0000, 0x0000, 0x6402, 0x6401, 0x5357, 0x6406, 0x7106, 0x7006, 0x7510, 0x5357,
  0x7006, 0x6401, 0x5367, 0x6404, 0x7420, 0x3776, 0x3376, 0x5356, 0x7776, 0x5301, 0x7777
}; // BIN LOADER 40/41

const PROGMEM word kaleidoscope[] = { 0x0200, 0x0000, 0x1220, 0x4221, 0x7040, 0x1217, 0x3217,
                                      0x1217, 0x6053, 0x4221, 0x1220, 0x6054, 0x6052, 0x5212,
                                      0x6055, 0x3220, 0x5200, 0x3777, 0x0006, 0x0000, 0x3236,
                                      0x7404, 0x7041, 0x3237, 0x1236, 0x7100, 0x7510, 0x7020,
                                      0x7010, 0x2237, 0x5227, 0x5621, 0x0000, 0x0000, 0x6144,
                                      0x5240, 0x0200 }; // Kaleidoscope

const PROGMEM word mi8_ee_typeset[] = { 0x7756, 0x0000, 0x7771, 0x6014, 0x6011, 0x5360,
                                        0x7106, 0x7106, 0x6012, 0x7420, 0x5357, 0x5756,
                                        0x4356, 0x3373, 0x4356, 0x7770 }; // MI8-EE Typeset


const PROGMEM word mi8_ef_edusys_low[] = {
  0x7737, 0x0000, 0x6007, 0x7604, 0x7510, 0x3343, 0x6766, 0x6771, 0x5344, 0x1376, 0x5343, 0x7600,
  0x6603, 0x6622, 0x5352, 0x5752, 0x7577, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510,
  0x5357, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x0200, 0x7737
}; // MI8-EF Edu sys low

const PROGMEM word mi8_eg_edusys_high[] = {
  0x7737, 0x0000, 0x6007, 0x7604, 0x7510, 0x3343, 0x6766, 0x6771, 0x5344, 0x1376, 0x5343, 0x7600,
  0x6603, 0x6622, 0x5352, 0x5752, 0x7577, 0x6014, 0x6011, 0x5357, 0x6016, 0x7106, 0x7006, 0x7510,
  0x5374, 0x7006, 0x6011, 0x5367, 0x6016, 0x7420, 0x3776, 0x3376, 0x5357, 0x0220, 0x7737
}; // MI8-EG Edu sys high


// from here programs are not selectable by the dipswitches. These can be loaded by toggeling the SW
// switch or pushbutton on the PCB only.
// group 2x
const PROGMEM word group1_microinstructions_a[] = {
  0x0200, 0x0000, 0x7200, 0x7100, 0x7040, 0x7020, 0x7020, 0x7010,
  0x7004, 0x7012, 0x7006, 0x7001, 0x7001, 0x7002, 0x7402, 0x0200
}; // group 1 microinstructions

const PROGMEM word group1_microinstructions_b[] = {
  0x0200, 0x0000, 0x7300, 0x7440, 0x7402, 0x7430, 0x7402, 0x7020, 0x7420, 0x7402, 0x7001, 0x7450,
  0x7402, 0x7510, 0x7402, 0x7410, 0x7402, 0x7012, 0x7500, 0x7402, 0x7404, 0x7402, 0x0200
}; // group 1 microinstructions

const PROGMEM word operate_instructions[] = {
  0x0200, 0x0000, 0x7240, 0x7001, 0x7640, 0x7402, 0x7120, 0x7010, 0x7510,
  0x7410, 0x7402, 0x7001, 0x7002, 0x1202, 0x7420, 0x7402, 0x7402, 0x0200
}; // Operate instructions

const PROGMEM word isz_instructions[] = {
  0x0200, 0x0000, 0x7500, 0x3300, 0x7001, 0x2300, 0x5202, 0x7440, 0x7402, 0x7402, 0x0200
}; // ISZ instructions

const PROGMEM word jms_instructions[] = {
  0x0200, 0x0000, 0x7300, 0x3300, 0x3204, 0x4204, 0x0000, 0x1204, 0x7041,
  0x1215, 0x7440, 0x7402, 0x2300, 0x5202, 0x7402, 0x0204, 0x0200
}; // JMS instruction

const PROGMEM word jmp_instruction[] = {
  0x0200, 0x0000, 0x5210, 0x7402, 0x5206, 0x7402, 0x5212, 0x7402,
  0x5204, 0x7402, 0x5204, 0x7402, 0x2300, 0x5200, 0x7402, 0x0200
}; // JMP instruction

const PROGMEM word ac_increment[] = {
  0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200
}; // AC increment

const PROGMEM word checkerboard_00007777[] = {
  0x7777, 0x0000, 0x0000, 0x7300, 0x1007, 0x7040, 0x3007,
  0x1007, 0x3410, 0x5000, 0x0000, 0x0011, 0x7777
}; // checker board runs endless MD alters between 0000 and 7777

// group 3x
const PROGMEM word checkerboard_52522525[] = {
  0x0020, 0x0000, 0x7300, 0x7020, 0x7420, 0x5025, 0x5027, 0x1032,
  0x7410, 0x1033, 0x3410, 0x5021, 0x5252, 0x2525, 0x0035, 0x0020
}; // checker board runs endless MD alters between 5252 and 2525

const PROGMEM word print_swreg[] = {
  0x0000, 0x0000, 0x7604, 0x6046, 0x6041, 0x5002, 0x5000, 0x0000
}; // print character in switch register

const PROGMEM word console_print_test[] = {
  0x0000, 0x0000, 0x7001, 0x6046, 0x6041, 0x5002, 0x5000, 0x0000
}; // console print test 03/04

const PROGMEM word echo_test_terminal_03[] = {
  0x0000, 0x0000, 0x6032, 0x6031, 0x5001, 0x6036, 0x6046, 0x6041, 0x5005, 0x5001, 0x0000
}; // Echo test for one terminal at 03/04

const PROGMEM word echo_test_1_to_4_terminals[] = { 0x0200, 0x0000, 0x7300, 0x1205, 0x6412, 0x6401,
                                                    0x5203, 0x0210, 0x6406, 0x5203, 0x7000, 0x7000,
                                                    0x7000, 0x5206, 0x7000, 0x7000, 0x7000, 0x6405,
                                                    0x6404, 0x5203, 0x0200 }; // echo 1-4 terminals

const PROGMEM word pc04_punch_alternating_1_0[] = {
  0x0200, 0x0000, 0x7001, 0x6026, 0x6021, 0x5202, 0x5200, 0x0200
}; // PC04 Punch alternating 1's and 0's

const PROGMEM word pc04_tape_read[] = {
  0x0200, 0x0000, 0x7300, 0x6016, 0x6011, 0x5202, 0x5200, 0x0200
}; // PC04 read the papertape (doesn't load to core, just for test purposes)

const PROGMEM word receive_char_from_term_03[] = {
  0x0000, 0x0000, 0x6032, 0x6031, 0x5001, 0x6036, 0x5001, 0x0000
}; // Place received character into AC from terminal at 03/04

// group 4x
const PROGMEM word memwipe_field0_vince[] = {
  0x3000, 0x0000, 0x0016, 0x3015, 0x3601, 0x2201, 0x2200, 0x5202,
  0x3203, 0x3204, 0x3205, 0x1201, 0x3014, 0x3212, 0x3414, 0x3000
}; // memory wipe field 0 Vince


#define PROGRAM_ENTRY(position, progname)                                                                    \
  [position] = {                                                                                                \
    (const word **) &progname, (word) sizeof(progname)                                             \
  }
#define NO_PROGRAM                                                                                 \
  {                                                                                                \
    NULL, (word) 0                                                                                 \
  }
#define END_PROGRAMS                                                                               \
  {                                                                                                \
    NULL, (word) -1                                                                                \
  }

typedef struct {
  const word **program;
  word size;
} program_t;


const PROGMEM program_t programlist[] = {

  // group 0x
  PROGRAM_ENTRY(00, NO_PROGRAM),                                // No program 0.
  PROGRAM_ENTRY(01, os8_server_40),              //
  PROGRAM_ENTRY(02, rx8_rx01_bootloader),        //
  PROGRAM_ENTRY(03, rx28_rx02_bootloader),       //
  PROGRAM_ENTRY(04, rk05_bootloader_mi8_ed_rk8), //
  PROGRAM_ENTRY(05, tu56_td8e_mi8_eh),           //
  PROGRAM_ENTRY(06, tu56_tc08_dectape_mi8_ec),   //
  PROGRAM_ENTRY(07, tu60_ta8e_caps8),            //

  // group 1x

  PROGRAM_ENTRY(010, pc04_pc8e_papertape_mi8_ea), //
  PROGRAM_ENTRY(011, 0rim_loader_03),              //
  PROGRAM_ENTRY(012, bin_loader_03),              //
  PROGRAM_ENTRY(013, bin_loader_40),              //
  PROGRAM_ENTRY(014, kaleidoscope),               //
  PROGRAM_ENTRY(015, mi8_ee_typeset),             //
  PROGRAM_ENTRY(016, mi8_ef_edusys_low),          //
  PROGRAM_ENTRY(017, mi8_eg_edusys_high),


  // from here programs are not selectable by
  // the dipswitches. These can be loaded by
  // toggeling the SW switch or pushbutton on the
  // PCB only. group 2x

  PROGRAM_ENTRY(020, group1_microinstructions_a), //
  PROGRAM_ENTRY(021, group1_microinstructions_b), //
  PROGRAM_ENTRY(022, operate_instructions),       //
  PROGRAM_ENTRY(023, isz_instructions),           //
  PROGRAM_ENTRY(024, jms_instructions),           //
  PROGRAM_ENTRY(025, jmp_instruction),            //
  PROGRAM_ENTRY(026, ac_increment),               //
  PROGRAM_ENTRY(027, checkerboard_00007777),

  // group 3x

  PROGRAM_ENTRY(030, checkerboard_52522525),      //
  PROGRAM_ENTRY(031, print_swreg),                //
  PROGRAM_ENTRY(032, console_print_test),         //
  PROGRAM_ENTRY(033, echo_test_terminal_03),      //
  PROGRAM_ENTRY(034, echo_test_1_to_4_terminals), //
  PROGRAM_ENTRY(035, pc04_punch_alternating_1_0), //
  PROGRAM_ENTRY(036, pc04_tape_read),             //
  PROGRAM_ENTRY(037, receive_char_from_term_03),  //

  // group 4x
  PROGRAM_ENTRY(memwipe_field0_vince) //
};


#define NUM_PROGRAMS (sizeof(programlist) / sizeof(program_t))


// =============================================================================================================
//                                         Variables
const char version_str = #VERSION

const byte GPIOA = 0x12;  // GPIOA adres in 16-bit mode, 2x 8 I/O ports.
const byte IOCON = 0x0A;  // IOCON adres in 16-bit mode, I/O Expander Configuration Register.
const byte IODIRA = 0x00; // IODIRA adres in 16-bit mode, is het I/O Direction Register voor PortA.
volatile byte ProgramNumber = 0x00; // program to run
volatile byte pulseState = 0x00;    // Previous state of switch
volatile unsigned long SwitchTimeOut =
  3000; // This is the wait time (ms) after the last toggle. Then the program loads.
volatile word ProgramLength = 0x0000; // To calculate the amount of words in the programs
volatile byte RunOnce = 0x00;         // just run Kitt once at turn on

unsigned long SlowDown = 35; // Blink delay in milli seconds. This slows down the loading of a
// bootstrap to give it a nice blinking effect.
// Placing a 0 loads the program at full speed, you can't really see a program to be loaded.
// Placing 50 will give a nice blinking effect but it slows down the program loading.


void setup()
{
  // =============================================================================================================
  //                                         Pin definitions


  pinMode(r_RUN, INPUT); // read RUN signal from Omnibus
  pinMode(r_SW, INPUT);  // read SW signal from Omnibus
  pinMode(Dip_1, INPUT); // Default bootprogam select for one time toggeling SW
  pinMode(Dip_2, INPUT); // Default bootprogam select for one time toggeling SW
  pinMode(Dip_3, INPUT); // Default bootprogam select for one time toggeling SW
  pinMode(Dip_4, INPUT); // Default bootprogam select for one time toggeling SW

  digitalWrite(r_RUN, HIGH); // turn on pull up
  digitalWrite(r_SW, HIGH);  // turn on pull up
  digitalWrite(Dip_1, HIGH); // turn on pull up
  digitalWrite(Dip_2, HIGH); // turn on pull up
  digitalWrite(Dip_3, HIGH); // turn on pull up
  digitalWrite(Dip_4, HIGH); // turn on pull up

  digitalWrite(w_INITIALIZE_H, LOW); // Write zero before initializing output
  digitalWrite(w_PULSE_LA_H, LOW);   // Write zero before initializing output
  digitalWrite(w_MEM_START, LOW);    // Write zero before initializing output
  digitalWrite(w_STOP, LOW);         // Write zero before initializing output

  pinMode(w_INITIALIZE_H, OUTPUT); // Set to output mode
  pinMode(w_PULSE_LA_H, OUTPUT);   // Set to output mode
  pinMode(w_MEM_START, OUTPUT);    // Set to output mode
  pinMode(w_STOP, OUTPUT);         // Set to output mode

  digitalWrite(Set_Flip_Flop, LOW);   // Write zero before initializing output
  digitalWrite(Show_Data, LOW);       // Write zero before initializing output
  digitalWrite(Exam, LOW);            // Write zero before initializing output
  digitalWrite(w_LA_ENABLE, LOW);     // Write zero before initializing output
  digitalWrite(w_MS_IR_DISABLE, LOW); // Write zero before initializing output
  digitalWrite(w_KEY_CONTROL, LOW);   // Write zero before initializing output

  pinMode(Set_Flip_Flop, OUTPUT);   // Set to output mode
  pinMode(Show_Data, OUTPUT);       // Set to output mode
  pinMode(Exam, OUTPUT);            // Set to output mode
  pinMode(w_LA_ENABLE, OUTPUT);     // Set to output mode
  pinMode(w_MS_IR_DISABLE, OUTPUT); // Set to output mode
  pinMode(w_KEY_CONTROL, OUTPUT);   // Set to output mode


  // =============================================================================================================
  //                                          Start I2C bus
  Wire.begin(); // start Wire library as I2C-Bus Master

  Wire.beginTransmission(0x20); // MCP23017 Address
  Wire.write(IOCON);            // IOCON register
  Wire.write(byte(B01000000));  // Enable sequential addresses
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(IODIRA);     // IODIRA register
  Wire.write(byte(0x00)); // Write zeto's to outputs A
  Wire.write(byte(0x00)); // Write zeto's to outputs B
  Wire.endTransmission();


  // =============================================================================================================
  //                                          Setup serial port for debugging
  Serial.begin(115200);
  digitalWrite(0, HIGH); // turn on pull up on RX line

  Kitt();
}
//                                                  End setup
// =============================================================================================================


// =============================================================================================================
//                                                 Main loop
void loop()
{
  Serial.println("PDP8/E, PDP8/F, PDP8/M bootloader by Roland Huisman v" #VERSION);
  Serial.println();
  Serial.print("Default program number by dipswitch ");
  Serial.println(ReadDefaultProgramNumber(), HEX);

  Serial.print("Use SW switch to select program number please... ");
  ProgramNumber = (GetProgramNumber());
  Serial.println(ProgramNumber, HEX);
  Serial.println();

  if (ProgramNumber == 0x00 || ProgramNumber >= NUM_PROGRAMS) {
    ProgramNumber = ReadDefaultProgramNumber();
    if (ProgramNumber == 0x00 || ProgramNumber >= NUM_PROGRAMS) {

      Serial.print("No default selected, no program will be loaded !");
      Serial.println();
    }
    else {
      Serial.print("Default program ");
      Serial.print(ProgramNumber, HEX);
      Serial.println(" will be loaded !");
      Serial.println();
    }
  }
  else {
    LoadProgram(*(programlist[ProgramNumber].program), programlist[ProgramNumber].size);
  }


  // etc...


  Serial.println();
}
//                                                End of main loop
// =============================================================================================================


// =============================================================================================================
//                  Count amount of switch pulses for program number and show in address LEDs
byte GetProgramNumber()
{
  byte ToggledProgramNumber = 0x00;
  byte OctalProgramNumber = 0x00; // highest valid program number is 077
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();

  while ((ToggledProgramNumber == 0) | (currentMillis - previousMillis < SwitchTimeOut)) {
    if ((digitalRead(r_SW) == LOW) && (pulseState == false)) {
      pulseState = true;
      ToggledProgramNumber++;
      currentMillis = millis();
      previousMillis = millis();

      if (ToggledProgramNumber > 1) {
        OctalProgramNumber = ToggledProgramNumber - 1;
        OctalProgramNumber =
          ((OctalProgramNumber << 1) & 0x70)
          | (OctalProgramNumber & 0x07); // ToggledProgramNumber transfer to octal
        SingleStep();
        SwitchRegister(OctalProgramNumber);
        AddresLoad();
      }
    }

    else if (digitalRead(r_SW) == HIGH) {
      pulseState = false;
      currentMillis = millis();
    }
    delay(20);
  }
  SwitchRegister(0x0000);
  Serial.println();
  UndoSingleStep();
  Serial.println();
  return (OctalProgramNumber);
}


// =============================================================================================================
//                             Read dipswitches for the default boot loader to load
byte ReadDefaultProgramNumber()
{
  byte DefaultProgramNumber = PINB;
  DefaultProgramNumber = DefaultProgramNumber >> 2;    // move bits to the right
  DefaultProgramNumber = ~DefaultProgramNumber & 0x0F; // invert reading and wipe out extra bits
  DefaultProgramNumber = ((DefaultProgramNumber << 1) & 0x70)
                         | (DefaultProgramNumber & 0x07); // dipswitch transfer to octal
  return DefaultProgramNumber;
}


// =============================================================================================================
//                                            Load program
void LoadProgram(const word TheProgram[], int ProgramLength)
{
  SingleStep();
  Serial.println();

  ProgramLength = ProgramLength / 2; // calculate programlength in words

  // Get load address:
  SwitchRegister(pgm_read_word_near(TheProgram++));
  AddresLoad();

  // Get extended address:
  SwitchRegister(pgm_read_word_near(TheProgram++));
  ExtendedAddressLoad();

  for (int i = 0; i < (ProgramLength - 3); i++) {
    // Serial.println(pgm_read_word_near(TheProgram+i),HEX);
    SwitchRegister(pgm_read_word_near(TheProgram++));
    Deposit();
    delay(SlowDown);
  }

  // Fetch start address:
  SwitchRegister(pgm_read_word_near(TheProgram));
  AddresLoad();

  SwitchRegister(0x0000);
  Serial.println();
  Serial.println();
  UndoSingleStep();
  Clear();
  Continue();
}


// =============================================================================================================
//                       Transfer the switchregisterdata to the MC23017 to deposit or load address
void SwitchRegister(word LoadData)
{
  Serial.print("Set Switch Register to ");
  Serial.print(LoadData, HEX);
  Serial.print(" ");
  word WordA = (LoadData) &0x00FF;
  word WordB = (LoadData >> 8) & 0x00FF;
  // Serial.println (WordA, HEX);
  // Serial.println (WordB, HEX);
  Wire.beginTransmission(0x20);
  Wire.write(GPIOA);              // gpioa
  Wire.write(byte(WordA) & 0xFF); // set A outputs to WordA
  Wire.write(byte(WordB) & 0xFF); // set B outputs to WordB
  Wire.endTransmission();
}


// =============================================================================================================
//                                          Put PDP into Single Step mode
void SingleStep()
{
  Serial.println("Go into Single Step mode");
  digitalWrite(w_STOP, HIGH); // Places the machine in Single step mode
}


// =============================================================================================================
//                                          Get PDP out of Single Step mode
void UndoSingleStep()
{
  Serial.println("Undo Single Step mode");
  digitalWrite(w_STOP, LOW); // Get the machine out of Single step mode
}


// =============================================================================================================
//                                                Deposit
void Deposit()
{
  Serial.println("Deposit");
  digitalWrite(Set_Flip_Flop, HIGH);
  digitalWrite(w_KEY_CONTROL, HIGH);
  digitalWrite(Show_Data, HIGH);
  digitalWrite(w_MS_IR_DISABLE, HIGH);
  Trigger_Mem_Start();
  digitalWrite(Set_Flip_Flop, LOW);
  digitalWrite(w_KEY_CONTROL, LOW);
  digitalWrite(Show_Data, LOW);
  digitalWrite(w_MS_IR_DISABLE, LOW);
}


// =============================================================================================================
//                                               Address Load
void AddresLoad()
{
  Serial.println("Addres Load");
  digitalWrite(w_LA_ENABLE, HIGH);     // get machine ready to receive an address
  digitalWrite(w_MS_IR_DISABLE, HIGH); // get machine ready to receive an address
  digitalWrite(Set_Flip_Flop, HIGH);   // get machine ready to receive an address
  digitalWrite(Show_Data, HIGH);
  digitalWrite(Exam, HIGH);
  Trigger_Adres_Latch();
  digitalWrite(w_LA_ENABLE, LOW);     // get machine out of address latch mode
  digitalWrite(w_MS_IR_DISABLE, LOW); // get machine out of address latch mode
  digitalWrite(Set_Flip_Flop, LOW);   // get machine out of address latch mode
  digitalWrite(Show_Data, LOW);
  digitalWrite(Exam, LOW);
}


// =============================================================================================================
//                                       Extended Memory Address Load
void ExtendedAddressLoad()
{
  Serial.println("Extended Memory Address Load");
  digitalWrite(w_LA_ENABLE, HIGH);   // get machine ready to receive an extended address
  digitalWrite(w_KEY_CONTROL, HIGH); // get machine ready to receive an extended address
  digitalWrite(Set_Flip_Flop, HIGH); // get machine ready to receive an extended address
  digitalWrite(Show_Data, HIGH);
  Trigger_Adres_Latch();
  digitalWrite(w_LA_ENABLE, LOW);   // get machine out of extended address latch mode
  digitalWrite(w_KEY_CONTROL, LOW); // get machine out of extended address latch mode
  digitalWrite(Set_Flip_Flop, LOW); // get machine out of extended address latch mode
  digitalWrite(Show_Data, LOW);
}


// =============================================================================================================
//                                                 Clear
void Clear()
{
  Serial.print("Clear machine");
  if (digitalRead(r_RUN) == HIGH) // check if machine is not running
  {
    Trigger_Initialize(); // give 400ns positive pulse on Initialize_H
    Serial.print(" >> Machine cleared");
  }
  if (digitalRead(r_RUN) == LOW) // Warning, machine seems to run ! Not cleared
  {
    Serial.print(" >> ERROR !! Machine not cleared due RUN state !");
  }
  Serial.println();
}


// =============================================================================================================
//                                      Continue, set machine in RUN mode
void Continue()
{
  Serial.print("Continue, set machine in RUN mode");
  if (digitalRead(r_RUN) == LOW) // Warning, machine seems to run ! Not started
  {
    Serial.print(" >> ERROR !! Machine not started due RUN state !");
  }
  if (digitalRead(r_RUN) == HIGH) // check if machine is not running
  {
    Trigger_Mem_Start(); // give 400ns positive pulse on Initialize_H
    Serial.print(" >> Running");
  }
  Serial.println();
}

// =============================================================================================================
//                                     Apply 400 ns pulse to selected pin(s) on Port C
void Pulse_PortC(word pattern)
{
  PORTC |= (pattern);  // set bit(s) in pattern
  __asm__("nop\n\t");  //
  __asm__("nop\n\t");  //
  __asm__("nop\n\t");  // Wait for 400nS
  __asm__("nop\n\t");  //
  __asm__("nop\n\t");  //
  __asm__("nop\n\t");  //
  PORTC &= ~(pattern); // clear bit(s) in pattern
}

// =============================================================================================================
//                                      400nS pulse to Initialize
void Trigger_Initialize()
{
  Pulse_PortC(1 << INITIALIZE_BIT);
}


// =============================================================================================================
//                                      400nS pulse to Latch in address
void Trigger_Adres_Latch()
{
  Pulse_PortC(1 << ADDR_LATCH_BIT);
}


// =============================================================================================================
//                                      400nS pulse to start memorycycle
void Trigger_Mem_Start()
{
  Pulse_PortC(1 << MEM_START_BIT);
}


// =============================================================================================================
//                                           Kitt scanner at turn on PDP

void kitt_flash(word address)
{
  SwitchRegister(address);
  AddresLoad();
  delay(KITT_SCAN_DELAY);
}

void Kitt()
{
  static const word kitt_sequence[] = { 0x0001, 0x0003, 0x0007, 0x0016, 0x0034, 0x0070, 0x0160,
                                        0x0340, 0x0700, 0x1600, 0x3400, 0x7000, 0x6000, 0x4000,
										0x4000, 0x6000, 0x7000, 0x3400, 0x1600, 0x0700, 0x0340,
										0x0160, 0x0070, 0x0340, 0x0160, 0x0007, 0x0003, 0x0001};


# define KITT_LENGTH (sizeof(kitt_sequence) / sizeof(word))

  SingleStep();

  for (int i = (1 - KITT_LENGTH); i < KITT_LENGTH; i++) {
    kitt_flash(kitt_sequence[i]);
  }
  UndoSingleStep();
}
