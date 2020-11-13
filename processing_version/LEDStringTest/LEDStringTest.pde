class Swoosh {
  float swooshPixel;
  float speed;
  int swooshBright;

  Swoosh() { 
    this.swooshPixel = numPixels;
    this.speed = random(-.5, .5);
    println("Speed is " + speed);
  }

  void resetSwoosh() { 
    this.swooshPixel = numPixels;
    this.speed = random(-.5, .5);
    this.swooshBright = random(50);
    println("Speed is " + speed);
  }

  void drawSwoosh () { 
    swooshPixel += speed;
  
    //change speed a bit 
    speed += random(-0.05, 0.05);
    
    if (swooshPixel > numPixels) { 
      swooshPixel = 0; 
      resetSwoosh();
    }
    if (swooshPixel < 0) {
      swooshPixel = numPixels;
      resetSwoosh();
    }

    for (int i =0; i < numPixels; i ++) { 
      Pixel pixel = pixels.get(i);
      if (int(swooshPixel) == i) { 
        pixel.bright += swooshBright;
        pixel.sat = 50;
        //println("adding brightness to pixel " + i);
      }
    }
  }
}

class Pixel { 
  color c = color(100);
  int x = 0;
  int y = 0;
  int hue = 0;
  float bright = 0;
  int sat = 255;
  int dir  = 0; //are we falling or raising intensity? 
  float speed = 0.0;

  Pixel(int x, int y) {
    this.x = x;
    this.y = y;
    this.hue = (int) random(150, 255);
    this.speed = random(0.01, 1.5);
    if (random(0, 100) > 50) { 
      this.dir = 1;
    } else { 
      this.dir = 0;
    }
  }

  void draw() { 
    if (sat < 255) {
      sat ++;
    }
    noStroke();
    fill(hue, sat, bright);
    ellipse(x, y, 5, 5);
  }
}

//how many leds?
int numPixels = 150;

int numSwooshes = 1;

ArrayList<Swoosh> swooshes = new ArrayList<Swoosh>();

ArrayList<Pixel> pixels = new ArrayList<Pixel>();

void setup() { 
  size(1200, 600); 
  background(0);
  pixelDensity(2);
  colorMode(HSB);



  for (int i = 0; i < numPixels; i ++) { 
    // Objects can be added to an ArrayList with add()
    int x = (int) (width / numPixels) * i;
    int y = height / 2;
    pixels.add(new Pixel(x, y));
  }

  for (int i = 0; i < numSwooshes; i ++) { 
    swooshes.add(new Swoosh());
  }
}


void draw() { 
  background(0);

  for (int i = 0; i < numSwooshes; i ++) { 
    swooshes.get(i).drawSwoosh();
  }

  for (int i = 0; i < numPixels; i ++) { 
    //get the pixel
    Pixel pixel = pixels.get(i);
    flickerUpdate(i);

    //draw the pixel
    pixel.draw();
  }
}

void flickerUpdate(int i) { 
  Pixel pixel = pixels.get(i);
  //calculate next color;
  //println("updating");
  if (pixel.dir == 1 && pixel.bright < 255) { 

    pixel.bright += pixel.speed;
    //println("increasing brightness " + bright);
  } 
  if (pixel.bright > 255) {
    pixel.dir = 0;
  } 

  if (pixel.dir == 0 && pixel.bright > 0) {
    pixel.bright -= pixel.speed;
  }

  if (pixel.bright < 0) { 
    pixel.dir = 1; 
    pixel.hue = (int) random(150, 255);
    pixel.speed = random(0.01, 1.5);
  }
}

void mousePressed() {
}
