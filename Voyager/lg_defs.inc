/*******************************************************************************/
/*                                                                             */
/* LGEO Libray Include File     (C) Chaot!X@weird.cologne.de (Lutz Uhlmann)    */
/*                                                                             */
/* This file is in no way related to the LEGO(tm) Group.                       */
/* It is provided for private non-commercial use only.                         */
/*                                                                             */
/* lg_defs: Definitions of standard sub-parts and sizes                        */
/*                                                                             */ 
/*******************************************************************************/
#ifdef(LG_DEFS_INC)
#else
#declare LG_DEFS_INC = 1;

#include "lg_color.inc"

/***********************************************************************
 *  Dimensions
 ***********************************************************************/

#declare LG_KNOB_RADIUS = 0.24;
#declare LG_KNOB_HEIGHT = 0.16;
#declare LG_KNOB_INNER_RADIUS = 0.16;
#declare LG_WALL_WIDTH = 0.16;
#declare LG_BRICK_WIDTH = 0.8;
#declare LG_BRICK_HEIGHT = 0.96;
#declare LG_BRICK_INNER_HEIGHT = 0.84;
#declare LG_PLATE_HEIGHT = 0.32;
#declare LG_PLATE_INNER_HEIGHT = 0.2;
#declare LG_TOP_HEIGHT = LG_BRICK_HEIGHT-LG_BRICK_INNER_HEIGHT;
#declare LG_CYLINDER_RADIUS = (sqrt(2)*LG_BRICK_WIDTH/2-LG_KNOB_RADIUS) ;
#declare LG_CYLINDER_WALL_WIDTH = (LG_CYLINDER_RADIUS-LG_KNOB_RADIUS);
#declare LG_CORNER_SPACE = 0.025;
#declare LG_KNOB_CORNER_SPACE = 0.0375;
#declare LG_CROSSAXLE_WIDTH = 0.18 ;
#declare LG_GRID_WIDTH=LG_BRICK_WIDTH/sqrt(2)-2*LG_KNOB_RADIUS;
#declare LG_E = 0.01;

#declare lg_knob = 
union {
 union {
  cylinder {
   <0, 0, LG_KNOB_HEIGHT-LG_KNOB_CORNER_SPACE>,
   <0, 0, -LG_E>,
   (LG_KNOB_RADIUS)
  }
  cylinder {
   <0, 0, LG_KNOB_HEIGHT>,
   <0, 0, -LG_E>,
   (LG_KNOB_RADIUS-LG_KNOB_CORNER_SPACE)
  }
 }
 torus {
  (LG_KNOB_RADIUS-LG_KNOB_CORNER_SPACE),
  (LG_KNOB_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_KNOB_CORNER_SPACE)>
 }
}

#declare lg_tech_knob = 
union{
 difference {
  union {
   cylinder {
    <0, 0, LG_KNOB_HEIGHT-LG_CORNER_SPACE>,
    <0, 0, -LG_E>,
    (LG_KNOB_RADIUS)
   }
   difference {
    cylinder {
     <0, 0, LG_KNOB_HEIGHT>,
     <0, 0, -LG_E>,
     (LG_KNOB_RADIUS-LG_CORNER_SPACE)
    }
    cylinder {
     <0, 0, LG_KNOB_HEIGHT+LG_E>,
     <0, 0, -2*LG_E>,
     (LG_KNOB_INNER_RADIUS+LG_CORNER_SPACE)
    }
   }
  }
  cylinder {
   <0, 0, (LG_KNOB_HEIGHT+2*LG_E)>,
   <0, 0, -3*LG_E>,
   (LG_KNOB_INNER_RADIUS) 
  }
 }
 torus {
  (LG_KNOB_INNER_RADIUS+LG_CORNER_SPACE),
  (LG_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_CORNER_SPACE)>
 }
 torus {
  (LG_KNOB_RADIUS-LG_CORNER_SPACE),
  (LG_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_CORNER_SPACE)>
 }
}

#declare lg_brick_cylinder = 
union {
 difference {
  cylinder {
   <0, 0, LG_BRICK_INNER_HEIGHT+LG_E>,
   <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>,
   (LG_CYLINDER_RADIUS) 
  }
  cylinder {
   <0, 0, LG_BRICK_INNER_HEIGHT+LG_CORNER_SPACE>,
   <0, 0, 0>,
   (LG_KNOB_RADIUS)
  }
 }
 torus {
  (LG_CYLINDER_RADIUS-LG_CYLINDER_WALL_WIDTH/2),
  (LG_CYLINDER_WALL_WIDTH/2)
  rotate <90, 0, 0>
  translate <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>
 }
}

#declare lg_plate_cylinder = 
union {
 difference {
  cylinder {
   <0, 0, LG_PLATE_INNER_HEIGHT+LG_E>,
   <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>,
   (LG_CYLINDER_RADIUS) 
  }
  cylinder {
   <0, 0, LG_PLATE_INNER_HEIGHT+LG_CORNER_SPACE>,
   <0, 0, 0>,
   (LG_KNOB_RADIUS)
  }
 }
 torus {
  (LG_CYLINDER_RADIUS-LG_CYLINDER_WALL_WIDTH/2),
  (LG_CYLINDER_WALL_WIDTH/2)
  rotate <90, 0, 0>
  translate <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>
 }
}

#declare lg_brick_column = 
cylinder {
 <0, 0, LG_BRICK_INNER_HEIGHT+LG_E>,
 <0, 0, 0>,
 (LG_KNOB_INNER_RADIUS)
}

