class Pixel {
  public: 
    int hue = 0;
    int index = 0;//the how manieth LED in the string am i?
    float bright = 0.;
    int sat = 255;
    int dir = 0; //are we falling or raising intensity?
    float speed = 0.0;

  Pixel() { 
    //pick a random starting color
    hue = (int) random(150,255);
    speed = random(0.01, 1.5);
    //decide the initial brightness direction of this pixel
    if (random(0,100) > 50) { 
      dir = 1;
    } else {
      dir = 0;
    }
  }

  void draw() {   
    if (sat < 255) { 
      sat ++; //increment saturation
    }
    //strip.setPixelColor(index, strip.Color
  }
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
