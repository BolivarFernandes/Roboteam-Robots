#include <stdio.h>
#include <math.h>
#include <compass.h>
#include <motor.h>
#include <selector.h>

void follow(void);
void run(int x,int y,int z,int w);
void run_(int qw,int ss);
void run0(void);
void dribble_f(void);//dribble
void dribble_b(void);
void turn_f(void);   //rotate
void turn_b(void);
void shoot_f(void);  //shoot
void shoot_b(void);
void wayball(void);
void x_way(void);
void sos(void);
void back(void);
void ready(void); 
void test(void); 
//-----------------------



void setup() {
 
  int ball=10,dbf=20,dbf_=300,dbb=20,dbb_=300,nball=520;
  int sml_20=98,sml_40=207,sml_60=290,sml_80=310;//small ultrasonic sensors
//---------------------------------------------

int cmp,pcs,num=500,iof=0,iob=0,db_=0,nb=0,ok,i;
int ll,rr,fl,fr,bl,br,l_30,r_30,l[7],r[7],x_,f_,b_,l_,r_;
int door,way,max,right,gd[9],gd_;
int xx,yy,zz,ww,lf,rf,rb,lb,fw,sd,s;
float tt;
}

void loop() {

//--grayscale--1.2.3-(4front.5back)-6.7.8--
 gd[1]=450;gd[2]=520;gd[3]=460;gd[4]=460;gd[5]=450;gd[6]=395;gd[7]=460;gd[8]=480;
 //sos_32- opponents_28-------55-------80------105--------  
 l_30=375;l[0]=386;l[1]=350;l[2]=335;l[3]=296;l[4]=0;
 r_30=368;r[0]=374;r[1]=350;r[2]=330;r[3]=290;r[4]=0;
 //----------- x_= --- 1 --|--- 2 --|-- 3 ---|-- 4 --

 pcs=selector();seconds(0);
 if(pcs==0)test();
 //if(pcs<6){dbf_=dbf+(dbf_-dbf)/5*pcs;dbb_=dbb+(dbb_-dbb)/5*pcs;}//20+56+56+56+56+56
 //else {dbf_=dbf+(dbf_-dbf)/5*(pcs-5);dbb_=dbb+(dbb_-dbb)/5*(pcs-5);}
 ready();
 
 //--------------------------------------
 while(1)
  {cmp=compass();sos();
   if(cmp>25&&cmp<155||cmp>205&&cmp<335)run0(); 
   else {if(cmp<90||cmp>270){door=1;if(cmp<180)s=cmp/5*10;else s=(cmp-360)/5*10;}
         else {door=0;if(cmp>180)s=(cmp-180)/5*10;else s=(180-cmp)/5*10;}
         x_way();wayball();if(way)follow();else back();}
  } 
}
// RCJ double dribble_soccer_2015
// infrared sensors--1:dbf 2:dbb
// untrasonic sensors--3:ll  4:rr  5:fl 6:fr  7:br 8:bl(big ultrasonic left and right、small ultrasonic front and back）
//                4front
// grayscale sensors--1.2.3-|-6.7.8
//                5back
// port--11:front dribbler 12:back dribbler 7.8:switch
// motor port--3:lf 1:rf 2:rb 4:lb(clockwise is positive) 
// test:pcs=0
// main:pcs=<6:60cm shoot.>5:40cm shoot  pcs larger   dbf_larger



//----------------------------------------------------




void run0(void)//ok
{if(cmp<90||cmp>180&&cmp<270)
  {if(cmp<30||cmp>180&&cmp<210)run(-120,-120,-120,-120);
   else run(-250,-250,-250,-250);}
 else if(cmp>330||cmp<180&&cmp>150)run(120,120,120,120);
 else run(250,250,250,250);}
 
//      4
//1.2.3-|-6.7.8
//      5
void sos(void)//ok
{gd_=0;for(i=1;i<9;i++){if(geteadc(i+8)<gd[i]){s=0;gd_=i;i=10;run(0,0,0,0);wait(0.1);tt=seconds(1)+1;}}//--
 while(gd_)
  {cmp=compass();
   if(cmp>12&&cmp<168||cmp>192&&cmp<348)run0();
   else 
    {fl=analogRead(5);fr=analogRead(6);if(fl>sml_40||fr>sml_40)f_=0;else f_=1;
     br=analogRead(7);bl=analogRead(8);if(bl>sml_40||br>sml_40)b_=0;else b_=1;
     ll=analogRead(3);if(ll<l_30)l_=0;else l_=1;
     rr=analogRead(4);if(rr<r_30)r_=0;else r_=1;
     //--------------------------------------
     if(seconds(1)>tt||f_+b_+l_+r_==0){run(0,0,0,0);gd_=0;}     
     else if(f_&&b_&&l_&&r_)run(0,0,0,0);
     else if(l_||r_)
      {if(fl>bl&&fl>br||fr>bl&&fr>br)
        {if(l_==0)run_(3,1);else if(r_==0)run_(17,1);else run(250,-250,-250,250);}  // 54.306. 0
       else if(l_==0)run_(7,1);else if(r_==0)run_(13,1);else run(-250,250,250,-250);//126.234.180
       }
     else if(f_&&b_)
       {if(ll>rr)run(250,250,-250,-250);else run(-250,-250,250,250);}// 90.270
     else if(f_){if(ll>rr)run_(8,1);else run_(12,1);}                //144.216
     else if(b_){if(ll>rr)run_(2,1);else run_(18,1);}                // 36.324
     else run(0,0,0,0);
  }}
}

