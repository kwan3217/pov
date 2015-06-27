#include "math.inc"
#include "AimAtt3.inc"
#declare BetaD=9;
#include "AimAttDerived4.inc"

#debug "Stuff!\n"

#declare clockSec=floor(-Peak);
PrintNumber("clockSec: ",clockSec)
#declare EndTime=-SofieObsStart+15;
PrintNumber("EndTime:  ",EndTime)
#while(clockSec<EndTime)
  #debug concat(str(clockSec,6,1),",",str(clockSec*nD,6,2),",",str(TableRow(clockSec),6,2),",",str(ScRoll(clockSec),6,2),",",str(ScPitch(clockSec),6,2),",",str(ScYaw(clockSec),6,2),"\n")
  sphere {
    <clockSec/10,ScRoll(clockSec),0>,0.1
    pigment {color rgb <1,0,0>}
  }
  #declare clockSec=clockSec+1;
#end

background {color rgb 1}

camera {
  up y*30
  right x*40
  translate -z*50
}

PrintNumber(concat("Yaw command time:   "),YPRTimeTable[2])
PrintNumber(concat("Pitch command time: "),PitchD/nD)
PrintNumber(concat("Roll command time:  "),YPRTimeTable[3])


