// Defining all pins
const int EchoPin_0 = 24; //38
const int TriggerPin_0 = 25; //39

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

    unsigned int *sonar_readings;

    // sonar_readings = read_sensors();

    sonar_readings = average_read_sensors();
    for(int i = 0; i < 8; i++){
        Serial.print(sonar_readings[i]);
        Serial. print(" ");
    }

    Serial.println(" ");

    // If obstacle is detected, print it.
    if(check_for_obstacles(sonar_readings)){
        Serial.println("Obstacle detected!");
    }
    // delay(500);
}

int check_for_obstacles(unsigned int *sonar_readings){
    unsigned int bubble_boundary[8];
    float elapsed_time = 10;
    const int K_i = 50;
    const int v = 62.4; // (cm/s)

    // Filling the array
    for(int i = 0; i < 8; i++){
        bubble_boundary[i] = K_i*v*elapsed_time/1000;
    }
    for(int i = 0; i < 8; i++){
        if(sonar_readings[i] <= bubble_boundary[i]){
            return 1;
        }
    }
    return 0;
}

// Filter sensor readings by doing average
unsigned int *average_read_sensors(){
    unsigned int sum[8] = {0}; //Initialize to zero.
    static unsigned int average[8] = {0}; //Initialize to zero.
    unsigned int *sonar_readings;

    for(int j = 0; j < 2; j++){
        sonar_readings = read_sensors();
        for(int i = 0; i < 8; i++){
            sum[i] += sonar_readings[i];
        }
    }

    for(int k = 0; k < 8; k++){
        average[k] = sum[k]/2;
    }

    return average;
}

// 0 3 6 1 4 7 2 5
unsigned int *read_sensors(){
    static unsigned int sonar_readings[8] = {0}; //Initialize to zero.
    int i = 0;
    int cont = 0;
    while(cont < 8){
        sonar_readings[i] = calculate_distance(TriggerPin_0 + (2 * i), EchoPin_0 + (2 * i));
        if(cont == 2){
            i = 1;
        }
        else if(cont == 5){
            i = 2;
        }
        else{
            i += 3;
        }
        cont++;
        delay(10); // 10 ms delay to avoid false positives
    }
    return sonar_readings;
}

// unsigned int *read_sensors(){
//     static unsigned int sonar_readings[8] = {0}; //Initialize to zero.
//     for(int i = 0; i < 8; i++){
//         sonar_readings[i] = calculate_distance(TriggerPin_0 + (2 * i), EchoPin_0 + (2 * i));
//         delay(5); // 20 ms delay to avoid false positives
//     }
//     return sonar_readings;
// }

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