// qw: 0 . 1 . 2 . 3 . 4 . 5 . 6 . 7 . 8 . 9 .10 .11 .12 .13 .14 .15 .16 .17 .18 .19 .
//cmp: 0 .18 .36 .54 .72 .90 .108.126.144.162.180.198.216.234.252.270.288.306.324.342.
void wayball(void)
{max=geteadc(1);
 if(max>ball)
   {way=geteadc(2)/10;if(geteadc(3)>300)right=0;else right=1;
    if(max>nball){if(nb<num)nb++;}else if(nb>0)nb--;else nb=0;}
 else {way=0;nb=0;}
 //---dribble switch---
 if(way>2&&way<6&&analogRead(1)>dbf){if(iof==0){digitalWrite(11,0);iof=1;}}else if(iof==1){digitalWrite(11,1);iof=0;}
 if(way>9&&way<13&&analogRead(2)>dbb){if(iob==0){digitalWrite(12,0);iob=1;}}else if(iob==1){digitalWrite(12,1);iob=0;}
}
 
void ready(void)//port 7=left 8=right
{cls();locate(2,1);printf("-- READYING -PCS=%2d",pcs);wait(0.5);
 while(i==0)
  {x_way();if(digitalRead(7))i=1;else if(digitalRead(8))i=2;
   locate(4,1);printf(" cmp  dbf dbf_  x_");
   locate(5,1);printf("%4d%5d%5d%4d",compass(),dbf,dbf_,x_);}
 cls();}
 
//motor port--3:lf 1:rf 2:rb 4:lb() 
void run(x,y,z,w)
{if(x!=xx){motor(3,1,x);xx=x;}//fl
 if(y!=yy){motor(1,1,y);yy=y;}//fr
 if(z!=zz){motor(2,1,z);zz=z;}//br
 if(w!=ww){motor(4,1,w);ww=w;}//bl
}

//  x_=  1.2.3.4
//l[5]=0.1.2.3.4
//r[5]=  4.3.2.1.0
void x_way(void)//1
{ll=analogRead(3);if(ll>l[0]){l[5]=0;l[6]=1;}else for(i=1;i<5;i++){if(ll>l[i]){l[5]=i;i=6;}}
 rr=analogRead(4);if(rr>r[0]){r[5]=0;r[6]=1;}else for(i=1;i<5;i++){if(rr>r[i]){r[5]=i;i=6;}}
 if(l[5]+r[5]>3){l[6]=0;r[6]=0;if(l[5]>r[5])x_=l_;else x_=5-r_;}
 else 
  {if(abs(x_-l[5])>1){if(++l[6]>2000)l[6]=0;}else l[6]=0;
   if(abs(5-x_-r[5])>1){if(++r[6]>2000)r[6]=0;}else r[6]=0;
   if(l[6]==0||r[6]==0)
     {if(l[6])x_=5-r[5];else if(r[6])x_=l[5];
      else if(l[5]>r[5])x_=l[5];else x_=5-r[5];}
}}

void back(void)//ok
{fl=analogRead(5);fr=analogRead(6);if(fl>sml_40||fr>sml_40)f_=0;else f_=1;
 br=analogRead(7);bl=analogRead(8);if(bl>sml_40||br>sml_40)b_=0;else b_=1;
 if(f_&&b_)
    {if(cmp>12&&cmp<168||cmp>192&&cmp<348)run0();
     else if(x_==1)run_(5,1);else if(x_==4)run_(15,1);//90.270
     else if(ll<rr)run(250,250,-250,-250);else run(-250,-250,250,250);}
 else if(x_>1&&x_<4)//x_=2.3
    {if(door)
      {if(f_||bl>sml_80||br>sml_80)
        {if(ll>rr)run_(9,1);else run_(11,1);}          //162.198
       else if(b_){if(ll>rr)run_(1,1);else run_(19,1);}// 18.342
       else if(cmp>10&&cmp<350)run0();else run(0,0,0,0);}
     else
      {if(b_||fl>sml_80||fr>sml_80)
        {if(ll>rr)run_(1,1);else run_(19,1);}          // 18.342
       else if(f_){if(ll>rr)run_(9,1);else run_(11,1);}//162.198
       else if(cmp<170||cmp<190)run0();else run(0,0,0,0);}
    }
 else if(bl>fl&&bl>fr||br>fl&&br>fr)
    {if(x_==1)run_(7,1);else if(x_==4)run_(13,1);else run_(10,1);}//126.234.180
 else if(x_==1)run_(3,1);else if(x_==4)run_(17,1);else run_(0,1); // 54.306. 0
}
 
