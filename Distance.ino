/*
 Name:		Distance.ino
 Created:	3/1/2022 5:56:42 PM
 Author:	amird
*/
#define TRIG 12
#define ECHO 11

int HandPosition;
#define HAND_IN		1
#define HAND_OUT	2
#define HAND_BLURED 3

int handCounter;
float maxLenInMicroSec = 30 * 2 / 0.034; // max time we wait for responses. this calculation is for 50 cm
void setup() {
	Serial.begin(9600);
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	HandPosition = HAND_BLURED;
}


void loop() {
	int d = getDist();
	switch (HandPosition) {
		case HAND_IN:
			if ((d==0)||(d >= 21)) {
				HandPosition = HAND_OUT;
			}
			handCounter++;
			break;
		case HAND_OUT:
			if ((d>0)&&(d <= 19)) {
				HandPosition = HAND_IN;
			}
			break;
		default:
			handCounter = 0;
			if (d == 0) {
				HandPosition = HAND_OUT;
			}
			else if (d <= 19) {
				HandPosition = HAND_IN;
			} else {
				HandPosition = HAND_OUT;
			}
			break;
	}

	// Prints the distance on the Serial Monitor
	Serial.print("Distance: ");
	Serial.print(d);
	Serial.println(" cm");
}

int getDist() {
	sendTrig();
	// Reads the echoPin, returns the sound wave travel time in microseconds
	int duration = pulseIn(ECHO, HIGH, maxLenInMicroSec);
	// Calculating the distance
	int distance = duration * 0.034 / 2;

	return distance;
}
void sendTrig() {
	digitalWrite(TRIG, LOW);
	delayMicroseconds(10);
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);
}



