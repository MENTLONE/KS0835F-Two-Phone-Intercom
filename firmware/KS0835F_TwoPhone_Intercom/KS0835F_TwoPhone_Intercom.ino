/*
  KS0835F Two-Phone Automatic Ringing - Fixed
  Arduino UNO R4 Minima
  Serial Monitor: 9600 baud

  Prototype notes:
  - Two KS0835F SLIC breakout boards, two analog corded telephones
  - Audio cross-connections: Board A AOUT -> Board B AIN;
    Board B AOUT -> Board A AIN
  - User verified a mock conversation with both handsets picked up and
    that hanging up returned the system to idle without resetting.

  Board A: F/R D2, RM D3, SHK D4
  Board B: F/R D5, RM D6, SHK D7

  This is the two-phone prototype sketch, NOT 10-house exchange firmware.
  Ringing circuits can generate hazardous telephone-line voltage.
*/
const byte FR_A  = 2;
const byte RM_A  = 3;
const byte SHK_A = 4;
const byte FR_B  = 5;
const byte RM_B  = 6;
const byte SHK_B = 7;

const unsigned long RING_ON_MS = 1000;
const unsigned long RING_OFF_MS = 4000;
const unsigned long HALF_CYCLE_MS = 25;
const unsigned long MAX_ATTEMPT_MS = 30000;
const unsigned long DEBOUNCE_MS = 60;
const unsigned long STATUS_MS = 500;

enum CallState { IDLE, RINGING_A, RINGING_B, ANSWERED, TIMED_OUT };
CallState state = IDLE;
bool ringPhaseOn = false;
bool polarity = false;
unsigned long attemptStartedAt = 0;
unsigned long phaseStartedAt = 0;
unsigned long lastToggleAt = 0;
unsigned long lastStatusAt = 0;
int rawA = LOW, rawB = LOW;
int stableA = LOW, stableB = LOW;
unsigned long changedAAt = 0, changedBAt = 0;

int readStable(byte pin, int &raw, int &stable,
               unsigned long &changedAt, unsigned long now) {
  int v = digitalRead(pin);
  if (v != raw) { raw = v; changedAt = now; }
  if (now - changedAt >= DEBOUNCE_MS) stable = raw;
  return stable;
}
void stopAllRinging() {
  digitalWrite(RM_A, LOW); digitalWrite(FR_A, LOW);
  digitalWrite(RM_B, LOW); digitalWrite(FR_B, LOW);
  ringPhaseOn = false;
}
void startRingPhase() {
  if (state != RINGING_A && state != RINGING_B) return;
  stopAllRinging();
  ringPhaseOn = true; polarity = false;
  phaseStartedAt = millis(); lastToggleAt = millis();
  if (state == RINGING_A) {
    digitalWrite(RM_A, HIGH); Serial.println("Phone A: RING ON");
  } else {
    digitalWrite(RM_B, HIGH); Serial.println("Phone B: RING ON");
  }
}
void stopRingPhase() {
  stopAllRinging(); phaseStartedAt = millis();
  Serial.println("RING OFF: pause");
}
void beginCall(bool ringPhoneB) {
  stopAllRinging();
  state = ringPhoneB ? RINGING_B : RINGING_A;
  attemptStartedAt = millis();
  if (ringPhoneB) Serial.println("CALL: Phone A is off-hook; ringing Phone B.");
  else Serial.println("CALL: Phone B is off-hook; ringing Phone A.");
  startRingPhase();
}
void finishCall(const char *message, CallState finalState) {
  stopAllRinging(); state = finalState; Serial.println(message);
}
void setup() {
  Serial.begin(9600);
  digitalWrite(FR_A, LOW); digitalWrite(RM_A, LOW);
  digitalWrite(FR_B, LOW); digitalWrite(RM_B, LOW);
  pinMode(FR_A, OUTPUT); pinMode(RM_A, OUTPUT);
  pinMode(FR_B, OUTPUT); pinMode(RM_B, OUTPUT);
  pinMode(SHK_A, INPUT_PULLUP); pinMode(SHK_B, INPUT_PULLUP);
  rawA = stableA = digitalRead(SHK_A);
  rawB = stableB = digitalRead(SHK_B);
  changedAAt = changedBAt = millis();
  Serial.println("KS0835F Two-Phone Ringing - Fixed");
  Serial.println("Waiting for a handset to be picked up.");
}
void loop() {
  unsigned long now = millis();
  int hookA = readStable(SHK_A, rawA, stableA, changedAAt, now);
  int hookB = readStable(SHK_B, rawB, stableB, changedBAt, now);
  if (now - lastStatusAt >= STATUS_MS) {
    lastStatusAt = now;
    Serial.print("A SHK="); Serial.print(hookA);
    Serial.print(" | B SHK="); Serial.print(hookB);
    Serial.print(" | State=");
    switch (state) {
      case IDLE: Serial.println("IDLE"); break;
      case RINGING_A: Serial.println("RINGING PHONE A"); break;
      case RINGING_B: Serial.println("RINGING PHONE B"); break;
      case ANSWERED: Serial.println("ANSWERED - AUDIO NOT CONNECTED"); break;
      case TIMED_OUT: Serial.println("TIMED OUT"); break;
    }
  }
  if (state == IDLE) {
    if (hookA == HIGH && hookB == LOW) beginCall(true);
    else if (hookB == HIGH && hookA == LOW) beginCall(false);
    return;
  }
  if (state == RINGING_B) {
    if (hookA == LOW) { finishCall("Caller A hung up. Returning to idle.", IDLE); return; }
    if (hookB == HIGH) { finishCall("Phone B answered. Ringing stopped.", ANSWERED); return; }
  }
  if (state == RINGING_A) {
    if (hookB == LOW) { finishCall("Caller B hung up. Returning to idle.", IDLE); return; }
    if (hookA == HIGH) { finishCall("Phone A answered. Ringing stopped.", ANSWERED); return; }
  }
  if (state == RINGING_A || state == RINGING_B) {
    if (now - attemptStartedAt >= MAX_ATTEMPT_MS) {
      finishCall("Ring attempt timed out.", TIMED_OUT); return;
    }
    if (ringPhaseOn) {
      if (now - lastToggleAt >= HALF_CYCLE_MS) {
        lastToggleAt = now; polarity = !polarity;
        byte fr = (state == RINGING_A) ? FR_A : FR_B;
        digitalWrite(fr, polarity ? HIGH : LOW);
      }
      if (now - phaseStartedAt >= RING_ON_MS) stopRingPhase();
    } else if (now - phaseStartedAt >= RING_OFF_MS) startRingPhase();
    return;
  }
  if ((state == ANSWERED || state == TIMED_OUT) && hookA == LOW && hookB == LOW) {
    state = IDLE; Serial.println("Both phones on-hook. System ready.");
  }
}
