//LED strip reads GRB (green, red, blue)

#include <FastLED.h>
#include <pixeltypes.h>

#define NUM_LEDS 150
//which pin the data pin is inserted into
#define LED_PIN 3
#define MAX_VAL 255
#define NUM_COLORS 3
#define LOW_MID 74
#define HIGH_MID 75

CRGB led[NUM_LEDS];
CRGB backup[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_PIN>(led, NUM_LEDS);
  //insert static setup code below
}

void loop() {
  int selection = random(0, 13);
  demo(selection);
}

/**
 * Sets the entire strip to given color and shows it
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
 * Generates a random color with values between 0-255
 * @return CRGB random color
 */
CRGB randomColor() {
  return CRGB(random(MAX_VAL + 1), random(MAX_VAL + 1), random(MAX_VAL + 1));
}

/**
 * Generates a random color with values between given floor and ceiling
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
 * Saves the current board into the backup board
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

/**
 * Loads a saved board to the current board
 * @param int startIndex represents the start of the range to load
 * @param int endIndex represents the end of the range to load
 */
void loadBoard(int startIndex, int endIndex) {
  for(int i = startIndex; i < endIndex + 1; i++) {
    led[i] = backup[i];
  }
  FastLED.show();
} 

/**
 * Switches between red, green, and blue. Fades in and out
 * @param int delaySpeed represents the amount of time in ms
 *        to delay the fade (10 is a good setting)
 */
