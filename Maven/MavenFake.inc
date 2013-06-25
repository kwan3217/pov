#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"
#declare StarRatio=1500;
#include "Stars.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "mvn/mvn.tm"
//#furnsh "mvn_iuv_fake_tag.bsp"
#furnsh "mvn_iuv_fake_dec.bc"

#declare StartUTC="2014-Dec-12 03:48:10.672 TDB";
//#declare StartUTC="2015-Apr-22 02:44:48.719 TDB";
//#declare StartUTC="2015-Apr-22 00:00:00.000 TDB";
//#declare StartUTC="2015-08-03 10:40:30.773UTC";
#declare StartET=str2et(StartUTC);
PrintNumber("StartET: ",StartET)
#declare ET=StartET+40*60;
PrintNumber("ET:      ",ET)
#include "SpiceQuat.inc"
#declare Period=16200;
#declare T0=-670.8;
#declare T1=T0+Period;

