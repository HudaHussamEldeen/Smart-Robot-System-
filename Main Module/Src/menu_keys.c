/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/


#include "menu_keys.h"
Menu_Inputs Menu_btns;
Menue_Data Module_Data;

uint8_t Selected_Page = 0;

static void USB_Send_Report(const char *Str)
{
    if (Str != NULL)                                 // Check if input is valid
    {
        uint8_t StrLen = strlen(Str);                // Get the length of the string
        if (StrLen > 0)                              // Ensure non-zero length
        {
            CDC_Transmit_FS((uint8_t*)Str, StrLen);  // Transmit string over USB
        }
    }
}

void MenuKeys_Init(void)
{
	Menu_btns.X_IdPtr = &Menu_btns.X_Id;
	Menu_btns.Y_IdPtr = &Menu_btns.Y_Id;
	Menu_btns.Z_IdPtr = &Menu_btns.Z_Id;
	Menu_btns.PagePtr = &Menu_btns.Page;
	Menu_btns.PrevPagePtr = &Menu_btns.PrevPage;

}
uint8_t EnterHandle(void)
{
	if ( ENTER_BTN_STATE == 0)
	{
		GLCD_ClearScreen();
		IdHandle();
		DataForwardingHandle();
		while ( ENTER_BTN_STATE == 0);
		HAL_GPIO_TogglePin(GPIOB, LED_B_15_Pin);
		HAL_GPIO_TogglePin(GPIOB, LED_B_14_Pin);
		return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t UpHandle(void)
{
	if (UP_BTN_STATE == 0)
	{
		while (UP_BTN_STATE == 0);

		HAL_GPIO_TogglePin(GPIOD, LED_D_12_Pin);
		return 0;
	}
	return 1;
}
uint8_t DownHandle(void)
{
	if (DOWN_BTN_STATE == 0)
	{
		while ( DOWN_BTN_STATE == 0);

		HAL_GPIO_TogglePin(GPIOD, LED_D_14_Pin);
		return 0;
	}
	return 1;
}
uint8_t RightHandle(void)
{
	if (RIGHT_BTN_STATE == 0)
	{
		while (RIGHT_BTN_STATE == 0);

		HAL_GPIO_TogglePin(GPIOD, LED_D_15_Pin);
		return 0;
	}
	return 1;
}

uint8_t LeftHandle(void)
{
	if (LEFT_BTN_STATE == 0)
	{
		while (LEFT_BTN_STATE == 0);
		HAL_GPIO_TogglePin(GPIOD, LED_D_13_Pin);
		return 0;
	}
	return 1;
}
uint8_t CancelHandle(void)
{
	if (CANCEL_BTN_STATE == 0)
	{
		GLCD_ClearScreen();
		Menu_btns.Page = Menu_btns.PrevPage;
		while ( CANCEL_BTN_STATE == 0);
		HAL_GPIO_TogglePin(GPIOC, LED_C_8_Pin);
		return 0;
	}
	return 1;
}

void MenuHandler(void)
{

}

void page_0(void)
{
	Menu_btns.PrevPage = MAIN_PAGE;
	Menu_btns.Max_Page_Y_Id = 1;
	GLCD_GoTo(25, 56);
	GLCD_WriteString_h("*Robot System*");
	GLCD_GoTo(5, 58);
	GLCD_WriteString("Select Mode:");
	GLCD_GoTo(5, 60);
	Menu_btns.Y_Id == 0 ? GLCD_WriteString_h("Bluetooth Mode") : GLCD_WriteString("Bluetooth Mode");

	GLCD_GoTo(5, 61);
	Menu_btns.Y_Id == 1 ?
			GLCD_WriteString_h("Manual Mode") : GLCD_WriteString("Manual Mode");
	MaxIdHanle();
}



void page_1(void)
{
	Menu_btns.PrevPage = MAIN_PAGE;
	Menu_btns.Max_Page_Y_Id = 4;

	MaxIdHanle();
	GLCD_GoTo(5, 56);
	GLCD_WriteString("Select Module:");
	GLCD_GoTo(5, 58);
	Menu_btns.Y_Id == 0 ?
			GLCD_WriteString_h("Robot Arm ") : GLCD_WriteString("Robot Arm ");
	GLCD_GoTo(5, 59);
	Menu_btns.Y_Id == 1 ?
			GLCD_WriteString_h("MotorStudy") : GLCD_WriteString("MotorStudy");
	GLCD_GoTo(5, 60);
	Menu_btns.Y_Id == 2 ?
			GLCD_WriteString_h("Sensors&Actuators") :
			GLCD_WriteString("Sensors&Actuators");
	GLCD_GoTo(5, 61);
	Menu_btns.Y_Id == 3 ?
			GLCD_WriteString_h("Pendulum ") : GLCD_WriteString("Pendulum ");

	GLCD_GoTo(5, 62);
	Menu_btns.Y_Id == 4 ?
			GLCD_WriteString_h("Intelligent ") :
			GLCD_WriteString("Intelligent ");

}

// Related to Robot Arm
void page_2(void)
{
	MaxIdHanle();
	MaxDataHandle();
	Menu_btns.PrevPage = MANUAL_MODE;


	Menu_btns.Max_Page_Y_Id = 5;
	Menu_btns.Max_Page_X_Id = 1;
	Menu_btns.Max_Page_Z_Id = 2;

	GLCD_GoTo(5, 56);

	GLCD_WriteString_h("*Robot Arm Module*");

	GLCD_GoTo(5, 58);

	if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 0))
	{
		GLCD_WriteString_h("Base     ");
		GLCD_WriteIntData(Module_Data.Arm0Value, 0);
	}
	else if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Base     ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 58);
		GLCD_WriteIntData(Module_Data.Arm0Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			if (Module_Data.Arm0Value > 180)
			{
				//Module_Data.Arm0Value = 90;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm0Value += 10;
				Menu_btns.Z_Id = 0;
			}
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm0Value == 0)
			{
				Module_Data.Arm0Value = 180;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm0Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Base     ");
		GLCD_WriteIntData(Module_Data.Arm0Value, 0);
	}

	/************************************************************************/

	GLCD_GoTo(5, 59);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 1))
	{
		GLCD_WriteString_h("Waist    ");

		GLCD_WriteIntData(Module_Data.Arm1Value, 0);
	}

	else if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Waist    ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 59);
		GLCD_WriteIntData(Module_Data.Arm1Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			if (Module_Data.Arm1Value > 160)
			{
				//Module_Data.Arm1Value = 90;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm1Value += 10;
				Menu_btns.Z_Id = 0;
			}
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm1Value == 0)
			{
				Module_Data.Arm1Value = 160;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm1Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}

	} else
	{
		GLCD_WriteString("Waist    ");
		GLCD_WriteIntData(Module_Data.Arm1Value, 0);
	}

	GLCD_GoTo(5, 60);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 2))
	{
		GLCD_WriteString_h("Shoulder ");

		GLCD_WriteIntData(Module_Data.Arm2Value, 0);
	}
	else if ((Menu_btns.Y_Id == 2) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Shoulder ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 60);
		GLCD_WriteIntData(Module_Data.Arm2Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			if (Module_Data.Arm2Value > 180)
			{
				//Module_Data.Arm2Value = 90;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm2Value += 10;
				Menu_btns.Z_Id = 0;
			}
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm2Value == 0)
			{
				Module_Data.Arm2Value = 180;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm2Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Shoulder ");
		GLCD_WriteIntData(Module_Data.Arm2Value, 0);
	}

	GLCD_GoTo(5, 61);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 3))
	{
		GLCD_WriteString_h("Elbow    ");
		GLCD_WriteIntData(Module_Data.Arm3Value, 0);
	}

	else if ((Menu_btns.Y_Id == 3) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Elbow    ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 61);
		GLCD_WriteIntData(Module_Data.Arm3Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			if (Module_Data.Arm3Value > 160)
			{
				//Module_Data.Arm3Value = 90;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm3Value += 10;
				Menu_btns.Z_Id = 0;
			}
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm3Value == 0)
			{
				Module_Data.Arm3Value = 160;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm3Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Elbow    ");
		GLCD_WriteIntData(Module_Data.Arm3Value, 0);
	}

	GLCD_GoTo(5, 62);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 4))
	{
		GLCD_WriteString_h("Wrist    ");
		GLCD_WriteIntData(Module_Data.Arm4Value, 0);
	}

	else if ((Menu_btns.Y_Id == 4) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Wrist    ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 62);
		GLCD_WriteIntData(Module_Data.Arm4Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			if (Module_Data.Arm4Value > 180)
			{
				//Module_Data.Arm4Value = 90;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm4Value += 10;
				Menu_btns.Z_Id = 0;
			}
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm4Value == 0)
			{
				Module_Data.Arm4Value = 160;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm4Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Wrist    ");
		GLCD_WriteIntData(Module_Data.Arm4Value, 0);
	}

	GLCD_GoTo(5, 63);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 5))
	{
		GLCD_WriteString_h("Gripper  ");
		GLCD_WriteIntData(Module_Data.Arm5Value, 0);
	}
	else if ((Menu_btns.Y_Id == 5) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Gripper  ");
		GLCD_WriteString("   ");
		GLCD_GoTo(58, 63);
		GLCD_WriteIntData(Module_Data.Arm5Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.Arm5Value += 5;
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Arm5Value == 0)
			{
				Module_Data.Arm5Value = 45;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Arm5Value -= 5;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Gripper  ");
		GLCD_WriteIntData(Module_Data.Arm5Value, 0);
	}
}

