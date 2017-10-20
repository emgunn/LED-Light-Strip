//LED strip reads GRB (green, red, blue)

#include <FastLED.h>
#include <pixeltypes.h>

#define NUM_LEDS 150
//which pin the data pin is inserted into
#define LED_PIN 3
#define MAX_VAL 255
#define NUM_COLORS 3

CRGB led[NUM_LEDS];
CRGB backup[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_PIN>(led, NUM_LEDS);

  //insert static setup code here
  //setColor(CRGB(150,150,150));
}
void loop() {
  //gradualBlinkIncrease(10, 1000, 50);

  //randomAppearDisappear(150, 20);

  //RANDOM COLOR SUICIDES
  /*CRGB color = randomColor();
  suicides(color, 25, 20);*/

  //RANDOM COLOR SKIP FILL demo
  CRGB color = randomColor();
  wave(color, 2, 20);
  delay(3000);
  waveRandom(2, 20);
  delay(5000);
  off();
  CRGB color2 = randomColor();
  wave(color, 5, 40);
  delay(3000);
  waveRandom(5, 40);
  delay(5000);
  off();

  /*CRGB color = randomColor();
  singleColorRun(color, CRGB(0,0,0), 20, 0, 150);
  singleColorRunBackwards(color, CRGB(0,0,0), 20, 150, 0);*/
  
  /*popRandom(150, 20);
  popOverwrite(150, 20, CRGB(50,0,50));*/
  //unpop(150, 20);
  
  /*alternatingNRandomColors(3, 50, 0, 200);
  delay(5000);*/

  
  /*alternating3Colors(5, randomColor(), randomColor(), randomColor());
  delay(3000);*/

  /*alternatingNRandomColors(1, 150);
  delay(5000);*/

  /*
  CRGB color1 = randomColor();
  CRGB color2 = randomColor();
  singleColorRun(color1, color2, 10,
    0, 150, 30); */
}

/**
 * Sets entire strip to given color and shows it
 * @param CRGB color represents the color
 */
void setColor(CRGB color) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = color;
  }
  FastLED.show();
}

/**
 * Sets entire strip to given color and shows it
 * @param CRGB color represents the color
 * @param int startIndex represents index of beginning of range (inclusive)
 * @param int endIndex represents index of end of range (inclusive)
 */
void setColor(CRGB color, int startIndex, int endIndex) {
  for(int i = startIndex; i < endIndex + 1; i++) {
    led[i] = color;
  }
  FastLED.show();
}

/**
 * Sets entire strip to given color and shows it
 * @param int hex represents the integer hex value of the color
 */
void setColor(int hex) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(hex);
  }
  FastLED.show();
}

/**
 * Sets entire strip to given color and shows it
 * @param ints R, G, and B represent the RGB values
 */
void setColor(int R, int G, int B) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(R, G, B);
  }
  FastLED.show();
}

/**
 * Sets entire strip to a given intensity of red
 * @param int val represents the 0-255 value for red
 */
void setRed(int val) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(val, 0, 0);
  }
}

/**
 * Sets entire strip to a given intensity of green
 * @param int val represents the 0-255 value for green
 */
void setGreen(int val) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0, val, 0);
  }
}

/**
 * Sets entire strip to a given intensity of blue
 * @param int val represents the 0-255 value for blue
 */
void setBlue(int val) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0, 0, val);
  }
}

/**
 * Generates a random color with values between 0-255
 * @return CRGB random color
 */
CRGB randomColor() {
  return CRGB(random(MAX_VAL + 1), random(MAX_VAL + 1), random(MAX_VAL + 1));
}

/**
 * Generates a random color with values between 0-255
 * @param int floor1 represents floor of RGB values
 * @param int ceiling represents ceiling of RGB values
 * @return CRGB random color
 */
CRGB randomColor(int floor1, int ceiling) {
  return CRGB(random(floor1, ceiling), random(floor1, ceiling),
    random(floor1, ceiling));
}

/**
 * Turns all the lights off (sets to black)
 */
void off() {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0);
  }
  FastLED.show();
}

/**
 * Getter method to check if an LED is off
 * @param CRGB led represents light to be checked
 * @return boolean true if off, false if on
 */
boolean isOff(CRGB led) {
  if(led == CRGB(0, 0, 0)) {
    return true;
  }
  return false;
}

/**
 * Saves the current board into one of the save slots
 */
void saveBoard() {
  for(int i = 0; i < NUM_LEDS; i++) {
    backup[i] = led[i];
  }
}

