#include "Nunchuck.h"
Nunchuck::Nunchuck(uint8_t data_pin, uint8_t sclk_pin) :
		Accessory(data_pin, sclk_pin) {

}
int Nunchuck::getJoyX() {
	return decodeInt(UNUSED,0,0,UNUSED,0,0,BYTE0,BIT0,BIT7,-127,1.0); // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}
int Nunchuck::getJoyY() {
	return decodeInt(UNUSED,0,0,UNUSED,0,0,BYTE1,BIT0,BIT7,-127,1.0); // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}

int Nunchuck::getRollAngle() {
	return (int) (atan2((double) getAccelX(), (double) getAccelZ()) * 180.0 / PI);
}
int Nunchuck::getPitchAngle() {
	return (int) (atan2((double) getAccelY(), (double) getAccelZ()) * 180.0 / PI);
}
int Nunchuck::getAccelX() {
	return decodeInt(UNUSED,0,0,BYTE2,BIT0,BIT7,BYTE5,BIT2,BIT3,-512,1.0); // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}
int Nunchuck::getAccelY() {
	return decodeInt(UNUSED,0,0,BYTE3,BIT0,BIT7,BYTE5,BIT4,BIT5,-512,1.0); // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}
int Nunchuck::getAccelZ() {
	return decodeInt(UNUSED,0,0,BYTE4,BIT0,BIT7,BYTE5,BIT6,BIT7,-512,1.0); // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}
boolean Nunchuck::checkButtonC() {
	return decodeBit(BYTE5,BIT1,true);  // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}
boolean Nunchuck::checkButtonZ() {
	return decodeBit(BYTE5,BIT0,true);  // see http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
}

void Nunchuck::printInputs(Stream& stream) {
	char st[100];
	stream.println("");

	stream.print("NUNCHUCK ");
	sprintf(st,
			"  JoyX: %4d  | JoyY: %4d | Ax: %4d | Ay: %4d | Az: %4d | Buttons: ",
			getJoyX(), getJoyY(), getAccelX(), getAccelY(),getAccelZ());

	stream.print(st);

	if (checkButtonC())
		stream.print("C");
	else
		stream.print("-");
	if (checkButtonZ())
		stream.print("Z");
	else
		stream.print("-");
	stream.println();
}

