# Arduino Guitar Hero
For converting a Wii Wireless Guitar Hero 3 Controller into a wired one for PC.

## Why is this needed?
Guitar Hero for PC, especially through games such as [Clone Hero](http://clonehero.net/), has allowed the rhythm game to be touched by a large community of talented and devoted song charters. Growing up, I played a lot of Guitar Hero 3 for the Wii and still had the old wireless controller. So, wanting to play some Clone Hero, I bought a $20 dollar classic controller to USB (The Classic Controller is the port on the bottom of Wii Remotes) off of [Amazon](https://www.amazon.com/Mayflash-Wii-Classic-Controller-Adapter/dp/B07BN49ZFR). It didn't work for guitars, and looking into how the guitar worked it seemed as if it was solely on the blame of the adapter maker not wanting to deal with the data conversion. So, I did it myself using an Arduino Uno.

### Words of Warning
- This tutorial has no support for **Guitar Hero World Tour Wii Guitars**, only Guitar Hero 3 Wii Guitars.
- Make sure you are willing to part with the guitar for usage on the Wii, as this tutorial doesn't include keeping it usable for Wii Guitar Hero play.
- All photos of this project were taken after the project was completed. As such, some cuts into the plastic are visible that would not be there on your guitar.
- This will "void the guitars warranty", however, I believe at the time of writing this [those statements are illegal now?](https://www.npr.org/sections/thetwo-way/2018/04/11/601582169/warranty-void-if-removed-as-it-turns-out-feds-say-those-warnings-are-illegal)

## Equipment
- GH3 Wii Controller
- Wire Strippers
- Screwdriver with a PH0 bit and a T9 bit
- USB Type B Cable (The ones used to compile to an Arduino)
- Arduino Uno R3
- Soldering Equipment
- Some Male pin breadboard connectors or solid core 22 gauge wire
- Tools to cut and remove the plastic (A Dremel could work very well for this, but I just used gardening shears and pliers)

# Part 1: The Guitar Breakdown

#### Disassemble
First, use your T9 bit and take out the 9 screws in the back of the guitar (Including the one under the void warranty sticker).
![step1](https://i.imgur.com/vW0tMFV.jpg)

Next, take the neck of the guitar off using the latch and flip the guitar over. You should be able to pry up the plastic top piece beginning at the part that is overhanging where the guitar neck was. Under this plate, you should find 4 more screws at the top. Take those out using your PH0 bit.
![step2](https://i.imgur.com/6obJDri.jpg)

With all screws out, the guitar's two plastic pieces should easily come apart, revealing this on the top piece.
![step3](https://i.imgur.com/aVzCmqz.jpg)

The centerboard as you can see is what is connected to the white cable that is connected to the classic controller head. Taking a look closer at the connections to the classic controller cable you'll find the cable is separated into different colors.
![step4](https://i.imgur.com/R4gHC8w.jpg)

Here's reference for what each of those actually correlates to:
- Red: VCC (3.3V)
- Yellow: SCL (System Clock for Data Communication)
- Green: SDA (Data Line for Communication)
- White: GND
- Black: I discussed this wire and findings with a few more electrically inclined friends, and we concluded that it is some sort of antenna to minimize interference to the fragile system clock. However, for our purposes, this wire will go unused.

#### Prep Wires for the Arduino
Now that all the wires are figured out, we can move onto separating them for use on the Arduino. Take off the bundled cable cover and clean up the shield and insulation. There will be an uninsulated wire in the bundle, that is connected to the black wire. Strip each of the individually insulated wires and solder them to some male breadboard jumpers or solid core 22 gauge wire. These are just to aid in securing the wires into the Arduino. If you are concerned about inference and want the black cable to be utilized, solder it to a male breadboard pinhead (Inside the classic controller head, it was originally just connected to a metal mass).

#### Connection time
Finally, it is time to insert them into the Arduino.
- Red should be connected to the 3.3V
- White should be connected to any of the GNDs
- Green should be connected to A4
- Yellow should be connected to A5

Why the green and yellow positions? Those are the defined I2C pins for the Uno board. This is a good reference for other [boards.](https://www.arduino.cc/en/Reference/Wire)

Here is a photo reference of what it should look like.
![step5](https://i.imgur.com/i2WcJ2i.jpg)

#### Fitting the Arduino
Now unless you want the Arduino hanging out the front of the guitar (which for the first day of testing was how I had it), you will want to secure it inside the guitar. I found that the Wii remote compartment is very convenient for this, as it can fit the Uno board well and allows for easy access in the event of needing to reprogram. Measure how much space you'll need (USB B inserted) and get to work testing and removing material. I was able to get mine looking so:
![step6](https://i.imgur.com/UPS6upZ.jpg)

#### Reassemble
Once you're happy with the Arduino fit and position, it's time to figure out putting the other piece back on for reassembly. This ended up being trial and error for me, as I began having to cut away at the other piece in order to better fit the USB cable. Work at it until the Arduino looks well positioned and the USB cable is not overly strained at the connection to the board. Make a cut into the removable remote place in order to allow for your USB cable to come out.
![step7](https://i.imgur.com/SAKjnhH.jpg)
Finally, reassemble the guitar fully using the screws. Place the plastic front plate back on and then put the guitar neck back on. You should have a fully reassembled guitar!

# Part 2: Code
Don't get too excited, the next part is even more important!
1. Download ArduinoGuitarHero: https://github.com/ChristopherJMiller/ArduinoGuitarHero/archive/master.zip
2. Unzip the downloaded file.
3. (In the Arduino IDE) Sketch > Include Library > Add .ZIP Library > select the `libraries/ArduinoGuitarHero` subfolder of the unzipped file > Open
4. Repeat the process with the [UnoJoy library](https://github.com/AlanChatham/UnoJoy), which is the software that is going to allow us to turn the Uno into what you would usually use an [Arduino Leonardo](https://store.arduino.cc/usa/arduino-leonardo-with-headers) for, interfacing seamlessly as a device.
5. File > Examples > ArduinoGuitarHero > ArduinoGuitarHero
6. The current setup is basic bindings to a game controller for use in Clone Hero, but you may modify it as needed. When ready, connect the Arduino to your computer via the Type B USB and upload the sketch.

#### Optional but recommended: Fixing the I2C Clock Speed
The Wire library for Arduino actually runs at a lower clockrate than what is reccommended for the I2C clock speed (10kHz vs. 40kHz). This can be fixed by modifiying `twi.h` in `\Program Files\Arduino\hardware\arduino\avr\libraries\Wire\src\utility`. Change the define of TWI_FREQ from `100000L` to `400000L`. Save your change and open up the `ArduinoGuitarHero.ino` sketch. Generally, Arduino IDE and avrdude will compile the libraries only once to save time, which means compiling now will still use the slow version of `twi.h`. To remedy this, change your target Arduino device to a random other device and click Verify to compile but not attempt uploading. This will cause the IDE to rebuild the libraries. Then, swap back to Arduino Uno as your target platform and Verify again, which will again rebuild the libraries now for the Uno.

#### DFU Mode and UnoJoy
With code uploaded to the Arduino, it's time to convert it to a joystick. The [UnoJoy README](https://github.com/AlanChatham/UnoJoy) is a really good resource for this step. Follow the Drivers step to get yourself set up. The next we will be doing is Hardware, however, I found part of their description confusing so here is what I found worked stepwise with my Arduino. The Hardware step is to enter your Arduino into DFU mode, which will allow you to reprogram the communication chips on the Arduino. To enter your Arduino into DFU mode, use some wire or a breadboard connecter to (while still plugged into your computer) short the two connectors that are boxed in.
![step8](https://i.imgur.com/erqv4xd.jpg)
You should hear the Arduino disconnect and reconnect to your computer if on Windows. According to the UnoJoy steps the device should appear as Arduino UNO DFU, however, mine would instead just disappear from its normal section of the windows device manager. Now, follow the "Once you are in DFU Mode" steps on the UnoJoy README, which will update the firmware. Once updated, unplug and plug in the Arduino and it should appear to your system as "UnoJoy Joystick".

#### Need to modify the code?
If you need to modify the code after reflashing the Arduino into a joystick, while the Arduino is powered reenter it into DFU mode and run the `TurnIntoAnArduino` executables that are included alongside the previously used TurnIntoAJoystick. Once reflashed unplug and plug in the Arduino as usual and modify your code per normal.

# Part 3: Play

#### Calibrate
Verify that all the functions on your guitar appear in Windows correctly (Neck Buttons, Strumming, etc). However, you may notice that the analog joystick on the guitar may be acting poorly. To fix this, calibrate the controller within windows, following the laid out steps. A few of their steps such as Z rotation are not applicable, but you should be able to skip past them with ease.

#### Play!
Boot up your game of choice, bind their functions to the keys, and enjoy!

## Credits and References
- Huge thanks to WiiBrew for their wonderful information on [Guitar Hero Wii Guitars](http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Guitar_Hero_(Wii)_Guitars)
- Thanks to [ConnorJC](https://github.com/ConnorJC3) for the aid on figuring out the wire correlations.
- Credit to Gabriel Bianconi's [ArduinoNunchuck library](https://github.com/GabrielBianconi/arduino-nunchuk), which was a basis for the ArduinoGuitarHero library.
- Thanks to [Acai](https://www.twitch.tv/acai) for making me want to play Clone Hero so bad I did this.
