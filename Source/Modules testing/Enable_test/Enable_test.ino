const int enable_pin = 48;
int enable = 0;

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(enable_pin, INPUT); // Pin 48 as input.
}

void loop(){
    enable = digitalRead(enable_pin);     // read the input pin
    Serial.println(enable);
    if(enable == 1){
        Serial.println("Enable!");
        digitalWrite(LED_BUILTIN, LOW);
    }
    else{
        Serial.println("Disable!");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    delay(500);
}
