// C++ code

#include <Servo.h>

Servo servoMoto10, servoMoto11, servoMoto12;
int latchPin =2;//ST_CP
int clockPin=3;//SH_CP
int dataPin =4;//ds
int buzzer = 13;
int score =0;
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 2;
task tasks[tasksNum];
enum Target_States {Start_wait, Play, T1_up, T2_up, T3_up, T1_down, T2_down, T3_down, Reset, End } Target_state;

int Tick1(int state) {
  int target;
  int photoc1;
  int photoc2;
  int photoc3;
  int max = 450;
  digitalRead(A2);
  Serial.println("A2222222222222222"); Serial.println(digitalRead(A2));
  switch (Target_state) {
    case Start_wait:
      if (digitalRead(A5))
      {
        Target_state = Play;
      }
      else {
        Target_state = Start_wait;
      }

      break;
    case Play:
        
      if (digitalRead(A4))
      {
        Target_state = Reset;
      } 
      if (digitalRead(A2) && !digitalRead(A4)) {
        Serial.println("End"); Serial.println(digitalRead(A2));
        Target_state = End;
      }
       else if ( !digitalRead(A2) && !digitalRead(A4))
      {
        target = random(1, 4);
        Serial.println("target"); Serial.println(target);

        if (target == 1)
        {
          Target_state = T1_up;
        } else if (target == 2)
        {
          Target_state = T2_up;
        } else if (target == 3)
        {
          Target_state = T3_up;
        }
      }
      break;
    case T1_up:
    photoc1 = analogRead(A0);
    Serial.println("A0"); Serial.println(photoc1);
        Target_state = Play;
      if (digitalRead(A4))
      {
        Serial.println("reset"); Serial.println(digitalRead(A4));
        Target_state = Reset;
      }else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }
      else if(photoc1 <max && !digitalRead(A4))
      {

        Target_state = T1_down;
      } else {
        Target_state = T1_up;
      }

      break;
    case T2_up:
      photoc2 = analogRead(A1);
      Serial.println("A1"); Serial.println(photoc2);
      if (digitalRead(A4))
      {
        Serial.println("reset"); Serial.println(digitalRead(A4));
        Target_state = Reset;
      }
      else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }
      else if (photoc2 < max && !digitalRead(A4))
      {

        Target_state = T2_down;
      } else  {
        Target_state = T2_up;
      }
      break;
    case T3_up:
      photoc3 = analogRead(A3);
      Serial.println("A3"); Serial.println(photoc3);
      if (digitalRead(A4))
      {
        Serial.println("reset"); Serial.println(digitalRead(A4));
        Target_state = Reset;
      }
      else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }
      else if (photoc3 < max && !digitalRead(A4))
      {

        Target_state = T3_down;
      } else {
        Target_state = T3_up;
      }
      break;
    case T1_down:

      if (digitalRead(A4))
      {
        Target_state = Reset;
      } 
      else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }
       else {
        Target_state = Play;
      }
      break;
    case T2_down:
      if (digitalRead(A4))
      {
        
        Target_state = Reset;
      } else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }else {
        Target_state = Play;
      }
      break;
    case T3_down:

      if (digitalRead(A4))
      {
        Target_state = Reset;
      } else if(digitalRead(A2)&& !digitalRead(A4))
      {
        Target_state = End;
       }
       else {
        Target_state = Play;
      }
      break;
    case Reset:
      Target_state = Start_wait;
      break;
    case End:
      if (digitalRead(A4))
      {
        Target_state = Reset;
      } else {
        Target_state = End;
      }
      break;
    default:
      break;
  }
  //state actions
  switch (Target_state) {
    case Start_wait:
      target = 0;
      score = 0;
      servoMoto12.write(0);
      servoMoto11.write(0);
      servoMoto10.write(0);

      break;
    case Play:
      break;
    case T1_up:
      servoMoto10.write(90);
      delay(10);
      break;
    case T2_up:
      servoMoto11.write(90);
      delay(100);
      break;
    case T3_up:
       
      servoMoto12.write(90);
      delay(10);
      break;
    case T1_down:

      servoMoto10.write(0);
      score++;
      Serial.println("score"); Serial.println(score);
      break;
    case T2_down:

      servoMoto11.write(0);
      score++;
      Serial.println("score"); Serial.println(score);
      break;
    case T3_down:

      servoMoto12.write(0);
      score++;
      Serial.println("score"); Serial.println(score);
      break;
    case Reset:
      score = 0;
      target = 0;
      servoMoto12.write(0);
      servoMoto11.write(0);
      servoMoto10.write(0);
      Serial.println("score"); Serial.println(score);
      Serial.println("target"); Serial.println(target);
      break;
    case End:
    if(score>3){
    tone(buzzer,262);
    delay(100);
    noTone(buzzer);
    tone(buzzer,294);
    delay(100);
    noTone(buzzer);
    tone(buzzer,330);
    delay(100);
    tone(buzzer,349);
    delay(200);
    noTone(buzzer);
    tone(buzzer,294);
    delay(100);
    noTone(buzzer);
    tone(buzzer,349);
    delay(100);
    noTone(buzzer);
    tone(buzzer,330);
    delay(100);
    noTone(buzzer);
    tone(buzzer,349);
    delay(100);
    tone(buzzer,392);
    delay(200);
    noTone(buzzer);
    tone(buzzer,330);
    delay(200);
    noTone(buzzer);
    }else if(score<=3){    
      
    tone(buzzer,262);
    delay(100);
    tone(buzzer,262);
    delay(100);
    noTone(buzzer);
    }
      break;
    default:
      break;
  }
  return state;
}
enum Score_States {Score_Start, Display } Score_state;
int  Tick2(int state) {

  switch (Score_state) {
    case Score_Start:
      if (digitalRead(A5))
      {
        Score_state = Display;
      } else {
        Score_state = Score_Start;
      }
      break;
    case Display:
      if (digitalRead(A4))
      {
        Score_state = Score_Start;
      } else {
        Score_state = Display;
      }

      break;
  }
  switch (Score_state) {
    case Score_Start:
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      digitalWrite(latchPin, HIGH);
      break;
    case Display:
      if (score == 0)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin,MSBFIRST, 63);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 1)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 6);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 2)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 91);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 3)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST,79);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 4)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST,102);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 5)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 109);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 6)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 125);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 7)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 7);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 8)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 127);
      digitalWrite(latchPin, HIGH);
      }
      else if (score == 9)
      { 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 103);
      digitalWrite(latchPin, HIGH);
      }
      break;

    default:
      break;
  }
  return state;
}
void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  pinMode(buzzer, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT);

  servoMoto12.attach(12);
  servoMoto11.attach(11);
  servoMoto10.attach(10);

  unsigned char i = 0;
  tasks[i].state = Start_wait;
  tasks[i].period = 150;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Tick1;
  i++;
  tasks[i].state = Score_Start;
  tasks[i].period = 150;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Tick2;
  
}
void loop()
{
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran

    }
  }
}
