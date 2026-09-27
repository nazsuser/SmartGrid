#include <LiquidCrystal.h>

// ----------------------
// PIN DEFINITIONS
// ----------------------

// Potentiometer simulating grid voltage
const int gridSensor = A0;

// Relays
const int relay1 = 5;   // Priority load
const int relay2 = 6;   // Secondary load

// LCD pins
// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


// ----------------------
// SETUP
// ----------------------

void setup() {

  // Relay outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  // Start loads OFF
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);

  // Serial Monitor
  Serial.begin(9600);

  // Start 16x2 LCD
  lcd.begin(16, 2);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("SMART GRID");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(1500);

  lcd.clear();
}


// ----------------------
// MAIN LOOP
// ----------------------

void loop() {

  // Read potentiometer
  int sensorValue = analogRead(gridSensor);

  // Convert reading (0-1023) to voltage (0-5V)
  float gridVoltage = sensorValue * (5.0 / 1023.0);


  // ----------------------
  // SERIAL MONITOR
  // ----------------------

  Serial.print("Simulated Grid Voltage: ");
  Serial.print(gridVoltage);
  Serial.println(" V");


  // ----------------------
  // LCD - FIRST LINE
  // ----------------------

  lcd.setCursor(0, 0);

  lcd.print("Grid: ");
  lcd.print(gridVoltage, 2);
  lcd.print("V   ");


  // ----------------------
  // FULL POWER
  // ----------------------

  if (gridVoltage >= 4.0) {

    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);

    Serial.println("GRID STATUS: FULL POWER");
    Serial.println("Priority Load: ON");
    Serial.println("Secondary Load: ON");

    lcd.setCursor(0, 1);
    lcd.print("L1:ON  L2:ON   ");
  }


  // ----------------------
  // LOW POWER
  // ----------------------

  else if (gridVoltage >= 2.0) {

    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);

    Serial.println("GRID STATUS: LOW POWER");
    Serial.println("Priority Load: ON");
    Serial.println("Secondary Load: OFF");

    lcd.setCursor(0, 1);
    lcd.print("L1:ON  L2:OFF  ");
  }


  // ----------------------
  // GRID FAILURE
  // ----------------------

  else {

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);

    Serial.println("GRID STATUS: CRITICAL");
    Serial.println("Priority Load: OFF");
    Serial.println("Secondary Load: OFF");

    lcd.setCursor(0, 1);
    lcd.print("GRID CRITICAL   ");
  }


  Serial.println("-------------------------");

  delay(500);
}