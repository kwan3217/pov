/*******************************************************************************/
/*                                                                             */
/* LGEO Libray Include File     (C) Chaot!X@weird.cologne.de (Lutz Uhlmann)    */
/*                                                                             */
/* This file is in no way related to the LEGO(tm) Group.                       */
/* It is provided for private non-commercial use only.                         */
/*                                                                             */
/* lg_color: Color Definitions for LGEO POV-Ray Library                        */
/*                                                                             */ 
/*******************************************************************************/
#ifdef(LG_COLOR_INC)
#else
#declare LG_COLOR_INC = 1;
#include "colors.inc"

#declare lg_red = texture {
 pigment { rgb <0.85, 0.1, 0.1> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_yellow = texture {
 pigment { rgb <0.9, 0.8, 0.1> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_orange = texture {
 pigment { rgb <0.9, 0.45, 0> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_light_yellow = texture {
 pigment { rgb <0.99, 0.94, 0.63> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_tan = texture {
 pigment { rgb <0.78, 0.66, 0.37> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_green = texture {
 pigment { rgb <0.1, 0.5, 0.1> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_blue = texture {
 pigment { rgb <0.1, 0.15, 0.8> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_cyan = texture {
 pigment { rgb <0, 0.65, 0.45> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_white = texture {
 pigment { White }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_grey = texture {
 pigment { Gray65 }
 finish {
  ambient 0.12
  phong 0.3
  phong_size 20
 }
}

#declare lg_dark_grey = texture {
 pigment { Gray40 }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_black = texture {
 pigment { Gray15 }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_brown = texture {
 pigment { rgb <0.45, 0.35, 0> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_rose = texture {
 pigment { rgb <1, 0.675, 0.98> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_pink = texture {
 pigment { rgb <0.85, 0.4, 0.75> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_purple = texture {
 pigment { rgb <0.65, 0.25, 0.65> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_mint = texture {
 pigment { rgb <0.55, 0.98, 0.69> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_blue_green = texture {
 pigment { rgb <0.08, 0.38, 0.32> }
 finish {
  ambient 0.1
  phong 0.3
  phong_size 20
 }
}

#declare lg_chrome = texture {
 pigment { color rgb <0.95, 0.95, 0.95> }
 finish {
  ambient 0.25
  brilliance 5
  diffuse 0.6
  metallic
  specular 0.70
  roughness 1/100
  reflection 0.6
 }
}

#declare lg_gold_chrome = texture {
 pigment { color rgb <0.95, 0.78, 0.25> }
 finish {
  ambient 0.25
  brilliance 5
  diffuse 0.6
  metallic
  specular 0.70
  roughness 1/100
  reflection 0.6
 }
}

#declare lg_clear_int=interior {ior 1.5}

#declare lg_clear = texture {
 pigment { rgbf <1, 1, 1, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_red = texture {
 pigment { rgbf <1.0, 0.2, 0, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_brown = texture {
 pigment { rgbf <0.99, 0.92, 0.85, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_green = texture {
 pigment { rgbf <0, 0.83, 0, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_yellow = texture {
 pigment { rgbf <0.99, 0.96, 0, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_blue = texture {
 pigment { rgbf <0, 0, 0.94, 0.9> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_cyan = texture {
 pigment { rgbf <0.55, 1, 1, 0.95> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_neon_yellow = texture {
 pigment { rgbf <0.85, 1, 0, 0.85> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_clear_neon_orange = texture {
 pigment { rgbf <1, 0.68, 0, 0.8> }
 finish {
  ambient 0.3
  diffuse 0.6
  reflection 0.25
  phong 0.3
  phong_size 60
 }
}

#declare lg_undefined = texture {
 pigment { rgb <0.5, 0.7, 0.9> }
}

#end
