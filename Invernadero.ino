//Control de Invernadero
//[2018] planBe
//Inicio
constint ledPin13=13; //led azul     = temperatura baja
constint ledPin12=12; //led rojo     = temperatura alta
constint ledPin11=11;// led amarillo = temperatura ideal
int ledPin10=10;//rele para control de bomba
int ledPin9=9; // rele para control de calefactor
int ledPin8=8; // rele para control de ventiladores
float TC; //  temperatura promedio
float TC1; // temperatura sensor 1
float TC2; // temperatura sensor 2
float TC3; // temperatura sensor 3
float TC4; // temperatura sensor 4
float TC5; // temperatura sensor 5
float TC6; // temperatura sensor 6
int tempPin1=0; //entrada del sensor 1
int tempPin2=1; //entrada del sensor 2
int tempPin3=2; //entrada del sensor 3
int tempPin4=3; //entrada del sensor 4
int tempPin5=4; //entrada del sensor 5
int tempPin6=5; //entrada del sensor 6
//Conexión Serie con Excel
voidsetup(){
Serial.begin(9600);
pinMode(ledPin13,OUTPUT);
pinMode(ledPin12,OUTPUT);
pinMode(ledPin11,OUTPUT);
pinMode(ledPin10,OUTPUT);
pinMode(ledPin9,OUTPUT);
pinMode(ledPin8,OUTPUT);
Serial.println("CLEARDATA"); // Limpia los datos en Excel
Serial.println("LABEL,Time,TempCasa");
}
//Lectura de Sensores
void loop (){
TC1=analogRead(tempPin1);
TC2=analogRead(tempPin2);
TC3=analogRead(tempPin3);
TC4=analogRead(tempPin4);
TC5=analogRead(tempPin5);
TC6=analogRead(tempPin6);
//Procesamiento de Señales
//Conversión a Cº
TC1= (5* TC1 * 100)/1024;
TC2= (5* TC2 * 100)/1024;
TC3= (5* TC3 * 100)/1024;
TC4= (5* TC4 * 100)/1024;
TC5= (5* TC5 * 100)/1024;
TC6= (5* TC6 * 100)/1024;
//Temperatura promedio
TC=((TC1+TC2+TC3+TC4+TC5+TC6)/6);
Serial.print("DATA,TIME,"); //comando en excel
Serial.print(TC); //envío de datos
Serial.print(",");
Serial.println();
delay(1000);
//Temperatura dentro del rango = enciende el led amarillo
if (TC>=25 && TC<=28){
digitalWrite(ledPin13,LOW);
digitalWrite(ledPin12,LOW);
digitalWrite(ledPin11,HIGH); //led amarillo
digitalWrite(ledPin10,LOW);
digitalWrite(ledPin9,LOW);
digitalWrite(ledPin8,LOW);
}
//Temperatura bajo el rango = enciende el led azul, el calefactor y la bomba
if (TC<25){
digitalWrite(ledPin13,HIGH); //led azul
digitalWrite(ledPin12,LOW);
digitalWrite(ledPin11,LOW);
digitalWrite(ledPin10,HIGH); //bomba
digitalWrite(ledPin9,HIGH); //calefactor
digitalWrite(ledPin8,LOW);
}
//Temperatura arriba del rango = enciende led rojo y sistema de ventilación
if (TC>28){
digitalWrite(ledPin13,LOW);
digitalWrite(ledPin12,HIGH); //led rojo
digitalWrite(ledPin11,LOW);
digitalWrite(ledPin10,LOW);
digitalWrite(ledPin9,LOW);
digitalWrite(ledPin8,HIGH); //ventilación
}
}
//Fin