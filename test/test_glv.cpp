/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

#include "test_glv.h"

using namespace glv;

int main(int argc, char ** argv){

	//---- Intialize GLV
	GLV top;
	top.colors().back.set(0);

	Window win(640, 640, "GLV Test", &top);

	top << new Label("Right-drag moves views.\nMiddle-drag resizes views.", 10, 10);


	// Top view layout (2x2 grid)
	LayoutGrid layout(top, 2, 2, 60);
	

	//---- Hierarchy View
	View hierView; layout << hierView;
	hierView	(Event::MouseDrag, Behavior::mouseMove)
				<< new Label("Hierarchy", 0, -10);

	LayoutGrid lg0(hierView, 2, 2, 14);
	for(int i=0; i<4; ++i){
		View& v = (new View)->enable(CropChildren)(Event::MouseDrag, Behavior::mouseMove);
		lg0 << v;
	
		LayoutGrid lg(v, 2, 2, 14);
		for(int j=0; j<4; ++j)
			lg << (*(new View))(Event::MouseDrag, Behavior::mouseMove);
	}
	
	//---- Anchored children view
	View anchorView; layout << anchorView;
	anchorView	.disable(DrawBack)
				(Event::MouseDrag, Behavior::mouseMove)
				(Event::MouseDrag, Behavior::mouseResize)
				<< new Label("Anchored Children", 0, -10);

	LayoutGrid lg(anchorView, 3, 3, 14);
	//for(int i=0; i<9; ++i) lg << (new View)->anchor((i%3)/2., (i/3)/2.);
	for(int i=0; i<9; ++i) lg << (new View)->anchor((i%3)/3., (i/3)/3.).stretch(1/3., 1/3.);


	//---- Keyboard char view
	CharView charView; layout << charView;
	charView.width(charView.w * 8/11.);
	charView.style(&top.style());
	charView << new Label("Character View", 0, -10);
	
	
	//---- Color view
	ColorView colorView; layout << colorView;
	colorView	(Event::MouseDrag, Behavior::mouseMove)
				(Event::MouseDrag, Behavior::mouseResize)
				<< new Label("Colorful View", 0, -10)
				<< (new Label("Hue"))->size(6).anchor(Place::BC).pos(Place::TC,0,4)
				<< (new Label("Saturation", true))->size(6).anchor(Place::CL).pos(Place::CR,-4);
    
	Application::run();
	return 0;
}
