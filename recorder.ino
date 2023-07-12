#define IR_USE_AVR_TIMER1
//#include<Wire.h>
#include <IRremote.h>
#include <PCD8544.h>
#include <SoftwareSerial.h>
#define RXpin 13
#define TXpin 12
SoftwareSerial mySerial=  SoftwareSerial(RXpin, TXpin);
PCD8544 lcd;
//add playbackk differ from write song in other files
 const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
#define IR_RECEIVE_PIN 8
#define A 466.16
#define B 493.88
#define C 261.63
#define Cs 277.18
#define D 293.66
#define Ds 311.13
#define E 329.63
#define F 349.23
#define Fs 369.99
#define G 392.00
char named[10]={'_','_','_','_','_','_','_','_','_','_'};
char alpha[28]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_'};
int letpick=0;
int saver=15;
bool out=true;
int entered=0;
bool enterName=false;
bool pushed=false;
bool sdPush=false;
bool recorded=false;
int checker=0;
bool noNote=false;
char holder2;
int pausedP=0;
bool paused=false;
const unsigned short tasksNum = 4;
double note;
int np;
int pb;
int traverse=0;
int traversing=0;
int j=0;
int holder;
int p=0;
bool reset=false;
String pushName;
double noted;
double getNote;
bool nfin=false;
bool pauser=false;
int oncer=0;
int oneChance=0;
struct Song{

  char name[10]={'_','_','_','_','_','_','_','_','_','_'};
  int posNum;
  //double duration;
  //changed from int to double
  double tunes[50];
  int noteNum;
  bool rec;
};
Song songList;

//songList.rec = false;

//to assign the name for the first song -> songList[0].name = "Cupid"

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int); 
} task;
task tasks[tasksNum];

//double tester[100];
//bool rec[10];
//bool songSize[10];

int OnOff=0;
bool on=false;
int pbSwitch=0;
int recordSwitch=0;
int noteSwitch=0;
bool sName=false;
bool printing=false;
//int posNum=0;
double toNote(int holder){
  //mySerial.println("in toNote: ");
  mySerial.println(holder);
  if(holder==65){
    noted=A;
  }
  else if(holder==66){
    noted=466.16;
  }
  else if(holder==67){
    noted=493.88;
  }
  else if(holder==68){
    noted=261.63;
  }
  else if(holder==69){
    noted=277.18;
  }
  else if(holder==70){
    noted=277.18;
  }
  else if(holder==71){
    noted=311.13;
  }
  else if(holder==72){
    noted=329.63;
  }
  else if(holder==73){
    noted=349.23;
  }
  else if(holder==74){
    noted=369.99;
  }
  else if(holder==75){
    noted=0.00;
  }

}
enum SM1_States { SM1_INIT, SM1_OFF, SM1_ON};
int SM1_Tick(int state){
    switch(state){ // State transitions
      case SM1_INIT:
          state = SM1_OFF;    
        break;
      case SM1_OFF:
      if((IrReceiver.decode())&&(IrReceiver.decodedIRData.command==69)){
        OnOff++;
        if(OnOff==1){
          state=SM1_ON;
        }
      }
        break;
      case SM1_ON: 
        if((IrReceiver.decode())&&IrReceiver.decodedIRData.command==69){
          OnOff=0;
          if(OnOff==0){
          state=SM1_OFF;
          }
        }      
        break;

    }
    switch(state){ // State Action
      case SM1_INIT:
        break;
      case SM1_OFF:
      //Serial.print("OFF: ");
      //Serial.println(IrReceiver.decodedIRData.command);
      on=false;
        if (IrReceiver.decode()) {
          IrReceiver.resume();
        }
        lcd.clear();
        break;
      case SM1_ON:
      //Serial.print("ON: ");
     // Serial.println(IrReceiver.decodedIRData.command);
      on=true;
      if (IrReceiver.decode()) {
            IrReceiver.resume();
            Serial.print(IrReceiver.decodedIRData.command);
            //Serial.println("WE R ON");
        }
        if(out){
        lcd.setCursor(0,0);
        lcd.print("Press EQ ");
        lcd.setCursor(0,1);
        lcd.print("to record");
        lcd.setCursor(0,2);
        lcd.print("Press play");
        lcd.setCursor(0,3);
        lcd.print("to play song");
        }
        break;

    }
    return state;
}



