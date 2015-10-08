#include "frustum.inc"

#declare S4B=union {
  //J2 Engine
  object {J2 translate y*2645}
  //Thrust Structure
  cone {
    <0,2719.4,0>,84,<0,2657,0>,0
    pigment {color Yellow}
  }
  //Aft skirt
  union {
    cylinder {
      <0,2746.5,0>,<0,2832,0>,260.8/2
      open
    }
    Stringers(2746.5,2832,260.8/2,216)
    pigment {color White}
  }
  //Propellant Tank
  cylinder {
    <0,2832,0>,<0,3100.56,0>,260/2
    open
    pigment {color White}
  }
  //Forward Skirt
  union {
    cylinder {
      <0,3100.56,0>,<0,3161.56,0>,260.8/2
      open
    }
    Stringers(3100.56,3161.56,260.8/2,216)
    pigment {color White}
  }
  union {
    cylinder {
      <0,3161.56,0>,<0,3222.56,0>,260.8/2
      open
    }
    Stringers(3161.56,3222.56,260.8/2,216)
    pigment {color rgb 0.2}
  }
  //Instrumentation Unit
  cylinder {
    <0,3222.56,0>,<0,3258.56,0>,260/2
    open
    pigment {color rgb 0.2}
  }
}

#declare Spacecraft=union {
  //Spacecraft-LM Adaptor
  cone {
    <0,3258.56,0>,260/2,<0,3593.50,0>,154/2
    open
    pigment {color White}
  }
  //Service Module
  cylinder {
    <0,3593.50,0>,<0,3749.56,0>,154/2
    texture {T_Chrome_4A}
  }
  cylinder {
    <0,3749.56,0>,<0,3767.11,0>,154/2
    open
    texture {T_Chrome_4A}
  }
  //Command Module
  cylinder {
    <0,3767.11,0>,<0,3775.39,0>,154/2
    open
    texture {T_Chrome_5C}
  }
  cone {
    <0,3775.39,0>,154/2,<0,3874.31,0>,10.85
    texture {T_Chrome_5C}
  }
}
#declare BPC_LES=union {
  //Boost Protective Cover
  cylinder {
    <0,3767.11,0>,<0,3775.39,0>,157/2
    open
  }
  sphereFrust(<0,3775.39,0>,157/2,<0,3890.03,0>,12.86)
  
  #include "LES.inc"
  object {
    LES
    translate y*4240.79
  }    
  bounded_by {
    cylinder {
    <0,3767.11,0>,<0,4240.79,0>,157/2
    }
  }
  pigment {color White}
}
