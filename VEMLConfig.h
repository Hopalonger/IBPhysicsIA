/*
/*
2019-09-06 VEML7700 Configuration creation.
2019-09-29 fixed error in register numbers;  was hex, now binary.

Instructions:
  - Uncomment one #define from each of the 1st groups
  - For the Gain and Integration Time (ALS_IT) find
    the factor in the table below. Assign
    Lux_Factor to the listed lux/count.

*/

// Unless edited, this configuration is for:
//  0.9216 lux / count  and a range of 16 bits.
//  0 to 65536 counts * 0.9216 lux/count = 0 to 60397 Lux
//  (for both ALS and White channels)


// --- Configuration Section -----------------------
// --- all operations are performed by the pre-processor
// --- No memory or processor resources are req'd
// -------------------------------------------------

//--- Uncomment one from this group: 
//#define ALS_GAIN 0b00 // Gain = 1
//#define ALS_GAIN 0b01 // Gain = 2
#define ALS_GAIN 0b10 // Gain = 1/8
//#define ALS_GAIN 0b11 // Gain = 1/4

// --- Uncomment one from this group: 
//#define ALS_IT 0b1100   //   25 ms
#define ALS_IT 0b1000   //   50 ms
//#define ALS_IT 0b0000   //  100 ms
//#define ALS_IT 0b0001   //  200 ms
//#define ALS_IT 0b0010   //  400 ms
//#define ALS_IT 0b0011   //  800 ms

// See datasheet for options for this group:
#define ALS_PERS  0b00
#define ALS_INT_EN  0b00
#define ALS_SD      0b00

#define cmd00  ( (ALS_GAIN << 11) | (ALS_IT << 6) |(ALS_PERS << 4) |(ALS_INT_EN << 1) | (ALS_SD << 0) )

#define Lux_Factor 0.9216

/*
    Gain = 2  Gain = 1  Gain = 1/4  Gain = 1/8
IT(ms)  Resolution lux/count      
800 0.0036  0.0072    0.0288    0.0576
400 0.0072  0.0144    0.0576    0.1152
200 0.0144  0.0288    0.1152    0.2304
100 0.0288  0.0576    0.2304    0.4608
 50 0.0576  0.1152    0.4608    >0.9216<
 25 0.1152  0.2304    0.9216    1.8432

*/