enum record_States { record_INIT, record_OFF, rpos, record_ON, saveName, saveS};
int record_Tick(int state){
    switch(state){ // State transitions
      case record_INIT:
      state=record_OFF;
      break;
      case record_OFF:
      //Serial.println("on record_OFF");
      if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==25){
        Serial.println("in");
          recordSwitch=0;
          if(recordSwitch==0){
            Serial.println("choose rpos");
            noNote=false;
            out=false;
            lcd.clear();
            state=rpos;
          }
      }
      break;
      case rpos: 
      //Serial.println("on rpos");
      if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==22){
        songList.rec=true;
        recordSwitch=1;
        songList.posNum=0;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==12){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=1;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==24){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=2;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==94){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=3;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==8){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=4;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==28){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=5;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==90){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=6;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==66){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=7;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==82){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=8;
      }
      else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==74){
        songList.rec=true;
          recordSwitch=1;
          songList.posNum=9;
      }else{
        //songList.rec=false;
      }
      if(recordSwitch==1){
            Serial.print(rpos);
            //Serial.println(" :position recording");
            lcd.clear();
            state=record_ON;
          }
      break;
      case record_ON:
      //Serial.println("on record_ON");
      if((IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==25)||np==49){
        recordSwitch=0;
        noNote=true;
        lcd.clear();
      }
      if(recordSwitch==0){
            //Serial.println("not recording");
            if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==12){
          //might need record switch
          Serial.println("go to save name");
          lcd.clear();
              state=saveName;
              }
            if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==24){
              Serial.println("not be here");
              songList.rec=false;
              out=true;
              lcd.clear();
              state=record_OFF;
            }
        }
      break;
      case saveName:
     // Serial.print("INsaved name");
      //dont know if data is loaded instantly will use bool
      if(sName){
        lcd.clear();
      //  Serial.print("saved name");
        state=saveS;
      }
      break;
      case saveS:
      //Serial.print("in saveS");
      //dont know if data is loaded instantly will use bool
      if(sdPush){
        lcd.clear();
        out=true;
        state=record_OFF;
      }
      break;
    }
    switch(state){ // State actions
      case record_INIT:
      break;
      case record_OFF:
      saver=15;
      oneChance=0;
      digitalWrite(2,LOW);
     /* if(recorded){
        Serial.print(" ");
        lcd.clear();
        lcd.setCursor(20,0);
        lcd.print("Save Song? Press 1 for yes and 2 for no");
        }  */
     // lcd.clear();
      //songList.rec=false;
      break;
      case rpos:
      digitalWrite(2,LOW);
     // Songlist.rec=false;
      memset(songList.tunes, 0, sizeof(songList.tunes));
      np=0;
      lcd.setCursor(0,0);
      lcd.print("Choose song");
      lcd.setCursor(0,1);
      lcd.print("position 0-9");
      break;
      case record_ON:
      //lcd.clear();
      if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==22){
        noteSwitch=1;
        note=A;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==12){
          noteSwitch=1;
          note=B;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==24){
          noteSwitch=1;
          note=C;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==94){
          noteSwitch=1;
          note=Cs;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==8){
          noteSwitch=1;
          note=D;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==28){
          noteSwitch=1;
          note=Ds;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==90){
          noteSwitch=1;
          note=E;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==66){
          noteSwitch=1;
          note=F;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==82){
          noteSwitch=1;
          note=Fs;
      }
      else if(!noNote&&IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==74){
          noteSwitch=1;
          note=G;
      }else{
        //note=0.00;
        noTone(9);
      }
      if(!printing){
      lcd.setCursor(40,4);
      lcd.print("max 49");
      }
      lcd.setCursor(0,4);
      if(recordSwitch==1&&noteSwitch==1&&np<50){
        if(!printing){
        lcd.print(np);
        }
        digitalWrite(2,HIGH);
        songList.rec=true;
            tone(9,note);
            noteSwitch=0;
            songList.tunes[np]=note;
            np++;
      }
      else if(recordSwitch==1&&np<50){
        if(!printing){
       // lcd.setCursor(0,4);
        lcd.print(np);
        }
        digitalWrite(2,HIGH);
        songList.tunes[np]=0.0;
        np++;
      }
      if(printing&&oncer==1){
        lcd.clear();
      }
     // lcd.clear();
     if(oneChance==0){
      lcd.setCursor(0,0);
      lcd.print("Press EQ to");
      lcd.setCursor(0,1);
       lcd.print("Stop recording");
      oneChance++;
     }
      if(recordSwitch==0||np==49){
        printing=true;
        oncer++;
        digitalWrite(2,LOW);
        songList.noteNum=np;
       // Serial.print("number of notes: ");
       // Serial.println(np);
       // lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Press 1 to");
        lcd.setCursor(0,1);
        lcd.print("Save Song");
        lcd.setCursor(0,2);
        lcd.print("or 2 to delete");
        lcd.setCursor(0,3); 
        lcd.print("recording");
      }
      break;
      case saveName:
     // lcd.clear();
     oncer=0;
     printing=false;
      lcd.setCursor(0,0);
      lcd.print("Enter songName");
      lcd.setCursor(0,1);
      lcd.print("^ or v button");
      lcd.setCursor(0,2);
      lcd.print("0 to enter");
      lcd.setCursor(0,3);
      lcd.print("St to finish");
      lcd.setCursor(0,4);
      lcd.print("max 10 char");
      lcd.setCursor(0,20);
      //name selecthere for now fake name
     /* songList.name[0]='S';
      songList.name[1]='O';
      songList.name[2]='S';*/
      enterName=true;
      //need to choose name here
       // sName=true;
      
      break;
      case saveS:
      //lcd.clear();
      lcd.setCursor(20,0);
      mySerial.write('W');
      char cpn=songList.posNum+48;
      Serial.print("posnum:");
      Serial.println(songList.posNum);
      mySerial.write(cpn);

      Serial.print("songname:");
      for(int t=0; t<10;t++){
      Serial.print(songList.name[t]);
      }
      for(int t=0; t<10;t++){
      cpn=songList.name[t];
      mySerial.write(cpn);
      }

     /* Serial.print("songdura:");
      Serial.println(songList.noteNum);
      cpn=songList.noteNum+48;
      mySerial.write(cpn);
*/
      while(j<=songList.noteNum){
        //send letter based on note
        Serial.print(j); 
        Serial.println(" while"); 
        if(songList.tunes[j]==466.16){
          Serial.println("a");
          mySerial.write('a');
          //delay(50);
        }
        else if(songList.tunes[j]==493.88){
          Serial.println("b");
          mySerial.write('b');
         // delay(50);
        }
        else if(songList.tunes[j]==261.63){
          Serial.println("c");
          mySerial.write('c');
         // delay(50);
        }
        else if(songList.tunes[j]==277.18){
          Serial.println("d");
          mySerial.write('d');
         // delay(50);
        }
         else if(songList.tunes[j]==293.66){
          Serial.println("e");
          mySerial.write('e');
        //  delay(50);
        }
        else if(songList.tunes[j]==311.13){
          Serial.println("f");
          mySerial.write('f');
          //delay(50);
        }
        else if(songList.tunes[j]==329.63){
          Serial.println("g");
          mySerial.write('g');
         // delay(50);
        }
        else if(songList.tunes[j]==349.23){
          Serial.println("h");
          mySerial.write('h');
         // delay(50);
        }
        else if(songList.tunes[j]==369.99){
          Serial.println("i");
          mySerial.write('i');
         // delay(50);
        }
        else if(songList.tunes[j]==392.00){
          Serial.println("j");
          mySerial.write('j');
          //delay(50);
        }else{
          Serial.println("k");
          mySerial.write('k');
        }
      
        Serial.println(songList.tunes[j]); 
       // mySerial.write(arr[j]);
        j++;
      }
     // mySerial.write('d');
      Serial.println("iffed"); 
      mySerial.write('z');
      
     // Serial.println("b4");
      
      Serial.println("after trans");
      songList.rec=false;
      recordSwitch=0;
      songList.noteNum=0;
      songList.posNum=0;
      j=0;
      sdPush=true;

      break;
    }
    return state;

}