/**
 * Saves the current board into one of the save slots
 * @param int startIndex represents the start of the range to save
 * @param int endIndex represents the end of the range to save
 */
void saveBoard(int startIndex, int endIndex) {
  for(int i = startIndex; i < endIndex + 1; i++) {
    backup[i] = led[i];
  }
}

/**
 * Loads a saved board to the current board
 */
void loadBoard() {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = backup[i];
  }
  FastLED.show();
}

void loadBoard(int startIndex, int endIndex) {
  for(int i = startIndex; i < endIndex + 1; i++) {
    led[i] = backup[i];
  }
  FastLED.show();
}

/**
 * Sets the entire strip to the brightest red
 */
void makeRed() {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(MAX_VAL, 0, 0);
  }
}

/**
 * Sets the entire strip to the brightest green
 */
void makeGreen() {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0, MAX_VAL, 0);
  }
}

/**
 * Sets the entire strip to the brightest blue
 */
void makeBlue() {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0, 0, MAX_VAL);
  }
}

/**
 * Switches between red, green, and blue. Fades in and out
 * @param int timeDelay represents the amount of time in ms
 *        to delay the fade (timeDelay = 10 is a good setting)
 */
void fadeRGB(int timeDelay) {
  for(int i = 0; i < MAX_VAL + 1; i++) {
    setBlue(i);
    FastLED.show();
    delay(timeDelay);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    setBlue(i);
    FastLED.show();
    delay(timeDelay);
  }
  for(int i = 0; i < MAX_VAL + 1; i++) {
    setRed(i);
    FastLED.show();
    delay(timeDelay);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    setRed(i);
    FastLED.show();
    delay(timeDelay);
  }
  for(int i = 0; i < MAX_VAL + 1; i++) {
    setGreen(i);
    FastLED.show();
    delay(timeDelay);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    setGreen(i);
    FastLED.show();
    delay(timeDelay);
  }
}

/**
 * Gradually changes colors by adding or subtracting a random value between
 * R, G, or B
 * @param int timeDelay represents the time in ms to delay each iteration
 */
//set delay to 0 for a dynamic color set
//set delay to 10 for a slower change
//still something wrong as colors should not be jumping (should have a gradual change)
void fadeRandomColors(int timeDelay) {
  //red is 0, green is 1, blue is 2
  int RGB[NUM_COLORS];
  //directions: false = adding, true = subtracting
  bool dir[NUM_COLORS];
  off();
  for(int i = 0; i < NUM_COLORS; i++) {
    dir[i] = true;
    RGB[i] = 1;
  }
  int randomNum;
  while(1) {
    for(int i = 0; i < NUM_COLORS; i++) {
      if(RGB[i] >= MAX_VAL || RGB[i] == 1) {
        dir[i] = !dir[i];
      }
    }
    randomNum = random(0, NUM_COLORS);
    if(dir[randomNum] == false) {
      RGB[randomNum]++;
    }
    else if(dir[randomNum]) {
      RGB[randomNum]--;
    }
    setColor(RGB[0], RGB[1], RGB[2]);
    delay(timeDelay);
  }
}

/**
 * Sets the entire strip to a random color with given floors
 * and ceilings for the R, G, and B values
 * @param int changeSpeed represents the timed delay in ms
 */
void setRandomColor(int changeSpeed) {
  int red = random(0, MAX_VAL + 1);
  int green = random(0, MAX_VAL + 1);
  int blue = random(0, MAX_VAL + 1);
  setColor(red, green, blue);
  delay(changeSpeed);
}

/**
 * Sets the entire strip to a random color with given floors
 * and ceilings for the R, G, and B values
 * @param int changeSpeed represents the timed delay in ms
 * @param int floor1 represents the floor for the RGB values
 * @param int ceiling represents the ceiling for the RGB values
 */
//int floor should be 0 for all colors
//int ceiling should be 256 for all colors
void setRandomColor(int changeSpeed, int floor1, int ceiling) {
  int red = random(floor1, ceiling);
  int green = random(floor1, ceiling);
  int blue = random(floor1, ceiling);
  setColor(red, green, blue);
  delay(changeSpeed);
}

/**
 * Sets each individual LED light to a random color within a given range
 * @param int changeSpeed represents the delay in ms
 * @param int floor1 represents the minimum value (inclusive) for R, G, and B
 * @param int ceiling represents the maximum value (exclusive) for R, G, and B
 */
//0 and 256 for all colors
void allRandomColors(int changeSpeed, int floor1, int ceiling) {
  for(int i = 0; i < NUM_LEDS; i++) {
    int red = random(floor1, ceiling);
    int green = random(floor1, ceiling);
    int blue = random(floor1, ceiling);
    led[i] = CRGB(red, green, blue);
  }
  FastLED.show();
  delay(changeSpeed);
}

