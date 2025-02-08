#define BUZZER_PIN  23  
#define BUTTON_PIN  22  
hw_timer_t *My_timer = NULL;

volatile int speedIndex = 0;  
int speedMultipliers[5] = {200, 100, 75 , 50, 25}; 

int melody[] = { 587.3	, 587.3	, 	1175, 880, 830.6, 784, 698.5, 587.3, 698.5 , 784}; 
int noteDurations[] = { 250, 250, 500, 750, 500, 500, 500, 250, 250, 250}; 


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void IRAM_ATTR buttonISR() {

  if (millis() - lastDebounceTime > debounceDelay) {
    speedIndex = (speedIndex + 1) % 5;
    Serial.println(speedIndex);
    lastDebounceTime = millis(); 
  }
}

void lumpoong () {
  for (int i = 0; i < 10; i++) {
    playNote(melody[i], noteDurations[i]);
  }
}

void playNote(int frequency, int duration) {
  if (frequency > 0) {
    tone(BUZZER_PIN, frequency, duration * speedMultipliers[speedIndex] / 100);
  }
  delay(duration * speedMultipliers[speedIndex] / 100 + 20);
}

void setup() {
  Serial.begin(9600);
  My_timer = timerBegin(1000000);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  timerAlarm(My_timer, 1000000, true, 0);  
}

void loop() {
  attachInterrupt(BUTTON_PIN, buttonISR, FALLING);
  lumpoong();
  delay(4000);
}