enum playback_States { playback_INIT, wait, play, stop};
int playback_Tick(int state){
    switch(state){
      case playback_INIT:
      state=wait;
      break;
      case wait:
      if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==64){
        pushed=true;
        lcd.clear();
      }
      if(pbSwitch==1){
        out=false;
        pushed=false;
        lcd.clear();
          state=play;
        }
      break;
      case play:

      if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==71){
        pbSwitch=0;
        if(pbSwitch==0){
          //traverse=0;
          lcd.clear();
          out=true;
          state=wait;
        }
      }
      if(pb==10&&reset){
        Serial.println("pb:");
        Serial.println(pb);
        memset(songList.name, '_', sizeof(songList.name));
        memset(songList.tunes, 0, sizeof(songList.tunes));
        noTone(9);
        out=true;
        p=0;
        pushName="";
        traverse=0;
        traversing=0;
        reset=false;
        pbSwitch=0;
        pushed=false;
        Serial.println("back to wait");
        lcd.clear();
        state=wait;
      }
      break;
    }
    switch(state){
      case playback_INIT:
      break;
      case wait:
      //Serial.println("wait");
     // traversing=0;
      pauser=false;
     // pushName="";
      //traverse=0;
      if(pushed){
        out=false;
        lcd.setCursor(0,0);
        //Serial.println("pick song to playback");
        lcd.print("Pick song 0-9");
         lcd.setCursor(0,1);
        lcd.print("to playback");
       // Serial.println(pbSwitch);
        if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==22){
            Serial.println("read in correct");
        pbSwitch=1;
        pb=0;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==12){
          pbSwitch=1;
          pb=1;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==24){
          pbSwitch=1;
          pb=2;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==94){
          pbSwitch=1;
          pb=3;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==8){
          pbSwitch=1;
          pb=4;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==28){
          pbSwitch=1;
          pb=5;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==90){
          pbSwitch=1;
          pb=6;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==66){
          pbSwitch=1;
          pb=7;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==82){
          pbSwitch=1;
          pb=8;
        }
        else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==74){
          pbSwitch=1;
          pb=9;
        }
      }
      break;
      case play:
      Serial.println("play state");
      //Serial.println(pb);
      //mySerial.write()
      //reading the stored songs takes too much memory
     /* if(traverse<=songList.noteNum){
      Serial.println(traverse);
      Serial.println(songList.noteNum);
      tone(9,songList.tunes[traverse]);
      }
      traverse++;
      */
    if(!pauser){
      Serial.println("playback");
      mySerial.write('P');
      mySerial.write(pb+48);
     // delay(50);
  while(mySerial.available()>0){
      Serial.println("available");
      while(p<10){
        Serial.println("name");
        holder=mySerial.read();
        if(holder==95){
        Serial.print(holder);
        Serial.print("underscore");
          holder=27;
        }else{
        Serial.print(holder);
        Serial.print("not");
        holder-=65;
        Serial.print(holder);
        Serial.print(" ");
        }
        Serial.println(alpha[holder]);
        named[p]=alpha[holder];
        delay(50);
        Serial.print(pushName);
        Serial.print(" ");
        p++;
      }
  if(p==10){
    for(int i=0;i<10;i++){
      delay(10);
      Serial.println("fullname");
    lcd.setCursor(i,0);
    lcd.print(named[i]);
    Serial.println(named[i]);
    }
    p++;
  }
  holder=mySerial.read();
  Serial.println(holder);
  if(holder==65){
  noted=466.16;
  }
  else if(holder==66){
    noted=493.88;
  }
  else if(holder==67){
    noted=261.63;
  }
  else if(holder==68){
    noted=277.18;
  }
  else if(holder==69){
    noted=277.18;
  }
  else if(holder==70){
    noted=311.13;
  }
  else if(holder==71){
    noted=329.63;
  }
  else if(holder==72){
    noted=349.23;
  }
  else if(holder==73){
    noted=369.99;
  }
  else if(holder==74){
    noted=392.00;
  }
  else if(holder==75){
    noted=0.00;
  }
  Serial.println("passed noted");
   // pushName="";
    Serial.println(noted);
    songList.tunes[traverse]=noted;
    traverse++;
    pb=10;
    }
    
  }
  if(traverse>0){
    Serial.println("traverse more than 0");
    Serial.println(traversing);
    Serial.println(traverse);
    
    while(traversing<=traverse){
      lcd.setCursor(0,3);
      lcd.print("duration: ");
      lcd.print(traverse);
      //Serial.print(IrReceiver.decodedIRData.command);
      if(songList.tunes[traversing]==0&&!paused){
       // lcd.print("traverse");
       lcd.setCursor(0,4);
       lcd.print("song at:");
        lcd.print(traversing);
        Serial.println("still song");
          noTone(9);
          traversing++;
      }else if (!paused){
        lcd.setCursor(0,4);
    //lcd.print("traverse");
      lcd.print(traversing);
       // Serial.println("still song");
        tone(9,songList.tunes[traversing]);
        traversing++;
      }else if(paused){
        //lcd.print("traverse");
        lcd.setCursor(0,4);
      lcd.print(traversing);
        noTone(9);
      }
      delay(200);
      if (IrReceiver.decode()) {
            IrReceiver.resume();
            Serial.print(IrReceiver.decodedIRData.command);
            if(on&&IrReceiver.decodedIRData.command==13){
              pauser=true;
              paused=true;
              Serial.println("paused");
            }
            if(on&&IrReceiver.decodedIRData.command==64){
              paused=false;
              Serial.println("play again");
            }
            //Serial.println("WE R ON");
        }
      }
    }     
    
    reset=true;
      break;

    }
    return state;
}
enum name_States { name_INIT, wait_name, enter_name};
int name_Tick(int state){
  switch(state){ // State transitions
      case name_INIT:
      state = wait_name;    
      break;
      case wait_name:
        if(enterName){
          Serial.println("to enter_name");
          state=enter_name;
        }
      break;
      case enter_name:
      if(!enterName){
        state=wait_name;
      }
      break;
  }
  switch(state){
    case name_INIT:
    break;
    case wait_name:
    //Serial.print("waiting to go to enter_name");
    break;
    case enter_name:
    //Serial.print(IrReceiver.decodedIRData.command);
    //Serial.print("enteringname");
  while(!nfin){
    
   // Serial.print("in big while");
    if(entered>9){
      nfin=true;
      lcd.setCursor(0,4);
      Serial.println("max name space");
      Serial.print("song Name: ");
      for(int i=0;i<10;i++){
      Serial.println(songList.name[i]);
      }
    }
     if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==13){
      nfin=true;
      Serial.print("pressed finish name");
      Serial.print("song Name: ");
      for(int i=0;i<10;i++){
      Serial.println(songList.name[i]);
      }
    }
    lcd.setCursor(0,5);
    lcd.print(alpha[letpick]);
    if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==9&&letpick<26){
      letpick++;
    lcd.setCursor(0,5);
    lcd.print(alpha[letpick]);
      Serial.println(alpha[letpick]);
    }
    else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==7&&letpick>0){
      letpick--;
      lcd.setCursor(0,5);
    lcd.print(alpha[letpick]);
      Serial.println(alpha[letpick]);
    }
    else if(IrReceiver.decode()&&on&&IrReceiver.decodedIRData.command==22){
      songList.name[entered]=alpha[letpick];
      lcd.setCursor(7,5);
    lcd.print(":");
    lcd.setCursor(0,5);
    lcd.setCursor(saver,5);
    lcd.print(alpha[letpick]);
    saver+=7;
      Serial.print("saved:");
      Serial.println(alpha[letpick]);
      entered++;
    }
    
    if (IrReceiver.decode()) {
            IrReceiver.resume();
            Serial.print(IrReceiver.decodedIRData.command);
            if(IrReceiver.decodedIRData.command==13){
               nfin=true;
            }
            //Serial.println("WE R ON");
        }
   //up is 9
   //down is 7
       
  
  }
    letpick=0;
    nfin=false;
    entered=0;
    sName=true;
    enterName=false;
    break;

  }
    return state;
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  lcd.begin(84,48);
  pinMode(2,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(RXpin, INPUT);
  pinMode(TXpin, OUTPUT);
  mySerial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = record_INIT;
  tasks[i].period = 150;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &record_Tick;
  i++;
  tasks[i].state = playback_INIT;
  tasks[i].period = 150;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &playback_Tick;
  i++;
  tasks[i].state = name_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &name_Tick;
  i++;
  
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }

}
//0->22
//2->24
//1->12
//3->94
//4->8
//5->28
//6->90
//7->66
//8->82
//9->74