/**
 * Swaps between 3 given colors (taken as their integer value)
 * @param int timeDelay represents delay between swaps in ms
 * @param int color1 represents first color value
 * @param int color2 represents second color value
 * @param int color3 represents third color value
 */
//timeDelay of 1000 is around 2 seconds
void swap3Colors(int timeDelay, int color1, int color2, int color3) {
  delay(timeDelay);
  setColor(color1);
  delay(timeDelay);
  setColor(color2);
  delay(timeDelay);
  setColor(color3);
 }

/**
 * Shuts off the entire strip for given time in ms
 * @param int changeSpeed represents delay in ms
 */
//color has already been set and shown
void blink(int changeSpeed) {
  //blinks it off
  off();
  delay(changeSpeed);
}

/**
 * Shuts off the entire strip for given time in ms
 * Also sets the strip to a specified color
 * @param int color represents hex value of color
 * @param int changeSpeed represents delay in ms
 */
void blink(int color, int changeSpeed) {
 setColor(color);
 delay(changeSpeed);
 off();
 delay(changeSpeed);
}

/**
 * Starts blinking with a faster rate, then ends slower
 * @param int minSpeed represents minimum time in ms of blink
 * @param int maxSpeed represents maximum time in ms of blink
 * @param int interval represents the step size of each iteration
 */
//100, 500, 30 is a good setting
//minSpeed is inclusive, maxSpeed is exclusive
//in milliseconds
//starts fast, then ends slower
void gradualBlinkIncrease(int minSpeed, int maxSpeed, int interval) {
  for(int i = minSpeed; i < maxSpeed; i += interval) {
    allRandomColors(i, 0, MAX_VAL + 1);
    blink(i);
  }
}

/**
 * Starts blinking with a slower rate, then ends faster
 * @param int minSpeed represents minimum time in ms of blink
 * @param int maxSpeed represents maximum time in ms of blink
 * @param int interval represents the step size of each iteration
 */
//minSpeed is inclusive, maxSpeed is exclusive
//in milliseconds
//starts slow, then ends faster
void gradualBlinkDecrease(int minSpeed, int maxSpeed, int interval) {
  for(int i = maxSpeed - 1; i >= minSpeed; i -= interval) {
    allRandomColors(i, 0, MAX_VAL + 1);
    blink(i);
  }
}

/**
 * Makes an alternating pattern of 3 given colors with a given thickness
 * @param int thickness represents the thickness of each bar
 * @param unsigned int colors represents the 3 colors' hex values
 */
//makes a pattern of 3 colors with specified thickness
void alternating3Colors(int thickness, unsigned int color1,
  unsigned int color2, unsigned int color3) {
  CRGB colors[NUM_COLORS];
  colors[0] = CRGB(color1);
  colors[1] = CRGB(color2);
  colors[2] = CRGB(color3);
  int index = 0;
  for(int i = 0; i < NUM_LEDS; i += thickness) {
    for(int j = 0; j < thickness; j++) {
      if(i + j == NUM_LEDS) {
        return;
      }
      led[i + j] = colors[index];
    }
    index = (index + 1) % NUM_COLORS;
  }
  FastLED.show();
}

/**
 * Makes an alternating pattern of 3 given colors with a given thickness
 * @param int thickness represents the thickness of each bar
 * @param CRGB colors represents the 3 colors
 */
//makes a pattern of 3 colors with specified thickness
void alternating3Colors(int thickness, CRGB color1,
  CRGB color2, CRGB color3) {
  CRGB colors[3];
  colors[0] = color1;
  colors[1] = color2;
  colors[2] = color3;
  int index = 0;
  for(int i = 0; i < NUM_LEDS; i += thickness) {
    for(int j = 0; j < thickness; j++) {
      if(i + j == NUM_LEDS) {
        return;
      }
      led[i + j] = colors[index];
    }
    index = (index + 1) % NUM_COLORS;
  }
  FastLED.show();
}

/**
 * Makes a pattern of n colors with a given thickness
 * @param int thickness represents the thickness of each bar
 * @param CRGB colors[] represents the colors that we want
 * @param int n represents the number of distinct colors
 */
//makes a pattern of n colors with specified thickness
void alternatingNColors(int thickness, CRGB colors[], int n) {
  int index = 0;
  for(int i = 0; i < NUM_LEDS; i += thickness) {
    for(int j = 0; j < thickness; j++) {
      if(i + j == NUM_LEDS) {
        return;
      }
      led[i + j] = colors[index];
    }
    index = (index + 1) % n;
  }
  FastLED.show();
}

