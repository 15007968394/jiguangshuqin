//引入红外解码库
#include<IRremote.h>
//C调
int A =262;
int B =294;
int C =330;
int D =360;
int E =392;
int F =442;
int G =496;
//用于换调
float tune=1;
//读取电压
int val=0;
//红外线接收器OUTPUT端接在pin 10
int RECV_PIN = 10;
//定义IRrecv对象来接收红外线信号
IRrecv irrecv(RECV_PIN);
//解码结果放在decode_results构造的对象results里
decode_results results;
//新的发声函数
void newtone(byte tonePin, int frequency, int duration) 
{
    //定义周期
    int period = 1000L / frequency;
    //设置高电平和低电平各占1/2周期
    int pulse = period / 2;
    //发声周期过程
    for (long i = 0; i < duration; i += period) 
    {
       digitalWrite(tonePin, HIGH);
       delayMicroseconds(pulse);
       digitalWrite(tonePin, LOW);
       delayMicroseconds(pulse); 
    }
}
void setup() {
   Serial.begin(9600);//初始化串口
   irrecv.enableIRIn(); // 启动红外解码
   pinMode(9,INPUT);
}

void loop() {
     //模拟输入口获得光敏电阻两端电压
     int n0 =analogRead(A0); 
     int n1 =analogRead(A1); 
     int n2 =analogRead(A2); 
     int n3 =analogRead(A3); 
     int n4 =analogRead(A4); 
     int n5 =analogRead(A5);
     //9号数字I/O口读取光敏电阻两端电压
     val=digitalRead(9);
    //解码成功，收到一组红外线信号
    if (irrecv.decode(&results))
    {
       //串口打印接收的红外信息
       Serial.println(results.value,HEX); 
       //按键1，换低调
       if(results.value==16724175)
         { tune=0.5;}
        //按键2，换中调
       if(results.value==16718055)
         { tune=1;}
        //按键3，换高调
       if(results.value==16743045)
         { tune=2;}
       delay(100);
      //  接收下一个值
      irrecv.resume();
   }  
      
    Serial.println(tune);
   //若遮挡激光，光敏电阻阻值增大，发出对应的音调
   if(n0>1000){
     pinMode(2,OUTPUT);
     newtone(2,A*tune,200); 
    } 
   if(n1>1000){
     pinMode(3,OUTPUT);
     newtone(3,B*tune,200); 
   }
   if(n2>1000){
     pinMode(4,OUTPUT);
     newtone(4,C*tune,200); 
   }
  if(n3>1000){
     pinMode(5,OUTPUT);
     newtone(5,D*tune,200); 
   }   
   if(n4>1000){
     pinMode(6,OUTPUT);
     newtone(6,E*tune,200); 
   }
   if(n5>1000){
     pinMode(7,OUTPUT);
     newtone(7,F*tune,200); 
   }
  if(val==HIGH){
     pinMode(8,OUTPUT);
     newtone(8,G*tune,200);
  }
}
    
