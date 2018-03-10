/**
 * @file libLCD
 */
#include "lcd.h"
#include "liftControl.h"
#include "main.h"
#include "string.h"

#define LCD_TASK_DELTA 20

static FILE* lcdPort;
static int selection;
static int type;
bool waitForRelease;
int page = 0;
unsigned int sensorTypeNumber = 0;
int lastPage;
bool showBackup;
bool showLift;

void lcdPrintCentered(unsigned char line, const char* string) {
	char out[16];
	for (int i = 0; i < 16; i++)
		out[i] = ' ';
	for (unsigned int i = (16 - (strlen(string) % 16)) / 2, j = 0; j < strlen(string); i++, j++)
		out[i] = string[j];

	lcdPrint(lcdPort, line, out);
}

void lcdScriptInit(FILE* port) {
	lcdInit(port);
	lcdClear(port);
	lcdSetBacklight(port, true);
	lcdPort = port;
}

void _lcdScriptSelect() {
	selecting = true;
	fprintf(stdout, "%s\n", "Choose An Autonomous");
	type = -1;
	unsigned int typeNumber = 0;
	unsigned int scriptNumber = 0;
	selection = -1;
	while (selection == -1) {
		delay(20);
		unsigned int button = lcdReadButtons(lcdPort);

		if (button == 0) {
			waitForRelease = false;
		}

		if (type == -1) { //	Skills Or Match
			lcdPrintCentered(1, "<Match Type>");

			if (button == 1) {
				if (typeNumber != 0)
					typeNumber--;
			}

			else if (button == 4) {
				if (typeNumber < (NUM_TYPE_SCRIPTS - 1))
					typeNumber++;
			}

			if (button == 2 && !waitForRelease) {
				type = typeNumber;
				lcdPrintCentered(1, "<Selected>");
				waitForRelease = true;
				delay(750);
			}

			lcdPrintCentered(2, typeTitles[typeNumber]);
		}
		else if (type == 0) { //	Skills
			lcdSetText(lcdPort, 1, "<Skills Program>");
			if (button == 1) {
				if (scriptNumber != 0)
					scriptNumber--;
			}

			else if (button == 4) {
				if (scriptNumber < (NUM_SKILLS_SCRIPTS - 1))
					scriptNumber++;
			}

			if (button == 2) {
				selection = scriptNumber;
				// lcdPrintCentered(1, "<Selected>");
				lcdPrintCentered(1, "Auton Selected");
				lcdPrintCentered(2, "CHECK THE DRIVE");
				delay(1000);
				selecting = false;
				isSkills = true;
				waitForRelease = true;
				page = 0;
				taskRunLoop(mainMenu, TASK_DEFAULT_STACK_SIZE);
				taskSuspend(NULL);
			}

			lcdPrintCentered(2, skillsTitles[scriptNumber]);
			delay(150);
		}
		else if (type == 1) { //	Match

			lcdPrintCentered(1, "<Match Program>");
			if (button == 1) {
				if (scriptNumber != 0)
					scriptNumber--;
			}

			else if (button == 4) {
				if (scriptNumber < (NUM_MATCH_SCRIPTS - 1))
					scriptNumber++;
			}

			if (button == 2) {
				selection = scriptNumber;
				// lcdPrintCentered(1, "<Selected>");
				lcdPrintCentered(1, "May The Force");
				lcdPrintCentered(2, "Be With You");
				delay(1000);
				selecting = false;
				isSkills = false;
				waitForRelease = true;
				page = 0;
				taskRunLoop(mainMenu, TASK_DEFAULT_STACK_SIZE);
				taskSuspend(NULL);
			}

			lcdPrintCentered(2, matchTitles[scriptNumber]);
			delay(150);
		}
	}
}

void lcdScriptSelect() {
	taskRunLoop(_lcdScriptSelect, LCD_TASK_DELTA);
}

