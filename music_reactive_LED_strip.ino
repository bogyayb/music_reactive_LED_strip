#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 60
#define DATA_PIN 7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);  

int noiseless = 0;

void setup()
{
  pixels.begin();
  pixels.setBrightness(150);

  for(int i = 0; i < NUM_LEDS; i++) 
  {
    pixels.setPixelColor(i+30, pixels.Color(128, 0, 128));
    delay(15); 
    
    pixels.setPixelColor(29-i, pixels.Color(128, 0, 128));
    delay(15);

    pixels.show();
  }

  Serial.begin(9600);
}

void loop()
{
  int s = analogRead(A0);
  Serial.println(s, DEC);

  int x = 4;
  int y = 30;
  noiseless = 648;

  /*
  if(s < noiseless) {
    x = -30;
    y = -3;
  }
  */
  
  int limit = map(s, noiseless+x, noiseless+y, 3, 30);
  int bright = map(limit, 3, 30, 5, 40);
 
  
  for(int i = 0; i < NUM_LEDS/2; i++)
  {
    if(i >= limit) 
    {
      pixels.setPixelColor(i+30, pixels.Color(0, 0, 0));
      pixels.setPixelColor(29-i, pixels.Color(0, 0, 0));      
    } else
    {
      pixels.setPixelColor(i+30, pixels.Color(128, 0, 128));
      pixels.setPixelColor(29-i, pixels.Color(128, 0, 128));
    }
  }
  
  delay(1);
  pixels.show();
  
}
