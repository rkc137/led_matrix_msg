#include <FastLED.h>

#define DATA_PIN 3
#define X 16
#define Y 16
#define NUM_LEDS (X * Y)
#define color CRGB(1, 1, 1);

CRGB leds[NUM_LEDS];

void setled(int x, int y)
{
    if(0 > x || x > X - 1)
        return;
    int index = y * Y;
    if(y % 2 == 0)
        index += x;
    else
        index += Y - x - 1;
    leds[index] = color;
}

void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    for(int i = 0; i < NUM_LEDS; i++)
        leds[i].setColorCode(0);
    FastLED.show();
}

void loop()
{
    String msg("hello");
    for(int pos = -X; pos < 60; pos++)
    {
        for(int i = 0; i < msg.length(); i++)
        {
            int step = i * -10 + pos;
            switch (msg.charAt(i))
            {
            case 'h':
                for(int y = 0; y < Y; y++)
                {
                    setled(4 - step, y);
                    setled(X - 5 - step, y);
                }
                for(int x = 5; x < X - 5; x++)
                    setled(x - step, Y / 2);
                break;
            case 'e':
                for(int y = 0; y < Y; y++)
                    setled(4 - step, y);
                for(int x = 5; x < X - 4; x++)
                {
                    setled(x - step, 0);
                    setled(x - step, Y / 2);
                    setled(x - step, Y - 1);
                }
                break;
            case 'l':
                for(int y = 0; y < Y; y++)
                    setled(4 - step, y);
                for(int x = 4; x < X - 4; x++)
                    setled(x - step, 0);
                break;
            case 'o':
                for(int x = 4; x < X - 5; x++)
                {
                    setled(x - step, 0);
                    setled(x - step, Y - 1);
                }
                for(int y = 0; y < Y; y++)
                {
                    setled(4 - step, y);
                    setled(X - 5 - step, y);
                }
                break;
            }
            FastLED.show();
        }
        for(int j = 0; j < NUM_LEDS; j++)
            leds[j].setColorCode(0);
    }
}