// Related to Motor Study
void page_3(void)
{
	// Handles maximum IDs for menu navigation and updates
	MaxIdHanle();
	MaxDataHandle();

	// Configure menu buttons with specific parameters
	Menu_btns.PrevPage = MANUAL_MODE;
	Menu_btns.Max_Page_Y_Id = 3;
	Menu_btns.Max_Page_X_Id = 1;
	Menu_btns.Max_Page_Z_Id = 2;

	 // Display the page title
	GLCD_GoTo(5, 56);
	GLCD_WriteString_h("*Robot Motor Module*");

	// First menu item: Servo Angle
	GLCD_GoTo(5, 58);
	if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 0))
	{
		// Display servo angle and its value
		GLCD_WriteString_h("ServoAngle");
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.ServoValue, 0);
	}
	else if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("ServoAngle ");
		GLCD_WriteString("    ");			// Clear previous value
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.ServoValue, 1);
		 // Adjust servo angle based on Z-axis menu interaction
		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.ServoValue += 10;	// Increase servo value
			Menu_btns.Z_Id = 0;				// Reset Z-axis state
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.ServoValue==0)
			{
				Module_Data.ServoValue = 180;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.ServoValue -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		// Default display for servo angle
		GLCD_WriteString("ServoAngle ");
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.ServoValue, 0);
	}

	// Second menu item: Stepper Degree
	GLCD_GoTo(5, 59);
	if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 0))
	{
		// Display stepper degree and its value
		GLCD_WriteString_h("StepperDeg ");
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.StepperValue, 0);

	}
	else if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("StepperDeg ");
		GLCD_WriteString("    ");				// Clear previous value
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.StepperValue, 1);
		// Adjust stepper degree based on Z-axis menu interaction
		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.StepperValue += 10;		// Increase stepper value
			Menu_btns.Z_Id = 0;					// Reset Z-axis state
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.StepperValue==0)
			{
				Module_Data.StepperValue = 350;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.StepperValue -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		 // Default display for stepper degree
		GLCD_WriteString("StepperDeg ");
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.StepperValue, 0);
	}

	// Third menu item: DC Motor Direction
	GLCD_GoTo(5, 60);
	if ((Menu_btns.Y_Id == 2) && (Menu_btns.X_Id == 0))
	{
		// Display DC motor direction
		GLCD_WriteString_h("DCMotorDir ");
		GLCD_GoTo(70, 60);
		//GLCD_WriteIntData(Module_Data.DCDIR, 0);
		Module_Data.DCDIR == 0 ?
				GLCD_WriteString("Right") : GLCD_WriteString("Left ");
	}
	else if ((Menu_btns.Y_Id == 2) && (Menu_btns.X_Id == 1))
	{
		// Adjust DC motor direction based on Z-axis menu interaction
		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.DCDIR = 0;		// Set to "Right"
			Menu_btns.Z_Id = 0;			// Reset Z-axis state
		}
		else if (Menu_btns.Z_Id == 2)
		{
			Module_Data.DCDIR = 1;		// Set to "Left"
			Menu_btns.Z_Id = 0;			// Reset Z-axis state
		}
		GLCD_WriteString("DCMotorDir ");
		GLCD_WriteString("    ");		// Clear previous value
		GLCD_GoTo(70, 60);
		Module_Data.DCDIR == 0 ?
		GLCD_WriteString_h("Right") : GLCD_WriteString_h("Left ");
		//GLCD_WriteIntData(Module_Data.DCDIR, 1);
	}
	else
	{
		// Default display for DC motor direction
		GLCD_WriteString("DCMotorDir ");
		GLCD_GoTo(70, 60);
		Module_Data.DCDIR == 0 ?
				GLCD_WriteString("Right ") : GLCD_WriteString("Left ");
		//GLCD_WriteIntData(Module_Data.DCDIR, 0);

	}

	// Fourth menu item: DC Motor Duty Cycle
	GLCD_GoTo(5, 61);
	if ((Menu_btns.Y_Id == 3) && (Menu_btns.X_Id == 0))
	{
		// Display DC motor duty cycle and its value
		GLCD_WriteString_h("DCDutyCyc. ");
		GLCD_GoTo(70, 61);
		GLCD_WriteIntData(Module_Data.DCValue, 0);

	}
	else if ((Menu_btns.Y_Id == 3) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("DCDutyCyc. ");
		GLCD_WriteString("    ");
		GLCD_GoTo(70, 61);
		GLCD_WriteIntData(Module_Data.DCValue, 1);

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.DCValue += 10;
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.DCValue==0)
			{
				Module_Data.DCValue = 100;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.DCValue -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("DCDutyCyc. ");
		GLCD_GoTo(70, 61);
		GLCD_WriteIntData(Module_Data.DCValue, 0);
	}
}

