#include <stdio.h>
#include <math.h>
#include <HMC5883L.h>
#include <motor.h>
#include <compass.h>

void gol(void);
void gor(void);
void golr(void);
void run(int l,int r);
void sos(void);
void info(void);
void home(void);
void test(void);
void turn90(void);
void turn0(void);
void turn270(void);
void black(void);
void pause(void);

void motor(char pin,char pwmpin,int val);//motor
void compass(int degree);//compass

void setup() {
int gs1_s=325,gs2_s=365,gs3_s=355,gs4_s=440;   //Grayscale value = silver
int gs1_b=450,gs2_b=650,gs3_b=590,gs4_b=740;    //Grayscale value = black
int d_3=590,d_8=460,d_15=280,d_20=220,d_30=160,d_50=120;//distance to the wall
int h_l=260,h_r=230;  //heat resource
//----------------------------------------------
int f_0,b_0,l_0,r_0,s_0,c_0;
int f_9,b_9,l_9,r_9,s_9,c_9;

int lf,rf,fl,fr,ll,rr,bb;//infrared distance sensors from 6 directions
int rr_;//counter for back infrared distance sensors
int gs1,gs2,gs3,gs4,gsw_,gss_,gsb_;
int left=1,hl,hr,hl_,hr_,h;
int num=300,s,ds,dms,i,ok,cmp,cmp_,cmpa,pcs,cmpz,go3;

int hf,h_f,hf_,hf,ok_p,back,start;
float tt=1.5,t_s,t_h,t_p=2,time,time_p,t_w;
}

void loop() {
 dms=(d_3+d_8)/2;ds=d_3-d_8;
 wait(0.5);pcs=selector();seconds(0);servo(4,60);wait(0.5);
 //---test---
 if(pcs==0){while(1){test();}}
 else if(pcs==1){while(1){info();gol();}}
 else if(pcs==2){while(1){info();gor();}}
 else if(pcs==3){sos();wait(10);}
 else if(pcs==4){black();wait(10);}
 else if(pcs==5){left=1;while(1){golr();}}
 //----------
 
 //run(0,0);
 //choose which way to run(left or right)
 if(pcs<8)left=1;else left=0;
 while(trigger()==0){test();info();}
 //---------Origin----------
 if(fl>d_20&&fr>d_20)f_0=1;else f_0=0;
 if(ll>d_20)l_0=1;else l_0=0;
 if(rr>d_20)r_0=1;else r_0=0;
 if(bb>d_20)b_0=1;else b_0=0;
 c_0=cmp_;
 
 cls();wait(1);
 //-------------------------
 ok=0;seconds(0);
 //-------------------------
 
 
 while(ok<4)//--
  {
   pause();
   info();
   //---sos---
   if(hl_>5||hr_>5)sos();
     
   //---process silver block(wait for 1 second)---
   if(gss_>5){run(0,0);wait(1);gss_=0;gsb_=0;t_s=time+tt;}
   
   //---process black block(---change posture----)
   if(gsb_>50)black();
   
   //---searching rules---
   if(left)gol();else gor();
   }

 while(ok<6)//--
   {pause();golr();}
 
 home();run(0,0);
}

void info(void)//get all the data from every sensor
{time=seconds(1);cmp=compass();
 if(cmp<46||cmp>314){cmp_=0;if(cmp<180)cmpa=cmp;else cmpa=cmp-360;}
 else {cmp_=(cmp+45)/90;cmpa=cmp-cmp_*90;}//cmp_=0.1.2.3

 //---distance---
 lf=analogRead(1);rf=analogRead(2);fl=analogRead(3);fr=analogRead(4);
 ll=analogRead(5);rr=analogRead(6);bb=analogRead(7);

 //---Grayscale-Silver and Black---
 gs1=geteadc(1);gs2=geteadc(2);gs3=geteadc(3);gs4=geteadc(4);//--get grayscale data--
 if(time>t_s&&(gs1<gs1_s||gs2<gs2_s)&&(gs3<gs3_s||gs4<gs4_s)){if(gss_<num)gss_++;}//Silver Block counter
 else if(gs1>gs1_b&&gs2>gs2_b){if(gsb_<num)gsb_++;}//Black Block counter
 else {gss_=0;gsb_=0;}//Empty Block

 //---Heat Resource Searching---
 hl=geteadc(5);hr=geteadc(6);
 if(time>t_h)
   {if(hl>h_l&&ll>d_20){if(hl_<num)hl_++;hr_=0;}else hl_=0;
    if(hr>h_r&&rr>d_20){if(hr_<num)hr_++;hl_=0;}else hr_=0;
  }
}


void turn90(void)//turn right 90 degree
{if(left)run(200,-200);else run(-200,200);
 cmpz=cmp_;while(cmpz==cmp_){info();}
 turn0();}
   
void turn0(void)
{while(abs(cmpa)>5){info();if(cmpa>0)run(-200,200);else run(200,-200);}
 run(0,0);}

void turn270(void)//turn left 90 degree
{if(left==0)run(200,-200);else run(-200,200);
 cmpz=cmp_;while(cmpz==cmp_){info();}
 turn0();}
 
void sos(void)
{run(0,0);if(hl_>hr_)servo(4,85);else servo(4,35);
 for(i=1;i<6;i++){digitalWrite(7,1);wait(0.5);digitalWrite(7,0);wait(0.5);}//--flicker light
 servo(4,60);wait(0.5);
 t_h=time+tt;hl_=0;hr_=0;
 ok++;
}

