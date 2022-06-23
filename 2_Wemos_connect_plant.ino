float err;
float y;
float x;

class PID 
{  
  public:
    float c1, c2, c3, N, ts, kp, ti, td, integral, derivada, error;
    void update_constants (float k_, float ti_, float td_);
    float get_control_action (float error_k);
    PID (float N_, float tc_, float kc_, float ts_)
    {
      error = 0;
      integral = 0;
      derivada = 0;
      c1 = 0;
      c2 = 0;
      c3 = 0;
      N = N_;
      ts = ts_;
      kp = 0.6 * kc_;
      ti = tc_ / 2.0;
      td = tc_ / 8.0;
      update_constants(kp, ti, td);
    }
};

float PID::get_control_action(float error_k){
  integral = (c1 * (error_k + error)) + integral;
  derivada = (c2 * (error_k - error)) + (c3 * derivada);
  float u = kp * (error_k + integral + derivada);
  // Acotar la potencia de 0-100
  if (u>100){
    u=100;
  }
  if (u<0){
    u=0;
  }
  // Actualizacion Variables
  error = error_k;

  return u;
}

void PID::update_constants (float k_, float ti_, float td_)
{
  kp = k_;
  ti = ti_;
  td = td_;

  // Calculo de las constantes intermedias
  c1 = ts/(2*ti);
  c2 = (2*td) / (((2*td)/N)+ts);
  c3 = (((2*td)/N)-ts) / (((2*td)/N)+ts);
}

PID BIS(10, 20, 5.50, 1);
void setup() {
  Serial.begin(9600);
  pinMode (D3, OUTPUT);

  //analogWriteFreq(4000);
  analogRead(A0);
}

void loop() {
  y = (analogRead(A0)*100.0)/1023.0; //anlog to digital
  err = 50 - y; //calculate the error
  x = BIS.get_control_action(err);//returns power to plant valeie
  
  analogWrite(D3,(x*1023)/100); // digital to analog back
  delay (1000);
  Serial.println(err);


}
