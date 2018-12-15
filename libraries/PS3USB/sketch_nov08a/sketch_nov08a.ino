//led は　１３番ピン
intintintin
#define led 13
void setup() {
  // put your setup code here, to run once:
  //ピン指定
  pinMode(led,13);
}

void loop() {
 analogWrite(led 10);

 delay(1000);

 analogWrite(led,200);

 delay(1000);
}
