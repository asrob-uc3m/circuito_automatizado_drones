
#define laserpin 10
#define resistorpin A1
#define switchpin 5



int low;
int high;
char comando;
int resistorstatus;
void setup() {  
  
  pinMode(laserpin,OUTPUT);  
  pinMode(switchpin,INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 do{
  
	}
while(digitalRead(switchpin)==LOW);  // espera a que pulses el interruptor
digitalWrite(13,HIGH);
calibrate_high(); // calibra el valor de la resistencia cuando le da el laser
Serial.println(high);
delay(500);		// espera 
digitalWrite(13,LOW);
do{
  
}
while(digitalRead(switchpin)==LOW); // otra vez espera a que pulses el interruptor

calibrate_low();  // calibra el valor de la resistencia cuando no le da el laser

/*   

      FIN DE LA CALIBRACION
*/

while(1)
{
  if (Serial.available()<0) {
  comando = Serial.read();
  if(comando=='l'){
    laser(1);
    Serial.println("laser on");
  }
  
  if(comando=='k')
  {
    laser(0);
    Serial.println("laser off");
    
  }
  else  comando = 'a';
  }
  /*
            LASER FINALIZADO
  
  */
  resistorstatus = analogRead(resistorpin);
  if(resistorstatus>((low+high)/2)) 		
  /* si el valor de la resistencia es menor que la media entre cuando le da y cuando no es que esta el dron*/
  Serial.println("No hay dron");
  else Serial.println("Hay dron");
  /* si no es que la media es mayor y por tanto está el dron*/
  Serial.println(resistorstatus);
  
  delay(50);
}

}

void calibrate_low()
{
  
  low = analogRead(resistorpin);
    
}
void calibrate_high()
{
    
   high = analogRead(resistorpin); 
  
  
}
void laser(bool onoff)
{
  if(onoff==true) digitalWrite(laserpin,HIGH);
  else digitalWrite(laserpin,LOW);
  
}