// qw: 0 . 1 . 2 . 3 . 4 . 5 . 6 . 7 . 8 . 9 .10 .11 .12 .13 .14 .15 .16 .17 .18 .19 .
//cmp: 0 .18 .36 .54 .72 .90 .108.126.144.162.180.198.216.234.252.270.288.306.324.342.
void follow(void)//1
{fl=analogRead(5);fr=analogRead(6);if(fl>sml_40||fr>sml_40)f_=0;else f_=1;
 br=analogRead(7);bl=analogRead(8);if(bl>sml_40||br>sml_40)b_=0;else b_=1;
 switch(way)
  {case 3:case 4:case 5:
     if(analogRead(1)>dbf_)db_++;
     if(db_>3){if(door)turn_f();else dribble_f();} //--
     else {if(nb>10+door*10||f_)sd=1;else sd=0; //--
           if(way==4){if(right)fw=1;else fw=19;}//-342.+18
           else if(way==5)fw=17+right-sd;       //288.306.324
           else           fw=2+right+sd;}       // 36. 54. 72
     break; 
   case 10:case 11:case 12:
     if(analogRead(2)>dbb_)db_++;
     if(db_>3){if(door)dribble_b();else turn_b();}  //--
     else {if(nb>110-door*10||b_)sd=1;else sd=0; //--
           if(way==11){if(right)fw=11;else fw=9;}//+198.-162
           else if(way==10)fw=12+right+sd;       //216.234.252
           else            fw=8-right-sd;}       //108.126.144
     break;
   case 2:case 1:case 14:case 13:
     if(nb)sd=1;else sd=0;//||x_==4
     if(way==2)      fw=4+right+sd;// 72. 90.108
     else if(way==13)fw=5+right-sd;// 72. 90.108
     else if(way==1) fw=6+right+sd;//108.126.144
     else            fw=3+right-sd;// 36. 54. 72     
     break; 
   case 6:case 7:case 8:case 9:
     if(nb)sd=1;else sd=0;//||x_==1
     if(way==6)     fw=15+right-sd;//288.270.252
     else if(way==9)fw=14+right+sd;//288.270.252
     else if(way==7)fw=13+right-sd;//252.234.216
     else           fw=16+right+sd;//324.306.288     
     break;
  }
 run_(fw,sd);
}

void dribble_f(void) 
{ok=0;b_=0;db_=1000;tt=seconds(1)+0.15;
 while(db_&&ok==0)
  {cmp=compass();sos();
   if(cmp>200&&cmp<160)run0();
   else 
     {x_way();br=analogRead(5);bl=analogRead(6);fl=analogRead(7);fr=analogRead(8);
      if(cmp>180)s=(cmp-180)/5*10;else s=(180-cmp)/5*10;
      if(fl<sml_20)l_=3;else if(fl<sml_40)l_=2;else if(fl<sml_60)l_=1;else l_=0;
      if(fr<sml_20)r_=3;else if(fr<sml_40)r_=2;else if(fr<sml_60)r_=1;else r_=0;
      if(analogRead(1)>dbf*2)db_=1000;else if(db_>0){if(analogRead(1)<dbf/3*2)db_--;}else db_=0;
      //-----------------
      if(seconds(1)<tt){if(bl<sml_20&&br<sml_20)run(0,0,0,0);else run(150,-150,-150,150);}
      else if(x_==1){if(l_&&r_)run_(5,1);else run_(8-l_,1);}  // 90.108.126.144(5-8)
      else if(x_==4){if(l_&&r_)run_(15,1);else run_(12+r_,1);}//270.252.234.216(15-12)
      else
        {if(b_==0&&(bl>sml_80||br>sml_80))b_=1;
         if(b_&&l_&&r_)
           {f_=fl-fr;
            if(l_+r_==6){if(ll>rr)run_(3,1);else run_(17,1);}//54.306
            else if(abs(f_)<40&&l_+r_<3)run(-150,150,150,-150);
            else if(f_>40&&rr<405)ok=4-x_;   //ok=1.2
            else if(f_<-40&&ll<405)ok=1-x_;  //ok=-1.-2
            else if(ll>rr)ok=2;else ok=-2;}
         else if(l_+r_==6){if(ll>rr)run_(5,1);else run_(15,1);}          //90.270
         else if(l_==3)run_(12,1);else if(r_==3)run_(8,1);else run_(10,1);//216.144.180
   }}}
 //------------------------------------
 if(ok==0)digitalWrite(11,1);else shoot_f();
 ok=0;b_=0;db_=0;iof=0; 
}  

