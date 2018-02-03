#include<stdio.h>
#include<math.h>

float effifunction(float X,float PI,float PC,float PF,float KVA);
void regufunction(float X,float ISC,float RSC,float PF,float XSC,float VSC);

void main()
{ // float voc=230.0,ioc=0.74,woc=146,roc,xoc,cosphi,sinphi,effi,pi,pc;
  // float vsc=148,isc=6.8,wsc=440,zsc,xsc,rsc,kva=3000.0;
  int i=0,j=0;
  float voc,ioc,woc,roc,xoc,cosphi,sinphi,effi,pi,pc,iw,im;//for oc test
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

 //////////calculations/////////////////
  woc/=2.0;ioc/=2.0;  //for single transformer
  wsc/=2.0;           //vsc/=2.0;
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
	      effi=effifunction(load[i],pi,pc,pf[j],kva);
              printf("\tEfficiency=%f ",effi);
	      //      regufunction(load[i],isc,rsc,pf[j],xsc,vsc);
               }
            }
     


         printf("\n\n\nRoc=%fΩ Xoc=%fΩ ",roc,xoc);
         printf("\nRsc=%fΩ Zsc=%fΩ Xsc=%fΩ\n",rsc,zsc,xsc);
        }
       
      

/////////////////////////////////////////////////////////////////plotfile
           int plot;float pload=0.0,powerfactor=0.0;
           printf("\n Plot ?:");scanf("%d",&plot);
           if (1)
           {
                 FILE *fp;
                 fp=fopen("data.txt","w");
                 if(fp==NULL) {printf("error");}
 
                for(;pload<=1;pload=pload+0.01)             
	        { fprintf(fp,"%f",pload);  //col1
                   for(i=0;i<5;i++)        //col1-6
                   { effi=effifunction(pload,pi,pc,pf[i],kva);
                     fprintf(fp,"  %f  ",effi);
                    }
                 fprintf(fp,"\n");
                 	       
                 }
          
               fclose(fp);  

            }

//////////////////////////piping to gnuplot
FILE * gnupipe = popen ("gnuplot -persistent", "w");if(gnupipe==NULL) {printf("e2rror");}
        fprintf(gnupipe,"plot \"data.txt\" using 1:2 title 'upf'with lines ,\"data.txt\" using 1:3 title '.8pf' with lines, \"data.txt\" using 1:4 title '.6'with lines ,\"data.txt\" using 1:5 title '.4pf' with lines,\"data.txt\" using 1:5 title '.2pf'with lines ");


fflush(gnupipe);


}//main closed













////////////////////////////////////////////////////////////////
float effifunction(float X,float PI,float PC,float PF,float KVA)
{         float effi;
 	  effi=X*100.0*(KVA*PF/((X*KVA*PF)+PI+(X*X*PC)));
          return(effi);
   
}
///////////////////////////////////////////////////////////////////////////
void regufunction(float X,float ISC,float RSC,float PF,float XSC,float VSC)
{	float regulag,regulead; //lagging
   	regulag=X*100.0*((ISC*RSC*PF)+(ISC*XSC*sin(acos(PF))))/VSC;
        regulead=X*100.0*((ISC*RSC*PF)-(ISC*XSC*sin(acos(PF))))/VSC;    
       
         if(PF!=1.0)
        {	printf("\nRegulation=%f (lagging )",regulag);
        	//leading
		
        	printf("\t Regulation=%f (leading)\n\n ",regulead);
        } else 
		{
		printf("\nRegulation=%f\n",regulag);  
		}      	
  }

