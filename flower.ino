/*
  Flowers
  
  Fade two sets of LEDs in and out

  Designed for an Adafruit Trinket plus 2N7000s with gates on pins 0
  and 1, LEDs connected to the drains and source connected to ground.

  Algorithm for fade from
    https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms/
 */

#define NSTEPS 50
#define NLEVELS (( 2 * NSTEPS ))
#define MAXBRIGHT 255
#define LED0 0
#define LED1 1
#define OFFSET NSTEPS

int brightness[NLEVELS];
int idx = 0;

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  float R = (NSTEPS * log10(2)) / log10(MAXBRIGHT);
  for (int i = 0; i < NLEVELS; i++) {
    brightness[i] = pow (2, abs(i - NSTEPS) / R) - 1;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  if (idx == NLEVELS) {
    idx = 0;
  }
  analogWrite(LED0, brightness[idx]);
  analogWrite(LED1, brightness[(idx + OFFSET) % NLEVELS]);
  idx++;
  delay(30);
}