void shoot_f(void)
{tt=seconds(1)+0.3;
 while(db_&&seconds(1)<tt&&cmp>40&&cmp<320)
  {cmp=compass();
   if(ok>0)
     {if(cmp>90&&cmp<180)run(150,150,150,150);
      else if(ok==1&&cmp>90&&cmp<220)run(0,500,500,500);
      else if(ok==2&&cmp>90&&cmp<205)run(0,500,500,500);
      else 
       {digitalWrite(11,1);if(cmp>90&&cmp<270)run(-100,800,800,800);else run(200,200,200,200);}}
   else if(cmp<270&&cmp>180)run(-150,-150,-150,-150);
   else if(ok==-1&&cmp<270&&cmp>140)run(-500,0,-500,-500);
   else if(ok==-2&&cmp<270&&cmp>155)run(-500,0,-500,-500);
   else
     {digitalWrite(11,1);if(cmp<270&&cmp>90)run(-800,100,-800,-800);else run(-200,-200,-200,-200);}
}}
 
//  x_=  1.2.3.4
//l[5]=0.1.2.3.4
//r[5]=  4.3.2.1.0
// qw: 0 . 1 . 2 . 3 . 4 . 5 . 6 . 7 . 8 . 9 .10 .11 .12 .13 .14 .15 .16 .17 .18 .19 .
//cmp: 0 .18 .36 .54 .72 .90 .108.126.144.162.180.198.216.234.252.270.288.306.324.342.
void dribble_b(void)//ok
{ok=0;b_=0;db_=1000;tt=seconds(1)+0.15;
 while(db_&&ok==0)
  {cmp=compass();sos();
   if(cmp>20&&cmp<340)run0();
   else 
     {x_way();fl=analogRead(5);fr=analogRead(6);br=analogRead(7);bl=analogRead(8);
      if(cmp<180)s=cmp/5*10;else s=(cmp-360)/5*10;
      if(fl<sml_20)l_=3;else if(fl<sml_40)l_=2;else if(fl<sml_60)l_=1;else l_=0;
      if(fr<sml_20)r_=3;else if(fr<sml_40)r_=2;else if(fr<sml_60)r_=1;else r_=0;
      if(analogRead(2)>dbb*2)db_=1000;else if(db_>0){if(analogRead(2)<dbb/3*2)db_--;}else db_=0;
      //-----------------
      if(seconds(1)<tt){if(bl<sml_20&&br<sml_20)run(0,0,0,0);else run(-150,150,150,-150);}
      else if(x_==1){if(l_&&r_)run_(5,1);else run_(r_+2,1);}  // 90. 72. 54. 36(5-2)
      else if(x_==4){if(l_&&r_)run_(15,1);else run_(18-l_,1);}//270.288.306.324(15-18)
      else 
        {if(b_==0&&(bl>sml_80||br>sml_80))b_=1;
         if(b_&&l_&&r_)
           {f_=fl-fr;
            if(l_+r_==6){if(ll>rr)run_(7,1);else run_(13,1);}//126.234
            else if(abs(f_)<40&&l_+r_<3)run(150,-150,-150,150);
            else if(f_>40&&ll<405)ok=x_-1;   //ok=1.2
            else if(f_<-40&&rr<405)ok=x_-4;  //ok=-1.-2
            else if(ll<rr)ok=2;else ok=-2;}
         else if(l_+r_==6){if(ll>rr)run_(5,1);else run_(15,1);}          //90.270
         else if(l_==3)run_(2,1);else if(r_==3)run_(18,1);else run_(0,1);//36.324.0
   }}}
 //------------------------------------
 if(ok==0)digitalWrite(12,1);else shoot_b();
 ok=0;b_=0;db_=0;iob=0; 
}       

void shoot_b(void)
{tt=seconds(1)+0.3;
 while(db_&&seconds(1)<tt&&(cmp<140||cmp>220))
  {cmp=compass();
   if(ok>0)
     {if(cmp>270)run(150,150,150,150);
      else if(ok==1&&cmp<40)run(500,500,0,500);
      else if(ok==2&&cmp<25)run(500,500,0,500);
      else 
       {digitalWrite(12,1);if(cmp<90)run(800,800,-100,800);else run(200,200,200,200);}}
   else if(cmp<90)run(-150,-150,-150,-150);
   else if(ok==-1&&cmp>320)run(-500,-500,-500,0);
   else if(ok==-2&&cmp>335)run(-500,-500,-500,0);
   else
     {digitalWrite(12,1);if(cmp>270)run(-800,-800,-800,100);else run(-200,-200,-200,-200);}
}}

