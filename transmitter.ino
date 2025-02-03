#define LED_PIN A3
#define BUTTON_PIN A0
#define PERIOD 100
#define ENCRYPTION_KEY 0xAA

char* string = "lalalalaal";
int string_length;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  string_length = strlen(string);
}

void loop() {
  for (int i = 0; i < string_length; i++) {
    char encrypted_byte = encrypt_byte(string[i]);
    send_byte(encrypted_byte);
  }
  delay(1000);
}

void send_byte(char my_byte) {
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD);

  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, (my_byte & (0x01 << i)) != 0);
    delay(PERIOD);
  }
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
}

char encrypt_byte(char my_byte) {
  return my_byte ^ ENCRYPTION_KEY;  // XOR with the encryption key
}
