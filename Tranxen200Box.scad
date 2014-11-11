//globals
small_thickness = 5;
medium_thickness = 16;

A2_x = 594;
A2_y = 420;

front_height = 30;
rear_height = 50;

box_y = sqrt(A2_y*A2_y - (rear_height-front_height)*(rear_height-front_height));

//components
module bottom()
{
  cube([A2_x,box_y,small_thickness]);
}

module side()
{
  translate([0,box_y,0]) rotate([90,0,-90]) linear_extrude(height=medium_thickness) polygon([[0,0],[box_y,0],[box_y,front_height],[0,rear_height]]);
}

module front()
{
  front_x = A2_x - 2 * medium_thickness;
  cube([front_x,medium_thickness,front_height]);
}

module rear()
{
  rear_x = A2_x - 2 * medium_thickness;
  difference()
  {
                                            cube([rear_x,5,rear_height]);
    translate([199,0,25]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([229,0,25]) rotate([270,0,0]) cylinder(h=20,r=4.5, center=true);
    translate([260,-5,20])                  cube([41,20,10]);
  }
}

module inside()
{
  to_cut_y=60*(box_y/A2_y);
  difference()
  {
    side();
    translate([-medium_thickness-1,-1,-10])             cube([medium_thickness+2,medium_thickness+1,50]);
    translate([-medium_thickness-1,box_y-to_cut_y,-10]) cube([medium_thickness+2,to_cut_y+1,60]);
  }
}

//box
module Tranxen200Box()
{
  translate([medium_thickness,0,small_thickness])                       color("GoldenRod") front();

  translate([medium_thickness,(box_y)-small_thickness,small_thickness]) color("DarkKhaki") rear();
  translate([medium_thickness,0,small_thickness])                       color("GoldenRod") side();
  translate([A2_x,0,small_thickness])                                   color("GoldenRod") side();
                                                                        color("DarkKhaki") bottom();

translate([medium_thickness+2+143.5,0,small_thickness])               color("GoldenRod") inside();
translate([medium_thickness+2+143.5*2,0,small_thickness])             color("GoldenRod") inside();
translate([medium_thickness+2+143.5*3,0,small_thickness])             color("GoldenRod") inside();
}

translate([-(A2_x/2),-(box_y/2),0]) Tranxen200Box();
//rear();