void turn_f(void)
{ok=1;db_=1000;door=1;//tt=seconds(1)+0.15;
 while(db_&&ok)
  {cmp=compass();sos();//--
   if(analogRead(1)>dbf*2)db_=1000;else if(db_>0){if(analogRead(1)<dbf/3*2)db_--;}else db_=0;
   if(ok==1)
     {if(cmp>25&&cmp<335)run0();
      else 
        {x_way();fl=analogRead(5);fr=analogRead(6);br=analogRead(7);bl=analogRead(8);
         if(cmp<180)s=cmp/5*10;else s=(cmp-360)/5*10;
         if(fl<sml_20)l_=1;else l_=0;
         if(fr<sml_20)r_=1;else r_=0;
         if(bl<sml_40&&br<sml_40)b_=1;else b_=0;
         //------
         if(l_&&r_){if(x_<3)run_(14+b_,1);else run_(6-b_,1);}//252.270--90.108
         else 
          {run(0,0,0,0);//--
           if(l_)ok=2;else if(r_)ok=3;else if(x_==4||x_>1&&ll>rr)ok=2;else ok=3;}
      }}
   else if(cmp>155&&cmp<205)ok=0;
   else if(ok==2)
     {if(cmp>270||cmp<25)run(150,150,150,150);
      else if(cmp<90)run(0,250,250,250);else run(200,200,200,200);}
   else if(ok==3)
     {if(cmp>335||cmp<90)run(-150,-150,-150,-150);
      else if(cmp>270)run(-250,0,-250,-250);else run(-200,-200,-200,-200);}
  }
 ok=0;run(0,0,0,0);if(db_)door=0;}

void turn_b(void)
{ok=1;db_=1000;door=0;
 while(db_&&ok)
  {cmp=compass();sos();//--
   if(analogRead(2)>dbb*2)db_=1000;else if(db_>0){if(analogRead(2)<dbb/3*2)db_--;}else db_=0;
   if(ok==1)
     {if(cmp<155||cmp>205)run0();
      else 
        {x_way();br=analogRead(5);bl=analogRead(6);fl=analogRead(7);fr=analogRead(8);
         if(cmp>180)s=(cmp-180)/5*10;else s=(180-cmp)/5*10;
         if(fl<sml_20)l_=1;else l_=0;
         if(fr<sml_20)r_=1;else r_=0;
         if(bl<sml_40&&br<sml_40)b_=1;else b_=0;
         //------
         if(l_&&r_){if(x_<3)run_(14+b_,1);else run_(6-b_,1);}//252.270--90.108
         else 
          {run(0,0,0,0);
           if(l_)ok=2;else if(r_)ok=3;else if(x_==1||x_<4&&ll>rr)ok=2;else ok=3;}
      }}
   else if(cmp<25||cmp>335)ok=0;
   else if(ok==2)
     {if(cmp>90&&cmp<205)run(150,150,150,150);
      else if(cmp<270)run(250,250,0,250);else run(200,200,200,200);}
   else if(ok==3)
     {if(cmp<270&&cmp>155)run(-150,-150,-150,-150);
      else if(cmp>90)run(-250,-250,-250,0);else run(-200,-200,-200,-200);}
  }
 ok=0;run(0,0,0,0);if(db_)door=1;}

