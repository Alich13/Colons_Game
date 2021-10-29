#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#include <string> // for string class
#define SCALE 1.25
using namespace std;

/*====================================================================*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&& Dessin   &&&&&&&&&&&&&&&&&&&*/
/*====================================================================*/

//---------------------------------- constructeur----------------------------------//

Dessin::Dessin()
{

	//  Load images
	pic_board = Gdk::Pixbuf::create_from_file("data/Board_org.png");
	pic2 = Gdk::Pixbuf::create_from_file("data/scarabine.png");
	pic_board = pic_board->scale_simple((pic_board->get_height()) * 0.2, (pic_board->get_width()) * 0.2, Gdk::INTERP_BILINEAR); // scale image
	pic2 = pic2->scale_simple((pic2->get_height()) * 0.25, (pic2->get_width()) * 0.35, Gdk::INTERP_BILINEAR);					// scale image
	// Set masks for mouse events
	add_events(Gdk::BUTTON_PRESS_MASK);

	// setting attributes value
	firstclick = false;
	secondclick = false;
	board_x = 100; // top right x cordonate inside the box
	board_y = 50;  // top right y cordonate inside the box
	board_width = 1000;
	board_height = 900; // same as the size of the box

	
}

//----------------------------------On draw----------------------------------//

bool Dessin::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
	/*---------------test to print mouse cordonates--------*/
        affiche_rendred_cord();
    /*---------------test to print mouse cordonates--------*/


	Gtk::Allocation allocation = get_allocation();
	// add board image //
	drawBoard(cr);
	// add elements scarabines //
	drawHouse(cr);
	// draw lines using mouse//
	drawRoute(cr);

	return true;
}

//---------------------------------- Mouse button press handling ----------------------------------//

bool Dessin::on_button_press_event(GdkEventButton *event)
{
	// save selected pressed
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		set_rendred_cord(event->x, event->y);
		ReafficheDessin();
	}

	if (add_route_pressed)
	{
		updateRoute(event);
	}

	if (add_house_pressed)
	{
		updateHouse(event);
	}
	return true;
}

//---------------------------------------events-------------------------------------------------------//

void Dessin::updateRoute(GdkEventButton *event)
{
	// Check if the event is a left(1) button click.
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{
		// check whether this is the first click
		if (!firstclick && !secondclick)
		{
			// the first coordinate
			x1 = event->x;
			y1 = event->y;

			firstclick = true;
		}
		// check whether this is the second click, and not on the same point as the previous
		if (firstclick && !secondclick && (int)event->x != x1 && (int)event->y != y1)
		{
			// the second coordinate
			x2 = event->x;
			y2 = event->y;
			secondclick = true;
			// refresh the screen
		}

		// check whether it was clicked two times in order to save values
		if (firstclick && secondclick)
		{
			
			vx1.push_back(x1);
			vy1.push_back(y1);
			vx2.push_back(x2);
			vy2.push_back(y2);
			// reinitialize firstclick and secondclick to false and
			firstclick = false;
			secondclick = false;
			set_add_route_pressed(false);
			ReafficheDessin();
		}
		// The event has been handled.
	}
}

void Dessin::updateHouse(GdkEventButton *event)
{
	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 1))
	{

		X.push_back(event->x);
		Y.push_back(event->y);
		set_add_house_pressed(false);
		ReafficheDessin();
	}
}

//-----------------------------draw Functions-----------------------------------------//

void Dessin::drawBoard(const Cairo::RefPtr<Cairo::Context> &cr)
{
	Gdk::Cairo::set_source_pixbuf(cr, pic_board, board_x, board_y); //(wifth, hight)
	cr->save();
	cr->rectangle(0, 0, board_width, board_height); // on ne peut pas suprimer
	cr->fill();
	cr->restore();
}

void Dessin::drawHouse(const Cairo::RefPtr<Cairo::Context> &cr)
{
	for (int i = 0; i < X.size(); i++)
	{
		cr->save();
		Gdk::Cairo::set_source_pixbuf(cr, pic2, X[i] - 50, Y[i] - 50);
		cr->rectangle(0, 0, board_width, board_height);
		cr->fill();
		cr->restore();
	}
}

void Dessin::drawRoute(const Cairo::RefPtr<Cairo::Context> &cr)
{
	for (int i = 0; i < vx1.size(); i++)
	{
		// don't put save here
		// cr->rectangle(0, 0, board_width, board_height);
		cr->set_line_width(6);
		cr->set_source_rgb(0, 0, 0);
		cr->move_to(vx1[i], vy1[i]);
		cr->line_to(vx2[i], vy2[i]);
		cr->stroke();
	}
}

//---------------------------------- Reaffiche----------------------------------//

void Dessin::ReafficheDessin()
{
	auto win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, board_width, board_height); // je touche un mon dessin et donc ça permet de redessiner
		win->invalidate_rect(r, false);
		// win->invalidate(false);
	}
}

void Dessin::affiche_rendred_cord()
{
	cout << "x = " << cord_x << " , " << " y = " << cord_y << endl;
}