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
  //translate([0,A2_y,0]) rotate([90,0,-90]) linear_extrude(height=medium_thickness) polygon([[0,0],[A2_y,0],[A2_y,box_height],[0,box_height]]);
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
                                              cube([rear_x,5,box_height]);
    translate([200.5,0,jack_holes_center_y]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([230.5,0,jack_holes_center_y]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([260.5,-5,datasub_lower_left_y])                  cube([41,20,datasub_height]);
  }
}

module inside()
{
  to_cut_y=60;
  difference()
  {
    side();
    translate([-1,-1,-10])            cube([medium_thickness+2,medium_thickness+1,70]);
    translate([-1,A2_y-to_cut_y,-10]) cube([medium_thickness+2,to_cut_y+1,70]);
  }
}

module support()
{
  support_height = 20;
  rotate([90,90,90]) linear_extrude(height=medium_thickness) polygon([[0,0],[0,A2_y],[support_height,A2_y]]);
}


//box
module Tranxen200Box()
{
  translate([medium_thickness,0,small_thickness])                       color("GoldenRod") front();

  translate([medium_thickness,(A2_y-small_thickness),small_thickness])  color("Aqua") rear();
  translate([0,0,small_thickness])                                      color("GoldenRod") side();
  translate([A2_x-medium_thickness,0,small_thickness])                  color("GoldenRod") side();
                                                                        color("Aqua") bottom();

  translate([2+143.5,0,small_thickness])               color("GoldenRod") inside();
  translate([2+143.5*2,0,small_thickness])             color("GoldenRod") inside();
  translate([2+143.5*3,0,small_thickness])             color("GoldenRod") inside();

                                         color("GoldenRod") support();
  translate([A2_x-medium_thickness,0,0]) color("GoldenRod") support();
}

translate([-(A2_x/2),-(A2_y/2),0]) Tranxen200Box();
//support();