//......-4+......
//....-5+.-3+.... 
//..-6+.....-2+..
//-7+.........-1+
//===============
//+8-........+14-
//..+9-----+13-..
//...+10-+12-.... 
//.....+11-......
void run_(qw,ss)
{if(ss==1)
  {switch(qw)
   { case 0: lf= 380  ; rf=-400-s; rb=-360-s; lb= 330  ; break;//(  0)
     case 1: lf= 400-s; rf=-140  ; rb=-400-s; lb= 220  ; break;//( 18)
     case 2: lf= 440-s; rf=   0  ; rb=-320-s; lb=   0  ; break;//( 36)**
     case 3: lf= 460-s; rf= 180  ; rb=-360-s; lb=-120  ; break;//( 54)
     case 4: lf= 500-s; rf= 260  ; rb=-400-s; lb=-220  ; break;//( 72)
     case 5: lf= 380-s; rf= 360-s; rb=-320  ; lb=-340  ; break;//( 90)
     case 6: lf= 200  ; rf= 330-s; rb=-200  ; lb=-400-s; break;//(108)
     case 7: lf= 100  ; rf= 310-s; rb=-100  ; lb=-400-s; break;//(126)
     case 8: lf=   0  ; rf= 310-s; rb=   0  ; lb=-440-s; break;//(144)**
     case 9: lf=-100  ; rf= 300-s; rb= 100  ; lb=-440-s; break;//(162)  
     //---------------------------------------------------------------
     case 10:lf=-360  ; rf= 320-s; rb= 360-s; lb=-420  ; break;//(180)
     case 11:lf=-360-s; rf= 100  ; rb= 480-s; lb=-110  ; break;//(198)
     case 12:lf=-350-s; rf=   0  ; rb= 460-s; lb=   0  ; break;//(216)**     
     case 13:lf=-320-s; rf=-140  ; rb= 440-s; lb= 150  ; break;//(234)
     case 14:lf=-300-s; rf=-240  ; rb= 400-s; lb= 310  ; break;//(252)  
     case 15:lf=-240-s; rf=-460-s; rb= 360  ; lb= 460  ; break;//(270)
     case 16:lf=-180  ; rf=-400-s; rb= 220  ; lb= 410-s; break;//(288)  
     case 17:lf=-140  ; rf=-400-s; rb= 140  ; lb= 410-s; break;//(306)
     case 18:lf=   0  ; rf=-440-s; rb=   0  ; lb= 330-s; break;//(324)**
     case 19:lf= 160  ; rf=-460-s; rb=-160  ; lb= 350-s; break;//(342)
   }}
 else //if(ss==0)
  {switch(qw)
    {case 0: lf= 800    ; rf=-660-s*2; rb=-640-s*2; lb= 640    ; break;//(  0)
     case 1: lf= 800-s*2; rf=-120    ; rb=-810-s*2; lb= 300    ; break;//( 18)
     case 2: lf= 700-s*2; rf=   0    ; rb=-400-s*2; lb=   0    ; break;//( 36)** 
     case 3: lf= 800-s*2; rf= 440    ; rb=-810-s*2; lb=-120    ; break;//( 54)
     case 4: lf= 800-s*2; rf= 600    ; rb=-730-s*2; lb=-300    ; break;//( 72) 
     case 5: lf= 840-s*2; rf= 680-s*2; rb=-770    ; lb=-700    ; break;//( 90)
     case 6: lf= 280    ; rf= 600-s*2; rb=-370    ; lb=-820-s*2; break;//(108) 
     case 7: lf= 280    ; rf= 480-s*2; rb=-270    ; lb=-840-s*2; break;//(126)
     case 8: lf=   0    ; rf= 480-s*2; rb=   0    ; lb=-840-s*2; break;//(144)**
     case 9: lf=-240    ; rf= 480-s*2; rb= 130    ; lb=-840-s*2; break;//(162)  
     //-----------------------------------------------------------------------
     case 10:lf=-520    ; rf= 540-s*2; rb= 790-s*2; lb=-840    ; break;//(180)
     case 11:lf=-780-s*2; rf= 360    ; rb= 790-s*2; lb=-100    ; break;//(198) 
     case 12:lf=-480-s*2; rf=   0    ; rb= 810-s*2; lb=   0    ; break;//(216)**  
     case 13:lf=-520-s*2; rf=-110    ; rb= 800-s*2; lb= 430    ; break;//(234) 
     case 14:lf=-420-s*2; rf=-230    ; rb= 840-s*2; lb= 440    ; break;//(252)  
     case 15:lf=-260-s*2; rf=-740-s*2; rb= 330    ; lb= 760    ; break;//(270)    
     case 16:lf=-180    ; rf=-740-s*2; rb= 180    ; lb= 710-s*2; break;//(288) 
     case 17:lf=-120    ; rf=-740-s*2; rb= 120    ; lb= 710-s*2; break;//(306)  
     case 18:lf=   0    ; rf=-720-s*2; rb=   0    ; lb= 400-s*2; break;//(324)**
     case 19:lf= 200    ; rf=-720-s*2; rb=-310    ; lb= 540-s*2; break;//(342)
   }}
 run(lf,rf,rb,lb);
}