void lcdScriptExecute() {
	if (selection < 0) {
		return; // Don't run a script if one has not been selected.
	}
	if (isSkills) {
		skillsScripts[selection]();
	}
	else if (!isSkills) {
		matchScripts[selection]();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void mainMenu(void) {
	unsigned int firstHeld;
	while (!selecting) {
		delay(20);

		unsigned int button = lcdReadButtons(lcdPort);

		if (button == 0) {
			waitForRelease = false;
			firstHeld = 0;
		}

		if (button == 2 && page > 2 && !waitForRelease) {
			waitForRelease = true;
			firstHeld = millis();
		}

		if (millis() == firstHeld + 1000) {
			page = lastPage;
			fprintf(stdout, "%s\n", "Home");
		}

		if (page <= 2) {
			lastPage = page;
		}

		if (button == 1 && !waitForRelease && page <= 2) {
			if (page != 0)
				page--;
			waitForRelease = true;
		}
		else if (button == 4 && !waitForRelease && page <= 2) {
			if (page < (NUM_MENU_PAGES - 1))
				page++;
			waitForRelease = true;
		}

		if (page == 0) {
			lcdPrintCentered(1, "Battery Levels");
			lcdPrintCentered(2, "   Select  >");
			if (button == 2 && !waitForRelease) {
				waitForRelease = true;
				showBackup = false;
				page = 3;
			}
		}
		else if (page == 1) {
			lcdPrintCentered(1, "Sensor  Values");
			lcdPrintCentered(2, "<  Select  >");
			if (button == 2 && !waitForRelease) {
				waitForRelease = true;
				page = 4;
			}
		}
		else if (page == 2) {
			lcdPrintCentered(1, "Suck Me DRY ");
			lcdPrintCentered(2, "<  Select   ");
			if (button == 2 && !waitForRelease) {
				waitForRelease = true;
				lcdScriptSelect();
			}
		}
		else if (page == 3) {

			if (!showBackup) {
				lcdPrint(lcdPort, 1, "Cortex: %dmV", powerLevelMain());
				lcdPrint(lcdPort, 2, "PwrExp: %1.2fV \\/", (double)analogRead(3) / (double)70);
			}
			else if (showBackup) {
				lcdPrint(lcdPort, 1, "PwrExp: %1.2f%s", (double)analogRead(3) / (double)70, "V");
				lcdPrint(lcdPort, 2, "9 Volt: %dmV   /\\", powerLevelBackup());
			}

			if (button == 4 && !waitForRelease && showBackup) {
				waitForRelease = true;
				showBackup = false;
			}
			else if (button == 4 && !waitForRelease && !showBackup) {
				waitForRelease = true;
				showBackup = true;
			}
		}
		else if (page == 4) {

			if (button == 4 && !waitForRelease && showLift) {
				waitForRelease = true;
				showLift = false;
			}
			else if (button == 4 && !waitForRelease && !showLift) {
				waitForRelease = true;
				showLift = true;
			}
			if (!showLift) {
				lcdPrint(lcdPort, 1, " Ptmr: %d", analogRead(1));
				lcdPrint(lcdPort, 2, "DL:%d DR:%d", encoderGet(enLeftDrive), encoderGet(enRightDrive));
			}
			if (showLift) {
				lcdPrint(lcdPort, 1, "Right Lift: %d", encoderGet(enRightLift));
				lcdPrint(lcdPort, 2, " Left Lift: %d", encoderGet(enLeftLift));
			}

				if (button == 2 && !waitForRelease) {
					waitForRelease = true;
					encoderReset(enLeftLift);
					encoderReset(enRightLift);
			}

			if (button == 1 && !waitForRelease) {
				waitForRelease = true;
				lift(150, false);
				// if (sensorTypeNumber != 0)
				//	sensorTypeNumber--;
			}

			else if (button == 4 && !waitForRelease) {
				waitForRelease = true;
				if (sensorTypeNumber < (NUM_SENSOR_TYPES - 1))
					sensorTypeNumber++;
			}

			// lcdPrintCentered(2, sensorTypes[sensorTypeNumber]);
		}
		else if (page == 5) {
			lcdPrint(lcdPort, 2, "<    Reset   >");
		}
	}
}
