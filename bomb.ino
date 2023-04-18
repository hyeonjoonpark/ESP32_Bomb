unsigned long bomb = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
int sw = false;
int old_btn = 0;

float count = 10.0;

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  pinMode(17, INPUT);
}

void loop() {
  if(digitalRead(16) == HIGH) {
    if(millis() - time2 > 5000) {
      digitalWrite(16 ,LOW);
    }
  }
  if(millis() - time1 > 100) {
    time1 = millis();
    if(sw) {
      Serial.print("= ");
      Serial.println(count);
      count-=0.1;
      if(count<=0) {
        Serial.println("폭탄이 터짐");
        digitalWrite(16, HIGH);
        time2 = millis();
        sw = false;
      }
    } else {
      Serial.println("중지");
      count = 10;
    }
  }
  bool now_btn = digitalRead(17);
  if(old_btn == HIGH && now_btn == LOW) {
    //하강엣지
    bomb = millis();
  } else if(old_btn == LOW && now_btn == HIGH) {
    //상승엣지
    if(millis() - bomb > 50) {
      // 버튼이 눌려짐
     sw = !sw;
    }
    
  }
  old_btn = now_btn;

  

}