// Related to Sensor and Actuators
void page_4(void)

{
	MaxIdHanle();
	MaxDataHandle();
	Menu_btns.PrevPage = MANUAL_MODE;
	Menu_btns.Max_Page_Y_Id = 1;
	Menu_btns.Max_Page_X_Id = 1;
	Menu_btns.Max_Page_Z_Id = 8;
	GLCD_GoTo(5, 56);
	GLCD_WriteString_h("*Sensors Module*");
	GLCD_GoTo(5, 58);
	if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 0))
	{
		GLCD_WriteString_h("DutyCycle");
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.Duty, 0);

	}
	else if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("DutyCycle ");
		GLCD_WriteString("    ");
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.Duty, 1);
		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.Duty += 10;
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id != 0)
		{
			Module_Data.Duty -= 10;
			Menu_btns.Z_Id = 0;
		}
	}
	else
	{
		GLCD_WriteString("DutyCycle ");
		GLCD_GoTo(70, 58);
		GLCD_WriteIntData(Module_Data.Duty, 0);
	}

	GLCD_GoTo(5, 59);
	if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 0))
	{
		GLCD_WriteString_h("Movement ");
		GLCD_GoTo(70, 59);
		switch(Module_Data.Movement)
		{
		   case 1:
			   GLCD_WriteString("Back   ");
			   break;
		   case 2:
			   GLCD_WriteString("Left   ");
		   	   break;
		   case 3:
			   GLCD_WriteString("Right  ");
		   	   break;
		   case 4:
			   GLCD_WriteString("R Right");
		   	   break;
		   case 5:
			   GLCD_WriteString("R Left ");
		   	   break;
		   case 6:
			   GLCD_WriteString("Stop   ");
		   	   break;
		   case 7:
			   GLCD_WriteString("Forward");
		   	   break;
		   default:
			   break;
		}
	}
	else if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 1))
	{
		if (Menu_btns.Z_Id > 7) Menu_btns.Z_Id = 1;
		else if (Menu_btns.Z_Id == 0) Menu_btns.Z_Id = 7;
		Module_Data.Movement = Menu_btns.Z_Id;
		GLCD_WriteString("Movement ");
		GLCD_GoTo(70, 59);
		switch(Module_Data.Movement)
		{
		   case 1:
			   GLCD_WriteString_h("Back   ");
			   break;
		   case 2:
			   GLCD_WriteString_h("Left   ");
		   	   break;
		   case 3:
			   GLCD_WriteString_h("Right  ");
		   	   break;
		   case 4:
			   GLCD_WriteString_h("R Right");
		   	   break;
		   case 5:
			   GLCD_WriteString_h("R Left ");
		   	   break;
		   case 6:
			   GLCD_WriteString_h("Stop   ");
		   	   break;
		   case 7:
			   GLCD_WriteString_h("Forward");
		   	   break;
		   default:
			   break;
		}
	}
	else
	{
		GLCD_WriteString("Movement ");
		GLCD_GoTo(70, 59);
		switch(Module_Data.Movement)
		{
		   case 1:
			   GLCD_WriteString("Back   ");
			   break;
		   case 2:
		   	   GLCD_WriteString("Left   ");
		   	   break;
		   case 3:
		   	   GLCD_WriteString("Right  ");
		   	   break;
		   case 4:
			   GLCD_WriteString("R Right");
		   	   break;
		   case 5:
			   GLCD_WriteString("R Left ");
		   	   break;
		   case 6:
		   	   GLCD_WriteString("Stop   ");
		   	   break;
		   case 7:
		   	   GLCD_WriteString("Forward");
		   	   break;
		   default:
			   break;
		}
	}
}

