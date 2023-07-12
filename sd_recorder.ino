
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

File myFile;
#define RXpin 4
#define TXpin 2
const int chipSelect = 10;

// change this to match your SD shield or module;
char trash;
char x;
int i=0;
int first=0;
int k=0;
int p=0;
int k2=0;
int tick=0;
int tick2=0;
int test;
char reader;
char pls='A';
bool once=false;
bool opened=false;
String posname="";
bool fin=false;
bool quit=false;
char n;
int d;
char check;
int never=0;
char name[10];
char duration[5];
int nd=0;
SoftwareSerial mySerial=  SoftwareSerial(RXpin, TXpin);

void setup()
{
  // Open serial communications and wait for port to open:
  pinMode(RXpin, INPUT);
  pinMode(TXpin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);

}
void open(){
  //for file name to write song to 
  if(!SD.begin(10)){
      Serial.println("Init Failed M");
    }  
 // Serial.println("HERE:");
 // Serial.println(mySerial.read());
  x=mySerial.read();
  if(x=='0'){
      Serial.println("0");
      posname="song1.txt";
    
    }
    else if(x=='1'){
      Serial.println("1");
      posname="song1.txt";
    
    }
    else if(x=='2'){
      Serial.println("s2");
      posname="song2.txt";
    
    }
   else if(x=='3'){
      Serial.println("s3");
      posname="song3.txt";
    
    }
   else if(x=='4'){
      Serial.println("s4");
      posname="song4.txt";
    
    }
   else if(x=='5'){
      Serial.println("s5");
      posname="song5.txt";
    
    }
   else if(x=='6'){
      Serial.println("s6");
      posname="song6.txt";
    
    }
    else if(x=='7'){
      Serial.println("s7");
      posname="song7.txt";
    
    }
   else if(x=='8'){
      Serial.println("s8");
      posname="song8.txt";
    
    }
   else if(x=='9'){
      Serial.println("s9");
      posname="song9.txt";
    
    }
    Serial.println(posname);
    //delay(100);
    if(k2==1){
      myFile = SD.open(posname, FILE_READ);
      if(myFile){
      Serial.println("My File opened");
      }
    }else{
      if(SD.exists(posname)){
      SD.remove(posname);
    }
      myFile = SD.open(posname, FILE_WRITE);
      if(myFile){
      Serial.println("My File opened");
      }
    }
  /*  if(SD.exists(posname)){
      SD.remove(posname);
    }
      myFile = SD.open(posname, FILE_WRITE);
      if(myFile){
      Serial.println("My File opened");
      }
      */
}

