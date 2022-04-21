//define LED port 
int Led = LED_BUILTIN; 

//define shock port 
int Shock = 2;

//define digital variable val 
int val;

void setup() 
{ 
  //define LED as a output port 
  pinMode(Led, OUTPUT); 
  //define shock sensor as a output port 
  pinMode(Shock, INPUT);
}

void loop() 
{ 
  //read the value of the digital interface 2 assigned to val 
  val = digitalRead(Shock); 

  //when the shock sensor have signal, LED blink 
  if (val == HIGH) 
  { 
    digitalWrite(Led, LOW); 
  } 
  else 
  { 
    digitalWrite(Led, HIGH); 
  } 
}
