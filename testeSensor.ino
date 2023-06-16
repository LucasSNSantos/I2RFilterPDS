#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 30

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


void deslocaVetor( float *vetorAddr, int tam, float valor){
    for (int k = tam-1; k > 0; k--){
        *(vetorAddr+k) = *(vetorAddr+k-1);
    }
    *vetorAddr = valor;
}

float medido = 0;
float filtrado = 0;
float filtroPassaBaixa (float x){
    static float y_pass[2] = {0,0}, x_pass[2] = {0,0};
    const float a = 0.65, b = 0.70;
    float y = (a+b)* y_pass[0] - a * b * y_pass[1] + (1 - a - b + a * b) * x_pass[1];
    deslocaVetor(y_pass, 2, y);
    deslocaVetor(x_pass, 2, x);
    return y;
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  medido = sonar.ping_cm();
  filtrado = filtroPassaBaixa(medido);
  Serial.print(medido);
  Serial.print(",");
  Serial.println(filtrado);  
}
