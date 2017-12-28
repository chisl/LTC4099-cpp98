/*
 * name:        LTC4099
 * description: I2C Controlled USB Power Manager/Charger with Overvoltage Protection
 * manuf:       Linear Technology
 * version:     0.1
 * url:         http://cds.linear.com/docs/en/datasheet/4099fd.pdf
 * date:        2017-12-20
 * author       https://chisl.io/
 * file:        LTC4099.hpp
 */

#include <cinttypes>

/* Derive from class LTC4099_Base and implement the read and write functions! */

/* LTC4099: I2C Controlled USB Power Manager/Charger with Overvoltage Protection */
class LTC4099_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG COMMAND_0                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/* REG COMMAND_0:
	 */
	struct COMMAND_0
	{
		static const uint16_t __address = 0;
		
		/* Bits ILim: */
		/*
		 * the maximum current that will be drawn from the VBUS pin in the event that the load at
		 * VOUT (battery charger plus systemload) exceeds the power
		 * available. Any additional power will be drawn from the battery.
		 * The default state for the input current limit setting is
		 * 000, representing the low power 100mA USB setting.
		 */
		struct ILim
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
			static const uint8_t USB_100mA = 0b00; // 
			static const uint8_t USB_500mA = 0b01; // 
			static const uint8_t USB_620mA = 0b10; // 
			static const uint8_t USB_790mA = 0b11; // 
			static const uint8_t USB_1000mA = 0b100; // 
			static const uint8_t USB_1200mA = 0b101; // 
			static const uint8_t USB_SUSPEND_LOW = 0b110; // 
			static const uint8_t USB_SUSPEND_HIGH = 0b111; // 
		};
		/* Bits ICharge: */
		/*
		 * The battery charger current settings are adjusted
		 * by selecting one of the eight servo voltages for the PROG
		 * pin. Recall that the programmed charge current is given
		 * by the expression:
		 * ICHG = VPROG / RPROG * 1030
		 * The default state forthe battery charger current settings is
		 * 000, giving the lowest available servo voltage of 500mV
		 */
		struct ICharge
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00011100; // [2,3,4]
			static const uint8_t PROG_500_mV = 0b00; // 
			static const uint8_t PROG_600_mV = 0b01; // 
			static const uint8_t PROG_700_mV = 0b10; // 
			static const uint8_t PROG_800_mV = 0b11; // 
			static const uint8_t PROG_900_mV = 0b100; // 
			static const uint8_t PROG_1000_mV = 0b101; // 
			static const uint8_t PROG_1100_mV = 0b110; // 
			static const uint8_t PROG_1200_mV = 0b111; // 
		};
		/* Bits COVERX: */
		/*
		 * The C/x setting controls the PROG pin level that the
		 * LTC4099’s C/x comparator uses to report full capacity
		 * charge. For example, if the 100mV setting is chosen, then
		 * the LTC4099 reports that its PROG pin voltage has fallen
		 * below 100mV. For the 50mV setting, LTC4099 reports
		 * that its PROG pin voltage has fallen below 50mV. The C/x
		 * settings are adjusted by comparing the PROG pin voltage
		 * with the values shows in Table 4. The default value for the
		 * C/x setting is 00, giving 100mV detection.
		 */
		struct COVERX
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t PROG_100mV = 0b00; // 
			static const uint8_t PROG_50mV = 0b01; // 
			static const uint8_t PROG_200mV = 0b10; // 
			static const uint8_t PROG_500mV = 0b11; // 
		};
	};
	
	/* Set register COMMAND_0 */
	void setCOMMAND_0(uint8_t value)
	{
		write(COMMAND_0::__address, value, 8);
	}
	
	/* Get register COMMAND_0 */
	uint8_t getCOMMAND_0()
	{
		return read8(COMMAND_0::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG COMMAND_1                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/* REG COMMAND_1:
	 */
	struct COMMAND_1
	{
		static const uint16_t __address = 1;
		
		/* Bits TIMER: */
		/*
		 * The TIMER2–TIMER0 bits control the duration of the battery
		 * charger safety timer. The safety timer starts once the
		 * LTC4099 reaches the 4.100V or the 4.200V float voltage.
		 * As long as input power is available, charging will continue
		 * in float voltage mode until the safety timer expires.
		 */
		struct TIMER
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
			static const uint8_t TIMEOUT_4h = 0b00; // 
			static const uint8_t TIMEOUT_5h = 0b01; // 
			static const uint8_t TIMEOUT_6h = 0b10; // 
			static const uint8_t TIMEOUT_7h = 0b11; // 
			static const uint8_t TIMEOUT_8h = 0b100; // 
			static const uint8_t TIMEOUT_1h = 0b101; // 
			static const uint8_t TIMEOUT_2h = 0b110; // 
			static const uint8_t TIMEOUT_3h = 0b111; // 
		};
		/* Bits DISABLE_CHARGER: */
		/*
		 * The DISABLE_CHARGER bit can be used to prevent battery
		 * charging if needed. This bit should be used with caution
		 * as it can prevent the battery charger from bringing up
		 * the battery voltage. Without the ability to address the I2C
		 * port, only a low voltage on DVCC will clear the I
		 * 2C port to its default state and re-enable charging.
		 */
		struct DISABLE_CHARGER
		{
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits ENABLE_BATTERY_CONDITIONER: */
		/*
		 * The ENABLE_BATTERY_CONDITIONER bit enables the
		 * automatic battery load circuit in the event of simultaneously
		 * high battery voltage and temperature. See the Overtemperature
		 * Battery Conditioner section.
		 */
		struct ENABLE_BATTERY_CONDITIONER
		{
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits VFLOAT: */
		/*
		 * The VFLOAT = 4.2V bit controls the final float voltage of the
		 * LTC4099’s battery charger. A 1 in this bit position changes
		 * the charger from the default float voltage value of 4.100V
		 * to the higher 4.200V level.
		 */
		struct VFLOAT
		{
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits TREG: */
		/*
		 * The TREG = 85°C control bit changes the LTC4099’s battery
		 * charger junction thermal regulation temperature from its
		 * default value of 105°C to a lower setting of 85°C. This may
		 * be used to reduce heat in highly thermally compromised
		 * systems. In general, the high efficiency charging system
		 * of the LTC4099 will keep the junction temperature low
		 * enough to avoid junction thermal regulation.
		 */
		struct TREG
		{
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register COMMAND_1 */
	void setCOMMAND_1(uint8_t value)
	{
		write(COMMAND_1::__address, value, 8);
	}
	
	/* Get register COMMAND_1 */
	uint8_t getCOMMAND_1()
	{
		return read8(COMMAND_1::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                           REG IRQ_MASK                                            *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG IRQ_MASK:
	 * A 1 written to a given position in the mask
	 * register allows status change in that category to generate
	 * an interrupt. A zero in a given position in the mask register
	 * prohibits the generation of an interrupt. The start-up state
	 * of the LTC4099 is all zeros for this register indicating that
	 * no interrupts will be generated without explicit request via
	 * the I2C port. See the Interrupt Generation section.
	 */
	struct IRQ_MASK
	{
		static const uint16_t __address = 2;
		
		/* Bits USBGOOD: */
		struct USBGOOD
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits WALLGOOD: */
		struct WALLGOOD
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits BADCELL: */
		struct BADCELL
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits THERMAL_REG: */
		struct THERMAL_REG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits THERMISTOR_STATUS: */
		struct THERMISTOR_STATUS
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits CHARGER_STATUS: */
		struct CHARGER_STATUS
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
		};
	};
	
	/* Set register IRQ_MASK */
	void setIRQ_MASK(uint8_t value)
	{
		write(IRQ_MASK::__address, value, 8);
	}
	
	/* Get register IRQ_MASK */
	uint8_t getIRQ_MASK()
	{
		return read8(IRQ_MASK::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG OUTPUT                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG OUTPUT:
	 * One status byte may be read from the LTC4099.
	 * A 1 read back in any of the bit positions indicates that the condition is true.
	 */
	struct OUTPUT
	{
		static const uint16_t __address = 3;
		
		/* Bits USBGOOD: */
		/*
		 * indicates the presence of power at VBUS. Criteria for determining this status bit
		 * is derived from the undervoltage lockout circuit on VBUS and is given by the
		 * electrical parameters VUVLO and VDUVLO.
		 */
		struct USBGOOD
		{
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits WALLGOOD: */
		/*
		 * indicates the presence of voltage available at the WALL pin and is derived from
		 * the WALL undervoltage lockout circuit. Like the VBUS pin, this pin has both an
		 * absolute voltage detection level given by the electrical parameter VWALL, as well
		 * as a level relative to BAT given by ΔVWALL. Both of the conditions must be met for
		 * bit 6 to indicate the presence of power at WALL.
		 */
		struct WALLGOOD
		{
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits BADCELL: */
		/*
		 * indicates that the battery has been below the pre- charge threshold level of approximately
		 * 2.85V for more than one-half hour while the charger was attempting to charge. When this occurs,
		 * it is usually the result of a defective cell. However, in some cases a bad cell indication
		 * may be caused by system load prioritization over battery charging. System software can test
		 * for this by forcing a reduction of system load and restarting the battery charger via I2C
		 * (a disable followed by an enable). If the bad cell indication returns, then the cell is
		 * definitively bad.
		 */
		struct BADCELL
		{
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits THERMAL_REG: */
		/*
		 * indicates that the battery charger is in thermal regulation due to excessive LTC4099
		 * junction temperature. Recall that there are two I2C programmable junction temperature
		 * settings available at which to regulate, 85°C and 105°C. Bit 4 indicates thermal regulation
		 * at whichever setting is chosen.
		 */
		struct THERMAL_REG
		{
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits NTC: */
		/* indicate the status of the thermistor measurement circuit  */
		struct NTC
		{
			static const uint8_t mask = 0b00001100; // [2,3]
			static const uint8_t NO_NTC_FAULT = 0b00; // 
			static const uint8_t BATTERY_TOO_COLD = 0b01; // 
			static const uint8_t BATTERY_TOO_HOT = 0b10; // 
			static const uint8_t BATTERY_OVERTEMPERATURE = 0b11; // 
		};
		/* Bits CHRGR: */
		/* status of the battery charger  */
		struct CHRGR
		{
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t CHARGER_OFF = 0b00; // 
			/*
			 * The constant-current state indicates that the battery charger is attempting to charge with
			 * all available current up to the constant-current level programmed, and that the battery has
			 * not yet reached the  oat voltage.
			 */
			static const uint8_t CONSTANT_CURRENT = 0b01;
			/*
			 * The CONSTANT V, IBAT > C/x bit indicates that the battery charger has entered the float voltage
			 * phase of charging (BAT at 4.1V or 4.2V), but that the charge current is still above the C/x
			 * detection level programmed.
			 */
			static const uint8_t CONSTANT_V_GREATER = 0b10;
			/*
			 * The CONSTANT V, IBAT <C/x bit indicates that the battery charge current has dropped below
			 * the C/x detection level programmed
			 */
			static const uint8_t CONSTANT_V_LESS = 0b11;
		};
	};
	
	/* Set register OUTPUT */
	void setOUTPUT(uint8_t value)
	{
		write(OUTPUT::__address, value, 8);
	}
	
	/* Get register OUTPUT */
	uint8_t getOUTPUT()
	{
		return read8(OUTPUT::__address, 8);
	}
	
};
