uses crt,graph,dos;
type rec=record
     name:string;
     maxlvl:byte;
     end;
var gd,gm,i,ii,x1,x2,page:integer;
    ch,ch2:char;
    y,L1,pam,jj,L10,LL,gro6,initiated,g,x,xx,ttt,tttt,x_c,xx_c,l_c,r_c,ccc:byte;
    cccc,l_cc,r_cc,x_cc,xx_cc,success,success_2:byte;
    ccccc,l_ccc,r_ccc,x_ccc,xx_ccc,KACHVANE,SLIZANE,lqvo,dqsno:byte;
    h,m,ss,hund:word;
    long1,long2:longint;
    f:file of rec;
    ff:file of rec;
    fff:file of integer;
    S:rec;
    size:word;
    PP:array[1..37,1..7] of pointer;
    ent,ttr,nick,sss:string;
Procedure WORLD_stated;
          begin
          cleardevice;
          setbkcolor(8);
          setcolor(1);
          settextstyle(defaultfont,horizdir,4);
          outtextxy(75,30,'ESCAPE FROM TUES');
          setfillstyle(1,14);
          bar(1,80,640,90);
          setfillstyle(9,4);
          bar(110,190,520,196);
          bar(110,280,520,286);
          bar(110,370,520,376);
          bar(110,460,520,466);
          setfillstyle(6,7);
          bar(20,120,30,475);
          bar(610,120,620,475);
          bar(20,120,610,130);
          bar(20,480,620,470);
          end;
          {VRATI}
Procedure FLOOR_4;
          begin
          setfillstyle(1,7);
          for i:=0 to 5 do
          bar(45+90*i,186,70+90*i,150);
          bar(530,184,545,150);
          bar(580,184,595,150);
          setcolor(white);
          settextstyle(defaultfont,horizdir,1);
          outtextxy(531,160,'WC');
          outtextxy(581,160,'WC');
          for i:=0 to 5 do
          begin
          outtextxy(50+i*90,160,'4');
          case i of
          0: outtextxy(50+i*90+8,160,'2');
          1: outtextxy(50+i*90+8,160,'3');
          2: outtextxy(50+i*90+8,160,'4');
          3: outtextxy(50+i*90+8,160,'5');
          4: outtextxy(50+i*90+8,160,'6');
          5: outtextxy(50+i*90+8,160,'7');
          end;
          end;
          end;
Procedure FLOOR_3;
          begin
          setfillstyle(1,7);
          for i:=0 to 5 do
          bar(45+90*i,276,70+90*i,240);
          bar(530,274,545,240);
          bar(580,274,595,240);
          setcolor(white);
          settextstyle(defaultfont,horizdir,1);
          outtextxy(531,250,'WC');
          outtextxy(581,250,'WC');
          for i:=0 to 5 do
          begin
          outtextxy(50+i*90,250,'3');
          case i of
          0: outtextxy(50+i*90+8,250,'2');
          1: outtextxy(50+i*90+8,250,'3');
          2: outtextxy(50+i*90+8,250,'4');
          3: outtextxy(50+i*90+8,250,'5');
          4: outtextxy(50+i*90+8,250,'6');
          5: outtextxy(50+i*90+8,250,'7');
          end;
          end;
          end;
procedure FLOOR_2;
          begin
          setfillstyle(1,7);
          for i:=0 to 5 do
          bar(45+90*i,366,70+90*i,330);
          bar(530,364,545,330);
          bar(580,364,595,330);
          setcolor(white);
          settextstyle(defaultfont,horizdir,1);
          outtextxy(531,340,'WC');
          outtextxy(581,340,'WC');
          for i:=0 to 5 do
          begin
          outtextxy(50+i*90,340,'2');
          case i of
          0: outtextxy(50+i*90+8,340,'2');
          1: outtextxy(50+i*90+8,340,'3');
          2: outtextxy(50+i*90+8,340,'4');
          3: outtextxy(50+i*90+8,340,'5');
          4: outtextxy(50+i*90+8,340,'6');
          5: outtextxy(50+i*90+8,340,'7');
          end;
          end;
          end;
Procedure FLOOR_1;
          begin
          setfillstyle(1,7);
          for i:=0 to 5 do
          if i>0 then
          bar(45+90*i,456,70+90*i,420);
          bar(530,454,545,420);
          bar(580,454,595,420);
          setcolor(white);
          settextstyle(defaultfont,horizdir,1);
          outtextxy(531,430,'WC');
          outtextxy(581,430,'WC');
          for i:=0 to 5 do
          begin
          outtextxy(50+i*90,430,'1');
          case i of
          0: outtextxy(50+i*90+8,430,'2');
          1: outtextxy(50+i*90+8,430,'3');
          2: outtextxy(50+i*90+8,430,'4');
          3: outtextxy(50+i*90+8,430,'5');
          4: outtextxy(50+i*90+8,430,'6');
          5: outtextxy(50+i*90+8,430,'7');
          end;
          end;
          end;
          {KRAI VRATI}
Procedure STAIRS;
          begin
          {STULBI LQVO}
          setfillstyle(1,2);
          for i:=0 to 68 do
          bar(40,188+i*4,105,190+i*4);
          setfillstyle(1,8);
          bar(40,192,70,230);
          bar(70,236,105,278);
          bar(40,284,70,322);
          bar(70,327,105,370);
          bar(40,376,70,414);
          bar(70,419,105,459);
          {KRAI NA STULBI LQVO}
          {STULBI-DQSNO}
          setfillstyle(1,2);
          bar(530,190,604,192);
          bar(530,280,604,282);
          bar(530,370,604,372);
          bar(530,460,604,462);
          for i:=1 to 5 do
          bar(580,190+i*45,604,190+i*45+2);
          setcolor(green);
          for i:=0 to 2 do
          begin
          line(550,190+i*90,580,235+i*90);
          line(551,190+i*90,581,235+i*90);
          line(552,190+i*90,582,235+i*90);
          line(550,280+i*90,582,235+i*90);
          line(549,280+i*90,581,235+i*90);
          line(548,280+i*90,580,235+i*90);
          end;
          {KRAI NA STULBI-DQSNO}
          end;
Procedure DOOM;
          begin
          rewrite(fff);
          close(fff);
          end;
Procedure KID_L;
          begin
          setfillstyle(1,lightgreen);
          {tqlo}
          bar(37+x*15,480-xx*45,41+x*15,492-xx*45);
          {kraka}
          bar(34+x*15,490-xx*45,37+x*15,500-xx*45);
          bar(40+x*15,490-xx*45,42+x*15,496-xx*45);
          bar(42+x*15,493-xx*45,46+x*15,496-xx*45);
          {ruce}
          bar(31+x*15,484-xx*45,36+x*15,486-xx*45);
          setcolor(lightgreen);
          line(40+x*15,480-xx*45,45+x*15,485-xx*45);
          line(40+x*15,481-xx*45,45+x*15,486-xx*45);
          line(41+x*15,489-xx*45,45+x*15,485-xx*45);
          line(40+x*15,490-xx*45,45+x*15,486-xx*45);
          {glava}
          bar(36+x*15,475-xx*45,42+x*15,480-xx*45);
          end;
Procedure Cleaner_LLL;
          begin
          setfillstyle(1,3);
          {tqlo}
          bar(37+x_ccc*15,480-xx_ccc*45,41+x_ccc*15,492-xx_ccc*45);
          {kraka}
          bar(34+x_ccc*15,490-xx_ccc*45,37+x_ccc*15,500-xx_ccc*45);
          bar(40+x_Ccc*15,490-xx_ccc*45,42+x_ccc*15,496-xx_ccc*45);
          bar(42+x_ccc*15,493-xx_ccc*45,46+x_ccc*15,496-xx_ccc*45);
          {ruce}
          bar(31+x_ccc*15,484-xx_ccc*45,36+x_ccc*15,486-xx_ccc*45);
          setcolor(3);
          line(40+x_ccc*15,480-xx_ccc*45,45+x_ccc*15,485-xx_ccc*45);
          line(40+x_ccc*15,481-xx_ccc*45,45+x_ccc*15,486-xx_ccc*45);
          line(41+x_ccc*15,489-xx_ccc*45,45+x_ccc*15,485-xx_ccc*45);
          line(40+x_ccc*15,490-xx_ccc*45,45+x_ccc*15,486-xx_ccc*45);
          {glava}
          bar(36+x_ccc*15,475-xx_ccc*45,42+x_ccc*15,480-xx_ccc*45);
          end;
Procedure Cleaner_LL;
          begin
          setfillstyle(1,9);
          {tqlo}
          bar(37+x_cc*15,480-xx_cc*45,41+x_cc*15,492-xx_cc*45);
          {kraka}
          bar(34+x_cc*15,490-xx_cc*45,37+x_cc*15,500-xx_cc*45);
          bar(40+x_Cc*15,490-xx_cc*45,42+x_cc*15,496-xx_cc*45);
          bar(42+x_cc*15,493-xx_cc*45,46+x_cc*15,496-xx_cc*45);
          {ruce}
          bar(31+x_cc*15,484-xx_cc*45,36+x_cc*15,486-xx_cc*45);
          setcolor(9);
          line(40+x_cc*15,480-xx_cc*45,45+x_cc*15,485-xx_cc*45);
          line(40+x_cc*15,481-xx_cc*45,45+x_cc*15,486-xx_cc*45);
          line(41+x_cc*15,489-xx_cc*45,45+x_cc*15,485-xx_cc*45);
          line(40+x_cc*15,490-xx_cc*45,45+x_cc*15,486-xx_cc*45);
          {glava}
          bar(36+x_cc*15,475-xx_cc*45,42+x_cc*15,480-xx_cc*45);
          end;