// Related to Pendulum
void page_5(void)
{
	MaxIdHanle();
	MaxDataHandle();
	Menu_btns.PrevPage = MANUAL_MODE;

	Menu_btns.Max_Page_Y_Id = 2;
	Menu_btns.Max_Page_X_Id = 1;
	Menu_btns.Max_Page_Z_Id = 2;
	GLCD_GoTo(5, 56);
	GLCD_WriteString_h("*Pendulum Module*");

	GLCD_GoTo(5, 58);
	if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 0))
	{
		GLCD_WriteString_h("Task: ");
		GLCD_GoTo(70, 58);
		GLCD_WriteString(Module_Data.Task == 'C' ? "Cart    " : "Pendulum");
	}
	else if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Task: ");
		GLCD_GoTo(70, 58);
		GLCD_WriteString_h(Module_Data.Task == 'C' ? "Cart    " : "Pendulum");

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.Task = 'P';
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			Module_Data.Task = 'C';
			Menu_btns.Z_Id = 0;
		}
	}
	else
	{
		GLCD_WriteString("Task: ");
		GLCD_GoTo(70, 58);
		GLCD_WriteString(Module_Data.Task == 'C' ? "Cart    " : "Pendulum");
	}

	GLCD_GoTo(5, 59);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 1))
	{
		GLCD_WriteString_h("P_SetPoint");
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.P_SetPoint, 0);
		GLCD_WriteString(" ");
	}
	else if ((Menu_btns.X_Id == 1) && (Menu_btns.Y_Id == 1))
	{
		GLCD_WriteString("P_SetPoint");
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.P_SetPoint, 1);
		GLCD_WriteString(" ");

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.P_SetPoint += 5;
			Menu_btns.Z_Id = 0;
			if(Module_Data.P_SetPoint >= 40)
				Module_Data.P_SetPoint = 40;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			Module_Data.P_SetPoint -= 5;
			Menu_btns.Z_Id = 0;
			if(Module_Data.P_SetPoint <= 10)
				Module_Data.P_SetPoint = 10;
		}
	}
	else
	{
		GLCD_WriteString("P_SetPoint");
		GLCD_GoTo(70, 59);
		GLCD_WriteIntData(Module_Data.P_SetPoint, 0);
		GLCD_WriteString(" ");
	}

	GLCD_GoTo(5, 60);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 2))
	{
		GLCD_WriteString_h("A_SetPoint");
		GLCD_GoTo(70, 60);
		GLCD_WriteIntData(Module_Data.A_SetPoint, 0);
	}
	else if ((Menu_btns.X_Id == 1) && (Menu_btns.Y_Id == 2))
	{
		GLCD_WriteString("A_SetPoint");
		GLCD_GoTo(70, 60);
		GLCD_WriteIntData(Module_Data.A_SetPoint, 1);

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.A_SetPoint += 1;
			Menu_btns.Z_Id = 0;
			if(Module_Data.A_SetPoint >= 185)
				Module_Data.A_SetPoint = 185;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			Module_Data.A_SetPoint -= 1;
			Menu_btns.Z_Id = 0;
			if(Module_Data.A_SetPoint <= 175)
				Module_Data.A_SetPoint = 175;
		}
	}
	else
	{
		GLCD_WriteString("A_SetPoint");
		GLCD_GoTo(70, 60);
		GLCD_WriteIntData(Module_Data.A_SetPoint, 0);
	}
}

