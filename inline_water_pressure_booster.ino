// ===== PIN DEFINITIONS =====
#define FLOW_PIN   34
#define RELAY_PIN  27
#define LED_GREEN  25
#define LED_RED    26

// ===== SETTINGS =====
#define FLOW_SAMPLE_WINDOW_MS 2000
#define MIN_PULSES_FOR_FLOW   3
#define PUMP_ON_DELAY_MS     3000
#define MIN_PUMP_ON_TIME_MS  10000
#define MIN_PUMP_OFF_TIME_MS 5000

volatile unsigned long pulseCount = 0;

unsigned long lastSampleTime = 0;
unsigned long flowStartTime = 0;
unsigned long pumpStateChangeTime = 0;

bool pumpOn = false;
bool flowConfirmed = false;

// ===== ISR =====
void IRAM_ATTR flowISR() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);

  pinMode(FLOW_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // relay OFF
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);

  attachInterrupt(FLOW_PIN, flowISR, FALLING);

  lastSampleTime = millis();
}

void loop() {
  unsigned long now = millis();

  // ===== FLOW SAMPLING =====
  if (now - lastSampleTime >= FLOW_SAMPLE_WINDOW_MS) {
    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    flowConfirmed = (pulses >= MIN_PULSES_FOR_FLOW);

    lastSampleTime = now;
  }

  // ===== FLOW PRESENT =====
  if (flowConfirmed) {
    if (!pumpOn) {
      if (flowStartTime == 0)
        flowStartTime = now;

      if ((now - flowStartTime >= PUMP_ON_DELAY_MS) &&
          (now - pumpStateChangeTime >= MIN_PUMP_OFF_TIME_MS)) {
        turnPumpOn();
      }
    }
  }
  // ===== NO FLOW =====
  else {
    flowStartTime = 0;

    if (pumpOn &&
        (now - pumpStateChangeTime >= MIN_PUMP_ON_TIME_MS)) {
      turnPumpOff();
    }
  }
}

// ===== FUNCTIONS =====
void turnPumpOn() {
  pumpOn = true;
  pumpStateChangeTime = millis();
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  Serial.println("Pump ON");
}

void turnPumpOff() {
  pumpOn = false;
  pumpStateChangeTime = millis();
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
  Serial.println("Pump OFF");
}
