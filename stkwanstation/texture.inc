/***************************************************************************/
//		texture.inc
/***************************************************************************/
#ifndef (Skin_Color)
  #declare Skin_Color = 1;
  #end
#if (Skin_Color = 1)
  #declare Skin_Pigment = color (Flesh*8+Wheat*2+Gold*5)/15;
  #end
#if (Skin_Color = 2)
  #declare Skin_Pigment = color (Flesh*6+Copper*2+BakersChoc+Gold*6)/15;
  #end
#if (Skin_Color = 3)
  #declare Skin_Pigment = color (Flesh*2+Copper*2+BakersChoc*9+Gold*2)/15;
  #end
#if (Skin_Color = 4)
  #declare Skin_Pigment = color (Flesh*0+Copper*0+BakersChoc*15+Gold*0)/17.5;
  #end
#ifndef (Hair_Color)
  #declare Hair_Color = DarkWood;
  #end
#ifndef (Eye_Color)
  #declare Eye_Color = DarkWood;//SkyBlue/2+Blue/2
  #end

#ifndef (Suit_Color)
  #declare Suit_Color = 2;
  #end
#if (Suit_Color = 1)
  #declare Suit_Pigment =
  pigment{
    bozo
    turbulence 1
    lambda 3
    scale Size*0.1
    color_map{
      [0.0 (Black*3+MediumBlue*1+LightBlue*2)/6]
      [1.0 (Black*3+MediumBlue*0.9+LightBlue*1.9)/6]
    }
  }
  #end
#if (Suit_Color = 2)
  #declare Suit_Pigment =
  pigment{
    bozo
    turbulence 1
    lambda 3
    scale Size*0.1
    color_map{
      [0.0 rgb 0.5]
      [1.0 rgb 0.52]
    }
  }
  #end
#if (Suit_Color = 3)
  #declare Suit_Pigment =
  pigment{
    granite
    turbulence 0.5
    lambda 2
    scale <Size*1.5,Size*0.25,Size*1.5>*5
    color_map{
      [0.0 ForestGreen]
      [1.0 BakersChoc]
    }
  }
  #end
#if (Suit_Color = 4)
  #declare Suit_Pigment =
  pigment{ White }
  #end
#if (Suit_Color = 5)
  #declare Suit_Pigment =
  pigment{ Blue }
  #end
/***************************************************************************/
#declare Base =
texture{
//  pigment{ White }
//  pigment{ color (Flesh*6+Copper*2+BakersChoc+Gold*6)/15 }
  pigment{ color (Flesh*8+Wheat*2+Gold*5)/15 }
//  pigment{ Blue }
/*  pigment{
    White
//    image_map{ gif "front4.gif" interpolate 2 }
    translate <-0.5,0,0>
    scale <1,2,1>
    scale <Size*4.3,Size*4.3,1>
    translate <0,-Size*4.675,0>
  }*/
  finish{
    ambient 0
    diffuse 1
    //specular 0.35
    roughness 0.005
    brilliance 2.1
    //reflection 0.35
  }
//  normal{ wrinkles 0.5 }
}

#declare Base2 =
texture{
//  pigment{ White }
//  pigment{ color (Flesh*6+Copper*2+BakersChoc+Gold*6)/15 }
  pigment{ color (Flesh*8+Wheat*2+Gold*5)/15 }
//  pigment{ Red }
/*  pigment{
    White
//    image_map{ gif "back4.gif" interpolate 2 }
    translate <-0.5,0,0>
    scale <1,2,1>
    scale <Size*4.3,Size*4.3,1>
    translate <0,-Size*4.675,0>
    rotate <0,180,0>
  }*/
  finish{
    ambient 0
    diffuse 1
    //specular 0.35
    roughness 0.005
    brilliance 2.1
    //reflection 0.35
  }
//  normal{ wrinkles 0.5 }
}

#ifndef (Hair_Texture)
#declare Hair_Texture =
texture{
  pigment{ Hair_Color }
  normal{ bumps 0.5 scale <0.02,1,1> }
}
#end

#ifndef (Skin_Texture)
#declare Skin_Texture =
texture{
  pigment{ color Skin_Pigment }
  finish{ ambient 0.15 diffuse 0.85 }
}
#end

#ifndef (Head_Texture)
#declare Head_Texture =
texture{
  pigment{ color Skin_Pigment }
  finish{ ambient 0.15 diffuse 0.85 }
}
#end

#declare Eye_Texture =
texture{
  pigment{
    wood
    color_map{
      [0.0 rgb 0.1]
      [0.1 rgb 0.1]
      [0.1 Eye_Color]
      [0.3 Eye_Color]
      [0.4 White]
      [1.0 White]
    }
    scale 2
  }
  finish{
    ambient 0.125
    diffuse 0.75
    specular 0.15
    roughness 0.002
    brilliance 0.75
  }
}

#ifndef (Suit_Texture)
#declare Suit_Texture =
texture{
  pigment{ Suit_Pigment }
  finish{
    ambient 0.05
    diffuse 0.7
    brilliance 1.25
  }
  normal{
    wrinkles 0.25
    scale <Size*3/4,Size*1/5,Size*3/4>
    scale 1.25
    turbulence 0.25
    lambda 1.5
    omega 0.65
  }
}
#end

#ifndef (Foot_Texture)
#declare Foot_Texture =
texture{
  pigment{ rgb 0.8 }
  finish{
    ambient 0.075
    diffuse 0.85
    //specular 0.1
    roughness 0.03
  }
  normal{ bumps 0.1 scale Size*0.1 }
}
#end

#ifndef (Hand_Texture)
#declare Hand_Texture = texture {
  Head_Texture
/*
//  Flesh_Texture
  pigment{ rgb 0.25 }
  finish{
    ambient 0.075
    diffuse 0.85
    specular 0.075
    roughness 0.02
  }
*/
} 
#end
/***************************************************************************/
