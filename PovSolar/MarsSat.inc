//MarsSat.inc
//Orbital motion for Phobos and Deimos
//Derived from orbital elements and formulas given in 
//  The Explanatory Supplement to the Astronomical Almanac, p342-345

//  Position is returned in units of km, centered on the mars barycenter, B1950 ecliptic

#macro CalcMarsSatPos(Body,T)
  #local MseA=0;
  #local MseE=1;
  #local MseI=2;
  #local MseL=3;
  #local MseP=4;
  #local MseK=5;
  #local MseDL=6;  //=n
  #local MseDP=7;
  #local MseDK=8;
  #local MseN=9;
  #local MseDN=10;
  #local MseJ=11;
  #local MseDJ=12;
  #local Body=Body-1;

  #local MarsSatEle=array[2][13] {
                 //  a km      e        I deg   L deg    P deg   K deg   dL deg/day    dP deg/day   dK deg/day    N deg   dN deg/yr  J deg  dJ deg/yr
    /* Phobos */ {  9379.40, 0.014979, 1.1029, 232.412, 278.96, 327.90, 1128.8445566,    0.435258,   -0.435330,  47.386,  -0.00140, 37.271,    0.0008 },
    /* Deimos */ { 23461.13, 0.000391, 1.7901,  28.963, 111.70, 240.38,  285.1618875,    0.017985,   -0.018008,  46.367,  -0.00138, 36.623,    0.0008 }
  }
  #local D=T-41266.5;
  #local Y=D/365.25;
  #local MarsSatEle[Body][MseK]=MarsSatEle[Body][MseK]+MarsSatEle[Body][MseDK]*D;
  #local MarsSatEle[Body][MseP]=MarsSatEle[Body][MseP]+MarsSatEle[Body][MseDP]*D;
  #local MarsSatEle[Body][MseN]=MarsSatEle[Body][MseN]+MarsSatEle[Body][MseDN]*Y;
  #local MarsSatEle[Body][MseJ]=MarsSatEle[Body][MseJ]+MarsSatEle[Body][MseDJ]*Y;
  #local L=Rev(MarsSatEle[Body][MseL]+MarsSatEle[Body][MseDL]*D);
  #if(Body=1)
    #local L=L+0.001237*Y*Y;  //Death spiral acceleration!
  #else
    #local H=196.55-0.01801*D;
    #local L=L-0.27*SinD(H);
  #end
  #local M=radians(L-MarsSatEle[Body][MseP]);
  #local Q=MeanToAnom(M,MarsSatEle[Body][MseE]);
  #local R=RadFromAnom(MarsSatEle[Body][MseA],MarsSatEle[Body][MseE],Q);
  #local AP=MarsSatEle[Body][MseP]-MarsSatEle[Body][MseN]-MarsSatEle[Body][MseK];
  #local V=<R*cos(Q),0,R*sin(Q)>;
  #local V=vrotate(V,-y*AP);
  #local V=vrotate(V,-x*MarsSatEle[Body][MseI]);
  #local V=vrotate(V,-y*MarsSatEle[Body][MseK]);
  #local V=vrotate(V,-x*MarsSatEle[Body][MseJ]);
  #local V=vrotate(V,-y*MarsSatEle[Body][MseN]);
  (V)
#end


