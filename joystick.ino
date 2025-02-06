char lastDirection = ' '; 

void setup() {
  pinMode(A0, INPUT); // VY of JoyStick
  pinMode(A1, INPUT); // VY of JoyStick
  Serial.begin(9600);
}

void loop() {
  int VX = analogRead(A0); // Taking Value from VX
  int VY = analogRead(A1); // Taking Value from VY
  char direction = ' '; // Default: no direction change

  if (VX > 600) {
    direction = 'W'; // UP
  } else if (VX < 400) {
    direction = 'S'; // DOWN
  } else if (VY > 600) {
    direction = 'D'; // RIGHT
  } else if (VY < 400) {
    direction = 'A'; // LEFT
  }

  // Print only if the direction changes
  if (direction != ' ' && direction != lastDirection) {
    Serial.println(direction);
    lastDirection = direction; // Update last direction
  }
}