void test(void)
{while(1)
   {wait(0.5);
    while(digitalRead(8)==0&&digitalRead(7)==0)
     {pcs=selector();cls();
      locate(1,1);printf("test   pcs=%3d",pcs);
      locate(2,1);printf("------------------");
      locate(3,1);printf("0:test   5:follow");
      locate(4,1);printf("1:dianji 6:fw+sos");
      locate(5,1);printf("2:panqiu 7:dribble_f");
      locate(6,1);printf("3:run_1  8:dribble_b");
      locate(7,1);printf("4:run_0 9.10:t_f.b");//9:turn_f 10:turn_b
      locate(8,1);printf("----port 7.8 ok----");
      wait(0.1);}
    //------------------------------------------
    if(pcs==0)
     {while(trigger()==0)
       {cls();wayball();x_way();fl=analogRead(5);fr=analogRead(6);br=analogRead(7);bl=analogRead(8);
        if(fl<sml_20)l_=3;else if(fl<sml_40)l_=2;else if(fl<sml_60)l_=1;else l_=0;//--
        if(fr<sml_20)r_=3;else if(fr<sml_40)r_=2;else if(fr<sml_60)r_=1;else r_=0;//--
        gd_=0;for(i=1;i<9;i++){if(geteadc(i+8)<gd[i]){gd_=i;i=10;}}//--
        locate(1,1);printf("max=%3d way=%3d r=%2d",max,way,right);
        locate(2,1);printf("cp=%3d dbf=%3d b=%3d",compass(),analogRead(1),analogRead(2));
        locate(3,1);printf("x=%1d l=%1d r=%1d flr=%4d ",x_,l_,r_,fl-fr);
        locate(4,1);printf("ll=%3d fl=%3d fr=%3d",ll,fl,fr);
        locate(5,1);printf("rr=%3d bl=%3d br=%3d",rr,bl,br);
        locate(6,1);printf("gd=%2d io7=%2d io8=%2d",gd_,digitalRead(7),digitalRead(8)); 
        locate(7,1);printf("1234 %3d %3d %3d %3d",geteadc(9),geteadc(10),geteadc(11),geteadc(12));
        locate(8,1);printf("5678 %3d %3d %3d %3d",geteadc(13),geteadc(14),geteadc(15),geteadc(16));
        wait(0.05);}}
    else if(pcs==1)//motor test
     {cls();printf("--dianji-");
      while(trigger()==0)
       {run(400,0,0,0);wait(0.5);run(0,400,0,0);wait(0.5);
        run(0,0,400,0);wait(0.5);run(0,0,0,400);wait(0.5);
        run(0,0,0,0);wait(5);}
      }
    else if(pcs==2)//dribble test
     {cls();printf("--dribble-num-");
      while(trigger()==0)
        {locate(3,1);printf("--dribble=%3d",i);
         locate(4,1);printf("pcs=%3d",pcs);
         locate(5,1);printf("dbf =%3d",analogRead(1));
         locate(6,1);printf("dbb =%3d",analogRead(2));
         if(digitalRead(7)){digitalWrite(11,0);wait(1);digitalWrite(11,1);wait(1);}
         if(digitalRead(8)){digitalWrite(12,0);wait(1);digitalWrite(12,1);wait(1);}
         wait(0.1);}
      }
    else if(pcs==3||pcs==4)//run_()
     {s=4-pcs;
      while(trigger()==0)
       {i=0;wait(0.3);
        while(i==0)
          {pcs=selector();cls();
           locate(1,1);printf("test run_() pcs=%2d",pcs);
           locate(2,1);if(s==1)printf("low speed fw=%2d",pcs);else printf("high speed fw=%2d",pcs);
           locate(5,1);printf("port7 fw=pcs");
           locate(6,1);printf("port8 fw=pcs+10");
           if(digitalRead(7)||digitalRead(8))
             {if(digitalRead(7)){if(s){run_(pcs,1);}else run_(pcs,0);i=1;fw=pcs;}
              else if(digitalRead(8)){if(s){run_(pcs+10,1);}else run_(pcs+10,0);i=2;fw=pcs+10;}
              run(0,0,0,0);wait(1);}     
           wait(0.1);} 
        while(i)
          {pcs=selector();wayball();wait(0.2);cls();
           locate(1,1);printf("way=%3d %1d fw=%2d",way,right,fw);
           locate(2,1);printf("**** pcs= %2d ****",pcs);
           locate(3,1);printf("1:lf=%4d 2:rf=%4d",lf,rf);
           locate(4,1);printf("4:lb=%4d 3:rb=%4d",lb,rb);
           locate(7,1);printf("5-7:run 8-10 return ");
           locate(8,1);printf(" port 7++ port 8--");
           locate(6,1);
           if(pcs==1){printf("-pcs=%2d lf 7+ 8-",pcs);if(digitalRead(7))lf=lf+20;if(digitalRead(8))lf=lf-20;} 
           else if(pcs==2){printf("-pcs=%2d rf 7+ 8-",pcs);if(digitalRead(7))rf=rf+20;if(digitalRead(8))rf=rf-20;} 
           else if(pcs==4){printf("-pcs=%2d lb 7+ 8-",pcs);if(digitalRead(7))lb=lb+20;if(digitalRead(8))lb=lb-20;} 
           else if(pcs==3){printf("-pcs=%2d rb 7+ 8-",pcs);if(digitalRead(7))rb=rb+20;if(digitalRead(8))rb=rb-20;}
           else if(pcs>7){printf("-pls port 7.8 return");if(digitalRead(7)||digitalRead(8))i=0;}
           else {printf("-pls port 7.8 run-");
                 if(digitalRead(7)||digitalRead(8)){wait(1);run(lf,rf,rb,lb);wait(0.3);run(0,0,0,0);}}
      }}}
    else if(pcs==5||pcs==6)//follow()
     {cls();locate(1,1);printf("follow");wait(1);
      if(pcs<6){dbf_=dbf+(dbf_-dbf)/5*pcs;dbb_=dbb+(dbb_-dbb)/5*pcs;}
      else {dbf_=dbf+(dbf_-dbf)/5*(pcs-5);dbb_=dbb+(dbb_-dbb)/5*(pcs-5);}
      while(1)
       {cmp=compass();if(pcs==6)sos();
        if(cmp>25&&cmp<335)run0();
        else
         {wayball();x_way();if(cmp<180)s=cmp/5*10;else s=(cmp-360)/5*10;
          if(way){if(db_>2){run(0,0,0,0);wait(1);digitalWrite(11,1);digitalWrite(12,1);iof=0;iob=0;db_=0;wait(2);}else follow();}
          else back();}
      }}
    else if(pcs==7)//dribble_f
     {cls();locate(1,1);printf("dribble_f");wait(1);
      while(1)
       {if(analogRead(1)>dbf_){digitalWrite(11,0);wait(0.5);dribble_f();run(0,0,0,0);wait(2);}
        else {pcs=selector();run(0,0,0,0);
              locate(3,1);printf("dbf =%3d",dbf); if(pcs<7){if(digitalRead(7))dbf++;else if(digitalRead(8))dbf--;}
              locate(4,1);printf("dbf_=%3d",dbf_);if(pcs>7){if(digitalRead(7))dbf_=dbf_+10;else if(digitalRead(8))dbf_=dbf_-10;}
              locate(6,1);if(pcs<7)printf("dbf   7+ 8-");else printf("dbf_  7+ 8-");}
      }}
    else if(pcs==8)//dribble_b
     {cls();locate(1,1);printf("dribble_b");wait(1);
      while(1)
       {if(analogRead(2)>dbb_){digitalWrite(12,0);wait(0.5);dribble_b();run(0,0,0,0);wait(2);}
        else {pcs=selector();run(0,0,0,0);
              locate(3,1);printf("dbb =%3d",dbb); if(pcs<7){if(digitalRead(7))dbb++;else if(digitalRead(8))dbb--;}
              locate(4,1);printf("dbb_=%3d",dbb_);if(pcs>7){if(digitalRead(7))dbb_=dbb_+10;else if(digitalRead(8))dbb_=dbb_-10;}
              locate(6,1);if(pcs<7)printf("dbb   7+ 8-");else printf("dbb_  7+ 8-");}
      }}
    else if(pcs==9)//turn_l()
     {cls();locate(2,1);printf("***  turn_l() ***");wait(1);ok=1;
      while(ok)
        {cmp=compass();pcs=selector();s=-100-pcs*50;
         if(analogRead(1)>dbf*2)db_=1000;else if(db_>0){if(analogRead(1)<dbf/3*2)db_--;}else db_=0;
         locate(4,1);printf(" cmp=%3d db_=%4d",cmp,db_);
         locate(6,1);printf(" s=%4d ",s);
         if(db_>10&&(digitalRead(7)||digitalRead(8)))
           {run(0,0,0,0);digitalWrite(11,0);wait(1);
            run(-200,-200,-200,-200);while(compass()<180){;}
            run(s,0,s,s);while(compass()>200){;}
            run(0,0,0,0);wait(1);digitalWrite(11,1);}
      }}
    else //turn_b()
     {cls();locate(2,1);printf("***  turn_r() ***");wait(1);ok=1;
      while(ok)
        {cmp=compass();pcs=selector();s=100+pcs*50;
         if(analogRead(1)>dbf*2)db_=1000;else if(db_>0){if(analogRead(1)<dbf/3*2)db_--;}else db_=0;
         locate(4,1);printf(" cmp=%3d db_=%4d",cmp,db_);
         locate(6,1);printf(" s=%4d ",s);
         if(db_>10&&(digitalRead(7)||digitalRead(8)))
           {run(0,0,0,0);digitalWrite(11,0);wait(1);
            run(200,200,200,200);while(compass()>180){;}
            run(0,s,s,s);while(compass()<160){;}
            run(0,0,0,0);wait(1);digitalWrite(11,1);}
      }}
}}






