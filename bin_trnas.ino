#define LED_PIN A3
#define PERIOD 2500

// Boolean array for transmission (replace with your desired sequence)
bool transmissionData[] = {1, 0, 1, 1, 0, 0, 1, 0};
int dataLength = sizeof(transmissionData) / sizeof(transmissionData[0]);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Transmitting data...");

  // Loop through each element in the boolean array
  for (int i = 0; i < dataLength; i++) {
    bool value = transmissionData[i];

    // Print the value being transmitted to Serial Monitor
    Serial.print("Value ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);

    // Turn the LED on or off based on the current value
    if (value) {
      digitalWrite(LED_PIN, HIGH);  // LED on for '1'
    } else {
      digitalWrite(LED_PIN, LOW);   // LED off for '0'
    }

    delay(PERIOD);  // Delay between transmissions
  }

  // Delay before repeating the transmission
  delay(1000);
}