/**
 * Makes a pattern of n random colors with given thickness
 * @param int thickness represents the thickness of each bar
 * @param int n represents the number of random colors
 */
void alternatingNRandomColors(int thickness, int n) {
  CRGB randomColors[n];
  for(int i = 0; i < n ; i++) {
    randomColors[i] = randomColor();
  }
  alternatingNColors(thickness, randomColors, n);
}

/**
 * Makes a pattern of n random colors with given thickness
 * @param int thickness represents the thickness of each bar
 * @param int n represents the number of random colors
 * @param int floor1 represents floor of random
 * @param int ceiling represents ceiling of random
 */
void alternatingNRandomColors(int thickness, int n, int floor1,
  int ceiling) {
  CRGB randomColors[n];
  for(int i = 0; i < n ; i++) {
    randomColors[i] = randomColor(floor1, ceiling);
  }
  alternatingNColors(thickness, randomColors, n);
}

/**
 * Creates a Christmas-themed function in red, green, and white
 * @param int thickness represents thickness of each bar
 */
void christmasLights(int thickness) {
  CRGB colors[3];
  colors[0] = CRGB(MAX_VAL, 0, 0);
  colors[1] = CRGB(0, MAX_VAL, 0);
  colors[2] = CRGB(MAX_VAL, MAX_VAL, MAX_VAL);
  int index = 0;
  for(int i = 0; i < NUM_LEDS; i += thickness) {
    for(int j = 0; j < thickness; j++) {
      if(i + j == NUM_LEDS) {
        return;
      }
      led[i + j] = colors[index];
    }
    index = (index + 1) % NUM_COLORS;
  }
  FastLED.show();
}

/**
 * Makes a single light of given color run across a black strip
 * @param CRGB color represents the color of the single light
 * @param int delaySpeed represents the speed of the run
 */
//uses black as background
void singleColorRun(CRGB color, int delaySpeed) {
  CRGB black = CRGB(0, 0, 0);
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i == 0) {
      led[NUM_LEDS - 1] = black;
    }
    led[i] = color;
    led[i - 1] = black;
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Makes a single light of given color run across a background of
 * given color. Can specify a starting point and ending point, as well
 * as a speed
 * @param CRGB foreground represents the color of the running light
 * @param CRGB background represents the color of the background lights
 * @param int delaySpeed represents the delay time in ms
 * @param int startIndex represents the starting point in the LED strip
 * @param int endIndex represents the end point in the LED strip
 */
