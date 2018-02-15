//https://github.com/ivanseidel/ArduinoThread

#include <Thread.h>
int ledPin = 2;
int x = 0;

//My simple Thread
Thread myThread = Thread();

// callback for myThread
void niceCallback(){
	static bool ledStatus = false;
	ledStatus = !ledStatus;

	digitalWrite(ledPin, ledStatus);

	Serial.print("COOL! I'm running on: ");
	Serial.println(millis());
}

void setup(){
	Serial.begin(9600);

	pinMode(ledPin, OUTPUT);

	myThread.onRun(niceCallback);
	myThread.setInterval(1000);
}

void loop(){
	// checks if thread should run
	if(myThread.shouldRun())
		myThread.run();

	// Other code...
	x += 1;
  Serial.printf("Other code: %i", x);
  Serial.println();
}