// Related to Intelligent
void page_6(void)
{
	MaxIdHanle();
	MaxDataHandle();
	Menu_btns.PrevPage = MANUAL_MODE;
	Menu_btns.Max_Page_Y_Id = 1;
	Menu_btns.Max_Page_X_Id = 1;
	Menu_btns.Max_Page_Z_Id = 2;

	GLCD_GoTo(5, 56);
	GLCD_WriteString_h("*Intelligent Module*");
	GLCD_GoTo(5, 58);

	if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 0))
	{
		GLCD_WriteString_h("Servo0 ");
		GLCD_WriteIntData(Module_Data.Servo0Value, 0);
	}
	else if ((Menu_btns.Y_Id == 0) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Servo0 ");
		GLCD_WriteString("     ");
		GLCD_GoTo(45, 58);
		GLCD_WriteIntData(Module_Data.Servo0Value, 1);

		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.Servo0Value += 10;
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Servo0Value==0)
			{
				Module_Data.Servo0Value = 180;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Servo0Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Servo0 ");
		GLCD_WriteIntData(Module_Data.Servo0Value, 0);
	}

	GLCD_GoTo(5, 59);
	if ((Menu_btns.X_Id == 0) && (Menu_btns.Y_Id == 1))
	{
		GLCD_WriteString_h("Servo1 ");

		GLCD_WriteIntData(Module_Data.Servo1Value, 0);
	}

	else if ((Menu_btns.Y_Id == 1) && (Menu_btns.X_Id == 1))
	{
		GLCD_WriteString("Servo1 ");
		GLCD_WriteString("     ");
		GLCD_GoTo(45, 59);
		GLCD_WriteIntData(Module_Data.Servo1Value, 1);
		if (Menu_btns.Z_Id == 1)
		{
			Module_Data.Servo1Value += 10;
			Menu_btns.Z_Id = 0;
		}
		else if (Menu_btns.Z_Id == 2)
		{
			if (Module_Data.Servo1Value==0)
			{
				Module_Data.Servo1Value = 180;
				Menu_btns.Z_Id = 0;
			}
			else
			{
				Module_Data.Servo1Value -= 10;
				Menu_btns.Z_Id = 0;
			}
		}
	}
	else
	{
		GLCD_WriteString("Servo1 ");
		GLCD_WriteIntData(Module_Data.Servo1Value, 0);
	}
}

