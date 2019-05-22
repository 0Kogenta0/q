#define MOTION_SENSOR A0
#define RELAY D4

int led = D7;

void myHandler(const char *event, const char *data);
int Controller(String command);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode( MOTION_SENSOR, INPUT );
  pinMode( led, OUTPUT );
  digitalWrite( led, LOW );
  Particle.subscribe("Relay", myHandler);
  Particle.function("get", Controller);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead( MOTION_SENSOR ) == HIGH) {
      
      Particle.publish("Controller",String(1), PRIVATE );
      //String take = String(1);
      //Particle.publish("Controller",String(2), PRIVATE);
      Serial.println("Active");
  }
  else {
    //String noMotion = String(0);
    Particle.publish("Controller",String(0), PRIVATE );
    Serial.println("Inactive");
  }
  delay(1000);
}

void myHandler(const char *event, const char *data)
{
    if (strcmp(data,"relayOn")==0)
    {
        digitalWrite( RELAY, HIGH );
    }
    if (strcmp(data,"relayClose")==0)
    {
        digitalWrite( RELAY, LOW );
    }
}

int Controller(String command)
{
    if (command == "run")
    {
        Particle.publish("Controller",String(1), PRIVATE );
        return 1;
    }
    if (command == "take")
    {
        
        Particle.publish("Controller",String(2), PRIVATE );
        return 1;
    }
    else if (command == "on")
    {
        digitalWrite( RELAY, HIGH );
        return 1;
    }
    else if (command == "off")
    {
        digitalWrite( RELAY, LOW );
        return 1;
    }
    return -1;
}