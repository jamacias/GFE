// Defining all pins
const int EchoPin_0 = 24;
const int TriggerPin_0 = 25;

void setup() {
    Serial.begin(115200);

    // Configuring pins
    for(int i = 0; i < 8; i++){
        // Iteramos por cada sensor. Cada pin de echo y trigger aumenta de dos en dos.
        pinMode(EchoPin_0 + (2 * i), INPUT);
        pinMode(TriggerPin_0 + (2 * i), OUTPUT);
        delay(1); // Stabilization
    }
}

void loop(){
    // 0 4 2 6 1 5 3 7 (secuencia de lectura de sensores)
    // 0 3 6 1 4 7 2 5

    // unsigned int sonar_readings[8] = {0}; //Initialize to zero.
    // for(int i = 0; i < 8; i++){
    //     // Iteramos por cada sensor. Cada echo y trigger aumenta de dos en dos.
    //     sonar_readings[i] = calculate_distance(TriggerPin_0 + (2 * i), EchoPin_0 + (2 * i));
    //     Serial.print(sonar_readings[i]);
    //     Serial. print(" ");
    //     delay(10); // 40 ms delay to avoid false positives
    // }
    // Serial.println(sonar_readings);

    unsigned int *sonar_readings;
    sonar_readings = read_sensors();
    for(int i = 0; i < 8; i++){
        Serial.print(sonar_readings[i]);
        Serial. print(" ");
    }
    Serial.println(" ");
    delay(500);
}

unsigned int *read_sensors(){
    static unsigned int sonar_readings[8] = {0}; //Initialize to zero.
    for(int i = 0; i < 8; i++){
        sonar_readings[i] = calculate_distance(TriggerPin_0 + (2 * i), EchoPin_0 + (2 * i));
        delay(20); // 20 ms delay to avoid false positives
    }
    return sonar_readings;
}

// Raw output, unfiltered with average
int calculate_distance(int TriggerPin, int EchoPin){
    long duration, distanceCm;

    digitalWrite(TriggerPin, LOW);  //Setting to LOW for 4us for cleaner reading
    delayMicroseconds(4);
    digitalWrite(TriggerPin, HIGH);  //Triggering for 10us
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);

    duration = pulseIn(EchoPin, HIGH);  //Measuring the time between pulses in microseconds

    distanceCm = duration * 10 / 292 / 2;   //Converting to cm

    return distanceCm;
}

// Filters the readings by doing the average
// int calculate_distance(int TriggerPin, int EchoPin){
//     int num = 10;
//     long duration, distanceCm, value;
//
//     for(int i = 0; i < num; i++){
//         digitalWrite(TriggerPin, LOW);  //Setting to LOW for 4us for cleaner reading
//         delayMicroseconds(4);
//         digitalWrite(TriggerPin, HIGH);  //Triggering for 10us
//         delayMicroseconds(10);
//         digitalWrite(TriggerPin, LOW);
//
//         duration = pulseIn(EchoPin, HIGH);  //Measuring the time between pulses in microseconds
//
//         distanceCm = duration * 10 / 292 / 2;   //Converting to cm
//         value += distanceCm;
//     }
//
//     int average = value / 10;
//
//     return average;
// }