void page_7(void)
{
	Menu_btns.PrevPage = MAIN_PAGE;
	if (Uart_RX_Flag == 1)
	{
		USB_Send_Report("Bluetooth Mode: Message Received.\n");
		GLCD_ClearScreen();
		GLCD_GoTo(5, 56);
		GLCD_WriteString_h("*Bluetooth Mode*");
		GLCD_GoTo(5, 58);
		GLCD_WriteString("Message Received ...");
		osDelay(2000);
		Uart_RX_Flag = 0; //TODO
	}
	else
	{
		GLCD_GoTo(5, 56);
		GLCD_WriteString_h("*Bluetooth Mode*");
		GLCD_GoTo(5, 58);
		GLCD_WriteString("Waiting for Data ...");
	}
}

void button_scan()
{
	Menu_btns.Left   = LeftHandle();
	Menu_btns.Right  = RightHandle();
	Menu_btns.Up     = UpHandle();
	Menu_btns.Down   = DownHandle();
	Menu_btns.Enter  = EnterHandle();
	Menu_btns.Cancel = CancelHandle();

	if (Menu_btns.Left == 0)
	{
		Menu_btns.X_Id--;
	}

	else if (Menu_btns.Right == 0)
	{
		Menu_btns.X_Id++;
	}

	Z_Y_Id_scan();
}

