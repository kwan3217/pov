//#version unofficial Megapov 1.22;
#include "Actors.inc"

#local ShotTime=array[6] {3,3,15,15,15,15}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    union {
      Text("verdana.ttf","Moment of Inertia",0,Center)
      translate <0,-0.001,1>
      Fade(<1,1,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #break
  #case(1)
    Frame(ShotClockN,1)
    #break
  #case(2)
    #declare R0=<0,2,0>;
    #declare V=<-1,1,1>;
    #declare T=Linterp(0,-3,1,3,ShotClockN);
    #declare F=ASDR(0,0.1,0.9,1,0,1,ShotClockN);
    Particle(R0+V*T,V,0.2, 
      <1,1,0>, //RColor
      <0,1,1>, //VColor
      <1,0,1>, //LColor
      <1,0,0>, //MColor
      <1,0,1>, //PColor
      F,F,F,F,F*0.3)
    Frame(1,1)
    #break
  #case(3)
    #declare Omega=1;
    #declare Omegav=<0,0,Omega>;
    #declare T=Linterp(0,-2*pi,1,2*pi,ShotClockN);
    #declare ZSpd=DBezier(0,0,2,2,BLinterp(-0.5,0,0.5,1,T));
    #declare ZPos= Bezier(0,0,2,2,BLinterp(-0.5,0,0.5,1,T));
    #declare R=<2*cos(Omega*T),2*sin(Omega*T),ZPos>;
    #declare V=vcross(Omegav,R);
    #if((T>-0.5)*(T<0.5))
      #declare V=V+z*ZSpd;
    #end
    #declare F=ASDR(0,0.1,0.9,1,0,1,ShotClockN);
    Particle(R,V,0.2, 
      <1,1,0>, //RColor
      <0,1,1>, //VColor
      <1,0,1>, //LColor
      <1,0,0>, //MColor
      <1,0,1>, //PColor
      F,F,F,F,0)
    Frame(1,1)
    #break
  #case(4)
    #declare Omega=1;
    #declare Omegav=<0,0,Omega>;
    #declare T=Linterp(0,-2*pi,1,2*pi,ShotClockN);
    #declare Theta=Omega*T;
    #declare ZPos= Bezier(0,0,2,2,BLinterp(-0.5,0,0.5,1,T));
    #declare R=<2*cos(Theta),2*sin(Theta),ZPos>;
    #declare V=vcross(Omegav,R);
    #declare F=ASDR(0,0.1,0.9,1,0,1,ShotClockN);
    union {
      Particle(R,V,0.2, 
        <1,1,0>, //RColor
        <0,1,1>, //VColor
        <1,0,1>, //LColor
        <1,0,0>, //MColor
        <1,0,1>, //PColor
        F,F,F,F,0)
      Frame(1,ASDR(0,0,0.9,1,0,1,ShotClockN))
      translate -z*R.z
    }
    #break
  #case(5)
    #declare Omega=1;
    #declare Omegav=<0,0,Omega>;
    #declare T=Linterp(0,-2*pi,1,2*pi,ShotClockN);
    #declare NParticles=2;
    #declare R=array[NParticles];
    #declare V=array[NParticles];
    #declare I=0;
    #declare ZPos= Bezier(0,0,2,2,BLinterp(-0.5,0,0.5,1,T));
    #while(I<NParticles)
      #declare Theta=Omega*T+2*pi*I/NParticles;
      #declare R[I]=<2*cos(Theta),2*sin(Theta),ZPos>;
      #declare V[I]=vcross(Omegav,R[I]);
      #declare I=I+1;
    #end
    #declare F=ASDR(0,0.1,0.9,1,0,1,ShotClockN);
    union {
      Particles(R,V,0.2, 
        <1,1,0>, //RColor
        <0,1,1>, //VColor
        <1,0,1>, //LColor
        <1,0,0>, //MColor
        <1,0,1>, //PColor
        F,F,F,F,0)
      Frame(1,ASDR(0,0.1,1,1,0,1,ShotClockN))
      translate -z*ZPos
    }
    #break
#end


#local CameraPanAngle=Linterp(0,-60,1,-120,SceneClockN);
#local CameraR=9;
#local CameraHeight=Linterp(0,5,1,4,SceneClockN);

camera {
  up y
  right -x*16/9
  sky z
  location <cos(radians(CameraPanAngle))*CameraR,sin(radians(CameraPanAngle))*CameraR,CameraHeight>
  look_at <0,0,0>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
}


