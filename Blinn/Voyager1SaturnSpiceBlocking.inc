#version unofficial MegaPov 1.22;

#include "KwanMath.inc"

#declare CamAngleFadeTable=array[18][3] {{initial_frame,28,1},
                                        {         1353,28,1},
                                        {         1368,28,0},
                                        {         1411,28,0},
                                        {         1411,28,1},
                                        {         2324,28,1},
                                        {         2338,28,0},
                                        {         2338, 0.35,0},
                                        {         2349, 0.35,1},
                                        {         2532, 0.35,1},
                                        {         3120,28,1},
                                        {         3122,28,0.5},
                                        {         3122, 0.35,0.5},
                                        {         3125, 0.35,1},
                                        {         3279, 0.35,1},
                                        {         3279,28,0.5},
                                        {         3282,28,1},
                                        {  final_frame,28,1}
                                       } 
#declare SpacecraftKernel="Voyager/vgr1.tm";
#declare design_image_height=480;
#declare design_image_width=640;

#declare RubberClockTable=array[12][2] {{ 444,-25.309}, //604 transit ingress
                                       { 687,-22.869}, //604 transit egress
                                       { 711,-22.578}, //601 above ring ansa
                                       { 800,-21.759}, //603 above ring ansa 
                                       { 881,-20.563}, //603 above ring ansa 
                                       {1332,-18.143}, //Over Titan terminator
                                       {2224, -7.493}, //601 transit ingress
                                       {2316, -6.599}, //601 transit egress
                                       {2968, -1.476}, //Over Saturn terminator
                                       {3552,  4.542}, //Ring plane crossing
                                       {4356,  8.269}, //603 out of occultation
                                       {5149, 16.000}, //Estimate
                                      } 
#declare SuDetail=99;
#declare SaDetail=99;

#declare Spacecraft=-31;
#declare EpochStr="1980-Nov-12 23:46:30 TDB";

#declare Planet=699;
#declare Moons=array[11] {601,602,603,604,605,606,607,608,609,610,611};

#declare AxisKeyframe=array[14][2] {{initial_frame,699}, 
                                   {          857,699},
                                   {         1035,606},
                                   {         1410,606},
                                   {         1410,699},
                                   {         2338,699},
                                   {         2338,603}, //Tethys
                                   {         2532,603},
                                   {         2352,699},
                                   {         3122,699},
                                   {         3122,601}, //Mimas
                                   {         3279,601},
                                   {         3279,699},
                                   {  final_frame,699}}

//Target blocking 
//TargetLR - left to right. -1 puts target on left edge, +1 on right edge
//TargetUD - Up to down. -1 puts target on bottom edge, +1 on top edge
#declare TargetKeyframe=array[16][4] {{initial_frame,0.2, 0.2,0}, 
                                     {          274,0.29,-0.04,0},
                                     {          857,0.2, 0.2,0},
                                     {         1035,0.2, 0.2,0},
                                     {         1410,0.2, 0.2,0},
                                     {         1410,0.2, 0.2,0},
                                     {         2338,  0.2, 0.2,0},
                                     {         2338,(343+514)/640-1,1-(254+254)/480,0}, //Tethys
                                     {         2532,(167+167)/640-1,1-(100+275)/480,0},
                                     {         2352,134/320-1,1-316/240,0},
                                     {         3552,134/320-1,1-316/240,0},
                                     {         3689, 76/320-1,1-353/240,0},
                                     {         4290,330/320-1,1-200/240,0},
                                     {         5149,195/320-1,1-280/240,0},
                                     {         6631,(173+210)/640-1,1-(281+358)/480,0},
                                     {         6867,(155+193)/640-1,1-(303+376)/480,0}}
//Blocking of the foreground actor (spacecraft)
//FGBlockingLR - left to right. -1 puts actor on left edge, +1 on right edge
//FGBlockingUD - Up to down. -1 puts actor on bottom edge, +1 on top edge
#declare ForegroundKeyframe=array[19][5] {{initial_frame, -4.80,-4.20,0.10,0}, 
                                         {          384, -0.80,-2.20,0.10,0}, 
                                         {          857,  0.00,-0.45,0.33,0},
                                         {         1035,  1.20,-0.50,0.33,0},
                                         {         1410,  0.75,-0.75,0.33,0},
                                         {         1410,  0.00, 0.00,1.00,0},
                                         {         2338,  0.00, 0.00,1.00,0},
                                         {         2338,  0.00, 0.00,-1.00,0}, //Tethys
                                         {         2532,  0.00, 0.00,-1.00,0},
                                         {         2352,  0.00, 0.00,1.00,0},
                                         {         3122,  0.00, 0.00,1.00,0},
                                         {         3122,  0.00, 0.00,-1.00,0}, //Tethys
                                         {         3279,  0.00, 0.00,-1.00,0},
                                         {         3279,(232+233)/640-1,1-(170+273)/480,0.5,0},
                                         {         3552,(232+233)/640-1,1-(170+273)/480,0.5,0},
                                         {         3689,(246+260)/640-1,1-(135+246)/480,0.45,0},
                                         {         4290,242/320-1,1-238/240,0.50,0},
                                         {         5149,345/320-1,1-195/240,0.35,0},
                                         {  final_frame,  0.00, 0.00,-1.00,0}}

#include "Blinn.inc"