void menu()
{
	switch (Menu_btns.Page)
	{
		case 0:
			page_0();
			Selected_Page = MAIN_PAGE;
			break;
		case 1:
			page_1();
			Selected_Page = SELECT_PAGE;
			break;
		case 2:
			page_2();
			Selected_Page = ARM_MANUALMODE;
			break;
		case 3:
			page_3();
			Selected_Page = MOTOR_MANUALMODE;
			break;
		case 4:
			page_4();
			Selected_Page = SENSORS_MANUALMODE;
			break;
		case 5:
			page_5();
			Selected_Page = PENDULUM_MANUALMODE;
			break;
		case 6:
			page_6();
			Selected_Page = INTELLIGENT_MANUALMODE;
			break;
		case 7:
			page_7();
			Selected_Page = BlUETOOTH_MODE;
			break;
		case 8:
			//page_8();
			break;
	}
}

void IdHandle(void)
{
	switch (Menu_btns.Page)
	{
		case MAIN_PAGE:
			if (Menu_btns.Y_Id == 0)
			{
				Menu_btns.Page = BlUETOOTH_MODE;
				USB_Send_Report("Bluetooth Mode Selected. \n");
			}
			else if (Menu_btns.Y_Id == MANUAL_MODE)
			{
				Menu_btns.Page = 1;
				USB_Send_Report("Manual Mode Selected. \n");
			}

			break;

		case MANUAL_MODE:
			if (Menu_btns.Y_Id == 0)
			{
				Menu_btns.Page = ARM_MANUALMODE;
				USB_Send_Report("ARM Module Selected \n");
			}

			else if (Menu_btns.Y_Id == 1)
			{
				Menu_btns.Page = MOTOR_MANUALMODE;
				USB_Send_Report("Motor Study Module Selected \n");
			}

			else if (Menu_btns.Y_Id == 2)
			{
				Menu_btns.Page = SENSORS_MANUALMODE;
				USB_Send_Report("Sensors Module Selected \n");
			}

			else if (Menu_btns.Y_Id == 3)
			{
				Menu_btns.Page = PENDULUM_MANUALMODE;
				USB_Send_Report("Pendulum Module Selected \n");
			}

			else if (Menu_btns.Y_Id == 4)
			{
				Menu_btns.Page = INTELLIGENT_MANUALMODE;
				USB_Send_Report("Intelligent Module Selected \n");
			}

			break;
	}
}

void MaxIdHanle(void)
{
	if (Menu_btns.Y_Id > Menu_btns.Max_Page_Y_Id)
	{
		Menu_btns.Y_Id = 0;
	}
	else if (Menu_btns.Y_Id < 0)
	{
		Menu_btns.Y_Id = Menu_btns.Max_Page_Y_Id;
	}
	if (Menu_btns.X_Id > Menu_btns.Max_Page_X_Id)
	{
		Menu_btns.X_Id = 0;
	}
	else if (Menu_btns.X_Id < 0)
	{
		Menu_btns.X_Id = Menu_btns.Max_Page_X_Id;
	}
	if (Menu_btns.Z_Id > Menu_btns.Max_Page_Z_Id)
	{
		Menu_btns.Z_Id = 0;
	}
	else if (Menu_btns.Z_Id < 0)
	{
		Menu_btns.Z_Id = Menu_btns.Max_Page_Z_Id;
	}

}

