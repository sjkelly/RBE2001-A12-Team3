$fn=30;
include <../../Magpie/magpie.scad>
module drive_coupler(){
	difference(){
		union(){
			cylinder(r=7.5, h=24);
		}
		difference(){
			translate([0,0,-1])poly_cylinder(r=3.15, h=12, $fn=30);
			translate([0,3.7,8])cube([6,2,16], center=true);
		}
		translate([0,0,40/2])cube([3.95,3.95,40], center=true);
		translate([0,0,6])rotate([-90,0,0])cylinder(r=1.3, h=12, $fn=30);
		translate([0,0,18])rotate([-90,0,0])cylinder(r=1.3, h=12, $fn=30);
	}
}

rotate([0,180,0])drive_coupler();