Procedure Cleaner_L;
          begin
          setfillstyle(1,1);
          {tqlo}
          bar(37+x_c*15,480-xx_c*45,41+x_c*15,492-xx_c*45);
          {kraka}
          bar(34+x_c*15,490-xx_c*45,37+x_c*15,500-xx_c*45);
          bar(40+x_C*15,490-xx_c*45,42+x_c*15,496-xx_c*45);
          bar(42+x_c*15,493-xx_c*45,46+x_c*15,496-xx_c*45);
          {ruce}
          bar(31+x_c*15,484-xx_c*45,36+x_c*15,486-xx_c*45);
          setcolor(1);
          line(40+x_c*15,480-xx_c*45,45+x_c*15,485-xx_c*45);
          line(40+x_c*15,481-xx_c*45,45+x_c*15,486-xx_c*45);
          line(41+x_c*15,489-xx_c*45,45+x_c*15,485-xx_c*45);
          line(40+x_c*15,490-xx_c*45,45+x_c*15,486-xx_c*45);
          {glava}
          bar(36+x_c*15,475-xx_c*45,42+x_c*15,480-xx_c*45);
          end;
Procedure KID_R;
          begin
          setfillstyle(1,lightgreen);
          {tqlo}
          bar(37+x*15,480-xx*45,41+x*15,492-xx*45);
          {kraka}
          bar(41+x*15,490-xx*45,44+x*15,500-xx*45);
          bar(36+x*15,490-xx*45,38+x*15,496-xx*45);
          bar(32+x*15,493-xx*45,35+x*15,496-xx*45);
          {ruce}
          bar(41+x*15,484-xx*45,46+x*15,486-xx*45);
          setcolor(lightgreen);
          line(37+x*15,480-xx*45,32+x*15,485-xx*45);
          line(37+x*15,481-xx*45,32+x*15,486-xx*45);
          line(32+x*15,485-xx*45,37+x*15,489-xx*45);
          line(32+x*15,486-xx*45,37+x*15,490-xx*45);
          {glava}
          bar(36+x*15,475-xx*45,42+x*15,480-xx*45);
          end;
Procedure Cleaner_rrr;
          begin
          setfillstyle(1,3);
          {tqlo}
          bar(37+x_ccc*15,480-xx_ccc*45,41+x_ccc*15,492-xx_ccc*45);
          {kraka}
          bar(41+x_ccc*15,490-xx_ccc*45,44+x_ccc*15,500-xx_ccc*45);
          bar(36+x_ccc*15,490-xx_ccc*45,38+x_ccc*15,496-xx_ccc*45);
          bar(32+x_ccc*15,493-xx_ccc*45,35+x_ccc*15,496-xx_ccc*45);
          {ruce}
          bar(41+x_ccc*15,484-xx_ccc*45,46+x_ccc*15,486-xx_ccc*45);
          setcolor(3);
          line(37+x_ccc*15,480-xx_ccc*45,32+x_ccc*15,485-xx_ccc*45);
          line(37+x_ccc*15,481-xx_ccc*45,32+x_ccc*15,486-xx_ccc*45);
          line(32+x_ccc*15,485-xx_ccc*45,37+x_ccc*15,489-xx_ccc*45);
          line(32+x_ccc*15,486-xx_ccc*45,37+x_ccc*15,490-xx_ccc*45);
          {glava}
          bar(36+x_ccc*15,475-xx_ccc*45,42+x_ccc*15,480-xx_ccc*45);
          end;
Procedure Cleaner_rr;
          begin
          setfillstyle(1,9);
          {tqlo}
          bar(37+x_cc*15,480-xx_cc*45,41+x_cc*15,492-xx_cc*45);
          {kraka}
          bar(41+x_cc*15,490-xx_cc*45,44+x_cc*15,500-xx_cc*45);
          bar(36+x_cc*15,490-xx_cc*45,38+x_cc*15,496-xx_cc*45);
          bar(32+x_cc*15,493-xx_cc*45,35+x_cc*15,496-xx_cc*45);
          {ruce}
          bar(41+x_cc*15,484-xx_cc*45,46+x_cc*15,486-xx_cc*45);
          setcolor(9);
          line(37+x_cc*15,480-xx_cc*45,32+x_cc*15,485-xx_cc*45);
          line(37+x_cc*15,481-xx_cc*45,32+x_cc*15,486-xx_cc*45);
          line(32+x_cc*15,485-xx_cc*45,37+x_cc*15,489-xx_cc*45);
          line(32+x_cc*15,486-xx_cc*45,37+x_cc*15,490-xx_cc*45);
          {glava}
          bar(36+x_cc*15,475-xx_cc*45,42+x_cc*15,480-xx_cc*45);
          end;
Procedure Cleaner_R;
          begin
          setfillstyle(1,1);
          {tqlo}
          bar(37+x_c*15,480-xx_c*45,41+x_c*15,492-xx_c*45);
          {kraka}
          bar(41+x_c*15,490-xx_c*45,44+x_c*15,500-xx_c*45);
          bar(36+x_c*15,490-xx_c*45,38+x_c*15,496-xx_c*45);
          bar(32+x_c*15,493-xx_c*45,35+x_c*15,496-xx_c*45);
          {ruce}
          bar(41+x_c*15,484-xx_c*45,46+x_c*15,486-xx_c*45);
          setcolor(1);
          line(37+x_c*15,480-xx_c*45,32+x_c*15,485-xx_c*45);
          line(37+x_c*15,481-xx_c*45,32+x_c*15,486-xx_c*45);
          line(32+x_c*15,485-xx_c*45,37+x_c*15,489-xx_c*45);
          line(32+x_c*15,486-xx_c*45,37+x_c*15,490-xx_c*45);
          {glava}
          bar(36+x_c*15,475-xx_c*45,42+x_c*15,480-xx_c*45);
          end;
Procedure Frenski_2;
          begin
          setfillstyle(1,5);
          {tqlo}
          bar(36+3*15,482-4*45,42+3*15,492-4*45);
          {kraka}
          bar(32+3*15,490-4*45,36+3*15,500-4*45);
          bar(42+3*15,490-4*45,46+3*15,500-4*45);
          {ruce}
          bar(31+3*15,482-4*45,47+3*15,485-4*45);
          {glava}
          bar(35+3*15,475-4*45,43+3*15,482-4*45);
          end;
Procedure Frenski_1;
          begin
          setfillstyle(1,5);
          {tqlo}
          bar(36+1*15,482-4*45,42+1*15,492-4*45);
          {kraka}
          bar(32+1*15,490-4*45,36+1*15,500-4*45);
          bar(42+1*15,490-4*45,46+1*15,500-4*45);
          {ruce}
          bar(31+1*15,482-4*45,47+1*15,485-4*45);
          {glava}
          bar(35+1*15,475-4*45,43+1*15,482-4*45);
          end;
Procedure cleaner_asleep;
          begin
          setfillstyle(1,11);
          {tqlo}
          bar(36+27*15,482-7*45,42+27*15,492-7*45);
          {kraka}
          bar(32+27*15,490-7*45,36+27*15,500-7*45);
          bar(42+27*15,490-7*45,46+27*15,500-7*45);
          {ruce}
          bar(31+27*15,482-7*45,47+27*15,485-7*45);
          {glava}
          bar(35+27*15,475-7*45,43+27*15,482-7*45);
          end;
Procedure cleaner_asleep_2;
          begin
          setfillstyle(1,11);
          {tqlo}
          bar(36+27*15,482-5*45,42+27*15,492-5*45);
          {kraka}
          bar(32+27*15,490-5*45,36+27*15,500-5*45);
          bar(42+27*15,490-5*45,46+27*15,500-5*45);
          {ruce}
          bar(31+27*15,482-5*45,47+27*15,485-5*45);
          {glava}
          bar(35+27*15,475-5*45,43+27*15,482-5*45);
          end;
Procedure cleaner_asleep_3;
          begin
          setfillstyle(1,11);
          {tqlo}
          bar(36+20*15,482-5*45,42+20*15,492-5*45);
          {kraka}
          bar(32+20*15,490-5*45,36+20*15,500-5*45);
          bar(42+20*15,490-5*45,46+20*15,500-5*45);
          {ruce}
          bar(31+20*15,482-5*45,47+20*15,485-5*45);
          {glava}
          bar(35+20*15,475-5*45,43+20*15,482-5*45);
          end;
Procedure cleaner_asleep_4;
          begin
          setfillstyle(1,11);
          {tqlo}
          bar(36+20*15,482-3*45,42+20*15,492-3*45);
          {kraka}
          bar(32+20*15,490-3*45,36+20*15,500-3*45);
          bar(42+20*15,490-3*45,46+20*15,500-3*45);
          {ruce}
          bar(31+20*15,482-3*45,47+20*15,485-3*45);
          {glava}
          bar(35+20*15,475-3*45,43+20*15,482-3*45);
          end;
Procedure cleaner_stationary_1;
          begin
          setfillstyle(1,11);
          {tqlo}
          bar(36+10*15,482-7*45,42+10*15,492-7*45);
          {kraka}
          bar(32+10*15,490-7*45,36+10*15,500-7*45);
          bar(42+10*15,490-7*45,46+10*15,500-7*45);
          {ruce}
          bar(31+10*15,482-7*45,47+10*15,485-7*45);
          {glava}
          bar(35+10*15,475-7*45,43+10*15,482-7*45);
          end;
Procedure KID;
          begin
          setfillstyle(1,lightgreen);
          {tqlo}
          bar(36+x*15,482-xx*45,42+x*15,492-xx*45);
          {kraka}
          bar(32+x*15,490-xx*45,36+x*15,500-xx*45);
          bar(42+x*15,490-xx*45,46+x*15,500-xx*45);
          {ruce}
          bar(31+x*15,482-xx*45,47+x*15,485-xx*45);
          {glava}
          bar(35+x*15,475-xx*45,43+x*15,482-xx*45);
          end;
