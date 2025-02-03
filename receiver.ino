#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 3
#define LDR_PIN A2
#define THRESHOLD 100
#define PERIOD 100
#define ENCRYPTION_KEY 0xAA

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address if needed
String message = "";  // String to accumulate characters

bool previous_state;
bool current_state;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();   // Turn on the backlight
}

void loop() {
  current_state = get_ldr();
  if (!current_state && previous_state) {
    char encrypted_byte = get_byte();
    char decrypted_byte = decrypt_byte(encrypted_byte);
    print_byte(decrypted_byte);
  }
  previous_state = current_state;
}

bool get_ldr() {
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;
}

char get_byte() {
  char ret = 0;
  delay(1.5 * PERIOD);
  for (int i = 0; i < 8; i++) {
    ret = ret | (get_ldr() << i);
    delay(PERIOD);
  }
  return ret;
}

char decrypt_byte(char my_byte) {
  return my_byte ^ ENCRYPTION_KEY;  // XOR with the encryption key
}

void print_byte(char my_byte) {
  message += my_byte;  // Add character to the message string
  Serial.print(my_byte);  // Print to Serial Monitor

  // Display the message on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Decrypted Msg:");
  lcd.setCursor(0, 1);
  lcd.print(message);

  // Reset the message if it goes beyond display width
  if (message.length() > 16) {
    message = "";
  }
}
