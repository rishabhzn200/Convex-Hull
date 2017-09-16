#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

#define L_CLICK 1
#define R_CLICK 2

#define POP -1
#define PUSH 1

struct str
{
 float x_cor;
 float y_cor;
 double slope;
}ipoint[30],fpoint[30],rpoint[30];

void MarkPoint(float x,float y)
{
 setcolor(4);
 circle(x,y,3);
 for(int i=0;i<=3;i++)
  circle(x,y,i);
}

struct stack
{
 struct str x3[25];
}stk;

double findAngle(double x1, double y1, double x2, double y2)
{
 double dX=(double)(x2-x1);
 double dY=(double)(y2-y1);
 double angle;
 if (dX==0 && dY==0)
  return 0;
 angle=atan2(dY,dX)*57.295779513082;//to convert angle into degrees
 if (angle < 0)
  angle += 360;
 return angle;
}

int ConvexPoint(struct str p,struct str q,struct str r)
{
 double Angle1=findAngle(q.x_cor,q.y_cor,p.x_cor,p.y_cor); //COMPUTE CLOCKWISE ANGLE
 double Angle2=findAngle(q.x_cor,q.y_cor,r.x_cor,r.y_cor); //COMPUTER COUNTERCLOCKWISE ANGLE
 double difAngle;
 if (Angle1>Angle2)
  {
   difAngle=Angle1-Angle2;  //COMPUTE DIFFERENCE BETWEEN THE TWO ANGLES
   if (difAngle>180)
    return POP; //POINT Q IS CONCAVE
   else
    return PUSH; //POINT IS CONVEX
  }
  else if (Angle1<Angle2)
  {
   difAngle=Angle2-Angle1;  //COMPUTE DIFFERENCE BETWEEN THE TWO ANGLES
   if (difAngle>180)
    return PUSH; //POINT IS CONVEX
   else
   return POP; //POINT IS CONCAVE
  }
  else if (Angle1 == Angle2)
   return POP; //POINT IS COLINEAR
}

//merge sort routine
void merge_arr(struct str a[],int lb,int mid,int ub)
{
 struct str b[25];
 int i,j,k=lb;
 for(i=lb,j=mid+1;i<=mid&&j<=ub;)
 if(a[i].slope<=a[j].slope)               //compare ith and jth elements
  b[k++]=a[i++];
 else
  b[k++]=a[j++];
 if(i<=mid)
  while(i<=mid)
   b[k++]=a[i++];
   if(j<=ub)
    while(j<=ub)
     b[k++]=a[j++];
    i=lb;
    while(i<=ub)
    {
     a[i]=b[i];
     i++;
    }
}


void mergeSort(struct str a[],int lb,int ub)
{
 int mid=(lb+ub)/2;
 if(lb<ub)
 {
  mergeSort(a,lb,mid);
  mergeSort(a,mid+1,ub);
  merge_arr(a,lb,mid,ub);
 }
}

int InitMouse()
{
 union REGS in, out;
 in.x.ax = 0;
 int86( 0x33, &in, &out );
 return out.x.ax;
}

		// Show mouse pointer
void ShowMouse()
{
 union REGS in, out;
 in.x.ax = 1;
 int86( 0x33, &in, &out );
}

void HideMouse()
{
 union REGS in, out;
 in.x.ax = 2;
 int86( 0x33, &in, &out );
}

	// Get mouse position and button-click
void GetMouseStatus( float *x_pos, float *y_pos, float *btn )
{
 union REGS in, out;
 in.x.ax = 3;
 int86( 0x33, &in, &out );
 *x_pos = out.x.cx;
 *y_pos = out.x.dx;
 *btn = out.x.bx;
}