void sding(){
//convert sent parent data to number and store to sd
    x=mySerial.read();

    if(x=='a'){
      Serial.println("a");
      myFile.println("466.16");
    
    }
    else if(x=='b'){
      Serial.println("b");
      myFile.println("493.88");
    
    }
    else if(x=='c'){
      Serial.println("c");
      myFile.println("261.63");
    
    }
    else if(x=='d'){
      Serial.println("d");
      myFile.println("277.18");
    
    }
    else if(x=='e'){
      Serial.println("e");
      myFile.println("293.66");
    
    }
    else if(x=='f'){
      Serial.println("f");
      myFile.println("311.13");
    
    }
   else if(x=='g'){
      Serial.println("g");
      myFile.println("329.63");
    
    }
   else if(x=='h'){
      Serial.println("h");
      myFile.println("349.23");
    
    }
    else if(x=='i'){
      Serial.println("i");
      myFile.println("369.99");
    
    }
    else if(x=='j'){
      Serial.println("j");
      myFile.println("392.00");
    
    }else if(x=='k'){
      Serial.println("k");
      myFile.println("0.0000");
    
    }else if(x=='z'){
        quit=true;
    }
    //if x == 'd'
}
void finread(){
  //only need to read the first 2 numbers of note, rest is discareded
  for(int q=0; q<4;q++){
      myFile.read();
      }
}
char convert(){
//convert sd note data to char to send to parent
  test=myFile.read();
  if(test==52){
    //start w 4
    test=myFile.read();
    if(test==54){
      //6
     // mySerial.write('A');
   
      Serial.println("A");
      finread();
      tick=1;tick2=1;
        return 'A';
    }else{
      //9
      
      //mySerial.write('B');
      Serial.println("B");
      finread();
      tick=1;tick2=1;
      return 'B';
    }
  }
  else if(test==50){
    //2
    test=myFile.read();
    if(test==54){
      //6
      
     // mySerial.write('C');
      Serial.println("C");
      finread();
      tick=1;tick2=1;
      return 'C';
    }
    else if(test==55){
      //7
      
      //mySerial.write('D');
      Serial.println("D");
      finread();
      tick=1;tick2=1;
      return 'D';
    }else{
      //9
      
      //mySerial.write('E');
      Serial.println("E");
      finread();
      tick=1;tick2=1;
      return 'E';
    }
  }else if(test==51){
    //3
    test=myFile.read();
    if(test==49){
      //1
      
      //mySerial.write('F');
      Serial.println("F");
      finread();
      tick=1;tick2=1;
      return 'F';
    }
    else if(test==50){
      //2
      
     // mySerial.write('G');
      Serial.println("G");
      finread();
      tick=1;tick2=1;
      return 'G';
    }
    else if(test==52){
      //4
      
     // mySerial.write('H');
      Serial.println("H");
      finread();
      tick=1;tick2=1;
      return 'H';
    }
    else if(test==54){
      //6
      
     // mySerial.write('I');
      Serial.println("I");
      finread();
      tick=1;tick2=1;
      return 'I';
    }
    else if(test==57){
      //9
     
     // mySerial.write('J');
      Serial.println("J");
      finread();
      tick=1;tick2=1;
       return 'J';
    }
  }else if(test==48){
    //0
    Serial.println("K");
      finread();
      tick=1;tick2=1;
      return 'K';
  }
}
void snameDura(){
    Serial.println("in file snamedura able");
  for(int namer=0; namer<10; namer++){
      n=mySerial.read();
      name[namer]=n;
      Serial.println("in for");

  }
  Serial.println(name);
  myFile.println(name);
}
void writeback(){
  if(myFile){
      //mySerial.flush();
      
      Serial.println(" file opened for write back");
      //reading sd
      while (myFile.available()) {
      //get note from sd and send to parent
      //Serial.print("b4");
      while(p<10){
        trash=myFile.read();
       Serial.println(trash);
       delay(50);
        mySerial.write(trash);
        p++;
      }
      reader=convert();
      if(tick2==1){
      //Serial.println("ow");
      mySerial.write(reader);
      //delay(1000);
     // mySerial.flush();
    //  Serial.print("afters");
      }
      tick2=0;
      }
      p=0;
    myFile.close();
    Serial.println("closed2");
    
    }  
    quit=true;
    return;
  }

void loop() {

  while(mySerial.available()>0){
    if(never==0){
      check=mySerial.read();
      never++;
    }
    if(check=='W'){
      if(first==0){
        Serial.print("first");
        if(!SD.begin(10)){
          Serial.println("Init Failed M");
        } 
      first++;
      }
      if(k==0){
        Serial.print("open");
      //testing files only want this to happen once, later in main file will change
        open();
      //delay(25);
        snameDura();
        k++;
      }
    sding();
    }else if(check=='P'){
      if(k2==0){
      k2++;
      open(); 
      }
     writeback();
    }
  }
  //close after initial write and open to read and send to parent
  if(mySerial.available()<=0&&quit){
    //delay(15);
    myFile.close();
    Serial.println("1st file close");
    mySerial.flush();
    quit=false;
    never=0;
    k=0;
    k2=0;
    
  } 
}
