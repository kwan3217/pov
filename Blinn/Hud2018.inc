//Hud2018.inc
//Transform an object from screen normalized coordinates to world coordinates.
//Screen normalized coordinates are right handed, have X to the right, Y up, 
//and Z towards the camera. In the Z=0 plane, the right edge of the screen is right/2 units, while the top edge is up/2 units

#macro TestHud(Object,CamUp,CamRight,CamAngle)
  object {
    Object
  }
  camera {
    sky y
    up y*CamUp
    right -x*CamRight
    angle CamAngle
    location <0,0,(CamRight/2)/tan(radians(CamAngle/2))>
    look_at <0,0,0>
  }
#end

#macro Hud(Object,CamUp,CamRight,CamAngle,CamSky,CamLoc,CamLook,HudScale)
  //Stage In is the opposite of the direction the camera is looking in world coordinates, and is +Z in HUD object frame
  #local StageIn=vnormalize(CamLoc-CamLook)*HudScale;
  //Stage Right is perpendicular to sky and Stage In, and is +X in the HUD object frame
  #local StageRight=vnormalize(vcross(CamSky,StageIn))*HudScale;
  //Stage Up is perpendicular to Stage Right and Stage Out, and is +Y in the HUD object frame
  #local StageUp=vnormalize(vcross(StageIn,StageRight))*HudScale;
  //Calculate distance from camera to hud object
  #local Distance=(CamRight/2)/tan(radians(CamAngle/2));
  #local HudOrigin=CamLoc-StageIn*Distance;
  object {
    Object
    matrix <
      StageRight.x,StageRight.y,StageRight.z,
      StageUp   .x,StageUp   .y,StageUp   .z,
      StageIn   .x,StageIn   .y,StageIn   .z,
      HudOrigin .x,HudOrigin .y,HudOrigin .z
    >
  }
#end