Procedure Vote;
          begin
          setbkcolor(black);
          cleardevice;
          settextstyle(defaultfont,horizdir,3);
          setcolor(14);
          outtextxy(60,80,'DID YOU LIKE THE GAME?');
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(20,200,'YES! VERY MUCH!');
          setcolor(8);
          outtextxy(320,200,'NO! THE GAME SUCKS!');
          lqvo:=1;
          dqsno:=0;
          repeat
          repeat
          ch:=readkey;
          until (ch=#75)or(ch=#77)or(ch=#13);
          if (ch=#75)or(ch=#77) then
             if lqvo=1 then
                begin
                lqvo:=0;
                dqsno:=1;
                end
             else
                 begin
                 lqvo:=1;
                 dqsno:=0;
                 end;
          if lqvo=1 then
             begin
             setcolor(lightred);
             outtextxy(20,200,'YES! VERY MUCH!');
             setcolor(8);
             outtextxy(320,200,'NO! THE GAME SUCKS!');
             end
             else
             begin
             setcolor(8);
             outtextxy(20,200,'YES! VERY MUCH!');
             setcolor(lightred);
             outtextxy(320,200,'NO! THE GAME SUCKS!');
             end;
          until ch=#13;
          if lqvo=1 then
             begin
             cleardevice;
             settextstyle(defaultfont,horizdir,3);
             setcolor(lightred);
             outtextxy(200,250,'THANK YOU!');
             delay(2000);
             repeat
             if keypressed then
                readkey;
             until not keypressed;
             settextstyle(defaultfont,horizdir,1);
             setcolor(lightgreen);
             outtextxy(150,420,'Press Any key to get back to the main menu...');
             readkey;
             end
             else
             begin
             cleardevice;
             delay(1000);
             setcolor(lightgreen);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(250,200,'FUCK YOU THEN !!!');
             delay(1000);
             cleardevice;
             settextstyle(defaultfont,horizdir,2);
             outtextxy(200,210,'FUCK YOU THEN !!!');
             delay(1000);
             cleardevice;
             settextstyle(defaultfont,horizdir,3);
             outtextxy(150,220,'FUCK YOU THEN !!!');
             delay(1000);
             cleardevice;
             settextstyle(defaultfont,horizdir,4);
             outtextxy(80,230,'FUCK YOU THEN !!!');
             delay(3000);
             cleardevice;
             doom;
             end;
          end;
Procedure Movement;
          begin                     {75:80:78}
          if ttt>0 then
          ttt:=ttt-1
          else
          if keypressed then
             begin
             tttt:=1;
             TTT:=1;
             ch:=readkey;
             case ord(ch) of
             75: begin
                 if x>1 then
                    if (xx=2)or(xx=4)or(xx=6) then
                       begin
                       if (x=2)or(x=3) then
                          begin
                          putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                          x:=x-1;
                          KID_L;
                          end;
                       end
                       else
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       x:=x-1;
                       KID_L;
                       end;
                 end;
             77: begin
                 if x<37 then
                    if (xx=2)or(xx=4)or(xx=6) then
                       begin
                       if (x=1)or(x=2) then
                          begin
                          putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                          x:=x+1;
                          KID_r;
                          end;
                       end
                    else
                    begin
                    putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                    x:=x+1;
                    KID_r;
                    end;
                 end;
             72: begin
                 if (xx=2)or(xx=4)or(xx=6) then
                    begin
                    if x=37 then
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       x:=x-3;
                       xx:=xx+1;
                       ttt:=8;
                       KID_L;
                       end
                       else
                       if x=3 then
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       xx:=xx+1;
                       ttt:=8;
                       KID;
                       end;
                    end
                    else
                    if x=1 then
                       begin
                       if xx<7 then
                          begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       xx:=xx+1;
                       ttt:=8;
                       KID;
                           end;
                       end
                       else
                       if (x=34)and(xx<7) then
                           begin
                           putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                           xx:=xx+1;
                           ttt:=8;
                           x:=x+3;
                           KID_r;
                           end;
                 end;
             80: begin
                 if (xx=7)or(xx=5)or(xx=3) then
                    begin
                    if x=3 then
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       xx:=xx-1;
                       ttt:=8;
                       KID;
                       end
                    else
                    if x=34 then
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       x:=x+3;
                       xx:=xx-1;
                       ttt:=8;
                       KID_r;
                       end;
                    end
                    else
                    if (x=1)and(xx>1) then
                       begin
                       putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                       xx:=xx-1;
                       ttt:=8;
                       KID;
                       end
                       else
                       if x=37 then
                          begin
                          putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                          x:=x-3;
                          xx:=xx-1;
                          ttt:=8;
                          KID_L;
                          end;
                 end;
             end;
             end
             else
             if tttt=1 then
                begin
                putimage(31+x*15,470-xx*45, PP[x,xx]^ , NormalPut);
                KID;
                tttt:=0;
                end;
          end;
Procedure lvl10;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(200,200,'FIND MR FRENSKI AND KILL HIM !!!');
          outtextxy(70,220,'Note that he is bulletproof so you might have to shoot something');
          outtextxy(70,240,'else instead of him in order to kill him... Fint an alternative!');
          outtextxy(70,260,'Use the arrow keys to point the cursor at Mr Frenski.');
          outtextxy(200,280,'Press Enter to shoot...');
          outtextxy(70,400,'You may quit the level any time you want by pressing Esc...');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          x:=31;
          xx:=7;
          KID;
          tttt:=1;
          ttt:=0;
          success:=0;
          x1:=320;
          x2:=200;
          repeat
          Movement;
          if ((x=7)or(x=8))and(xx=3) then
             begin
             delay(1000);
             setbkcolor(black);
             cleardevice;
             setfillstyle(1,lightgreen);
             bar(280,350,360,400);
             bar(290,400,350,480);
             bar(250,410,390,440);
             bar(250,440,270,480);
             bar(370,410,390,320);
             setfillstyle(1,8);
             bar(373,325,387,285);
             bar(378,285,382,278);
             repeat
             setfillstyle(1,red);
             bar(295,10,345,45);
             bar(300,45,340,100);
             bar(290,90,315,150);
             bar(325,90,350,150);
             bar(250,50,390,70);
             setfillstyle(1,8);
                               {VODKA}
                               bar(235,40,250,60);
                               bar(240,35,245,40);
                               setcolor(lightred);
                               outtextxy(230,30,'Vodka');
                               {KRAI VODKA}
             if keypressed then
             begin
             ch:=readkey;
             if ch=#13 then
                if (x1<251)and(x1>234)and(x2<61)and(x2>39) then
                   begin
                   success:=1;
                   setfillstyle(1,6);
                   bar(100,10,500,200);
                   delay(500);
                   setfillstyle(1,14);
                   bar(180,40,420,160);
                   delay(500);
                   setfillstyle(1,4);
                   bar(250,70,350,120);
                   delay(500);
                   end;
             if ch=#72 then
                if x2>5 then
                   x2:=x2-2;
             if ch=#80 then
                if x2<250 then
                   x2:=x2+2;
             if ch=#75 then
                if x1>5 then
                   x1:=x1-2;
             if ch=#77 then
                if x1<635 then
                   x1:=x1+2;
             if ch=#27 then
                success:=2;
             end;
             setcolor(14);
             line(x1,x2-5,x1,x2+5);
             line(x1-5,x2,x1+5,x2);
             delay(10);
             setcolor(black);
             line(x1,x2-5,x1,x2+5);
             line(x1-5,x2,x1+5,x2);
             until (success=1)or(success=2);
             end;
          delay(70);
          until (ch=#27)or(success=1)or(success=2);
          if success=1 then
             begin
             delay(1000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(220,140,'MR FRENSKI''S VODKA EXPLODED!');
             outtextxy(220,160,'YOU JUST KILLED MR FRENSKI!');
             outtextxy(200,180,'YOU ARE BORN TO RUN AWAY FROM CLASS!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to vote wether you like the game ');
             outtextxy(150,460,'or not or Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             if ch=#13 then Vote;
             end;
          end;
Procedure lvl9;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In this level you have to escape from psycological class again');
          outtextxy(70,240,'which is on the first floor and like before there is a cleaner on');
          outtextxy(70,260,'the same floor. There are 2 patrolling cleaners and 1 sleeping');
          outtextxy(70,280,'on the second floor. Beware because one of the cleaners is patrolling');
          outtextxy(70,300,'on the third and the fourth floor at goes through the stairs to');
          outtextxy(70,320,'change the floor. He is slow so you can follow him on the fourth');
          outtextxy(70,340,'floor to get pass the fast cleaner on the third floor. You will ');
          outtextxy(70,360,'need the binoculars again on the second floor in the girl''s bathroom.');
          outtextxy(120,380,'   You have 75 seconds to complete the level.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          gettime(h,m,ss,hund);
          long1:=ss+m*60+h*3600;
          success_2:=0;
          success:=0;
          x:=30;
          xx:=1;
          SLIZANE:=0;
          KACHVANE:=0;
          x_c:=20;
          xx_c:=5;
          x_cc:=round(random(35));
          xx_cc:=5;
          x_ccc:=24;
          xx_ccc:=1;
          l_ccc:=1;
          r_ccc:=0;
          l_cc:=1;
          R_cc:=0;
          l_c:=1;
          r_c:=0;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
if ccc=0 then
begin
ccc:=6;
putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=34 then
                begin
                if xx_c=5 then
                   begin
                   KACHVANE:=1;
                   SLIZANE:=0;
                   xx_c:=6;
                   x_c:=37;
                   end;
                if xx_c=7 then
                   begin
                   KACHVANE:=0;
                   SLIZANE:=1;
                   xx_c:=6;
                   x_c:=37;
                   end;
                end
                else
                if x_c=37 then
                   if kachvane=1 then
                      begin
                      l_c:=1;
                      r_c:=0;
                      x_c:=34;
                      xx_c:=7;
                      kachvane:=0;
                      slizane:=0;
                      end
                      else
                      begin
                      l_c:=1;
                      r_c:=0;
                      x_c:=34;
                      xx_c:=5;
                      kachvane:=0;
                      slizane:=0;
                      end
                   else
                   x_c:=x_c+1;
                end;
             if success=0 then
             begin
             if (xx=6)and(x=37)and(xx_c=5) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             if ((xx=5)and(xx_c=5))or((xx=7)and(xx_c=7)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             end;
             if success=1 then
             begin
             if ((xx=6)and(x=37))or((xx=4)and(x=37)and(xx_c=5)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             if ((xx=5)and(xx_c=5))or((xx=7)and(xx_c=7)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             end;
             if l_c=1 then
             begin
             putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                x_c:=x_c-1;
                if success=0 then
             begin
             if (xx=6)and(x=37)and(xx_c=5) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             if ((xx=5)and(xx_c=5))or((xx=7)and(xx_c=7)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             end;
             if success=1 then
             begin
             if ((xx=6)and(x=37))or((xx=4)and(x=37)and(xx_c=5)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             if ((xx=5)and(xx_c=5))or((xx=7)and(xx_c=7)) then
                if r_c=0 then
                   Cleaner_l
                   else
                   Cleaner_r;
             end;

             end;
end_cleaner:;
end
else
ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=2;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=2;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          if (x=37)and(xx=3) then
             begin
             success:=1;
             settextstyle(defaultfont,horizdir,1);
             setcolor(white);
             outtextxy(5,20,'Binoculars');
             end;
          if (xx=3)and((x=19)or(x=20)or(x=21)) then
             begin
             delay(1000);
             goto gg;
             end;
          if (xx=3)or((xx=4)and(x=37)) then
          cleaner_asleep_4
          else
          putimage(31+20*15,470-3*45, PP[20,3]^ , NormalPut);
          gettime(h,m,ss,hund);
          long2:=ss+m*60+h*3600;
          if (75+long1-long2)=0 then
             goto gg
             else
             begin
             if (75+long1-long2)>9 then
                begin
                case (75+long1-long2)div 10 of
                1: begin sss:='1'; end;
                2: begin sss:='2'; end;
                3: begin sss:='3'; end;
                4: begin sss:='4'; end;
                5: begin sss:='5'; end;
                6: begin sss:='6'; end;
                7: begin sss:='7'; end;
                8: begin sss:='8'; end;
                9: begin sss:='9'; end;
                end;
                case (75+long1-long2)mod 10 of
                1: sss:=sss+'1';
                2: sss:=sss+'2';
                3: sss:=sss+'3';
                4: sss:=sss+'4';
                5: sss:=sss+'5';
                6: sss:=sss+'6';
                7: sss:=sss+'7';
                8: sss:=sss+'8';
                9: sss:=sss+'9';
                0: sss:=sss+'0';
                end;
                end
                else
                case (75+long1-long2) of
                1: sss:='1';
                2: sss:='2';
                3: sss:='3';
                4: sss:='4';
                5: sss:='5';
                6: sss:='6';
                7: sss:='7';
                8: sss:='8';
                9: sss:='9';
                end;
             setcolor(lightred);
             settextstyle(defaultfont,horizdir,2);
             outtextxy(390,10,'Time left: ');
             setfillstyle(1,8);
             bar(550,10,580,30);
             outtextxy(550,10,sss);
             end;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'HAHAHA   PETIO  VERNO LI ISKA6 1 LEV BE :D:D:D');
             outtextxy(150,170,' OT KUDE DA GO VZEMA BE :D:D:D');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 10 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl10;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(130,150,'You didn''t manage to escape in time. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 9 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl9;
                end;
             end;
          end;
Procedure lvl8;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In this level you have to escape from psycological class which');
          outtextxy(70,240,'is on the first floor but beware because there is a cleaner on');
          outtextxy(70,260,'the same floor. There are 3 patrolling cleaners and 1 sleeping');
          outtextxy(70,280,'on the second floor. You have to go up because the cleaner on');
          outtextxy(70,300,'the first floor is too fast to follow. Use the binoculars from');
          outtextxy(70,320,'the girl''s toilet on the second floor to pass the third floor.');
          outtextxy(70,340,'To get rid of the cleaner on the second floor just go to the');
          outtextxy(70,360,'girl''s toilet on floor 4 to make a mess. You have 50 seconds.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          gettime(h,m,ss,hund);
          long1:=ss+m*60+h*3600;
          success_2:=0;
          success:=0;
          x:=30;
          xx:=1;
          x_c:=10;
          xx_c:=5;
          x_cc:=27;
          xx_cc:=5;
          x_ccc:=24;
          xx_ccc:=1;
          l_ccc:=1;
          r_ccc:=0;
          l_cc:=1;
          R_cc:=0;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=5;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=5;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if success=0 then
             begin
             if (xx=5)or((xx=6)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             end
             else
             if (xx=5)or((xx=6)and(x=37))or((xx=4)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=2;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          if (x=37)and(xx=3) then
             begin
             success:=1;
             settextstyle(defaultfont,horizdir,1);
             setcolor(white);
             outtextxy(5,20,'Binoculars');
             end;
          if (x=37)and(xx=7) then
             success_2:=1;
          IF success_2=0 then
          begin
          if (xx=3)and((x=19)or(x=20)or(x=21)) then
             begin
             delay(1000);
             goto gg;
             end;
          if (xx=3)or((xx=4)and(x=37)) then
          cleaner_asleep_4
          else
          putimage(31+20*15,470-3*45, PP[20,3]^ , NormalPut);
          end;
          gettime(h,m,ss,hund);
          long2:=ss+m*60+h*3600;
          if (50+long1-long2)=0 then
             goto gg
             else
             begin
             if (50+long1-long2)>9 then
                begin
                case (50+long1-long2)div 10 of
                1: begin sss:='1'; end;
                2: begin sss:='2'; end;
                3: begin sss:='3'; end;
                4: begin sss:='4'; end;
                5: begin sss:='5'; end;
                6: begin sss:='6'; end;
                7: begin sss:='7'; end;
                8: begin sss:='8'; end;
                9: begin sss:='9'; end;
                end;
                case (50+long1-long2)mod 10 of
                1: sss:=sss+'1';
                2: sss:=sss+'2';
                3: sss:=sss+'3';
                4: sss:=sss+'4';
                5: sss:=sss+'5';
                6: sss:=sss+'6';
                7: sss:=sss+'7';
                8: sss:=sss+'8';
                9: sss:=sss+'9';
                0: sss:=sss+'0';
                end;
                end
                else
                case (50+long1-long2) of
                1: sss:='1';
                2: sss:='2';
                3: sss:='3';
                4: sss:='4';
                5: sss:='5';
                6: sss:='6';
                7: sss:='7';
                8: sss:='8';
                9: sss:='9';
                end;
             setcolor(lightred);
             settextstyle(defaultfont,horizdir,2);
             outtextxy(390,10,'Time left: ');
             setfillstyle(1,8);
             bar(550,10,580,30);
             outtextxy(550,10,sss);
             end;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 8!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 9 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl9;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(130,150,'You didn''t manage to escape in time. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 8 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl8;
                end;
             end;
          end;
Procedure lvl7;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the seventh level you have to run away from IT class again');
          outtextxy(70,240,'which is on the third floor. There are 5 cleaners and only 3');
          outtextxy(70,260,'are patrolling. One is asleep and one is just resting on the');
          outtextxy(70,280,'fourth floor. What you have to do is go to the girl''s toilet');
          outtextxy(70,300,'on the first floor and then the cleaner on the fourth floor');
          outtextxy(70,320,'will go to clean the mess you just made on the first floor.');
          outtextxy(70,340,'You don''t have a time limit because this level requires quite');
          outtextxy(70,360,'a lot of thinking. Also note that cleaners are very fast...');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          success:=0;
          x:=25;
          xx:=5;
          x_c:=10;
          xx_c:=3;
          x_cc:=20;
          xx_cc:=3;
          x_ccc:=round(random(36));
          xx_ccc:=1;
          l_ccc:=0;
          r_ccc:=1;
          l_cc:=0;
          R_cc:=1;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=3;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=3;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=2;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          if (xx=5)and((x=19)or(x=20)or(x=21)) then
             begin
             delay(1000);
             goto gg;
             end;
          if (xx=5)or((xx=6)and(x=37)) then
          cleaner_asleep_3
          else
          putimage(31+20*15,470-5*45, PP[20,5]^ , NormalPut);
          if (x=37)and(xx=1) then
             success:=1;
          if (success=0)and(xx=7) then
                begin
                cleaner_stationary_1;
                delay(1000);
                goto gg;
                end;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 7!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 8 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl8;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(130,150,'You were caught by a cleaner. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 7 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then
                lvl7;
                end;
             end;
          end;
Procedure lvl6;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the sixth level you have to run away from programming class');
          outtextxy(70,240,'which is on the third floor. There are 4 cleaners and only 3');
          outtextxy(70,260,'are patrolling. The fourth is asleep again. There is only 1 way');
          outtextxy(70,280,'of completing the level. However you have 1 minute to escape.');
          outtextxy(70,300,'Cleaners are smarter now and 2 of them are together but they');
          outtextxy(70,320,'aren''t fast like in the last level but a little slower.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          gettime(h,m,ss,hund);
          long1:=ss+m*60+h*3600;
          x:=1;
          xx:=5;
          x_c:=10;
          xx_c:=3;
          x_cc:=27;
          xx_cc:=3;
          x_ccc:=round(random(36));
          xx_ccc:=7;
          l_ccc:=0;
          r_ccc:=1;
          l_cc:=1;
          R_cc:=0;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=4;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=4;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=5;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if xx=7 then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if xx=7 then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          if (xx=5)and((x=26)or(x=27)or(x=28)) then
             begin
             delay(1000);
             goto gg;
             end;
          if (xx=5)or((xx=6)and(x=37)) then
          cleaner_asleep_2
          else
          putimage(31+27*15,470-5*45, PP[27,5]^ , NormalPut);
          gettime(h,m,ss,hund);
          long2:=ss+m*60+h*3600;
          if (60+long1-long2)=0 then
             goto gg
             else
             begin
             if (60+long1-long2)>9 then
                begin
                case (60+long1-long2)div 10 of
                1: begin sss:='1'; end;
                2: begin sss:='2'; end;
                3: begin sss:='3'; end;
                4: begin sss:='4'; end;
                5: begin sss:='5'; end;
                6: begin sss:='6'; end;
                7: begin sss:='7'; end;
                8: begin sss:='8'; end;
                9: begin sss:='9'; end;
                end;
                case (60+long1-long2)mod 10 of
                1: sss:=sss+'1';
                2: sss:=sss+'2';
                3: sss:=sss+'3';
                4: sss:=sss+'4';
                5: sss:=sss+'5';
                6: sss:=sss+'6';
                7: sss:=sss+'7';
                8: sss:=sss+'8';
                9: sss:=sss+'9';
                0: sss:=sss+'0';
                end;
                end
                else
                case (60+long1-long2) of
                1: sss:='1';
                2: sss:='2';
                3: sss:='3';
                4: sss:='4';
                5: sss:='5';
                6: sss:='6';
                7: sss:='7';
                8: sss:='8';
                9: sss:='9';
                end;
             setcolor(lightred);
             settextstyle(defaultfont,horizdir,2);
             outtextxy(390,10,'Time left: ');
             setfillstyle(1,8);
             bar(550,10,580,30);
             outtextxy(550,10,sss);
             end;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 6!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 7 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl7;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(130,150,'You didn''t manage to escape in time. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 6 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl6;
                end;
             end;
          end;
Procedure lvl5;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the fifth level you have to run away from Electronics class');
          outtextxy(70,240,'which is on the fourth floor. There are only 3 cleaners patrolling');
          outtextxy(70,260,'on the other three floors without hidden surprises like your');
          outtextxy(70,280,'dearest Mr Frenski. However you have only 1 minute to escape');
          outtextxy(70,300,'and the cleaners are moving a little more rapidly and start from');
          outtextxy(70,320,'a random location. The cleaner on the first floor is the fastest.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          gettime(h,m,ss,hund);
          long1:=ss+m*60+h*3600;
          x:=30;
          xx:=7;
          x_c:=round(random(36));
          xx_c:=3;
          x_cc:=round(random(36));
          xx_cc:=1;
          x_ccc:=round(random(36));
          xx_ccc:=5;
          l_ccc:=1;
          r_ccc:=0;
          l_cc:=1;
          R_cc:=0;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=4;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=3;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=4;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if (xx=5)or((xx=6)and(x=37)) then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if (xx=5)or((xx=6)and(x=37)) then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          gettime(h,m,ss,hund);
          long2:=ss+m*60+h*3600;
          if (60+long1-long2)=0 then
             goto gg
             else
             begin
             if (60+long1-long2)>9 then
                begin
                case (60+long1-long2)div 10 of
                1: begin sss:='1'; end;
                2: begin sss:='2'; end;
                3: begin sss:='3'; end;
                4: begin sss:='4'; end;
                5: begin sss:='5'; end;
                6: begin sss:='6'; end;
                7: begin sss:='7'; end;
                8: begin sss:='8'; end;
                9: begin sss:='9'; end;
                end;
                case (60+long1-long2)mod 10 of
                1: sss:=sss+'1';
                2: sss:=sss+'2';
                3: sss:=sss+'3';
                4: sss:=sss+'4';
                5: sss:=sss+'5';
                6: sss:=sss+'6';
                7: sss:=sss+'7';
                8: sss:=sss+'8';
                9: sss:=sss+'9';
                0: sss:=sss+'0';
                end;
                end
                else
                case (60+long1-long2) of
                1: sss:='1';
                2: sss:='2';
                3: sss:='3';
                4: sss:='4';
                5: sss:='5';
                6: sss:='6';
                7: sss:='7';
                8: sss:='8';
                9: sss:='9';
                end;
             setcolor(lightred);
             settextstyle(defaultfont,horizdir,2);
             outtextxy(390,10,'Time left: ');
             setfillstyle(1,8);
             bar(550,10,580,30);
             outtextxy(550,10,sss);
             end;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 5!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 6 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl6;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(130,150,'You didn''t manage to escape in time. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 5 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl5;
                end;
             end;
          end;
Procedure lvl4;
          label GG,end_cleaner,end_cleanerr,end_cleanerrr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the fourth level you have to run away from biology class and');
          outtextxy(70,240,'this time there are cleaners all over the school patrolling so that');
          outtextxy(70,260,'they can get you and send you back to class but the cleaner on');
          outtextxy(70,280,'the fourth floor won''t be bothering you because he is asleep.');
          outtextxy(70,300,'However, don''t go near him if you don''t want to wake him up.');
          outtextxy(70,320,'Also have in mind that Frenski might be somewhere on the stairs.');
          outtextxy(70,340,'Find your way through this jungle to advance to the next level.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          x:=10;
          xx:=7;
          x_c:=1;
          xx_c:=3;
          x_cc:=10;
          xx_cc:=1;
          x_ccc:=15;
          xx_ccc:=5;
          l_ccc:=1;
          r_ccc:=0;
          l_cc:=1;
          R_cc:=0;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccccc:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=7;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=7;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          if ccccc=0 then
          begin
          ccccc:=7;
          putimage(31+x_ccc*15,470-xx_ccc*45, PP[x_ccc,xx_ccc]^ , NormalPut);
          if r_ccc=1 then
             begin
             if (x>=x_ccc)and(xx=xx_ccc) then
                begin
                cleaner_rrr;
                delay(2000);
                goto GG;
                end;
             if x_ccc=37 then
                   begin
                   r_ccc:=0;
                   l_ccc:=1;
                   end
                   else
                   begin
                   x_ccc:=x_ccc+1;
                   end;
             if (xx=5)or((xx=6)and(x=37)) then
                if r_ccc=0 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          if l_ccc=1 then
             begin
             if (x<=x_ccc)and(xx=xx_ccc) then
                begin
                Cleaner_lll;
                delay(2000);
                goto GG;
                end;
             if x_ccc=1 then
                begin
                r_ccc:=1;
                l_ccc:=0;
                end
                else
                begin
                x_ccc:=x_ccc-1;
                end;
             if (xx=5)or((xx=6)and(x=37)) then
                if l_ccc=1 then
                   Cleaner_lll
                else
                   Cleaner_rrr;
             goto end_cleanerrr;
             end;
          end_cleanerrr:;
          end
          else
          ccccc:=ccccc-1;
          if (xx=7)and((x=26)or(x=27)or(x=28)) then
             begin
             delay(1000);
             goto GG;
             end;
          if (x=3)and(xx=4) then
             begin
             frenski_1;
             delay(1000);
             goto gg;
             end;
          if (x=1)and(xx=4) then
             begin
             frenski_2;
             delay(1000);
             goto gg;
             end;
          if xx=7 then
          cleaner_asleep
          else
          putimage(31+27*15,470-7*45, PP[27,7]^ , NormalPut);
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 4!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 5 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl5;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(150,150,'You didn''t manage to escape. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 4 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl4;
                end;
             end;
          end;
Procedure lvl3;
          label GG,end_cleaner,end_cleanerr;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the third level you have to run away from literature class and');
          outtextxy(70,240,'this time there are two cleaners patrolling on the second and the');
          outtextxy(70,260,'first floor so you have to find the right time to slip behind');
          outtextxy(70,280,'them without being spotted. You can''t see people on the other');
          outtextxy(70,300,'floors like in the real world.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          x:=25;
          xx:=5;
          x_c:=1;
          xx_c:=3;
          x_cc:=10;
          xx_cc:=1;
          l_cc:=1;
          R_cc:=0;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          cccc:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=7;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          if cccc=0 then
          begin
          cccc:=7;
          putimage(31+x_cc*15,470-xx_cc*45, PP[x_cc,xx_cc]^ , NormalPut);
          if r_cc=1 then
             begin
             if (x>=x_cc)and(xx=xx_cc) then
                begin
                cleaner_rr;
                delay(2000);
                goto GG;
                end;
             if x_cc=37 then
                   begin
                   r_cc:=0;
                   l_cc:=1;
                   end
                   else
                   begin
                   x_cc:=x_cc+1;
                   end;
             if (xx=1)or((xx=2)and(x=37)) then
                if r_cc=0 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          if l_cc=1 then
             begin
             if (x<=x_cc)and(xx=xx_cc) then
                begin
                Cleaner_ll;
                delay(2000);
                goto GG;
                end;
             if x_cc=1 then
                begin
                r_cc:=1;
                l_cc:=0;
                end
                else
                begin
                x_cc:=x_cc-1;
                end;
             if (xx=1)or((xx=2)and(x=37)) then
                if l_cc=1 then
                   Cleaner_ll
                else
                   Cleaner_rr;
             goto end_cleanerr;
             end;
          end_cleanerr:;
          end
          else
          cccc:=cccc-1;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 3!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 4 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl4;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(150,150,'You didn''t manage to escape. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 3 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl3;
                end;
             end;
          end;
Procedure lvl2;
          label GG,end_cleaner;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the second level you have to run away from IT class and');
          outtextxy(70,240,'this time one of the cleaners is patrolling on the second');
          outtextxy(70,260,'floor so you have to find the right time to slip behind');
          outtextxy(70,280,'the cleaner without being spotted. You can''t see people');
          outtextxy(70,300,'on the other floors so escaping depends on luck this time.');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          x:=25;
          xx:=5;
          x_c:=1;
          xx_c:=3;
          l_c:=0;
          r_c:=1;
          KID;
          tttt:=1;
          ttt:=0;
          ccc:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          if ccc=0 then
          begin
          ccc:=7;
          putimage(31+x_c*15,470-xx_c*45, PP[x_c,xx_c]^ , NormalPut);
          if r_c=1 then
             begin
             if (x>=x_c)and(xx=xx_c) then
                begin
                cleaner_r;
                delay(2000);
                goto GG;
                end;
             if x_c=37 then
                   begin
                   r_c:=0;
                   l_c:=1;
                   end
                   else
                   begin
                   x_c:=x_c+1;
                   end;
             if (xx=3)or((xx=4)and(x=37)) then
                if r_c=0 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          if l_c=1 then
             begin
             if (x<=x_c)and(xx=xx_c) then
                begin
                Cleaner_l;
                delay(2000);
                goto GG;
                end;
             if x_c=1 then
                begin
                r_c:=1;
                l_c:=0;
                end
                else
                begin
                x_c:=x_c-1;
                end;
             if (xx=3)or((xx=4)and(x=37)) then
                if l_c=1 then
                   Cleaner_l
                else
                   Cleaner_r;
             goto end_cleaner;
             end;
          end_cleaner:;
          end
          else
          ccc:=ccc-1;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(2000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 2!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 3 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl3;
             end
             else
             begin
             if ord(ch)<>27 then
                begin
                GG:;
                cleardevice;
                setbkcolor(black);
                settextstyle(defaultfont,horizdir,2);
                setcolor(lightred);
                outtextxy(250,100,nick);
                settextstyle(defaultfont,horizdir,1);
                outtextxy(150,150,'You were spotted by the cleaner. Game Over!');
                delay(2500);
                repeat
                if keypressed then readkey;
                until not keypressed;
                setcolor(lightgreen);
                outtextxy(150,440,'Press Enter to start level 2 over again or');
                outtextxy(150,460,'press Escape to return to the Main menu.');
                repeat
                ch:=readkey;
                until (ch=#27)or(ch=#13);
                if ord(ch)=13 then lvl2;
                end;
             end;
          end;
Procedure LVL1;
          begin
          cleardevice;
          setbkcolor(black);
          reset(ff);
          read(ff,s);
          nick:=s.name;
          settextstyle(defaultfont,horizdir,2);
          setcolor(lightred);
          outtextxy(250,100,s.name);
          settextstyle(defaultfont,horizdir,1);
          setcolor(white);
          outtextxy(70,220,'In the first level you have to run away from math class and');
          outtextxy(70,240,'it should be quite easy because there are no people outside');
          outtextxy(70,260,'the rooms.All you have to do is go to the exit!');
          outtextxy(70,420,'You may quit the level any time you want by pressing Escape.');
          delay(3000);
          repeat
          if keypressed then
          readkey;
          until not keypressed;
          setcolor(lightgreen);
          outtextxy(200,460,'Press any key to continue...');
          readkey;
          WORLD_stated;
          FLOOR_1;
          FLOOR_2;
          FLOOR_3;
          FLOOR_4;
          STAIRS;
          if initiated=0 then
          begin
          size:=imagesize(0,0,17,30);
          for xx:=1 to 7 do
              for x:=1 to 37 do
                  begin
                  getmem(PP[x,xx],size);
                  getimage(31+x*15,470-xx*45,48+x*15,500-xx*45, PP[x,xx]^);
                  end;
          initiated:=1;
          end;
          x:=31;
          xx:=7;
          KID;
          tttt:=1;
          ttt:=0;                       {72}
          repeat                     {75:80:78}
          Movement;
          delay(70);
          until (ch=#27)or((xx=1)and((x=1)or(x=2)));
          if (xx=1)and((x=1)or(x=2)) then
             begin
             delay(1000);
             nick:=s.name;
             cleardevice;
             setbkcolor(black);
             settextstyle(defaultfont,horizdir,2);
             setcolor(lightred);
             outtextxy(250,100,nick);
             settextstyle(defaultfont,horizdir,1);
             outtextxy(150,150,'Congratulations! You just passed level 1!');
             delay(2500);
             repeat
             if keypressed then readkey;
             until not keypressed;
             setcolor(lightgreen);
             outtextxy(150,440,'Press Enter to continue with level 2 or');
             outtextxy(150,460,'press Escape to return to the Main menu.');
             repeat
             ch:=readkey;
             until (ch=#27)or(ch=#13);
             reset(f);
             repeat
             read(f,s);
             until s.name=nick;
             seek(f,filepos(f)-1);
             s.maxlvl:=s.maxlvl+1;
             write(f,s);
             close(ff);
             close(f);
             if ch=#13 then lvl2;
             end;
          end;
Procedure WELCOME;
          begin
          setbkcolor(5);
          settextstyle(defaultfont,horizdir,3);
          for i:=1 to 125 do
              begin
              if keypressed then
                 begin
                 ch:=readkey;
                 if ord(ch)=27 then i:=125;
                 end;
              setcolor(1);
              settextstyle(defaultfont,horizdir,1);
              outtextxy(100,50,'Press Esc To Skip.');
              settextstyle(defaultfont,horizdir,3);
              outtextxy(-200+i*8,160,'Welcome to');
              setcolor(4);
              outtextxy(-300+i*8,240,'"ESCAPE FROM TUES"');
              setcolor(green);
              circle(350,300,20);
              line(350,320,320,360);
              line(320,360,360,370);
              line(320,360,280,390);
              line(360,370,380,400);
              line(280,390,260,360);
              line(260,360,250,370);
              line(380,400,388,388);
              line(335,340,380,340);
              line(335,340,300,345);
              line(380,340,410,295);
              line(300,345,285,370);
              circle(410,292,3);
              circle(285,373,3);
              setcolor(8);
              line(350,280,280,280);
              line(380,400,300,400);
              line(260,360,200,360);
              line(410,289,330,289);
              delay(80);
              cleardevice;
              end;
          repeat
          if keypressed then readkey;
          until not keypressed;
          end;
Procedure MAINMENU;
          Procedure Pr1;
                    begin
                    cleardevice;
                    settextstyle(defaultfont,horizdir,1);
                    setcolor(white);
                    outtextxy(100,460,'To cheat or vote for the game see the information.');
                    setcolor(green);
                    circle(180,90,40);
                    line(140,100,100,260);
                    line(100,260,80,450);
                    line(100,260,120,450);
                    line(120,180,110,300);
                    line(120,180,130,300);
                    line(80,450,100,450);
                    line(120,450,140,450);
                    circle(110,305,5);
                    circle(130,305,5);
                    setcolor(white);
                    fillellipse(200,140,5,5);
                    fillellipse(195,170,8,8);
                    ellipse(192,220,0,360,30,20);
                    ellipse(192,220,0,360,31,21);
                    settextstyle(defaultfont,horizdir,1);
                    outtextxy(170,220,'Why...');
                    settextstyle(defaultfont,horizdir,2);
                    setcolor(7);
                    outtextxy(250,80, '_.:  New Game   :._');
                    setcolor(green);
                    ellipse(400,90,0,360,180,30);
                    setcolor(8);
                    outtextxy(250,160,'_.:  Load Game  :._');
                    outtextxy(250,240,'_.: Information :._');
                    outtextxy(250,320,'_.:    Intro    :._');
                    outtextxy(250,400,'_.:    Exit     :._');
                    end;
          Procedure Pr2;
                    begin
                    cleardevice;
                    settextstyle(defaultfont,horizdir,1);
                    setcolor(white);
                    outtextxy(100,460,'To cheat or vote for the game see the information.');setcolor(green);
                    circle(130,56,40);
                    line(110,90,100,260);
                    line(100,260,80,450);
                    line(100,260,120,450);
                    line(105,175,225,185);
                    line(105,175,130,280);
                    line(80,450,100,450);
                    line(120,450,140,450);
                    circle(230,185,5);
                    circle(131,285,5);
                    setcolor(white);
                    fillellipse(180,40,5,5);
                    fillellipse(200,32,8,8);
                    ellipse(265,25,0,360,45,18);
                    settextstyle(defaultfont,horizdir,1);
                    outtextxy(229,22,'Why not...');
                    settextstyle(defaultfont,horizdir,2);
                    setcolor(8);
                    outtextxy(250,80, '_.:  New Game   :._');
                    setcolor(7);
                    outtextxy(250,160,'_.:  Load Game  :._');
                    setcolor(green);
                    ellipse(400,170,0,360,180,30);
                    setcolor(8);
                    outtextxy(250,240,'_.: Information :._');
                    outtextxy(250,320,'_.:    Intro    :._');
                    outtextxy(250,400,'_.:    Exit     :._');
                    end;
          Procedure Pr3;
                    begin
                    cleardevice;
                    settextstyle(defaultfont,horizdir,1);
                    setcolor(white);
                    outtextxy(100,460,'To cheat or vote for the game see the information.');
                    setcolor(green);
                    circle(80,50,40);
                    line(82,90,100,260);
                    line(91,185,150,140);
                    line(150,140,160,80);
                    line(91,185,210,250);
                    line(100,260,80,450);
                    line(100,260,120,450);
                    line(80,450,100,450);
                    line(120,450,140,450);
                    circle(215,250,5);
                    setcolor(white);
                    fillellipse(130,40,6,6);
                    fillellipse(163,77,8,3);
                    fillellipse(160,71,2,8);
                    fillellipse(155,35,10,10);
                    ellipse(300,30,0,360,120,25);
                    settextstyle(defaultfont,horizdir,1);
                    outtextxy(200,25,'I would better see this...');
                    settextstyle(defaultfont,horizdir,2);
                    setcolor(8);
                    outtextxy(250,80, '_.:  New Game   :._');
                    outtextxy(250,160,'_.:  Load Game  :._');
                    setcolor(7);
                    outtextxy(250,240,'_.: Information :._');
                    setcolor(green);
                    ellipse(400,250,0,360,180,30);
                    setcolor(8);
                    outtextxy(250,320,'_.:    Intro    :._');
                    outtextxy(250,400,'_.:    Exit     :._');
                    end;
          Procedure Pr4;
                    begin
                    cleardevice;
                    settextstyle(defaultfont,horizdir,1);
                    setcolor(white);
                    outtextxy(100,460,'To cheat or vote for the game see the information.');
                    setcolor(green);
                    ellipse(100,100,90,159,40,40);
                    ellipse(100,100,200,270,40,40);
                    ellipse(200,100,270,90,40,40);
                    line(100,60,200,60);
                    line(100,140,200,140);
                    line(20,86,62,86);
                    line(20,114,62,114);
                    ellipse(20,100,0,360,8,14);
                    ellipse(120,60,90,180,20,20);
                    ellipse(180,60,0,90,20,20);
                    line(120,40,180,40);
                    line(140,140,120,220);
                    line(160,140,180,220);
                    setcolor(white);
                    settextstyle(defaultfont,horizdir,2);
                    outtextxy(100,93,'CAMERA');
                    setcolor(8);
                    outtextxy(250,80, '_.:  New Game   :._');
                    outtextxy(250,160,'_.:  Load Game  :._');
                    outtextxy(250,240,'_.: Information :._');
                    setcolor(7);
                    outtextxy(250,320,'_.:    Intro    :._');
                    setcolor(green);
                    ellipse(400,330,0,360,180,30);
                    setcolor(8);
                    outtextxy(250,400,'_.:    Exit     :._');
                    end;
          Procedure Pr5;
                    begin
                    cleardevice;
                    settextstyle(defaultfont,horizdir,1);
                    setcolor(white);
                    outtextxy(100,460,'To cheat or vote for the game see the information.');
                    setcolor(8);
                    setfillstyle(1,7);
                    bar(50,200,180,205);
                    bar(55,190,175,195);
                    bar(60,180,170,185);
                    bar(65,170,165,175);
                    bar(70,160,160,165);
                    bar(75,150,155,155);
                    bar(80,140,150,145);
                    bar(85,130,145,135);
                    bar(90,120,140,125);
                    bar(95,110,135,115);
                    setfillstyle(1,15);
                    bar(95,105,135,45);
                    setcolor(yellow);
                    line(90,105,60,135);
                    line(90,75,40,75);
                    line(90,40,60,10);
                    line(115,40,115,0);
                    line(140,40,170,10);
                    line(140,75,190,75);
                    line(140,105,170,135);
                    setcolor(5);
                    settextstyle(defaultfont,horizdir,2);
                    outtextxy(40,400,'DARKNESS');
                    setcolor(8);
                    outtextxy(250,80, '_.:  New Game   :._');
                    outtextxy(250,160,'_.:  Load Game  :._');
                    outtextxy(250,240,'_.: Information :._');
                    outtextxy(250,320,'_.:    Intro    :._');
                    setcolor(7);
                    outtextxy(250,400,'_.:    Exit     :._');
                    setcolor(green);
                    ellipse(400,410,0,360,180,30);
                    setcolor(8);
                    end;
          Procedure Red;
                    begin
                    setfillstyle(1,lightred);
                    bar(5,23*JJ+15,15,23*JJ+10);
                    end;
          Procedure Blackk;
                    begin
                    setfillstyle(1,lightblue);
                    bar(5,23*jj+15,15,23*jj+10);
                    end;
          Procedure Bluee;
                    begin
                    setfillstyle(1,lightblue);
                    for i:=1 to 20 do bar(5,23*i+15,15,23*i+10);
                    end;
          Label TUT;
          Begin
          cleardevice;
          setbkcolor(black);
          settextstyle(defaultfont,horizdir,2);
          pr1;
          y:=1;
          repeat
          case pam of
          1: pr1;
          2: pr2;
          3: pr3;
          4: pr4;
          end;
          repeat
	    repeat
              ch:=readkey;
            until (ch=#0)or(ch=#13);
            repeat
                  if ch<>#13 then ch:=readkey;
            until (ch=#72)or(ch=#80)or(ch=#13);
            L1:=0;
            delay(50);
            repeat
            if keypressed then readkey;
            until not keypressed;
            if (ch=#72)and(y>1) then
                         begin;
                         y:=y-1;
                         L1:=1;
                         end;
            if (ch=#80)and(y<5) then
                         begin;
                         y:=y+1;
                         L1:=1;
                         end;
            if (ch=#72)and(y=1)and(L1=0) then y:=5;
            if (ch=#80)and(y=5)and(L1=0) then y:=1;
            L1:=0;
            case y of
            1: pr1;
            2: pr2;
            3: pr3;
            4: pr4;
            5: pr5;
            end;
            until ch=#13;
            case y of
            1: begin
               pam:=1;
               {$I-}
               reset(f);
               {$I+}
               if ioresult<>0 then rewrite(f);
               cleardevice;
               if filesize(f)=20 then
                  begin
                  settextstyle(defaultfont,horizdir,3);
                  setcolor(8);
                  outtextxy(10,230,'NO MORE SLOTS FOR PROFILES');
                  delay(500);
                  repeat
                  if keypressed then readkey;
                  until not keypressed;
                  readkey;
                  end
                  else
               begin
               setbkcolor(black);
               setfillstyle(1,15);
               setcolor(white);
               settextstyle(defaultfont,horizdir,1);
               outtextxy(250,200,'Enter Your Name: ');
               setcolor(lightgreen);
               outtextxy(150,450,'Press Enter To Confirm Or Esc To Cancel.');
               moveto(380,200);
               jj:=1;
               setfillstyle(1,8);
               bar(378,210,525,195);
               repeat
               ch:=readkey;
               if (ord(ch)<>8)and(ord(ch)<>27)and(ord(ch)<>13)and(jj<19) then
                  begin
                  ent:=ent+ch;
                  jj:=jj+1;
                  end;
               if ord(ch)=8 then
                  if jj>1 then
                     begin
                     jj:=jj-1;
                     delete(ent,jj,1);
                     end;
               setfillstyle(1,8);
               bar(378,210,525,195);
               outtextxy(380,200,ent);
               if (jj=1)and(ord(ch)=13) then ch:=chr(76);
               until (ord(ch)=13)or(ord(ch)=27);
               if ord(ch)<>27 then
               begin
               s.name:=ent;
               ent:='';
               s.maxlvl:=1;
               seek(f,filesize(f));
               write(f,s);
               rewrite(ff);
               write(ff,s);
               close(ff);
               LVL1;
               end;
               setfillstyle(1,15);
               setbkcolor(black);
               cleardevice;
               end;
               end;
            2: begin
               TUT:;
               pam:=2;
               {$I-}
               reset(f);
               {$I+}
               if ioresult=0 then
                  begin
                  if filesize(f)>0 then
                  begin
                  cleardevice;
                  setcolor(8);
                  outtextxy(18,10,'SLOT');
                  outtextxy(100,10,'NAME');
                  outtextxy(220,10,'LEVEL');
                  settextstyle(defaultfont,horizdir,1);
                  setcolor(lightgreen);
                  for jj:=1 to 20 do
                      begin
                      outtextxy(20,jj*23+10,'Slot ');
                      case jj of
                      1: ttr:='1';
                      2: ttr:='2';
                      3: ttr:='3';
                      4: ttr:='4';
                      5: ttr:='5';
                      6: ttr:='6';
                      7: ttr:='7';
                      8: ttr:='8';
                      9: ttr:='9';
                      10: ttr:='10';
                      11: ttr:='11';
                      12: ttr:='12';
                      13: ttr:='13';
                      14: ttr:='14';
                      15: ttr:='15';
                      16: ttr:='16';
                      17: ttr:='17';
                      18: ttr:='18';
                      19: ttr:='19';
                      20: ttr:='20';
                      end;
                      outtextxy(70,jj*23+10,ttr);
                      end;
                  setcolor(white);
                  jj:=1;
                  repeat
                  read(f,s);
                  moveto(100,jj*23+10);
                  outtext(s.name);
                  case s.maxlvl of
                  1: ttr:='1';
                  2: ttr:='2';
                  3: ttr:='3';
                  4: ttr:='4';
                  5: ttr:='5';
                  6: ttr:='6';
                  7: ttr:='7';
                  8: ttr:='8';
                  9: ttr:='9';
                  10: ttr:='10';
                  end;
                  setcolor(2);
                  outtextxy(250,jj*23+10,ttr);
                  setcolor(white);
                  jj:=jj+1;
                  until eof(f);
                  setfillstyle(1,lightblue);
                  for JJ:=1 to 20 do bar(5,23*jj+15,15,23*jj+10);
                  settextstyle(defaultfont,horizdir,2);
                  setcolor(8);
                  outtextxy(350,10,'SLOT STATUS:');
                  settextstyle(defaultfont,horizdir,1);
                  setcolor(white);
                  outtextxy(320,410,'Select The Profile You Want With The ');
                  outtextxy(320,425,'Arrow Keys And Press Enter To Continue');
                  outtextxy(320,440,'Or Esc To Quit Any Time You Want To.');
                  outtextxy(320,455,'To Delete A Profile Press Del.');
JJ:=1;
repeat
bluee;
red;
repeat
setfillstyle(1,8);
bar(545,27,630,5);
settextstyle(defaultfont,horizdir,2);
setcolor(lightred);
reset(f);
if JJ<=filesize(f) then
   outtextxy(547,10,'FULL')
   else
   outtextxy(547,10,'EMPTY');
      repeat
            ch:=readkey;
      until (ch=#0)or(ch=#13)or(ch=#27)or(ch=#83);
      repeat
        if (ch<>#13)and(ch<>#27)and(ch<>#83) then
        ch:=readkey;
      until (ch=#72)or(ch=#80)or(ch=#13)or(ord(ch)=27)or(ord(ch)=83);
      L10:=0;
      if (ch=#72)and(jj>1) then
                         begin;
                         Blackk;
                         jj:=jj-1;
                         L10:=1;
                         end;
      if (ch=#80)and(jj<20) then
                         begin;
                         Blackk;
                         jj:=jj+1;
                         L10:=1;
                         end;
      if (ch=#72)and(jj=1)and(L10=0) then
         begin
         blackk;
         jj:=20;
         end;
      if (ch=#80)and(jj=20)and(l10=0) then
         begin
         blackk;
         jj:=1;
         end;
L10:=0;
red;
LL:=0;
until (ch=#13)or(ord(ch)=27)or(ord(ch)=83);
if ord(ch)=83 then
   if JJ<=Filesize(f) then
      begin
      seek(f,filesize(f)-1);
      read(f,s);
      seek(f,jj-1);
      write(f,s);
      seek(f,filesize(f)-1);
      truncate(f);
      goto TUT;
      end;
if ch=#13 then
   if JJ<=filesize(f) then
      begin
      reset(f);
      seek(f,jj-1);
      read(f,s);
      rewrite(ff);
      write(ff,s);
      LL:=1;
      close(f);
      close(ff);
      end;
until (ord(ch)=27)or(LL=1);
                  if LL=1 then
                  case s.maxlvl of
                       1: begin LVL1; end;
                       2: begin lvl2; end;
                       3: begin lvl3; end;
                       4: begin lvl4; end;
                       5: begin lvl5; end;
                       6: begin lvl6; end;
                       7: begin lvl7; end;
                       8: begin lvl8; end;
                       9: begin lvl9; end;
                       10: begin lvl10; end;
                       end;
                  end
                  else
                  begin
                  settextstyle(defaultfont,horizdir,2);
                  setcolor(8);
                  cleardevice;
                  outtextxy(50,230,'NO EXISTING PROFILES TO BE LOADED!');
                  delay(500);
                  repeat
                  if keypressed then readkey;
                  until not keypressed;
                  readkey;
                  end;
               setbkcolor(black);
               cleardevice;
               setfillstyle(1,15);
               end
               else
               begin
                  settextstyle(defaultfont,horizdir,2);
                  setcolor(8);
                  cleardevice;
                  outtextxy(50,230,'NO EXISTING PROFILES TO BE LOADED!');
                  delay(500);
                  repeat
                  if keypressed then readkey;
                  until not keypressed;
                  readkey;
                  end;
               end;
            3: begin
               pam:=3;
               cleardevice;
               {PAGE 1}
               setcolor(white);
               settextstyle(defaultfont,horizdir,1);
               outtextxy(50,20,'1/3');
               settextstyle(defaultfont,horizdir,2);
               setcolor(lightgreen);
               outtextxy(200,30,'MAIN INFORMATION');
               settextstyle(defaultfont,horizdir,1);
               setcolor(white);
               outtextxy(50,100,'-Welcome to the ''Escape From TUES'' information section!');
               outtextxy(50,120,'On page 2 you can see the information how to play the game');
               outtextxy(50,140,'and on page 3 you can see some information about the game');
               outtextxy(50,160,'and it''s creator. To change pages press the UP and DOWN');
               outtextxy(50,180,'arrow keys.');
               outtextxy(50,220,'-To vote wether you like the game or not press Enter.');
               outtextxy(50,260,'-To cheat which means to boost your account maxlevel up');
               outtextxy(50,280,'by 1 press C.');
               page:=1;
               repeat
                     repeat
                     ch:=readkey;
                     until (ch=#13)or(ch=#27)or(ch=#67)or(ch=#99)or(ch=#72)or(ch=#80);
               if ch=#13 then
                  vote;
               if (ch=#67)or(ch=#99) then
                  begin
                  ent:='';
                  {$I-}
                  reset(f);
                  {$I+}
                  if (ioresult=0)and(filesize(f)>0) then
                  begin
                  setbkcolor(black);
                  cleardevice;
                  settextstyle(defaultfont,horizdir,1);
                  setcolor(lightgreen);
                  outtextxy(100,50,'Enter the profile you want to boost up with one level:');
                  setcolor(white);
                  moveto(200,100);
               jj:=1;
               setfillstyle(1,8);
               bar(198,110,345,95);
               repeat
               ch2:=readkey;
               if (ord(ch2)<>8)and(ord(ch2)<>27)and(ord(ch2)<>13)and(jj<19) then
                  begin
                  ent:=ent+ch2;
                  jj:=jj+1;
                  end;
               if ord(ch2)=8 then
                  if jj>1 then
                     begin
                     jj:=jj-1;
                     delete(ent,jj,1);
                     end;
               setfillstyle(1,8);
               bar(198,110,345,95);
               outtextxy(200,100,ent);
               if (jj=1)and(ord(ch2)=13) then ch2:=chr(76);
               until (ord(ch2)=13)or(ord(ch2)=27);
                     if ch2=#13 then
                        begin
                        reset(f);
                        repeat
                        read(f,s);
                        until (s.name=ent)or(filepos(f)=filesize(f));
                        if s.name=ent then
                           begin
                           ent:='';
                           if s.maxlvl<10 then
                              begin
                              s.maxlvl:=s.maxlvl+1;
                              seek(f,filepos(f)-1);
                              write(f,s);
                              cleardevice;
                              outtextxy(200,200,'Profile Boosted!');
                              delay(1000);
                              repeat
                              if keypressed then readkey;
                              until not keypressed;
                              outtextxy(200,400,'Press Any key to continue...');
                              readkey;
                              end
                              else
                              begin
                              cleardevice;
                              outtextxy(200,200,'Max Level reached. Boost impossible...');
                              delay(1000);
                              repeat
                              if keypressed then readkey;
                              until not keypressed;
                              outtextxy(200,400,'Press Any key to continue...');
                              readkey;
                              end;
                           end
                           else
                           begin
                           ent:='';
                           cleardevice;
                           outtextxy(200,200,'Profile not found!');
                           delay(1000);
                           repeat
                           if keypressed then readkey;
                           until not keypressed;
                           outtextxy(200,400,'Press Any key to continue...');
                           readkey;
                           end;
                        end;
                  end
                  else
                  begin
                  setbkcolor(black);
                  cleardevice;
                  settextstyle(defaultfont,horizdir,2);
                  setcolor(lightred);
                  outtextxy(100,200,'NO EXISTING PROFILES TO BOOST UP!');
                  delay(2000);
                  repeat
                  if keypressed then
                     readkey;
                  until not keypressed;
                  settextstyle(defaultfont,horizdir,1);
                  setcolor(lightgreen);
                  outtextxy(100,400,'Press Any key to continue...');
                  readkey;
                  end;
                  end;
               if ch=#80 then
                  if page=3 then
                     page:=1
                     else
                     page:=page+1;
               if ch=#72 then
                  if page=1 then
                     page:=3
                     else
                     page:=page-1;
               Cleardevice;
               case page of
               1: begin
               {PAGE 1}
               setcolor(white);
               settextstyle(defaultfont,horizdir,1);
               outtextxy(50,20,'1/3');
               settextstyle(defaultfont,horizdir,2);
               setcolor(lightgreen);
               outtextxy(200,30,'MAIN INFORMATION');
               settextstyle(defaultfont,horizdir,1);
               setcolor(white);
               outtextxy(50,100,'-Welcome to the ''Escape From TUES'' information section!');
               outtextxy(50,120,'On page 2 you can see the information how to play the game');
               outtextxy(50,140,'and on page 3 you can see some information about the game');
               outtextxy(50,160,'and it''s creator. To change pages press the UP and DOWN');
               outtextxy(50,180,'arrow keys.');
               outtextxy(50,220,'-To vote wether you like the game or not press Enter.');
               outtextxy(50,260,'-To cheat which means to boost your account maxlevel up');
               outtextxy(50,280,'by 1 press C.');
                  end;
               2: begin
               {PAGE 2}
               setcolor(white);
               outtextxy(50,20,'2/3');
               settextstyle(defaultfont,horizdir,2);
               setcolor(lightgreen);
               outtextxy(220,30,'HOW TO PLAY');
               settextstyle(defaultfont,horizdir,1);
               setcolor(white);
               outtextxy(50,100,'To play use the arrow keys. You can go from floor to floor');
               outtextxy(50,120,'by using the stairs on both sides of the school but note ');
               outtextxy(50,140,'that they are used differently. While on the stairs on the');
               outtextxy(50,160,'left side of the school you need to be in different positions');
               outtextxy(50,180,'for going up and down, on the right stairs of the school you');
               outtextxy(50,200,'don''t have to move - just press up or down and hold it until');
               outtextxy(50,220,'you reach the floor you seek. While on the stairs on the left,');
               outtextxy(50,240,'note that when between 2 floors you may see anyone who is on');
               outtextxy(50,260,'the lower floor but he can''t see you! This is quite useful.');
               outtextxy(50,280,'You should also know that some levels require a special item');
               outtextxy(50,300,'which must be found somewhere in the school. To know where to');
               outtextxy(50,320,'search for it you must carefully read the instructions before');
               outtextxy(50,340,'each level. For instance, the bunoculars are used to increase');
               outtextxy(50,360,'the visual sight of the player while on the right stairs.');
               outtextxy(50,380,'Also note that if you hold an arrow key for too long your');
               outtextxy(50,400,'character might not stop when you let go of the key so beware!');
               outtextxy(50,420,'And remember - the girls''s bathroom is on the right!');
                  end;
               3: begin
               {PAGE 3}
               setcolor(white);
               outtextxy(50,20,'3/3');
               settextstyle(defaultfont,horizdir,2);
               setcolor(lightgreen);
               outtextxy(120,30,'ABOUT THE GAME/GAME CREATOR');
               settextstyle(defaultfont,horizdir,1);
               setcolor(white);
               outtextxy(50,100,'I am proud to present to you my game - ''Escape From TUES''');
               outtextxy(50,120,'written on Pascal! This so called ''game'' doesn''t even have');
               outtextxy(50,140,'a game engine... has no sound... and is not frame based due');
               outtextxy(50,160,'to my lack of game programming skills... You can''t even make');
               outtextxy(50,180,'a screenshot! There are even a few bugs. This is a beta version');
               outtextxy(50,200,'so there were way much more but I fixed many of them!');
               outtextxy(50,220,'It took me about 60 hours of writing to complete the game, but');
               outtextxy(50,240,'i also had to think it over for atleast half a year before I');
               outtextxy(50,260,'started writing it. Many thanks to my friend qweqq who said a');
               outtextxy(50,280,'said a lot of bad things about me and this game during it''s');
               outtextxy(50,300,'creation so if it wasn''t for him the game would have been even');
               outtextxy(50,320,'worse than now! I learned a lot from this game - Pascal sucks!');
               setcolor(lightgreen);
               outtextxy(40,400,'Game Created By ThePro (16 years old) - One Of The "Dupinci inc." Members!');
               outtextxy(50,420,'Release Date: 29/11/2007');
                  end;
               end;
               until ch=#27;
               setfillstyle(1,white);
               end;
            4: begin
               pam:=4;
               WELCOME;
               setbkcolor(black);
               cleardevice;
               settextstyle(defaultfont,horizdir,2);
               end;
            end;
            until y=5;
          setcolor(green);
          end;
BEGIN
randomize;
initiated:=0;
gd:=detect;
assign(fff,'doom.int');
assign(f,'game/profiles.esc');
assign(ff,'game/current.esc');
initgraph(gd,gm,'Graphics/');
WELCOME;
MAINMENU;
closegraph;
END.