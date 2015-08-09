//globals
small_thickness = 5;
medium_thickness = 16;

A2_x = 594;
A2_y = 420;

box_height = 30;

//components
module bottom()
{
  cube([A2_x,A2_y,small_thickness]);
}

module side()
{
  cube([medium_thickness, A2_y, box_height]);
}

module front()
{
  front_x = A2_x - 2 * medium_thickness;
  cube([front_x,medium_thickness,box_height]);
}

module rear()
{
  rear_x = A2_x - 2 * medium_thickness;
  jack_holes_center_y = box_height/2;
  datasub_height = 10;
  datasub_lower_left_y=(box_height-datasub_height)/2;
  difference()
  {
                                              cube([rear_x,small_thickness,box_height]);
    translate([200.5,0,jack_holes_center_y]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([230.5,0,jack_holes_center_y]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([260.5,-5,datasub_lower_left_y])                  cube([41,20,datasub_height]);
  }
}

module inside()
{
	cube([medium_thickness, 160*2+20*2, box_height]);
}

module support()
{
  support_height = 20;
  rotate([90,90,90]) linear_extrude(height=medium_thickness) polygon([[0,0],[0,A2_y],[support_height,A2_y]]);
}

module foam()
{
  cube([123.5,160,box_height]);
}

module piezo()
{
                       cylinder(h=0.5,r=17.5);
  translate([0,0,0.5]) color("White") cylinder(h=0.5,r=12.5);
}

module plate()
{
  color("Silver") cube([123.5,160,1]);
  translate([61.25,80,,1]) piezo();
}

module pad()
{
                                      color("Grey") foam();
  translate([123.5,0,box_height+50]) rotate([0,180,0]) plate();
}

module touch()
{
  translate([20        ,20,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5  ,20,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5*2,20,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5*3,20,3]) color("DimGray") cube([123.5,160,1]);

  translate([20        ,200,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5  ,200,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5*2,200,3]) color("DimGray") cube([123.5,160,1]);
  translate([20+143.5*3,200,3]) color("DimGray") cube([123.5,160,1]);

  color("Black") cube([594,375,3]);
}

//box
module Tranxen200Box()
{
  translate([medium_thickness,0,small_thickness])                       color("GoldenRod") front();

  translate([medium_thickness,(A2_y-small_thickness),small_thickness])  color("Aqua") rear();
  translate([0,0,small_thickness])                                      color("GoldenRod") side();
  translate([A2_x-medium_thickness,0,small_thickness])                  color("GoldenRod") side();
                                                                        color("Aqua") bottom();

  translate([2+143.5  ,medium_thickness,small_thickness])             color("GoldenRod") inside();
  translate([2+143.5*2,medium_thickness,small_thickness])             color("GoldenRod") inside();
  translate([2+143.5*3,medium_thickness,small_thickness])             color("GoldenRod") inside();

  translate([20        ,20,small_thickness+box_height*2]) pad();
  translate([20+143.5  ,20,small_thickness+box_height*2]) pad();
  translate([20+143.5*2,20,small_thickness+box_height*2]) pad();
  translate([20+143.5*3,20,small_thickness+box_height*2]) pad();

  translate([20        ,200,small_thickness+box_height*2]) pad();
  translate([20+143.5  ,200,small_thickness+box_height*2]) pad();
  translate([20+143.5*2,200,small_thickness+box_height*2]) pad();
  translate([20+143.5*3,200,small_thickness+box_height*2]) pad();
 
  translate([0,0,small_thickness+box_height*7]) touch();

                                         color("GoldenRod") support();
  translate([A2_x-medium_thickness,0,0]) color("GoldenRod") support();
}

translate([-(A2_x/2),-(A2_y/2),-100]) Tranxen200Box();
