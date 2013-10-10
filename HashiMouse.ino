#define XYZDATASIZE 5

short xdatas[XYZDATASIZE], ydatas[XYZDATASIZE], zdatas[XYZDATASIZE], hdatas[XYZDATASIZE];


byte lead = 11;
byte button = 12;

short xGmin = 174;
short xGmax = 486;
short yGmin = 226;
short yGmax = 513;
short zGmin = 135;
short zGmax = 449;

float xMovin = 0;
float yMovin = 0;

/*
// for Mouse
short xSpeedDefault = 30;
short xSpeed = xSpeedDefault;
short xSpeedOffset = 8;
short ySpeedDefault = 40;
short ySpeed = ySpeedDefault;
short ySpeedOffset = 8;
*/

// for Box Demo
short xSpeedDefault = 20;
short xSpeed = xSpeedDefault;
short xSpeedOffset = 0;
short ySpeedDefault = 30;
short ySpeed = ySpeedDefault;
short ySpeedOffset = 0;

short xDirection = 0;
short yDirection = 0;
short speedLimit = 100;

boolean clicking = false;

float Map(int iIn, int iIn1, int iIn2, float dOut1, float dOut2, boolean bConstrain = false) {
  float dValue = (iIn - iIn1) * (dOut2 - dOut1) / (iIn2 - iIn1) + dOut1;
  if( bConstrain ) {
    float dOutMin, dOutMax;
    if( dOut1 < dOut2 ) {
      dOutMin= dOut1;
      dOutMax= dOut2;
    } else {
      dOutMin= dOut2;
      dOutMax= dOut1;
    }
    if( dOutMin > dValue ) {
      return dOutMin;
    }
    if( dOutMax < dValue ) {
      return dOutMax;
    }
  }
  return dValue;
}

void setup() {
  // Initialize the serial port.
  //Serial.begin(9600);

  pinMode(lead, INPUT);
  pinMode(button, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(lead, HIGH);
  digitalWrite(button, HIGH);
  
  Mouse.begin();
}

void loop() {
  setNewData(analogRead(0), xdatas);
  setNewData(analogRead(1), ydatas);
  setNewData(analogRead(2), zdatas);
  
  float dSinX = Map(getMedianData(xdatas), xGmin, xGmax, -1.0, 1.0, true);
  float dSinY = Map(getMedianData(ydatas), yGmin, yGmax, -1.0, 1.0, true);
  float dSinZ = Map(getMedianData(zdatas), zGmin, zGmax, -1.0, 1.0, true);

  float dAngleX = asin(dSinX) * 180.0 / M_PI;
  float dAngleY = asin(dSinY) * 180.0 / M_PI;
  float dAngleZ = asin(dSinZ) * 180.0 / M_PI;
/*
  Serial.print("X:\t");
  Serial.print(getMedianData(xdatas));
  Serial.print(" : ");
  Serial.print(map(getMedianData(xdatas), 305, 796, 0, 180));
  Serial.print(" : ");
  Serial.print(-dSinX);
  Serial.print(" : ");
  Serial.print(-dAngleX);
  Serial.print("\tY:\t");
  Serial.print(getMedianData(ydatas));
  Serial.print(" : ");
  Serial.print(map(getMedianData(ydatas), 356, 802, 0, 180));
  Serial.print(" : ");
  Serial.print(-dSinY);
  Serial.print(" : ");
  Serial.print(-dAngleY);
  Serial.print("\tZ:\t");
  Serial.print(getMedianData(zdatas));
  Serial.print(" : ");
  Serial.print(map(getMedianData(zdatas), 219, 711, 0, 180));
  Serial.print(" : ");
  Serial.print(-dSinZ);
  Serial.print(" : ");
  Serial.println(-dAngleZ);
*/
//    yMovin = dSinX < 0 ? pow(dSinX * 10, 2) : -1 * pow(dSinX * 10, 2);
//    xMovin = dSinY < 0 ? -1 * pow(dSinY * 10, 2) : pow(dSinY * 10, 2);
    //xMovin = xOrigin - getMedianData(hdatas);
    //xMovin *= -1;
  yMovin = -dSinX * ySpeed;
  xMovin = dSinY * xSpeed;    

  digitalWrite(13, digitalRead(lead));
 
  if (xMovin < 0) {
    if (xDirection < 0) {
      if (xSpeed < speedLimit) xSpeed += abs(dSinY) * xSpeedOffset;
    } else {
      xSpeed = xSpeedDefault;
    }
    xDirection = -1;
  } else if (xMovin > 0) {
    if (xDirection > 0) {
      if (xSpeed < speedLimit) xSpeed += abs(dSinY) * xSpeedOffset;
    } else {
      xSpeed = xSpeedDefault;
    }
    xDirection = 1;
  } else {
    xDirection = 0;
  }
  
  if (yMovin < 0) {
    if (yDirection < 0) {
     if (ySpeed < speedLimit) ySpeed += abs(dSinX) * ySpeedOffset;
    } else {
      ySpeed = ySpeedDefault;
    }
    yDirection = -1;
  } else if (yMovin > 0) {
    if (yDirection > 0) {
      if (ySpeed < speedLimit) ySpeed += abs(dSinX) * ySpeedOffset;
    } else {
      ySpeed = ySpeedDefault;
    }
    yDirection = 1;
  } else {
    yDirection = 0;
  }
/*
Serial.print("xMovin : ");
Serial.print(xMovin);
Serial.print("\txSpeed : ");
Serial.print(xSpeed);
Serial.print("\txDirection : ");
Serial.print(xDirection);
Serial.print("\tyMovin : ");
Serial.print(yMovin);
Serial.print("\tySpeed : ");
Serial.print(ySpeed);
Serial.print("\tyDirection : ");
Serial.print(yDirection);
Serial.println();
*/  
  if (!digitalRead(lead) || clicking) {
    if (clicking && digitalRead(lead)) {
      Mouse.release();
      //Serial.println(" ******* Mouse Release !! ****** ");
      clicking = false;
    } else {
      clicking = true;
      Mouse.press();
      //Serial.println(" ******* Mouse Press !! ****** ");
    }
  }
/*  
Serial.print("lead : ");
Serial.print(digitalRead(lead));
Serial.print("\tbutton :");
Serial.println(digitalRead(button));
*/
  Mouse.move(xMovin, yMovin, 0);
/*
Serial.print("heading median : ");
Serial.println(getMedianData(hdatas));

Serial.print("xMovin : ");
Serial.print(xMovin);
Serial.print("\txOrigin : ");
Serial.print(xOrigin);
Serial.print("\tyMovin :");
Serial.println(yMovin);
*/

  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
  delay(50);
  //delay(500);
}

void setNewData(short newData, short* datas) {
  for (byte i = XYZDATASIZE - 1; i > 0; i--) {
    *(datas + i) = *(datas + (i - 1));
  }
  *datas = newData;
}

short getAverageData(short* average) {
  short sum = 0;
  for (short i = 0; i < XYZDATASIZE; i++) {
    sum += *(average + i);
  }
  return sum / XYZDATASIZE;
}

short getMedianData(short* datas) {
  static short sortBuffer[XYZDATASIZE];
   
  for (byte i = 0; i < XYZDATASIZE; i++) {
    sortBuffer[i] = *(datas + i);
  }
  
  qsort(sortBuffer, XYZDATASIZE, sizeof(short), compareFunc);
  
  return sortBuffer[(int)XYZDATASIZE / 2];
}

int compareFunc(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