void black(void)//pause*
{turn0();
 while(geteadc(1)>gs1_b||geteadc(2)>gs2_b){run(-200,-200);pause();}wait(0.3);//--
 turn90();while(fl>d_20||fr>d_20){pause();turn90();}//&&
 if(analogRead(7)>d_20){while(analogRead(7)>d_20){pause();run(150,150);}}//d_15
 else if(analogRead(7)>d_50){while(analogRead(7)>d_50){pause();run(150,150);}}
 run(0,0);gsb_=0;}

void home(void)
{back=0;
  while(back==0)
   {
    info();
    //---silver block process (wait for 1s)---
    if(gss_>5){run(0,0);wait(1);gss_=0;gsb_=0;t_s=time+tt;}//tt
    //---black block process(rotate)---
    if(gsb_>5)black();
    
    if(fl>d_20&&fr>d_20)f_9=1;else f_9=0;
    if(ll>d_20)l_9=1;else l_9=0;
    if(rr>d_20)r_9=1;else r_9=0;
    if(bb>d_20)b_9=1;else b_9=0;
    
     if(time<t_s&&f_0==f_9&&l_0==l_9&&r_0==r_9&&b_0==b_9&&cmp_==c_0)back=1;
     else if(left)gol();else gor();
    }
  run(0,0);
}

void gol(void)
{if(lf<d_15)
    {if(cmpa<0)run(40,200);else run(0,200);}
 else if(fl>d_15){if(fl>d_8||lf>d_3)run(200,-200);else run(200,-100);}//rotate
 else if(lf<d_8)run(100,200);//turn left slowly
 else if(lf>d_3||lf>ll&&ll>d_15)run(200,100);//turn right slowly
 else {s=(100*(lf-dms))/ds*50/100;run(200+s,200-s);}   //go ahead and adjust the posture
}


void gor(void)//left-hand law
{if(rf<d_15)
    {cmpz=cmp_;while(rf<d_15&&cmpz==cmp_&&gsb_==0){info();run(250,0);}
     cmpz=cmp_;while(rf<d_8&&gsb_==0&&cmpz==cmp_){info();run(250,40);}
    }
 else if(fr>d_15){if(fr>d_8||rf>d_3)run(-200,250);else run(-100,250);}
 else if(rf<d_8)run(250,100);
 else if(rf>d_3||rf>rr&&rr>d_15)run(100,250);
 else {s=(100*(rf-dms))/ds*50/100;run(250-s,250+s);}  
}

void golr(void)//right-hand law
{info();
 pause();//-------------------------------------------------------------?
    //---silver block process (wait for 1s)---
   if(gss_>5){run(0,0);wait(1);gss_=0;gsb_=0;t_s=time+tt;}
    //---black block process(rotate)-
   if(gsb_>5)black();//-------------------------------------------------?

 if(left)
   {
    gol();
    if(cmpa<8&&cmpa>-8&&rr>d_50&&rr<d_30&&fl<d_30&&bb<d_30&&rf<d_8)rr_++;else rr_=0;//cmpa5-10
    }
 else
   {
    gor();
    if(cmpa<8&&cmpa>-8&&ll>d_50&&ll<d_30&&fr<d_30&&bb<d_30&&lf<d_8)rr_++;else rr_=0;//cmpa5-10
    }
 
 if(rr_>3000){go3=1;turn90();}
 else go3=0;
 
 while(go3)
   {
    info();//  run(0,0);wait(1); //--?? 
    
    pause();//-------------------------------------------------------------?
    
    if(abs(cmpa)>5)turn0();
    if(hl_>5||hr_>5)sos();
    if(gsb_>5)go3=4;
    switch(go3)
      {
       case 1:
         run(0,0);
         if(fl<d_15&&fr<d_15)go3=2;else go3=4;
         break;//if wrong judgement
       case 2:
         if(fl>d_8&&fr>d_8){turn90();go3=3;t_w=time;}
         else run(200-cmpa*5,200+cmpa*5);
         break;//turn left
       case 3: 
         run(0,0);
         if(time-t_w>0.5){turn270();go3=4;}
         break;//go along the wall
       case 4: 
         if(bb>d_8){turn270();go3=5;t_w=time;}
         else run(-200+cmpa*5,-200-cmpa*5);
         break;//go back
       case 5:
         if(time-t_w>1.1)go3=0;//00??
         else 
        {if(left)gol();else gor();
        //---silver block process (wait for 1s)---
        if(gss_>5){run(0,0);wait(1);gss_=0;gsb_=0;t_s=time+tt;}
        //---black block process(rotate)-
        if(gsb_>5)black();}
         break;//--0.5
      }
    }
}


void run(l,r)
{
  motor(2,3,l);motor(1,3,r);
   motor(3,4,l);motor(4,4,r);
 }

void test(void)//test all the sensor data
{
  info();
  locate(1,1);printf("cmp=%3d pcs=%2d",cmp,pcs);
  locate(2,1);printf("-adc--");
  locate(3,1);printf("1342 %3d %3d %3d %3d",lf,fl,fr,rf);
  locate(4,1);printf("576  %3d   %3d   %3d",ll,bb,rr);
  locate(5,1);printf("-eadc--");
  locate(6,1);printf("1234 %3d %3d %3d %3d",gs1,gs2,gs3,gs4);
  locate(7,1);printf("576  %3d   %3d   %3d",hl,hf,hr);
  wait(0.1);
}

void pause(void)
{if(trigger()==1)
   {cls();
    while(trigger()==1)
      {run(0,0);locate(1,1);printf("The car is pausing!");}   
    while(trigger()==0);
    while(trigger()==1){cls();}
    wait(0.5);
   }
}

