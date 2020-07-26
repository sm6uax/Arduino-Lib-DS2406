#include <OneWire.h>
#include <inttypes.h>

// Device family
#define DS2406_FAMILY       0x12

// Commands
#define DS2406_WRITE_STATUS 0x55
#define DS2406_READ_STATUS  0xAA
#define DS2406_ACCESS_READ  0xF5

// Macro to access the pio from the byte returned by getPioInputs
#define getPioAInputFromByte(a) (a & 0x01)
#define getPioBInputFromByte(a) ((a >> 1) & 0x01)

// Define types
#define uint32_T unsigned long
#define int32_T  signed long
#define uint16_T unsigned int
#define int16_T  signed int
#define uint8_T  unsigned char
#define int8_T   signed char

#define cDs2406Success    0
#define cDs2406NoCom     -1
#define cDs2406WrongCrc  -2
#define cDs2406NotStable -3

// Represents a single 1wire switch on an MLan.
class DS2406 {

 public:

    // Construct the OneWireSwitch with the given OneWire bus and address.
    // addr must be 8 bytes.
    DS2406(OneWire *b);

    // Deactivate the both io
    void init(uint8_t address[8]);

    // Functions to get the state of the ios
    int8_T getPioAInput(uint8_t address[8]);
    int8_T getPioBInput(uint8_t address[8]);
    int8_T getPioInputs(uint8_t address[8]);

    // Functions to set the state of the ios
    int8_T setPioAOutput(uint8_t address[8],bool bPioAState);
    int8_T setPioBOutput(uint8_t address[8],bool bPioBState);
    int8_T setPioOutputs(uint8_t address[8],bool bPioAState, bool bPioBState);

 private:
    OneWire *bus;

    // Flags to store the old state of ouputs
    bool bPioAMemo;
    bool bPioBMemo;

    // Read the status
    void readStatus(uint8_t address[8],uint8_t *buffer);
};
