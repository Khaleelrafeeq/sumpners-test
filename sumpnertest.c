#include<stdio.h>
#include<math.h>

void effifunction(float X,float PI,float PC,float PF,float KVA);
void regufunction(float X,float ISC,float RSC,float PF,float XSC,float V02);

void main()
{ // float voc=230.0,ioc=0.74,woc=146,roc,xoc,cosphi,sinphi,effi,pi,pc;
  // float vsc=148,isc=6.8,wsc=440,zsc,xsc,rsc,kva=3000.0;
  int i=0,j=0;
  float voc,ioc,woc,roc,xoc,cosphi,sinphi,effi,pi,pc,iw,im,v02;//for oc test
  float vsc,isc,wsc,zsc,xsc,rsc,kva=3000.0;//for sc test
  float pf[5]={1.0,0.8,0.6,0.4,0.2};
  float load[4]={1.0,0.75,0.5,0.25};

 /////////////////input/////////////
  printf("Enter kva rating of transformer:");
  scanf("%f",&kva);
  kva*=1000;
  printf("enter  voc ioc woc :");
  scanf( "%f %f %f",&voc,&ioc,&woc);
  printf("enter  vsc isc wsc :"); 
  scanf("%f %f %f",&vsc,&isc,&wsc);
  printf("Enter v02 of transformer:");
  scanf("%f",&v02);

 //////////calculations/////////////////
  woc/=2.0;ioc/=2.0;  //for single transformer
  wsc/=2.0;           //
  pi=woc;  pc=wsc;    ////subners test : wattmeter readings for single transformer: losses   
  cosphi=(woc/(voc*(ioc)));
  sinphi=sin(acos(cosphi));
              //printf("cosphi %f ",cosphi);printf("sinphi %f ",sinphi);

///////////////////////////////////////////////////
  if(cosphi>1)
     {
	printf("\nwrong input parameters \nEnter Exact Meter Readings\nError in claculating cuurrent through reactive & resistive components in oc test\n");
      }
  else { 
         //oc calc
         roc=(voc/iw);
         xoc=(voc/im); 
         //sc calc
         
         rsc=wsc/(isc*isc);
         zsc=vsc/isc;
         xsc=sqrt((zsc*zsc)-(rsc*rsc));
         for(i=0;i<4;i++)
          { printf("\n\n \t LOAD=%f \n",load[i]);
            for(j=0;j<5;j++)
             {printf("\n \t PF=%f",pf[j]);
	       effifunction(load[i],pi,pc,pf[j],kva);
	       regufunction(load[i],isc,rsc,pf[j],xsc,v02);
             }
          }
         printf("\n\n\nRoc=%fΩ Xoc=%fΩ ",roc,xoc);
         printf("\nRsc=%fΩ Zsc=%fΩ Xsc=%fΩ\n",rsc,zsc,xsc);
        }
}





////////////////////////////////////////////////////////////////
void effifunction(float X,float PI,float PC,float PF,float KVA)
{         float effi;
 	  effi=X*100.0*(KVA*PF/((X*KVA*PF)+PI+(X*X*PC)));
          printf("\tEfficiency=%f ",effi);
   
}
///////////////////////////////////////////////////////////////////////////
void regufunction(float X,float ISC,float RSC,float PF,float XSC,float V02)
{	float regu; //lagging
   	regu=X*100.0*((ISC*RSC*PF)+(ISC*XSC*sin(acos(PF))))/V02;
        if(PF!=1.0)
        {	printf("\nRegulation=%f (lagging )",regu);
        	//leading
		regu=X*100.0*((ISC*RSC*PF)-(ISC*XSC*sin(acos(PF))))/V02;
        	printf("\t Regulation=%f (leading)\n\n ",regu);
        } else 
		{
		printf("\nRegulation=%f\n",regu);  
		}      	
  }

