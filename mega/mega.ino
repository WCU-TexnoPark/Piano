const int trigPin[] = {7, 8, 9, 10, 11, 12, 13};
const int echoPin[] = {A0, A1, A2, A3, A4, A5, A6};
const int buzzerPin = 3;

const int led1 = 22;
const int led2 = 23;
const int led3 = 24;
const int led4 = 25;
const int led5 = 26;
const int led6 = 27;
const int led7 = 28;

const int notes[] = {262, 294, 329, 349, 392, 440, 494};
const int thresholdDistance = 10;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int distance[7];
  for (int i = 0; i < 7; i++) {
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);
    long duration = pulseIn(echoPin[i], HIGH);
    distance[i] = (duration / 2) / 29.1;
    Serial.print("Distance ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(distance[i]);
    Serial.println(" cm");
  }
  for (int i = 0; i < 7; i++) {
    if (distance[i] > 0 && distance[i] < thresholdDistance) {
      tone(buzzerPin, notes[i]);
      Serial.print("Playing '");
      switch(i) {
        case 0: Serial.print("do"); digitalWrite(led1, HIGH); break;
        case 1: Serial.print("Re"); digitalWrite(led2, HIGH); break;
        case 2: Serial.print("Mi"); digitalWrite(led3, HIGH); break;
        case 3: Serial.print("Fa"); digitalWrite(led4, HIGH); break;
        case 4: Serial.print("Sol"); digitalWrite(led5, HIGH); break;
        case 5: Serial.print("la"); digitalWrite(led6, HIGH); break;
        case 6: Serial.print("Si"); digitalWrite(led7, HIGH); break;
      }
      Serial.println("'");
      break;
    }
    else {
      noTone(buzzerPin);
    }
  }
}

