#include<stdio.h>
#include<math.h>



void effifunction(float X,float PI,float PC,float PF,float KVA);
void regufunction(float X,float ISC,float RSC,float PF,float XSC,float VSC);
void main()
{ // float voc=230.0,ioc=0.74,woc=146,roc,xoc,cosphi,sinphi,effi,pi,pc;
 // float vsc=148,isc=6.8,wsc=440,zsc,xsc,rsc,kva=3000.0;
  int i=0,j=0;
  float voc,ioc,woc,roc,xoc,cosphi,sinphi,effi,pi,pc;//for oc test
  float vsc,isc,wsc,zsc,xsc,rsc,kva=3000.0;//for sc test

  float pf[4]={1.0,0.8,0.6,0.4};
  float load[4]={1.0,0.75,0.5,0.25};
  printf("Enter Kva rating of transformer:");
  scanf("%f",&kva);
  printf("enter  voc ioc woc :");
  scanf( "%f %f %f",&voc,&ioc,&woc);
  printf("enter isc vsc isc wsc :"); 
  scanf("%f %f %f",&vsc,&isc,&wsc);
  //oc calc
  woc/=2.0;
  wsc/=2.0;
  cosphi=(woc/(voc*ioc));
  sinphi=sin(acos(cosphi));
  roc=(voc/(ioc*cosphi));
  xoc=(voc/(ioc*sinphi)); 
  pi=(roc*ioc*ioc); 
  pc=(xoc*ioc*ioc);
  //sc calc
  rsc=wsc/(isc*isc);
  zsc=vsc/isc;
  xsc=sqrt((zsc*zsc)-(rsc*rsc));
  for(i=0;i<4;i++)
  { printf("\n\n \t LOAD=%f \n",load[i]);
 	   for(j=0;j<4;j++)
  	   {printf("\n \t PF=%f",pf[j]);
	    effifunction(load[i],pi,pc,pf[j],kva);
 	    regufunction(load[i],isc,rsc,pf[j],xsc,vsc);
           }
   }
printf("\n\n\nRoc=%f Xoc=%f Pi=%f Pc=%f",roc,xoc,pi,pc);
printf("\nRsc=%f Zsc=%f Xsc=%f\n",rsc,zsc,xsc);
}


void effifunction(float X,float PI,float PC,float PF,float KVA)
{	  float effi;
 	  effi=X*100.0*(KVA*PF/((X*KVA*PF)+PI+(X*X*PC)));
          printf("\nEfficiency=%f ",effi);
   
}

void regufunction(float X,float ISC,float RSC,float PF,float XSC,float VSC)
{	float regu; //lagging
   	regu=X*100.0*((ISC*RSC*PF)+(ISC*XSC*sin(acos(PF))))/VSC;
        if(X!=1.0)
        {	printf("\nRegulation=%f (lagging )",regu);
        	//leading
		regu=X*100.0*((ISC*RSC*PF)-(ISC*XSC*sin(acos(PF))))/VSC;
        	printf("\t Regulation=%f (leading) ",regu);
        } else 
		{
		printf("\nRegulation=%f",regu);  
		}      	
  }