void fadeRGB(int delaySpeed) {
  for(int i = 0; i < MAX_VAL + 1; i++) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(0, 0, i);
    }
    FastLED.show();
    delay(delaySpeed);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(0, 0, i);
    }
    FastLED.show();
    delay(delaySpeed);
  }
  for(int i = 0; i < MAX_VAL + 1; i++) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(0, i, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(0, i, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
  for(int i = 0; i < MAX_VAL + 1; i++) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(i, 0, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
  for(int i = MAX_VAL; i > 0; i--) {
    for(int j = 0; j < NUM_LEDS; j++) {
      led[j] = CRGB(i, 0, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Gradually changes colors by adding or subtracting a random value between
 * R, G, or B
 * @param int iterations represents the number of iterations to
 *        go through before ending, set it to a high number like
 *        10000
 * @param int timeDelay represents the time in ms to delay each iteration
 */
//set delay to 0 for a dynamic color set
//set delay to 10 for a slower change
//still something wrong as colors should not be jumping (should have a gradual change)
void fadeRandomColors(int iterations, int delaySpeed) {
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
  int count = 0;
  while(count < iterations) {
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
    delay(delaySpeed);
    count++;
  }
}

/**
 * Sets the entire strip to a random color with given floors
 * and ceilings for the R, G, and B values
 * @param int changeSpeed represents the timed delay in ms
 */
void setRandomColor(int delaySpeed) {
  int red = random(0, MAX_VAL + 1);
  int green = random(0, MAX_VAL + 1);
  int blue = random(0, MAX_VAL + 1);
  setColor(red, green, blue);
  delay(delaySpeed);
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
void setRandomColor(int floor1, int ceiling, int delaySpeed) {
  int red = random(floor1, ceiling);
  int green = random(floor1, ceiling);
  int blue = random(floor1, ceiling);
  setColor(red, green, blue);
  delay(delaySpeed);
}

/**
 * Sets each individual LED light to a random color within a given range
 * @param int changeSpeed represents the delay in ms
 * @param int floor1 represents the minimum value (inclusive) for R, G, and B
 * @param int ceiling represents the maximum value (exclusive) for R, G, and B
 */
//0 and 256 for all colors
void allRandomColors(int floor1, int ceiling, int delaySpeed) {
  for(int i = 0; i < NUM_LEDS; i++) {
    led[i] = randomColor(floor1, ceiling);
  }
  FastLED.show();
  delay(delaySpeed);
}

/**
 * Shuts off the entire strip for given time in ms
 * @param int changeSpeed represents delay in ms
 */
//color has already been set and shown
void blink(int delaySpeed) {
  //blinks it off
  off();
  delay(delaySpeed);
}

/**
 * Shuts off the entire strip for given time in ms
 * Also sets the strip to a specified color
 * @param int color represents hex value of color
 * @param int changeSpeed represents delay in ms
 */
void blink(int color, int delaySpeed) {
 setColor(color);
 delay(delaySpeed);
 off();
 delay(delaySpeed);
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
    allRandomColors(0, MAX_VAL + 1, i);
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
    allRandomColors(0, MAX_VAL + 1, i);
    blink(i);
  }
}

/**
 * Makes an alternating pattern of 3 given colors with a given thickness
 * @param int thickness represents the thickness of each bar
 * @param CRGB colors represents the 3 colors
 */
//makes a pattern of 3 colors with specified thickness
void alternating3Colors(int thickness, CRGB color1,
  CRGB color2, CRGB color3) {
  CRGB colors[NUM_COLORS];
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
        break;
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
  CRGB colors[NUM_COLORS];
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
  int startIndex, int endIndex, int delaySpeed) {
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
//startIndex is exclusive (set to 150 for all lights)
void singleColorRunBackwards(CRGB foreground, CRGB background,
  int startIndex, int endIndex, int delaySpeed) {
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
  int startIndex, int endIndex, int thickness, int delaySpeed) {
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
 *        the end of the function
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
 *        the end of the function
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
 *        the end of the function
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
//int num cannot be greater than 150
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
    singleColorRun(color, CRGB(0,0,0), 0,
      (i * distance) + distance, delaySpeed);
    singleColorRunBackwards(color, CRGB(0,0,0),
      (i * distance) + distance, 0, delaySpeed);
  }
}

/**
 * Two lights start at the two midpoints and run towards the ends
 * @param CRGB color represents the color of the lights
 * @param boolean keepTip true if the ends will stay on at the
 *        end of the iterations, false if not
 * @param int delaySpeed represents the speed of the lights
 */
void splitOut(CRGB color, boolean keepTip, int delaySpeed) {
  for(int i = 0; i < HIGH_MID; i++) {
    if(!keepTip && i == 0) {
      led[0] = CRGB(0, 0, 0);
      led[NUM_LEDS - 1] = CRGB(0, 0, 0);
      FastLED.show();
    }
    led[LOW_MID - i] = color;
    led[HIGH_MID + i] = color;
    if(i != 0) {
      led[LOW_MID - i + 1] = CRGB(0, 0, 0);
      led[HIGH_MID + i - 1] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Two lights start at the ends and converge towards the middle
 * @param CRGB color represents the color of the lights
 * @param boolean keepTip true if the mids will stay on at the
 *        end of the iterations, false if not
 * @param int delaySpeed represents the speed of the lights
 */
void splitIn(CRGB color, boolean keepTip, int delaySpeed) {
  for(int i = 0; i < HIGH_MID; i++) {
    if(!keepTip && i == 0) {
      led[LOW_MID] = CRGB(0, 0, 0);
      led[HIGH_MID] = CRGB(0, 0, 0);
      FastLED.show();
    }
    led[i] = color;
    led[NUM_LEDS - i - 1] = color;
    if(i != 0) {
      led[i - 1] = CRGB(0, 0, 0);
      led[NUM_LEDS - i] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * A bar of light of given thickness starts in the middle and 
 * runs towards the ends
 * @param CRGB color represents the color of the lights
 * @param int thickness represents the thickness of the bar
 * @param int delaySpeed represents the speed of the lights
 */
void splitOutBar(CRGB color, int thickness, int delaySpeed) {
  for(int i = 0; i < thickness; i++) {
    led[LOW_MID - i] = color;
    led[HIGH_MID + i] = color;
  }
  FastLED.show();
  delay(delaySpeed);
  for(int i = 0; i < HIGH_MID - thickness; i++) {
    led[LOW_MID - i - thickness] = color;
    led[LOW_MID - i] = CRGB(0, 0, 0);
    led[HIGH_MID + i + thickness] = color;
    led[HIGH_MID + i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * A bar of light of given thickness starts at the ends and
 * converges towards the middle
 * @param CRGB color represents the color of the lights
 * @param int thickness represents the thickness of the bar
 * @param int delaySpeed represents the speed of the lights
 */
void splitInBar(CRGB color, int thickness, int delaySpeed) {
  for(int i = 0; i < thickness; i++) {
    led[i] = color;
    led[NUM_LEDS - i - 1] = color;
  }
  FastLED.show();
  delay(delaySpeed);
  for(int i = 0; i < HIGH_MID - thickness; i++) {
    led[i + thickness] = color;
    led[i] = CRGB(0, 0, 0);
    led[NUM_LEDS - i - 1 - thickness] = color;
    led[NUM_LEDS - i - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(delaySpeed);
  }
}

/**
 * Main demo function that demos a majority of the functions.
 * @param int choice represents an integer 0-12 inclusive that
 *        picks which function to perform
 */
void demo(int choice) {
  off();
  CRGB color = randomColor();

  //changes color with blinks 3-5 times per iteration
  if(choice == 0) {
    //runs 3-5 times
    int iterations = random(3, 6);
    int delaySpeed1 = random(2, 11);
    int delaySpeed2 = random(2, 11);
    for(int i = 0; i < iterations; i++) {
      color = randomColor();
      setColor(color);
      //delays by 0.2-1 seconds
      delay(delaySpeed1 * 100);
      off();
      delay(delaySpeed2 * 100);
    }
  }
  
  //changes strip to all random colors and blinks 3-5 times
  if(choice == 1) {
    //runs 3-5 times
    int iterations = random(3, 6);
    int delaySpeed1 = random(2, 11);
    int delaySpeed2 = random(2, 11);
    for(int i = 0; i < iterations; i++) {
      color = randomColor();
      allRandomColors(0, 256, delaySpeed1 * 100);
      //delays by 0.2-1 seconds
      off();
      delay(delaySpeed2 * 100);
    }
  }
  
  //fades between RGB
  if(choice == 2) {
    int delaySpeed = random(5, 11);
    fadeRGB(delaySpeed);
  }

  //makes random colored line segments
  if(choice == 3) {
    int iterations = random(10, 21);
    int delaySpeed = random(100, 750);
    off();
    for(int i = 0; i < iterations; i++) {
      int num1 = random(0, 120);
      int num2 = random(num1 + 1, 150);
      color = randomColor();
      setColor(color, num1, num2);
      delay(delaySpeed);
      off();
    }
  }

  //gradual blink increase and decrease with random colors
  if(choice == 4) {
    int startSpeed = random(100, 250);
    int endSpeed = random(500, 1000);
    int interval = random(10, 80);
    gradualBlinkIncrease(startSpeed, endSpeed, interval);
    gradualBlinkDecrease(startSpeed, endSpeed, interval);
  }

  //alternating bands of random colors with thickness
  if(choice == 5) {
    for(int i = 0; i < 5; i++) {
      int numColors = random(2, 5);
      int thickness = random(2, 30);
      alternatingNRandomColors(thickness, numColors);
      delay(3000);
    }
  }

  //meet in the middle function with thickness
  if(choice == 6) {
    //runs 5-10 times
    int iterations = random(5, 11);
    int thickness = random(10, 41);
    int delaySpeed = random(15, 50);
    for(int i = 0; i < iterations; i++) {
      color = randomColor();
      splitOutBar(color, thickness, 50);
      splitInBar(color, thickness, 50);
    }
  }

  //single light meet in the middle function
  if(choice == 7) {
    int iterations = random(5, 11);
    int delaySpeed = random(15, 50);
    for(int i = 0; i < iterations; i++) {
      color = randomColor();
      splitOut(color, false, delaySpeed);
      splitIn(color, false, delaySpeed);
    }
  }

  //single light split out or in
  if(choice == 8) {
    int iterations = random(4, 10);
    int secondChoice = random(0,2);
    int delaySpeed = random(15, 50);
    if(secondChoice == 0) {
      for(int i = 0; i < iterations; i++) {
        color = randomColor();
        splitOut(color, true, delaySpeed);
      }
    }
    else {
      for(int i = 0; i < iterations; i++) {
        color = randomColor();
        splitIn(color, true, delaySpeed);
      }
    }
  }

  //single color run with random thickness
  if(choice == 9) {
    //runs 5-10 times
    int iterations = random(5, 11);
    int delaySpeed = random(20, 51);
    for(int i = 0; i < iterations; i++) {
      CRGB color1 = randomColor();
      CRGB color2 = randomColor();
      int thickness = random(1, 51);
      singleColorRun(color1, color2, 0, 150, 
        thickness, delaySpeed);
    }
  }

  //multicolor pop and unpop
  if(choice == 10) {
    //runs 3-7 times
    int iterations = random(3, 8);
    for(int i = 0; i < iterations; i++) {
      off();
      int num = random(50, 151);
      int delaySpeed = random(5, 40);
      randomAppearDisappear(num, delaySpeed);
    }
  }

  //single color pop and unpop
  if(choice == 11) {
    int iterations = random(3, 8);
    for(int i = 0; i < iterations; i++) {
      color = randomColor();
      int num = random(50, 151);
      int delaySpeed = random(5, 40);
      pop(num, delaySpeed, color);
      unpop(num, delaySpeed);
    }
  }

  //wave skip-fill
  if(choice == 12) {
    //runs 5-10 times
    int iterations = random(5, 11);
    for(int i = 0; i < iterations; i++) {
      int bigDelay = random(10, 30);
      int delaySpeed1 = random(15, 30);
      int delaySpeed2 = random(31, 50);
      CRGB color1 = randomColor();
      int skip1 = random(1, 4);
      wave(color1, skip1, delaySpeed1);
      delay(bigDelay * 100);
      waveRandom(skip1, delaySpeed1);
      delay(bigDelay * 100);
      off();
      CRGB color2 = randomColor();
      int skip2 = random(5, 7);
      wave(color2, skip2, delaySpeed2);
      delay(bigDelay * 100);
      waveRandom(skip2, delaySpeed2);
      delay(bigDelay * 100);
      off();
    }
  }
}

