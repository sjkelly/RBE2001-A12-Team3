

claw_holes = [[0,0,0],[20,0,0],[20,58,0],[0,58,0]];
claw_center_hole = [10,29,0];
claw_plate_thick = 3;

module claw_base(){
	difference(){
		union(){
			for(i=[0:3])
				translate(claw_holes[i])cylinder(r=1.5, h=claw_plate_thick);
			translate(claw_center_hole)cylinder(r=6, h=claw_plate_thick);
		}
	}
}

claw_base();