void main()
{
 struct str point[30];
 float msbutton,x,y,prev=0,p_no=0,minxy,min_index,dr;
 /*Initialize grapichs*/
 int gdriver=DETECT,gmode,ecode;
 initgraph(&gdriver,&gmode,"");

   //FRONT PAGE:-
 int fi=1,fj=1,fo=16*6*2-2;
 do
 { //fj=fi;
  setbkcolor(0);
  setcolor(6);
  settextstyle(0,0,3);

  outtextxy(fi*2,25,"ASSIGNMENT");//180
  outtextxy(fo*2,25,"ASSIGNMENT");//180
  setcolor(9);
  outtextxy(fi*3,100,"ON");//270
  outtextxy(fo*3-1,100,"ON");//270
  setcolor(13);
  outtextxy(1.7*fi,175,"CONVEX  HULL");//160
  outtextxy(1.7*fo,175,"CONVEX  HULL");//160

  fo--;
  delay(10);
  if(fi<16*6-1)
   cleardevice();
//  delay(1);
  fi++;
  fj++;
  if(fj==16)
    fj=1;
 }while(fi!=16*6);

  //underline
 setbkcolor(0);
 int col=1;
 for(int ai=180,bi=270,di=160;ai<410;ai=ai+20,bi+=5,di+=25)
 {//setbkcolor(col);
  if(col==8)
   col=1;
  setcolor(++col);
  setlinestyle(0,0,3);
  line(ai,55,ai+20,55);
  line(bi,130,bi+5,130);
  line(di,205,di+25,205);
  delay(200);
 }

  /*setfillpattern(char far *upattern, int color);*/
 setcolor(2);
 settextstyle(0,0,3);
 outtextxy(50,300,"LOADING . . .");
 setcolor(4);
 delay(50);
 rectangle(50,355,600,395);
 delay(20);
 setcolor(4);
 for(int cr=0;cr<=20;cr++)
 {
  circle(79,375,cr);
 }
 for(int ci=70;ci<=580;ci++)
 {
  circle(ci,375,20);
  delay(1);
 }
 delay(50);
 setcolor(1);
 settextstyle(0,0,3);
 outtextxy(50,410,"Press Any Key . . .");
 getch();
 //giving spaces:-
 for(int sp=1;sp<=70;sp++)
 {
  printf("\n");
 }

 //end of first page
 closegraph();
 restorecrtmode();
 initgraph(&gdriver,&gmode,"");
 p_no=0;
 setbkcolor(7);
 setcolor(4);
 /*Initialize Mouse*/
 if( ! InitMouse( ))
 {
  cout<<"\nError: Cannot init mouse.\nAborting...";
  getch( );
  closegraph( );
 }

 ShowMouse( );
 /*let user draw points till button clicked is not equal to right click*/
 while(msbutton!=R_CLICK)
 {
  GetMouseStatus(&x,&y,&msbutton);
  if(msbutton==L_CLICK)
  {
   if(prev==1)
    continue;
   point[p_no].x_cor=x;
   point[p_no].y_cor=y;
    if(p_no==0)
    {
     minxy=y;
     min_index=p_no;
    }
    else if(minxy>y)
    {
     minxy=y;
     min_index=p_no;
    }
    else if(minxy==y&&point[min_index].x_cor>x)
    {
     minxy=y;
     min_index=p_no;
    }
    HideMouse( );
    MarkPoint(x,y);
    p_no++;
    ShowMouse( );
   }
   prev = msbutton;
  }
  /*start grahams scan*/
  if(p_no<3)
  {
   cleardevice();
   setcolor(1);
   settextstyle(0,0,2);
   outtextxy(50,100,"Error: Points must be greater than 3");//270
   outtextxy(50,150,"Press any key to exit...");//270
   getch();
   closegraph();
   restorecrtmode();
   exit(0);
  }
  //find the slopes
  point[min_index].slope=-1;
  for(int i=0;i<p_no;i++)
  {
   if( (dr=point[i].x_cor-point[min_index].x_cor) !=0 )
   {
    point[i].slope = ( point[i].y_cor - point[min_index].y_cor )/(dr) ;
   }
  }
  cout<<min_index<<endl;
  //min_index is correct
  //before sorting store the x and y cor of min index
  int cvpx1,cvpy1;
  cvpx1=point[min_index].x_cor;
  cvpy1=point[min_index].y_cor;
  struct str cvp1=point[min_index];
  //now sort the points
  mergeSort(point,0,p_no-1);
  //points sorted
   //arrange
  int c1=0,c2=0;
  for(i=0;i<p_no;i++)
  {
   if(point[i].slope>=0)
   {
    rpoint[c1++]=point[i];
   }
  }
  c2=c1;
  for(i=0;i<(p_no-c2);i++)     //p_no-c2
  if(point[i].slope!=-1)
   rpoint[c1++]=point[i];
  int np_no=c1;              //np_no=c1; 1 point less.
  //arranged

  struct str p,q,r;
  int st_ptr=2,orient;
  stk.x3[0]=cvp1;
  stk.x3[1]=rpoint[0];
  stk.x3[2]=rpoint[1];
  //trial
  //point should not go right
  for(i=2;i<np_no;i++)
  {//cout<<"in for"<<endl;
   p=stk.x3[st_ptr-1];
   q=stk.x3[st_ptr];
   r=rpoint[i];
   while((ConvexPoint(p,q,r))==POP)
   {
    st_ptr--;
    p=stk.x3[st_ptr-1];
    q=stk.x3[st_ptr];
    r=rpoint[i];
    //cout<<"\t"<<st_ptr<<endl;
   }
   stk.x3[++st_ptr]=rpoint[i];
  }

  setcolor(1);
  p=stk.x3[st_ptr];
  q=stk.x3[0];
  line(p.x_cor,p.y_cor,q.x_cor,q.y_cor);
  delay(300);
 /*end of grahams scan*/
  for(int dl=st_ptr;dl>0;dl--)
  {
   p=stk.x3[dl];
   q=stk.x3[dl-1];
   line(p.x_cor,p.y_cor,q.x_cor,q.y_cor);
   delay(300);
  }

 getch();

 //third page
 cleardevice();
 setbkcolor(0);
 setcolor(4);
 settextstyle(0,0,2);
 outtextxy(50,25,"COMPLEXITY OF");//180
 outtextxy(50,45,"GRAHAM'S SCAN");
 outtextxy(50,65,"ALGORITHM");
 outtextxy(50,100,"FIND MIN Y_COR PT :-");
 outtextxy(400,100,"O (n)");
 outtextxy(50,150,"SORTING OF POINTS :-");
 outtextxy(400,150,"O (nlog (n))");
 getch();
  //end of trial
 closegraph();
 restorecrtmode();
}