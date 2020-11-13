#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 50

#define LED_PIN    3
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


class Pixel {
  public:
    int index = 0;//the how manieth LED in the string am i?
    uint16_t hue = 0;
    float bright = 0.;
    uint8_t sat = 0;
    bool dir = 0; //are we falling or raising intensity?
    float speed = 0.0;

    Pixel() {
    }

    void resetPixel() {
      //pick a random starting color
      hue = random(39321, 65536);

      speed = random(10, 1500) / 1000.;
      //decide the initial brightness direction of this pixel
      if (random(0, 100) > 50) {
        dir = 1;
      } else {
        dir = 0;
      }
      Serial.println("Resetted pixel to hue:" + String(hue) + " sat: " + String(sat) + " bright:" + String(bright));
    }

    void draw() {
      if (sat < 255) {
        sat ++; //increment saturation
      }
      //    strip.setPixelColor(index, strip.ColorHSV(hue,sat,bright);
    }
};


Pixel pixels[NUM_PIXELS];

class Swoosh {
  public:
    float swooshPixel;
    float speed;
    uint8_t swooshBright;

    Swoosh() {
      swooshPixel = NUM_PIXELS;
      speed = random(-5, 5) / 10.;
    }

    void resetSwoosh() {
      swooshPixel = NUM_PIXELS;
      speed = random(-5, 5) / 10.;
      swooshBright = int(random(50));
    }

    void drawSwoosh() {
      swooshPixel += speed;
      Serial.println("Swoosh is now at " + String(swooshPixel));

      //change speed a bit;
      speed = + (random(-5, 5) / 100.);

      if (swooshPixel > NUM_PIXELS) {
        swooshPixel = 0;
        resetSwoosh();
      }
      if (swooshPixel < 0) {
        swooshPixel = NUM_PIXELS;
        resetSwoosh();
      }

      for (int i = 0; i < NUM_PIXELS; i ++) {
        if (int(swooshPixel == i)) {
          pixels[i].bright += swooshBright;
          pixels[i].sat = 50;
        }
      }
    }
};



Swoosh swoosh;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  Serial.println("I am alive");


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)
  swoosh = Swoosh();
  for (int i = 0; i < NUM_PIXELS; i ++) {
    pixels[i] = Pixel();
    pixels[i].resetPixel();
  }

}

void loop() {
  swoosh.drawSwoosh();
  for (int i = 0; i < NUM_PIXELS; i ++) {
    pixels[i].draw();
    flickerUpdate(i);

    strip.setPixelColor(i, strip.ColorHSV(pixels[i].hue, pixels[i].sat, pixels[i].bright));
    //    Serial.println("Setting pixel " + String(i) + " to hue " + String(pixels[i].hue) + " sat " + String(pixels[i].sat) + " bright " + String(pixels[i].bright));
  }
  strip.show();
  delay(1);
}

void flickerUpdate(int i) {
  if (pixels[i].dir == 1 && pixels[i].bright < 255) {
    pixels[i].bright += pixels[i].speed;
  }

  if (pixels[i].bright > 255) {
    pixels[i].dir = 0;
  }

  if (pixels[i].dir == 0 && pixels[i].bright > 0) {
    pixels[i].bright -= pixels[i].speed;
  }

  if (pixels[i].bright < 0) {
    pixels[i].dir = 1;
    pixels[i].hue = (int) random(65536 * 0.6, 65536);
    pixels[i].speed = random(10, 1500) / 1000.;
  }
}