void Z_Y_Id_scan(void)
{
	if ((Menu_btns.Page == ARM_MANUALMODE || Menu_btns.Page == SENSORS_MANUALMODE
	|| Menu_btns.Page == MOTOR_MANUALMODE || Menu_btns.Page == INTELLIGENT_MANUALMODE || Menu_btns.Page == PENDULUM_MANUALMODE)
	&& Menu_btns.X_Id == 1)
	{
		if (Menu_btns.Up == 0)
		{
			Menu_btns.Z_Id++;
		}
		else if (Menu_btns.Down == 0)
		{
			Menu_btns.Z_Id--;
		}
	}
	else
	{
		if (Menu_btns.Up == 0)
		{
			Menu_btns.Y_Id--;
		}
		else if (Menu_btns.Down == 0)
		{
			Menu_btns.Y_Id++;
		}
	}
}
void MaxDataHandle(void)
{
	switch (Menu_btns.Page)
	{
		case ARM_MANUALMODE:

			if (Module_Data.Arm0Value > 180)
				Module_Data.Arm0Value = 0;

			if (Module_Data.Arm1Value > 160)
				Module_Data.Arm1Value = 10;
			else if (Module_Data.Arm1Value < 10)
				Module_Data.Arm1Value = 160;

			if (Module_Data.Arm2Value > 180)
				Module_Data.Arm2Value = 0;

			if (Module_Data.Arm3Value > 160)
				Module_Data.Arm3Value = 0;

			if (Module_Data.Arm4Value > 160)
				Module_Data.Arm4Value = 0;

			if (Module_Data.Arm5Value > 45)
				Module_Data.Arm5Value = 0;
			break;

		case MOTOR_MANUALMODE:

			if (Module_Data.ServoValue > 180)
				Module_Data.ServoValue = 0;

			if (Module_Data.DCValue > 100)
				Module_Data.DCValue = 0;
			if (Module_Data.StepperValue > 360)
				Module_Data.StepperValue = 10;

			break;
		case SENSORS_MANUALMODE:

			if (Module_Data.Duty > 100)
				Module_Data.Duty = 0;

			if (Module_Data.Movement > 7)
				Module_Data.Movement = 1;
			else if (Module_Data.Movement < 1)
				Module_Data.Movement = 7;

		case INTELLIGENT_MANUALMODE:

			if (Module_Data.Servo0Value > 150 || Module_Data.Servo0Value < 30)
				Module_Data.Servo0Value = 90;
			if (Module_Data.Servo1Value > 150 || Module_Data.Servo1Value < 30)
				Module_Data.Servo1Value = 90;
			break;

		case PENDULUM_MANUALMODE:
			break;
	}
}

void DataForwardingHandle(void)
{
	switch (Menu_btns.Page)
	{
	case ARM_MANUALMODE:
		TxData[0] = 'R';
		TxData[1] = 'A';
		TxData[2] = Module_Data.Arm0Value;
		TxData[3] = Module_Data.Arm1Value;
		TxData[4] = Module_Data.Arm2Value;
		TxData[5] = Module_Data.Arm3Value;
		TxData[6] = Module_Data.Arm4Value;
		TxData[7] = Module_Data.Arm5Value;

		break;
	case MOTOR_MANUALMODE:
		TxData[0] = 'M';
		TxData[1] = 'S';
		TxData[2] = Module_Data.ServoValue;
		TxData[3] = Module_Data.StepperDir;
		uint8_t stepHighByte = (Module_Data.StepperValue >> 8) & 0xFF; // Get the high byte
		uint8_t stepLowByte = Module_Data.StepperValue;                // Get the low byte
		TxData[4] = stepLowByte;

		TxData[5] = stepHighByte;
		TxData[6] = Module_Data.DCDIR;
		TxData[7] = Module_Data.DCValue;
		break;
	case SENSORS_MANUALMODE:
		TxData[0] = 'S';
		TxData[1] = 'A';
		TxData[2] = Module_Data.Duty;
		TxData[3] = 0;
		TxData[4] = 0;
		TxData[5] = Module_Data.Movement;
		TxData[6] = 0;
		TxData[7] = 0;
		break;
	case INTELLIGENT_MANUALMODE:
		TxData[0] = 'I';
		TxData[1] = 'N';
		TxData[2] = Module_Data.Servo0Value;
		TxData[3] = Module_Data.Servo1Value;
		TxData[4] = 0;
		TxData[5] = 0;
		TxData[6] = 0;
		TxData[7] = 0;
		break;
	case PENDULUM_MANUALMODE:
		TxData[0] = 'P';
		TxData[1] = 'R';
		TxData[2] = 0;
		TxData[3] = 0;
		TxData[4] = 0;
		TxData[5] = Module_Data.Task;
		TxData[6] = Module_Data.P_SetPoint;
		TxData[7] = Module_Data.A_SetPoint;
			break;

	default:
		break;

	}

    if (Menu_btns.Page != MANUAL_MODE && Menu_btns.Page != BlUETOOTH_MODE)
    {
    	CanSendMessage(TxData);
    }
}
