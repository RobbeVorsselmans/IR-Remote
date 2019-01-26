#include <Arduino.h>
#include <IRremote.h>

enum Button { zero, one, two, three, four, five, six, seven, eight, nine, minus, plus, prev, next, pause, none };
Button command;

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

// Puts a PWM on PWM_PIN with a specific dutycycle, corresponding to a specific button
void translateIR() {
	//Serial.println(results.value);
	switch (results.value)
	{
	case 0xFF6897: //0
		command = zero;
		break;
	case 0xFF30CF: //1
		command = one;
		break;
	case 0xFF18E7: //2
		command = two;
		break;
	case 0xFF7A85: //3
		command = three;
		break;
	case 0xFF10EF: //4
		command = four;
		break;
	case 0xFF38C7: //5
		command = five;
		break;
	case 0xFF5AA5: //6
		command = six;
		break;
	case 0xFF42BD: //7
		command = seven;
		break;
	case 0xFF4AB5: //8
		command = eight;
		break;
	case 0xFF52AD: //9
		command = nine;
		break;
	case 0xFFC23D: //Play/Pause
		command = pause;
		break;
	case 0xFFE01F: //Vol-
		command = minus;
		break;
	case 0xFFA857: //Vol+
		command = plus;
		break;
	case 0xFF22DD: //Prev
		command = prev;
		break;
	case 0xFF02FD: //Next
		command = next;
		break;
	case 0xFFFFFFFF: //Same button pressed several times
		command = none;
		break; // do nothing, keep last command
	default:
		command = none;
		break;
	}
}

void readCommand(Button command) {
	switch (command) {
		case zero:
			Serial.println("You pressed Zero.");
			break;
		case one:
			Serial.println("You pressed One.");
			break;
		case two:
			Serial.println("You pressed Two.");
			break;
		default:
			break;
	}
}

void setup() {
	pinMode(PWM_PIN, OUTPUT);
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
}

void loop() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		translateIR(); // stores input in command
		readCommand(command);
		delay(50);
		irrecv.resume(); // Receive the next value
	}
}