//startIndex must be before endIndex
//endIndex is exclusive (set to 150 for all lights)
void singleColorRun(CRGB foreground, CRGB background,
  int delaySpeed, int startIndex, int endIndex) {
  setColor(background);
  for(int i = startIndex; i < endIndex; i++) {
    if(i == startIndex) {
      led[endIndex - 1] = background;
    }
    led[i] = foreground;
    led[i - 1] = background;
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Makes a single light of given color run across in the opposite
 * direaction a background of given color. Can specify a starting point
 * and ending point, as well as a speed.
 * @param CRGB foreground represents the color of the running light
 * @param CRGB background represents the color of the background lights
 * @param int delaySpeed represents the delay time in ms
 * @param int startIndex represents the starting point in the LED strip
 * @param int endIndex represents the end point in the LED strip
 */
//startIndex must be after endIndex
//startIndex is exclusiv e (set to 150 for all lights)
void singleColorRunBackwards(CRGB foreground, CRGB background,
  int delaySpeed, int startIndex, int endIndex) {
    setColor(background);
    for(int i = startIndex - 1; i >= endIndex; i--) {
      led[i] = foreground;
      led[i + 1] = background;
      FastLED.show();
      delay(delaySpeed);
    }
  }

/**
 * Makes a single bar of light of given color run across a background of
 * given color. Can specify a starting point and ending point, as well
 * as a speed. Can also specify a thickness for the running bar of light
 * @param CRGB foreground represents the color of the running light
 * @param CRGB background represents the color of the background lights
 * @param int delaySpeed represents the delay time in ms
 * @param int startIndex represents the starting point in the LED strip
 * @param int endIndex represents the end point in the LED strip
 * @param int thickness represents the thickness of the running bar
 */
//endIndex is exclusive (set to 150 for all lights)
void singleColorRun(CRGB foreground, CRGB background,
  int delaySpeed, int startIndex, int endIndex,
  int thickness) {
  setColor(background);
  for(int i = startIndex; i < endIndex; i++) {
    if(i == startIndex) {
      led[endIndex - 1] = background;
    }
    for(int j = 0; j < thickness; j++) {
      if(i + j < endIndex) {
        led[i + j] = foreground;
      }
      led[i - 1] = background;
    }
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Makes lights of given color appear one by one at given speed
 * @param int maxLights represents the max number of lights at
 *  the end of the function
 * @param int delaySpeed represents the speed of the lights
 * @param CRGB color represents the color of the light
 */
void pop(int maxLights, int delaySpeed, CRGB color) {
  off();
  int count = 0;
  while(count < maxLights) {
    int randomNum = random(0, NUM_LEDS);
    while(!isOff(led[randomNum])) {
      randomNum = (randomNum + 1) % NUM_LEDS;
    }
    led[randomNum] = color;
    FastLED.show();
    count++;
    delay(delaySpeed);
  }
}

/**
 * Makes lights of given color appear one by one at given speed
 * and also overwrite a previous board
 * @param int maxLights represents the max number of lights at
 *  the end of the function
 * @param int delaySpeed represents the speed of the lights
 * @param CRGB color represents the color of the light
 */
 //be careful with this: don't use values that are too bright
 //might put too much voltage through some LEDs
void popOverwrite(int maxLights, int delaySpeed, CRGB color) {
  int count = 0;
  while(count < maxLights) {
    int randomNum = random(0, NUM_LEDS);
    while(led[randomNum] == color) {
      randomNum = (randomNum + 1) % NUM_LEDS;
    }
    led[randomNum] = color;
    FastLED.show();
    count++;
    delay(delaySpeed);
  }
}

/**
 * Makes lights of random colors appear one by one at given speed
 * @param int maxLights represents the max number of lights at
 *  the end of the function
 * @param int delaySpeed represents the speed of the lights
 */
void popRandom(int maxLights, int delaySpeed) {
  off();
  int count = 0;
  while(count < maxLights) {
    CRGB color = randomColor();
    int randomNum = random(0, NUM_LEDS);
    while(!isOff(led[randomNum])) {
      randomNum = (randomNum + 1) % NUM_LEDS;
    }
    led[randomNum] = color;
    FastLED.show();
    count++;
    delay(delaySpeed);
  }
}

/**
 * Randomly makes lights disappear up to a given number
 * @param int num represents the number of lights to go off
 * @param int delaySpeed represents the speed of the lights
 */
//int n cannot be greater than 150
void unpop(int num, int delaySpeed) {
  int count = 0;
  while(count < num) {
    int randomNum = random(0, NUM_LEDS);
    while(isOff(led[randomNum])) {
      randomNum = (randomNum + 1) % NUM_LEDS;
    }
    led[randomNum] = CRGB(0, 0, 0);
    FastLED.show();
    count++;
    delay(delaySpeed);
  }
}

/**
 * Random colored lights appear, then disappear
 * @param int num represents total number of lights to appear
 * @param int delaySpeed represents the speed of the lights
 */
//150 and 20 are good settings
void randomAppearDisappear(int num, int delaySpeed) {
  popRandom(num, delaySpeed);
  unpop(num, delaySpeed);
}

/**
 * Adds lights from the beginning consecutively, one-by-one
 * @param CRGB color represents the single color of the lights
 * @param int skip represents the number of lights to step
 * @param int delaySpeed represents the speed of the lights
 */
 //set skip to 1 for consecutive
void wave(CRGB color, int skip, int delaySpeed) {
  for(int i = 0; i < NUM_LEDS; i += skip) {
    led[i] = color;
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Adds random-colored lights from the beginning consecutively
 * @param int skip represents the number of lights to step
 * @param int delaySpeed represents the speed of the lights
 */
void waveRandom(int skip, int delaySpeed) {
  for(int i = 0; i < NUM_LEDS; i += skip) {
    led[i] = randomColor();
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Light moves in the same way one would for suicides (the exercise)
 * @param CRGB color represents the color of the light
 * @param int distance represents the length to increase each suicide by
 * @param int delaySpeed represents the speed of the light
 */
 //try to use distances that divide 150 evenly
void suicides(CRGB color, int distance, int delaySpeed) {
  for(int i = 0; i < NUM_LEDS / distance; i++) {
    singleColorRun(color, CRGB(0,0,0), delaySpeed, 0, (i * distance) + distance);
    singleColorRunBackwards(color, CRGB(0,0,0), delaySpeed, (i * distance) + distance, 0);
  }
}