#declare lg_plate_column = 
difference {
 cylinder {
  <0, 0, LG_PLATE_INNER_HEIGHT+LG_E>,
  <0, 0, 0>,
  (LG_KNOB_INNER_RADIUS)
 }
 cylinder {
  <0, 0, 1>,
  <0, 0, -1>,
  (0.06)
 }
}

#declare lg_support_wall =
box {
 <-LG_CYLINDER_WALL_WIDTH/2, -LG_E, 0.225>,
 <LG_CYLINDER_WALL_WIDTH/2, LG_BRICK_WIDTH-LG_CYLINDER_RADIUS-LG_WALL_WIDTH+LG_E, LG_BRICK_HEIGHT>
} 

#declare lg_knob_inner_space =
cylinder {
 <0, 0, -LG_CORNER_SPACE>,
 <0, 0, 0.15>,
 (0.125)
}

/* CLEAR parts definitions */

#declare lg_knob_clear = 
merge {
 merge {
  cylinder {
   <0, 0, LG_KNOB_HEIGHT-LG_KNOB_CORNER_SPACE>,
   <0, 0, -LG_E>,
   (LG_KNOB_RADIUS)
  }
  cylinder {
   <0, 0, LG_KNOB_HEIGHT>,
   <0, 0, -LG_E>,
   (LG_KNOB_RADIUS-LG_KNOB_CORNER_SPACE)
  }
 }
 torus {
  (LG_KNOB_RADIUS-LG_KNOB_CORNER_SPACE),
  (LG_KNOB_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_KNOB_CORNER_SPACE)>
 }
}

#declare lg_tech_knob_clear = 
merge{
 difference {
  merge {
   cylinder {
    <0, 0, LG_KNOB_HEIGHT-LG_CORNER_SPACE>,
    <0, 0, -LG_E>,
    (LG_KNOB_RADIUS)
   }
   difference {
    cylinder {
     <0, 0, LG_KNOB_HEIGHT>,
     <0, 0, -LG_E>,
     (LG_KNOB_RADIUS-LG_CORNER_SPACE)
    }
    cylinder {
     <0, 0, LG_KNOB_HEIGHT+LG_E>,
     <0, 0, -2*LG_E>,
     (LG_KNOB_INNER_RADIUS+LG_CORNER_SPACE)
    }
   }
  }
  cylinder {
   <0, 0, (LG_KNOB_HEIGHT+2*LG_E)>,
   <0, 0, -3*LG_E>,
   (LG_KNOB_INNER_RADIUS) 
  }
 }
 torus {
  (LG_KNOB_INNER_RADIUS+LG_CORNER_SPACE),
  (LG_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_CORNER_SPACE)>
 }
 torus {
  (LG_KNOB_RADIUS-LG_CORNER_SPACE),
  (LG_CORNER_SPACE)
  rotate <90, 0, 0>
  translate <0, 0, (LG_KNOB_HEIGHT-LG_CORNER_SPACE)>
 }
}

#declare lg_brick_cylinder_clear = 
merge {
 difference {
  cylinder {
   <0, 0, LG_BRICK_INNER_HEIGHT+LG_E>,
   <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>,
   (LG_CYLINDER_RADIUS) 
  }
  cylinder {
   <0, 0, LG_BRICK_INNER_HEIGHT+LG_CORNER_SPACE>,
   <0, 0, 0>,
   (LG_KNOB_RADIUS)
  }
 }
 torus {
  (LG_CYLINDER_RADIUS-LG_CYLINDER_WALL_WIDTH/2),
  (LG_CYLINDER_WALL_WIDTH/2)
  rotate <90, 0, 0>
  translate <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>
 }
}

#declare lg_plate_cylinder_clear = 
merge {
 difference {
  cylinder {
   <0, 0, LG_PLATE_INNER_HEIGHT+LG_E>,
   <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>,
   (LG_CYLINDER_RADIUS) 
  }
  cylinder {
   <0, 0, LG_PLATE_INNER_HEIGHT+LG_CORNER_SPACE>,
   <0, 0, 0>,
   (LG_KNOB_RADIUS)
  }
 }
 torus {
  (LG_CYLINDER_RADIUS-LG_CYLINDER_WALL_WIDTH/2),
  (LG_CYLINDER_WALL_WIDTH/2)
  rotate <90, 0, 0>
  translate <0, 0, (LG_CYLINDER_WALL_WIDTH/2)>
 }
}

#declare lg_brick_column_clear = 
cylinder {
 <0, 0, LG_BRICK_INNER_HEIGHT+LG_E>,
 <0, 0, 0>,
 (LG_KNOB_INNER_RADIUS)
}

#declare lg_plate_column_clear = 
difference {
 cylinder {
  <0, 0, LG_PLATE_INNER_HEIGHT+LG_E>,
  <0, 0, 0>,
  (LG_KNOB_INNER_RADIUS)
 }
 cylinder {
  <0, 0, 1>,
  <0, 0, -1>,
  (0.06)
 }
}

#declare lg_support_wall_clear =
box {
 <-LG_CYLINDER_WALL_WIDTH/2, -LG_E, 0.225>,
 <LG_CYLINDER_WALL_WIDTH/2, LG_BRICK_WIDTH-LG_CYLINDER_RADIUS-LG_WALL_WIDTH+LG_E, LG_BRICK_HEIGHT>
} 

#declare lg_knob_inner_space_clear =
cylinder {
 <0, 0, -LG_CORNER_SPACE>,
 <0, 0, 0.15>,
 (0.125)
}

#end
