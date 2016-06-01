// This #include statement was automatically added by the Particle IDE.

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
int led = D7;    // Onboard LED is D7
int inputPin1 = D3; 



void setup()
{

Spark.function("servo", updateServo);
//Set pin D0 to be an output
pinMode(D0, OUTPUT);
//Attach the servo to D0
myservo.attach(D0);
//Set inputPin1 to pullup to detect when the button is pressed to create a circuit
pinMode(inputPin1, INPUT_PULLUP);
//Take control over the LED on the board
RGB.control(true);
//Turn off the LED - we dont want it flashing behind the photo frame at night
//There may be a better way to do this like turning it off, I found it just as easy to set the colour to nothing
RGB.color(0, 0, 0);

pinMode(led, OUTPUT); // Initialize D7 pin as output


}
 
void loop()
{

int inputPin1State;

    inputPin1State = digitalRead(inputPin1);

//first button checking state
  if(inputPin1State == LOW){      // Check State of the PIN (i.e. if the button has been pressed)
    digitalWrite(led, HIGH);   // Turn ON the LED
    Particle.publish("trigger","1");  //Send a message to IFTTT saying 'trigger' '1' has been activated
    delay(1000); // Wait 1 second so only one message is sent to IFTTT (as the loop function will run many times per second - we might not have let go of the button quickly enough in that time)
  }
  else
  {
    digitalWrite(led, LOW);  // Turn the LED off
  }

}
 
//This function is triggered by IFTTT - the 'command' word represents the object used to store the 'position' we send to the function.
//The 'position' we send represents where we want the servo to move to
int updateServo(String command)
{
//Convert string to integer, the code after this requires the 'command' object to be in a number format. IFTTT however passes the object as a 'string' even if it is a 'number'.
uint8_t pos = command.toInt();
//This tells the servo, attached to D0 to move to the position defined in the 'command' object that was passed when we triggered this function from IFTTT
myservo.write(pos);
//Flash the LED on so we can see that a message has been recieved - just because we can
RGB.color(0, 0, 255);
//Remember to add the delay for 2 seconds, otherwise the LED will just flash for a period of time too small for us to see
delay(2000);
//Now set the LED back to off
RGB.color(0, 0, 0);
//We return something to signify the end of the function - doesn't really matter what it is

return 0;
 

  }
